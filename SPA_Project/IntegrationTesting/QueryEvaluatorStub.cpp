#include "stdafx.h"
#include "QueryEvaluatorStub.h"
#include "ClauseType.h"


struct groupComparator {
	bool operator() (unordered_set<int> i, unordered_set<int> j) { return ((int)i.size() < (int)j.size()); };
} gComparator;

QueryEvaluatorStub::QueryEvaluatorStub() {

}
QueryEvaluatorStub::QueryEvaluatorStub(PKB* pkbSource) {
	pkb = pkbSource;
}

void QueryEvaluatorStub::setPKB(PKB* pkbInput) {
	this->pkb = pkbInput;
}

ResultTable* QueryEvaluatorStub::evaluate(QueryTree qt) {
	resTable = new ResultTable();
	resTable->setInitialEmpty(true);
	resTable = evaluateWithOptimization2(qt);
	for (int i = 0; i < (int)qt.getClauseSize(); i++)
		delete qt.getClause(i);
	return resTable;
}

ResultTable* QueryEvaluatorStub::createEarlyTerminationTable(QueryTree qt)
{
	delete resTable;
	ResultTable* emptyTable = new ResultTable();
	if ((int)qt.getSelectParameter().size() == 1 && qt.getSelectParameter().at(0).getParaType() == BOOLEAN) {
		emptyTable->setBoolean(false);
	}
	else
		emptyTable->setSynList(qt.getSelectParameter());
	return emptyTable;
}


