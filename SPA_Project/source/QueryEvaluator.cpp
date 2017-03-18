#include <queue>

#include "QueryEvaluator.h"
#include "ClauseType.h"
#include "Follow.h"
#include "FollowStar.h"
#include "Modifies.h"
#include "Parent.h"
#include "ParentStar.h"
#include "Pattern.h"
#include "Uses.h"
#include "ResultTable.h"
#include "ClauseType.h"


struct groupComparator {
	bool operator() (unordered_set<int> i, unordered_set<int> j) { return ((int)i.size() < (int)j.size()); };
} gComparator;

QueryEvaluator::QueryEvaluator() {

}
QueryEvaluator::QueryEvaluator(PKB* pkbSource){
	pkb = pkbSource;
	resTable = ResultTable();
	resTable.setInitialEmpty(true);
}

void QueryEvaluator::setPKB(PKB* pkbInput) {
	this->pkb = pkbInput;
}

ResultTable QueryEvaluator::evaluate(QueryTree qt) {
	for (int i = 0; i < qt.getClauseSize(); i++) {
		Clause* c = qt.getClause(i);
		//printClause(c);
		vector<Parameter> cSynList = c->getSynList();
		vector<Parameter> restrictedSynList;
		for (Parameter p : cSynList)
			if (resTable.isSynInTable(p)) {
				restrictedSynList.push_back(p);
			}

		ResultTable queryResult = c->evaluate(pkb, resTable.select(restrictedSynList));
		if ((int)cSynList.size() == 0) {
			if (queryResult.getBoolean() == false && (queryResult.getSynCount() == 0)) {
				ResultTable emptyTable;
				emptyTable.setSynList(qt.getSelectParameter());
				return emptyTable;
			}
		}
		else {
			joinResultTable(queryResult);
		}		
	}

	// add selected but unused param to table
	for (Parameter p : qt.getSelectParameter()) {
		if (!resTable.isSynInTable(p))
			joinResultTable(getAllValueForSyn(p));
	}
	return resTable.select(qt.getSelectParameter());
}

ResultTable QueryEvaluator::evaluateWithOptimization(QueryTree qt)
{
	vector<Clause*> synClauseList;   // list of clauses with 1/2 synonym
	vector<int> clauseSynCount;      // number of syn in the clause
	unordered_map<int, ResultTable> resultMap;  // key: index in synClauseList

	vector<Clause*> clause1SynList;
	vector<ResultTable> result1SynList;

	// graph attribute
	vector<Parameter> synList = qt.getUsedParameter(); // synonym list
	unordered_map<string, int> synMap; // key: param.getname(), value: index of synonym
	vector<unordered_set<int>> adjList; // adj list for graph
	for (int i = 0; i < (int)synList.size(); i++) {
		Parameter p = synList.at(i);
		synMap.insert(make_pair(p.getParaName(), i));
	}

	// evaluate queries that have 0 synonym first
	for (int i = 0; i < qt.getClauseSize(); i++) {
		Clause* c = qt.getClause(i);
		if ((int)c->getSynList().size() == 0) {
			ResultTable resTable = c->evaluate(pkb, ResultTable());
			if (resTable.getSynList().size() == 0 && resTable.getBoolean() == false) {
				// the 0-syn clause is not true
				ResultTable emptyTable;
				emptyTable.setSynList(qt.getSelectParameter());
				return emptyTable;
			}
		}
		else {
			// if have syn, save it for later use
			synClauseList.push_back(c);
			vector<Parameter> tmpList = c->getSynList();
			clauseSynCount.push_back((int)tmpList.size());
			if ((int)tmpList.size() == 2) {
				// create edge in adj list
				adjList.at(synMap[tmpList.at(0).getParaName()]).insert(synMap[tmpList.at(1).getParaName()]);
				adjList.at(synMap[tmpList.at(1).getParaName()]).insert(synMap[tmpList.at(0).getParaName()]);
			}

			// if only one synonym, evaluate
			if ((int)c->getSynList().size() == 1) {
				ResultTable resTable = c->evaluate(pkb, ResultTable());
				if ((int)resTable.getTupleList().size() == 0) {
					// if no result is selected, return no output
					ResultTable emptyTable;
					emptyTable.setSynList(qt.getSelectParameter());
					return emptyTable;
				}
				else {
					// else, store the clause and result.
					clause1SynList.push_back(c);
					result1SynList.push_back(resTable);
				}
			}
		}
	}

	// find syn group (connected components  BFS)
	vector<unordered_set<int>> synGroup; // int -> index of param
	unordered_set<int> spareIdx;
	for (int i = 0; i < (int)synList.size(); i++)
		spareIdx.insert(i);
	while ((int)spareIdx.size() > 0) {
		unordered_set<int> group;
		int idx = *spareIdx.begin();
		group.insert(idx);
		queue<int> q;
		q.push(idx);
		while (!q.empty()) {
			int currentIdx = q.front();
			q.pop();
			for (int adjIdx : adjList.at(currentIdx)) {
				if (spareIdx.find(adjIdx) != spareIdx.end()) {
					spareIdx.erase(idx);
					group.insert(idx);
					q.push(idx);
				}
			}
		}
		synGroup.push_back(group);
	}
	// sort synGroup by number of syn.
	sort(synGroup.begin(), synGroup.end(), gComparator);

	// start from group with small number of synonym. evaluate
	// create result Table for each group
	vector<ResultTable> resTableList;
	for (int i = 0; i < (int)synGroup.size(); i++) {
		/*
			For each group, get the clauses for the group, 
		*/ 
		unordered_set<int> group = synGroup.at(i);
		vector<Clause*> gClauseList;
		// get clauses of this group
		for (Clause* c : synClauseList) {
			vector<Parameter> tmpList = c->getSynList();
			for (Parameter p : tmpList) {
				if (group.find(synMap[p.getParaName()]) != group.end()) {
					// if any synonym is in the group, put clause in
					gClauseList.push_back(c);
				}
			}
		}
		// get syn list vector
		vector<Parameter> gSynList;
		for (int p : synGroup.at(i))
			gSynList.push_back(synList.at(p));

		resTableList.push_back(evaluateGroup(gSynList, gClauseList, clause1SynList, result1SynList));
	

	}

	// for each group, select sub resultTable containing what is selected
	for (int i = 0; i < (int)synGroup.size(); i++) {
		// get select syn list
		vector<Parameter> gSelectList;
		for (int p : synGroup.at(i)) {
			Parameter param = synList.at(p);
			for (Parameter sp : qt.getSelectParameter()) {
				if (param.getParaName().compare(sp.getParaName()) == 0)
					gSelectList.push_back(param);
			}
		}
		resTableList.at(i) = resTableList.at(i).select(gSelectList);
	}

	// merge all sub table, return final result
	ResultTable finalTable;
	finalTable.setInitialEmpty(true);
	for (int i = 0; i < (int)synGroup.size(); i++) {
		finalTable.join(resTableList.at(i));
	}

	return finalTable.select(qt.getSelectParameter());


}