ResultTable* QueryEvaluatorStub::evaluateWithOptimization2(QueryTree qt)
{
	vector<Clause*> synClauseList;
	vector<int> clauseSynCount;
	unordered_map<int, ResultTable> resultMap;

	vector<Clause*> clause1SynList;
	vector<ResultTable*> result1SynList;

	vector<Parameter> synList = qt.getUsedParameter();
	unordered_map<string, int> synMap;
	vector<unordered_set<int>> adjList;
	for (int i = 0; i < (int)synList.size(); i++) {
		Parameter p = synList.at(i);
		synMap.insert(make_pair(p.getParaName(), i));
		adjList.push_back({});
	}

	for (int i = 0; i < qt.getClauseSize(); i++) {
		Clause* c = qt.getClause(i);
		if ((int)c->getSynList().size() == 0) {
			ResultTable* resTable = c->evaluate(pkb, &ResultTable());
			if (resTable->getSynList().size() == 0 && resTable->getBoolean() == false) {
				return createEarlyTerminationTable(qt);
			}
		}
		else {
			synClauseList.push_back(c);
			vector<Parameter> tmpList = c->getSynList();
			clauseSynCount.push_back((int)tmpList.size());
			if ((int)tmpList.size() == 2) {
				adjList.at(synMap[tmpList.at(0).getParaName()]).insert(synMap[tmpList.at(1).getParaName()]);
				adjList.at(synMap[tmpList.at(1).getParaName()]).insert(synMap[tmpList.at(0).getParaName()]);
			}

			if ((int)c->getSynList().size() == 1) {
				ResultTable* resTable = c->evaluate(pkb, &ResultTable());
				if ((int)resTable->getTupleList().size() == 0) {
					return createEarlyTerminationTable(qt);
				}
				else {
					clause1SynList.push_back(c);
					result1SynList.push_back(resTable);
				}
			}
		}
	}

	vector<unordered_set<int>> synGroup;
	unordered_set<int> spareIdx;
	for (int i = 0; i < (int)synList.size(); i++)
		spareIdx.insert(i);
	while ((int)spareIdx.size() > 0) {
		unordered_set<int> group;
		int idx = *spareIdx.begin();
		group.insert(idx);
		queue<int> q;
		spareIdx.erase(idx);
		q.push(idx);
		while (!q.empty()) {
			int currentIdx = q.front();
			q.pop();
			for (int adjIdx : adjList.at(currentIdx)) {
				if (spareIdx.find(adjIdx) != spareIdx.end()) {
					spareIdx.erase(adjIdx);
					group.insert(adjIdx);
					q.push(adjIdx);
				}
			}
		}
		synGroup.push_back(group);
	}
	sort(synGroup.begin(), synGroup.end(), gComparator);

	vector<ResultTable*> resTableList;
	for (int i = 0; i < (int)synGroup.size(); i++) {
		unordered_set<int> group = synGroup.at(i);
		vector<Clause*> gClauseList;
		for (Clause* c : synClauseList) {
			vector<Parameter> tmpList = c->getSynList();
			bool shouldInsert = false;
			for (Parameter p : tmpList) {
				if (group.find(synMap[p.getParaName()]) != group.end()) {
					shouldInsert = true;
				}
			}
			if (shouldInsert)
				gClauseList.push_back(c);
		}

		vector<Parameter> gSynList;
		for (int p : synGroup.at(i))
			gSynList.push_back(synList.at(p));


		ResultTable* gTable = evaluateGroup2(gSynList, gClauseList, clause1SynList, result1SynList);
		if (gTable->getTupleSize() == 0) {
			return createEarlyTerminationTable(qt);
		}
		resTableList.push_back(gTable);


	}

	resTable = new ResultTable();
	resTable->setInitialEmpty(true);

	if ((int)qt.getSelectParameter().size() == 1 && qt.getSelectParameter().at(0).getParaType() == BOOLEAN) {
		bool isAnyTableEmpty = false;
		for (ResultTable* rt : resTableList) {
			if (rt->getTupleSize() == 0 && rt->getBoolean() == false)
				isAnyTableEmpty = true;
		}

		if (isAnyTableEmpty == false)
			resTable->setBoolean(true);
		else
			resTable->setBoolean(false);

		return resTable;
	}

	for (int i = 0; i < (int)synGroup.size(); i++) {
		vector<Parameter> gSelectList;
		for (int p : synGroup.at(i)) {
			Parameter param = synList.at(p);
			for (Parameter sp : qt.getSelectParameter()) {
				if (param.getParaName().compare(sp.getParaName()) == 0)
					gSelectList.push_back(param);
			}
		}
		if ((int)gSelectList.size() > 0) {
			resTableList.at(i) = resTableList.at(i)->select(gSelectList);
		}
		else {
			resTableList.at(i) = new ResultTable();
			resTableList.at(i)->setInitialEmpty(true);
		}
	}

	for (int i = 0; i < (int)synGroup.size(); i++) {
		resTable->join(resTableList.at(i));
		delete resTableList.at(i);
	}


	for (Parameter p : qt.getSelectParameter()) {
		if (resTable->isSynInTable(p) == false) {
			resTable->join(getAllValueForSyn(p));
		}
	}

	bool isCorrectOrder = true;
	if ((int)qt.getSelectParameter().size() != resTable->getSynCount()) {
		isCorrectOrder = false;
	}
	else {
		for (int i = 0; i < resTable->getSynCount(); i++) {
			if (qt.getSelectParameter().at(i).isSame(resTable->getSynList().at(i)) == false)
				isCorrectOrder = false;
		}
	}

	if (isCorrectOrder) {
		return resTable;
	}
	else {
		ResultTable* tTable = new ResultTable();
		tTable = resTable->select(qt.getSelectParameter());
		delete resTable;
		return tTable;
	}
}

ResultTable* QueryEvaluatorStub::evaluateGroup2(vector<Parameter> usedSynList,
	vector<Clause*> clauseList, vector<Clause*> clause1SynList, vector<ResultTable*> clause1SynResult)
{
	vector<bool> isClauseVisited;
	vector<bool> isSynVisited;
	vector<Clause*> gDeprioritizedClauseList;
	unordered_map<string, int> gSynMap;
	vector<int> gSynDegree;
	vector<vector<int>> clauseListForSyn;
	vector<int> withClauseList;
	ResultTable* gResultTable = new ResultTable();
	gResultTable->setInitialEmpty(true);

	for (int i = 0; i < (int)usedSynList.size(); i++) {
		gSynMap.insert(make_pair(usedSynList.at(i).getParaName(), i));
		isSynVisited.push_back(false);
		clauseListForSyn.push_back({});
		gSynDegree.push_back({});
	}

	for (int i = 0; i < (int)clauseList.size(); i++) {
		Clause* c = clauseList.at(i);
		isClauseVisited.push_back(false);
		for (Parameter p : c->getSynList()) {
			if ((int)c->getSynList().size() == 1) {
				gSynDegree.at(gSynMap[p.getParaName()])++;
				clauseListForSyn.at(gSynMap[p.getParaName()]).push_back(i);
			}
			if ((int)c->getSynList().size() == 2) {
				gSynDegree.at(gSynMap[p.getParaName()])++;
				clauseListForSyn.at(gSynMap[p.getParaName()]).push_back(i);
			}
		}
		if (c->getClauseType() == WITH)
			withClauseList.push_back(i);
	}

	for (int i = 0; i < (int)usedSynList.size(); i++) {
		int maxOccurance = -1; int maxIdx = -1;
		for (int k = 0; k < (int)usedSynList.size(); k++) {
			if (gSynDegree.at(k) > maxOccurance && isSynVisited.at(k) == false) {
				maxOccurance = gSynDegree.at(k);
				maxIdx = k;
			}
		}

		isSynVisited.at(maxIdx) = true;
		for (int k = 0; k < (int)clause1SynList.size(); k++) {
			Clause* c = clause1SynList.at(k);

			string paraName = c->getSynList().at(0).getParaName();
			if (paraName.compare(usedSynList.at(maxIdx).getParaName()) == 0) {
				gResultTable->join(clause1SynResult.at(k));
				if (gResultTable->getTupleSize() == 0) {
					delete resTable;
					resTable = new ResultTable();
					resTable->setSynList(usedSynList);
					return resTable;
				}
			}

		}
		for (int k = 0; k < (int)withClauseList.size(); k++) {
			int clauseIdx = withClauseList.at(k);
			Clause* c = clauseList.at(clauseIdx);
			bool isClauseContainCurrentSyn = false;
			for (Parameter p : c->getSynList())
				if (p.getParaName().compare(usedSynList.at(maxIdx).getParaName()) == 0)
					isClauseContainCurrentSyn = true;
			if (isClauseContainCurrentSyn && isClauseVisited.at(clauseIdx) == false && (int)c->getSynList().size() == 2) {
				isClauseVisited.at(clauseIdx) = true;
				vector<Parameter> newlyIntroducedParam;
				for (Parameter p : c->getSynList()) {
					if (!gResultTable->isSynInTable(p))
						newlyIntroducedParam.push_back(p);
				}
				ResultTable* queryResult = c->evaluate(pkb, &ResultTable());
				gResultTable->join(queryResult);
				if (gResultTable->getTupleSize() == 0) {
					delete resTable;
					resTable = new ResultTable();
					resTable->setSynList(usedSynList);
					return resTable;
				}
				for (Parameter p : newlyIntroducedParam) {
					for (int k = 0; k < (int)clause1SynList.size(); k++) {
						Clause* c = clause1SynList.at(k);
						if (c->getSynList().at(0).getParaName().compare(p.getParaName()) == 0) {
							gResultTable->join(clause1SynResult.at(k));
							if (gResultTable->getTupleSize() == 0) {
								delete resTable;
								resTable = new ResultTable();
								resTable->setSynList(usedSynList);
								return resTable;
							}
						}
					}
				}
			}

		}

		for (int k = 0; k < (int)clauseListForSyn.at(maxIdx).size(); k++) {
			int clauseIdx = clauseListForSyn.at(maxIdx).at(k);
			Clause* c = clauseList.at(clauseIdx);
			if ((int)c->getSynList().size() == 1) {
				isClauseVisited.at(clauseIdx) = true;
			}

			if ((int)c->getSynList().size() == 2 && isClauseVisited.at(clauseIdx) == false) {
				isClauseVisited.at(clauseIdx) = true;
				if (c->getClauseType() == AFFECTS || c->getClauseType() == NEXT || c->getClauseType() == AFFECTSSTAR || c->getClauseType() == NEXTSTAR) {
					gDeprioritizedClauseList.push_back(c);
				}
				else {
					vector<Parameter> cSynList = c->getSynList();
					vector<Parameter> restrictedSynList;
					for (Parameter p : cSynList)
						if (gResultTable->isSynInTable(p)) {
							restrictedSynList.push_back(p);
						}

					vector<Parameter> newlyIntroducedParam;
					for (Parameter p : c->getSynList()) {
						if (!gResultTable->isSynInTable(p))
							newlyIntroducedParam.push_back(p);
					}

					ResultTable* intResultTable = gResultTable->select(restrictedSynList);
					ResultTable* queryResult = c->evaluate(pkb, intResultTable);
					delete intResultTable;

					gResultTable->join(queryResult);

					if (gResultTable->getTupleSize() == 0) {
						delete resTable;
						resTable = new ResultTable();
						resTable->setSynList(usedSynList);
						return resTable;
					}

					for (Parameter p : newlyIntroducedParam) {
						for (int k = 0; k < (int)clause1SynList.size(); k++) {
							Clause* c = clause1SynList.at(k);
							if (c->getSynList().at(0).getParaName().compare(p.getParaName()) == 0) {
								gResultTable->join(clause1SynResult.at(k));
								if (gResultTable->getTupleSize() == 0) {
									delete resTable;
									resTable = new ResultTable();
									resTable->setSynList(usedSynList);
									return resTable;
								}
							}
						}
					}
				}
			}

		}

	}

	for (Clause* c : gDeprioritizedClauseList) {
		vector<Parameter> cSynList = c->getSynList();
		vector<Parameter> restrictedSynList;
		for (Parameter p : cSynList)
			if (gResultTable->isSynInTable(p)) {
				restrictedSynList.push_back(p);
			}

		ResultTable* intResultTable = gResultTable->select(restrictedSynList);
		ResultTable* queryResult = c->evaluate(pkb, intResultTable);
		gResultTable->join(queryResult);
		delete intResultTable;
	}

	return gResultTable;
}