ResultTable QueryEvaluator::evaluateGroup(vector<Parameter> usedSynList,
	vector<Clause*> clauseList, vector<Clause*> clause1SynList, vector<ResultTable> clause1SynResult)
{
	// this is to merge and peroduce a intermediate resulttable for a group

	/*
	within each group, start from the syn with highest degree.
	merge all clauses with that syn ( if any new syn have 1-clause,
	merge them first to shorten table)
	then merge clauses for lower degree syn. (TIE: pick arbitrage)

	for each synonym
	put all affect(*) and next(*) with 2 synonym at ver last
	put with at very first, then parent
	then arbitrage order
	*/
	vector<bool> isClauseVisited; 
	vector<bool> isSynVisited;
	vector<Clause*> gDeprioritizedClauseList; // affect and next with 2 synonyms
	unordered_map<string, int> gSynMap; // key: param.getname(), value: index of synonym
	vector<int> gSynDegree;   // index from usedSynList
	vector<vector<int>> clauseListForSyn; // one synonym contain list of clause index
	ResultTable gResultTable;
	gResultTable.setInitialEmpty(true);
	


	// set gSynMap
	for (int i = 0; i < (int)usedSynList.size(); i++) {
		gSynMap.insert(make_pair(usedSynList.at(i).getParaName(), i));
		isSynVisited.push_back(false);
		clauseListForSyn.push_back({});
	}
	// set gSynDegree
	for (int i = 0; i < (int)clauseList.size(); i++) {
		Clause* c = clauseList.at(i);
		isClauseVisited.push_back(false);
		for (Parameter p : c->getSynList()) {
			gSynDegree.at(gSynMap[p.getParaName()])++;
			clauseListForSyn.at(gSynMap[p.getParaName()]).push_back(i);
		}
	}

	// loop through all param, from high degree to low degree
	// if any clause contain the current syn, but is affect/next with 2 syn.
	// push to deprior list
	for (int i = 0; i < (int)usedSynList.size(); i++) {
		// loop number of synonyms times
		// get the syn with highest occurance
		int maxOccurance = -1; int maxIdx = -1;
		for (int k = 0; k < (int)usedSynList.size(); k++) {
			if (gSynDegree.at(k) > maxOccurance) {
				maxOccurance = gSynDegree.at(k);
				maxIdx = k;
			}
		}
		// cuurent index = maxIdx 
		// first, check 1-syn list, see if any clause contain the synonym
		// if some does, merge it.

		isSynVisited.at(maxIdx) = true; // set synonym visited
		for (int k = 0; k < (int)clause1SynList.size(); k++) {
			Clause* c = clause1SynList.at(k);
			int synIdx = gSynMap[c->getSynList().at(0).getParaName()];
			if (synIdx == maxIdx) 
				gResultTable = gResultTable.join(clause1SynResult.at(k));
		}
		// then loop through all clause that contain the synonym
		for (int k = 0; k < (int)clauseListForSyn.at(maxIdx).size(); k++) {
			int clauseIdx = clauseListForSyn.at(maxIdx).at(k);
			Clause* c = clauseList.at(clauseIdx);
			
			if ((int)c->getSynList().size() == 1) {
				//if only contain this syn, already calcualted, marked as visited
				isClauseVisited.at(clauseIdx) = true;
			}
			// if c contain one synonym skip, consider only two synonym
			if ((int)c->getSynList().size() == 2 || isClauseVisited.at(clauseIdx) == false) {
				// set clause as visited 
				isClauseVisited.at(clauseIdx) = true;
				
				// if affect / next, put into deprior list
				if (c->getClauseType() == AFFECTS || c->getClauseType() == NEXT)
					gDeprioritizedClauseList.push_back(c);
				else {
					// else, process and merge 
					// MAYBE PRIORTIZE PARENT > FOLLOWS > MODIFIES > USES (not impmemented yet)
					vector<Parameter> cSynList = c->getSynList();
					vector<Parameter> restrictedSynList;
					for (Parameter p : cSynList)
						if (gResultTable.isSynInTable(p)) {
							restrictedSynList.push_back(p);
						}

					ResultTable queryResult = c->evaluate(pkb, gResultTable.select(restrictedSynList));
					gResultTable = gResultTable.join(queryResult);

					/*
					IMPROVEMENT: FOR EACH NEW SYNONYM ADDED, CHECK WHETHER CLAUSE CONTAINS
					THAT SYNONYM ONLY, IF YES, EVALUATE AND MERGE. 
					*/
				}
			}

		}

	}

	// now, evaluate and merge the deprioritized list 
	for (Clause* c : gDeprioritizedClauseList) {
		vector<Parameter> cSynList = c->getSynList();
		vector<Parameter> restrictedSynList;
		for (Parameter p : cSynList)
			if (gResultTable.isSynInTable(p)) {
				restrictedSynList.push_back(p);
			}

		ResultTable queryResult = c->evaluate(pkb, gResultTable.select(restrictedSynList));
		gResultTable = gResultTable.join(queryResult);
	}


	return ResultTable();
}