ResultTable* QueryEvaluatorStub::getAllValueForSyn(Parameter param)
{
	ResultTable* res = new ResultTable();
	res->setSynList({ param });
	if (param.getParaType() == CALL) {
		for (int k : pkb->getAllCallId())
			res->insertTuple({ k });
	}

	if (param.getParaType() == WHILE) {
		for (int k : pkb->getAllWhileStmt())
			res->insertTuple({ k });
	}

	if (param.getParaType() == IF) {
		for (int k : pkb->getAllIfId())
			res->insertTuple({ k });
	}

	if ((param.getParaType() == STMT) || (param.getParaType() == PROG_LINE)) {
		for (int k : pkb->getAllStmtId())
			res->insertTuple({ k });
	}

	if (param.getParaType() == STMTLST) {
		for (int k : pkb->getAllStmtLst())
			res->insertTuple({ k });
	}

	if (param.getParaType() == ASSIGN) {
		for (int k : pkb->getAllAssignStmt())
			res->insertTuple({ k });
	}

	if (param.getParaType() == PROCEDURE) {
		for (int k : pkb->getAllProcId())
			res->insertTuple({ k });
	}

	if (param.getParaType() == VARIABLE) {
		for (int k : pkb->getAllVarId())
			res->insertTuple({ k });
	}

	if (param.getParaType() == CONSTANT) {
		for (int k : pkb->getAllConst())
			res->insertTuple({ k });
	}

	return res;
}