ResultTable QueryEvaluator::getAllValueForSyn(Parameter param)
{
	ResultTable res;
	res.setSynList({ param });
	if (param.getParaType() == CALL) {
		for (int k : pkb->getAllCallId())
			res.insertTuple({ k });
	}

	if (param.getParaType() == WHILE) {
		for (int k : pkb->getAllWhileStmt())
			res.insertTuple({ k });
	}

	if (param.getParaType() == IF) {
		for (int k : pkb->getAllIfId())
			res.insertTuple({ k });
	}

	if ((param.getParaType() == STMT) || (param.getParaType() == PROG_LINE)) {
		for (int k : pkb->getAllStmtId())
			res.insertTuple({ k });
	}

	if (param.getParaType() == STMTLST) {
		for (int k : pkb->getAllStmtLst())
			res.insertTuple({ k });
	}

	if (param.getParaType() == ASSIGN) {
		for (int k : pkb->getAllAssignStmt())
			res.insertTuple({ k });
	}

	if (param.getParaType() == PROCEDURE) {
		for (int k : pkb->getAllProcId())
			res.insertTuple({ k });
	}

	if (param.getParaType() == VARIABLE) {
		for (int k : pkb->getAllVarId())
			res.insertTuple({ k });
	}

	if (param.getParaType() == CONSTANT) {
		for (int k : pkb->getAllConstId())
			res.insertTuple({ k });
	}

	return res;
}

void QueryEvaluator::joinResultTable(ResultTable rt)
{
	cout << "current Table" << endl;
	resTable.printTable();
	cout << "joining Table" << endl;
	rt.printTable();
	resTable = resTable.join(rt);
	cout << "after joining, the table is " << endl;
	resTable.printTable();
}

void QueryEvaluator::printClause(Clause* c)
{
	string str;
	str += c->getClauseType();
	str = str + "(" + c->getLeftChild().getParaName() + ", " + c->getRightChild().getParaName() + ")";
	cout << "Clause is " << str << endl;
}
