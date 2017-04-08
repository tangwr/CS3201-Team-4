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
QueryEvaluator::QueryEvaluator(PKB* pkbSource) {
	pkb = pkbSource;
	resTable = ResultTable();
	resTable.setInitialEmpty(true);
}

void QueryEvaluator::setPKB(PKB* pkbInput) {
	this->pkb = pkbInput;
}

ResultTable QueryEvaluator::evaluate(QueryTree qt) {
 	ResultTable ans = evaluateWithOptimization2(qt);
	for (int i = 0; i < (int)qt.getClauseSize() ; i++)
		delete qt.getClause(i);
	return ans;
}

ResultTable QueryEvaluator::createEarlyTerminationTable(QueryTree qt)
{
	ResultTable emptyTable;
	if ((int)qt.getSelectParameter().size() == 1 && qt.getSelectParameter().at(0).getParaType() == BOOLEAN) {
		emptyTable.setBoolean(false);
	}
	else
		emptyTable.setSynList(qt.getSelectParameter());
	return emptyTable;
}



ResultTable QueryEvaluator::evaluateWithoutOptimization(QueryTree qt) {

	// clear result table
	resTable = ResultTable();
	resTable.setInitialEmpty(true);
	resTable.setBoolean(true);
	cout << "START EVALUATION" << endl;
	cout << "number of clause = " << qt.getClauseSize() << endl;
	for (int i = 0; i < qt.getClauseSize(); i++) {
		Clause* c = qt.getClause(i);
		printClause(c);
		vector<Parameter> cSynList = c->getSynList();
		vector<Parameter> restrictedSynList;
		for (Parameter p : cSynList)
			if (resTable.isSynInTable(p)) {
				restrictedSynList.push_back(p);
			}
		cout << "clause has # synym = " << (int)(cSynList.size()) << endl;
		ResultTable queryResult = c->evaluate(pkb, resTable.select(restrictedSynList));
		if ((int)queryResult.getTupleSize() == 0) {
			cout << "rt.getboolean = " << queryResult.getBoolean() << endl;
			queryResult.printTable();

			// false boolean clause with no synonym
			if ((queryResult.getBoolean() == false) && (queryResult.getSynCount() == 0)) {
				ResultTable emptyTable;
				if (qt.getSelectParameter().at(0).getParaType() == BOOLEAN)
					emptyTable.setBoolean(false);
				else
					emptyTable.setSynList(qt.getSelectParameter());
				return emptyTable;
			}
			// empty result clause with 1/2 synonym 
			if (queryResult.getSynCount() > 0) {
				ResultTable emptyTable;
				if (qt.getSelectParameter().at(0).getParaType() == BOOLEAN)
					emptyTable.setBoolean(false);
				else
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
		if (p.getParaType() != BOOLEAN && !resTable.isSynInTable(p)) {
			cout << "found selected but unused synonym: " + p.getParaName() << endl;
			joinResultTable(getAllValueForSyn(p));
		}
	}
	ResultTable finalTable;
	if ((int)qt.getSelectParameter().size() == 1 && qt.getSelectParameter().at(0).getParaType() == BOOLEAN) {
		if (resTable.getTupleSize() > 0)
			finalTable.setBoolean(true);
		else
			if (resTable.getBoolean() == true)
				finalTable.setBoolean(true);
			else
				finalTable.setBoolean(false);
	}
	else {
		finalTable = resTable.select(qt.getSelectParameter());
	}
	cout << "FINAL TABLE" << endl;
	finalTable.printTable();
	return finalTable;
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
		adjList.push_back({});
	}

	// evaluate queries that have 0 synonym first
	for (int i = 0; i < qt.getClauseSize(); i++) {
		Clause* c = qt.getClause(i);
		if ((int)c->getSynList().size() == 0) {
			cout << "Clause with 0 synonym found " << endl;
			printClause(c);
			ResultTable resTable = c->evaluate(pkb, ResultTable());
			if (resTable.getSynList().size() == 0 && resTable.getBoolean() == false) {
				// the 0-syn clause is not true
				ResultTable emptyTable;
				if ((int)qt.getSelectParameter().size() == 1 && qt.getSelectParameter().at(0).getParaType() == BOOLEAN) {
					emptyTable.setBoolean (false);
				}
				else
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
				cout << "one synonym clause found " << endl;
				printClause(c);
				ResultTable resTable = c->evaluate(pkb, ResultTable());
				if ((int)resTable.getTupleList().size() == 0) {
					// if no result is selected, return no output
					ResultTable emptyTable; 
					if ((int)qt.getSelectParameter().size() == 1 && qt.getSelectParameter().at(0).getParaType() == BOOLEAN) {
						emptyTable.setBoolean(false);
					}
					else
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

	cout << "clause Synlist size = " << (int)synClauseList.size() << endl;
	// find syn group (connected components  BFS)
	vector<unordered_set<int>> synGroup; // int -> index of param
	unordered_set<int> spareIdx;
	for (int i = 0; i < (int)synList.size(); i++)
		spareIdx.insert(i);
	while ((int)spareIdx.size() > 0) {
		cout << "sparesidx size  = " << (int)spareIdx.size() << endl;
		unordered_set<int> group;
		int idx = *spareIdx.begin();
		cout << "first index is " << idx << endl;
		group.insert(idx);
		queue<int> q;
		spareIdx.erase(idx);
		q.push(idx);
		while (!q.empty()) {
			int currentIdx = q.front();
			cout << "current idx = " << currentIdx << endl;
			cout << "spareidx size = " << (int)spareIdx.size() << endl;
			q.pop();
			for (int adjIdx : adjList.at(currentIdx)) {
				if (spareIdx.find(adjIdx) != spareIdx.end()) {
					spareIdx.erase(adjIdx);
					group.insert(adjIdx);
					cout << "push to queue : " << adjIdx << endl;
					q.push(adjIdx);
				}
			}
		}
		synGroup.push_back(group);
	}
	// sort synGroup by number of syn.
	sort(synGroup.begin(), synGroup.end(), gComparator);

	for (unordered_set<int> g : synGroup) {
		cout << " GROUP: ";
		for (int k : g)
			cout << synList.at(k).getParaName() << " ";
		cout << endl;
	}


	// start from group with small number of synonym. evaluate
	// create result Table for each group

	vector<ResultTable> resTableList;
	for (int i = 0; i < (int)synGroup.size(); i++) {
		/*
		For each group, get the clauses for the group,
		*/
		unordered_set<int> group = synGroup.at(i);

		// ---  output group synonym --- //
		cout << "evaluating Group " << i << endl;
		cout << "Group " << i << " contains synonym ";
		for (int k : group)
			cout << synList.at(k).getParaName() << " ";
		cout << endl;
		cout << endl;


		vector<Clause*> gClauseList;
		// get clauses of this group
		for (Clause* c : synClauseList) {
			vector<Parameter> tmpList = c->getSynList();
			bool shouldInsert = false;
			for (Parameter p : tmpList) {
				if (group.find(synMap[p.getParaName()]) != group.end()) {
					// if any synonym is in the group, put clause in
					shouldInsert = true;
				}
			}
			if (shouldInsert)
				gClauseList.push_back(c);
		}
		// get syn list vector
		vector<Parameter> gSynList;
		for (int p : synGroup.at(i))
			gSynList.push_back(synList.at(p));

		resTableList.push_back(evaluateGroup(gSynList, gClauseList, clause1SynList, result1SynList));


	}


	ResultTable finalTable;
	finalTable.setInitialEmpty(true);

	//if select BOOLEAN
	if ((int)qt.getSelectParameter().size() == 1 && qt.getSelectParameter().at(0).getParaType() == BOOLEAN) {
		cout << "Boolean is selected" << endl;
		bool isAnyTableEmpty = false;
		for (ResultTable rt : resTableList) {
			if (rt.getTupleSize() == 0 && rt.getBoolean() == false)
				isAnyTableEmpty = true;
			cout << isAnyTableEmpty << endl;
		}

		if (isAnyTableEmpty == false)
			finalTable.setBoolean(true);
		else
			finalTable.setBoolean(false);
		return finalTable;
	}




	// if not select BOOLEAN, proceed
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
		if ((int)gSelectList.size() > 0) {
			resTableList.at(i) = resTableList.at(i).select(gSelectList);
		}
		else {
			resTableList.at(i) = ResultTable();
			resTableList.at(i).setInitialEmpty(true);
		}
		cout << " SUBTABLE FOR GROUP " << i << "IS " << endl;
		resTableList.at(i).printTable();
	}

	// merge all sub table, return final result
	for (int i = 0; i < (int)synGroup.size(); i++) {
		finalTable.join(resTableList.at(i));
	}

	// merge selected but unused synonym
	for (Parameter p : qt.getSelectParameter()) {
		if (finalTable.isSynInTable(p) == false)
			cout << "find select but not in clause synonym " << p.getParaName() << endl;
			finalTable.join(getAllValueForSyn(p));
	}

	

	cout << "FINAL TABLE FOR THE QUERY" << endl;
	finalTable.printTable();

	return finalTable.select(qt.getSelectParameter());


}

ResultTable QueryEvaluator::evaluateWithOptimization2(QueryTree qt)
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
		adjList.push_back({});
	}

	// evaluate queries that have 0 synonym first
	for (int i = 0; i < qt.getClauseSize(); i++) {
		Clause* c = qt.getClause(i);
		if ((int)c->getSynList().size() == 0) {
			cout << "Clause with 0 synonym found " << endl;
			printClause(c);
			ResultTable resTable = c->evaluate(pkb, ResultTable());
			if (resTable.getSynList().size() == 0 && resTable.getBoolean() == false) {
				// the 0-syn clause is not true
				return createEarlyTerminationTable(qt);
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
				cout << "one synonym clause found " << endl;
				printClause(c);
				ResultTable resTable = c->evaluate(pkb, ResultTable());
				if ((int)resTable.getTupleList().size() == 0) {
					// if no result is selected, return no output
					return createEarlyTerminationTable(qt);
				}
				else {
					// else, store the clause and result.
					clause1SynList.push_back(c);
					result1SynList.push_back(resTable);
				}
			}
		}
	}

	cout << "clause Synlist size = " << (int)synClauseList.size() << endl;
	// find syn group (connected components  BFS)
	vector<unordered_set<int>> synGroup; // int -> index of param
	unordered_set<int> spareIdx;
	for (int i = 0; i < (int)synList.size(); i++)
		spareIdx.insert(i);
	while ((int)spareIdx.size() > 0) {
		cout << "sparesidx size  = " << (int)spareIdx.size() << endl;
		unordered_set<int> group;
		int idx = *spareIdx.begin();
		cout << "first index is " << idx << endl;
		group.insert(idx);
		queue<int> q;
		spareIdx.erase(idx);
		q.push(idx);
		while (!q.empty()) {
			int currentIdx = q.front();
			cout << "current idx = " << currentIdx << endl;
			cout << "spareidx size = " << (int)spareIdx.size() << endl;
			q.pop();
			for (int adjIdx : adjList.at(currentIdx)) {
				if (spareIdx.find(adjIdx) != spareIdx.end()) {
					spareIdx.erase(adjIdx);
					group.insert(adjIdx);
					cout << "push to queue : " << adjIdx << endl;
					q.push(adjIdx);
				}
			}
		}
		synGroup.push_back(group);
	}
	// sort synGroup by number of syn.
	sort(synGroup.begin(), synGroup.end(), gComparator);

	for (unordered_set<int> g : synGroup) {
		cout << " GROUP: ";
		for (int k : g)
			cout << synList.at(k).getParaName() << " ";
		cout << endl;
	}


	// start from group with small number of synonym. evaluate
	// create result Table for each group

	vector<ResultTable> resTableList;
	for (int i = 0; i < (int)synGroup.size(); i++) {
		/*
		For each group, get the clauses for the group,
		*/
		unordered_set<int> group = synGroup.at(i);

		// ---  output group synonym --- //
		cout << "evaluating Group " << i << endl;
		cout << "Group " << i << " contains synonym ";
		for (int k : group)
			cout << synList.at(k).getParaName() << " ";
		cout << endl;
		cout << endl;


		vector<Clause*> gClauseList;
		// get clauses of this group
		for (Clause* c : synClauseList) {
			vector<Parameter> tmpList = c->getSynList();
			bool shouldInsert = false;
			for (Parameter p : tmpList) {
				if (group.find(synMap[p.getParaName()]) != group.end()) {
					// if any synonym is in the group, put clause in
					shouldInsert = true;
				}
			}
			if (shouldInsert)
				gClauseList.push_back(c);
		}
		// get syn list vector
		vector<Parameter> gSynList;
		for (int p : synGroup.at(i))
			gSynList.push_back(synList.at(p));

		
		ResultTable gTable = evaluateGroup2(gSynList, gClauseList, clause1SynList, result1SynList);
		if (gTable.getTupleSize() == 0) {
			// early termination
			return createEarlyTerminationTable(qt);
		}
		resTableList.push_back(gTable);

	}


	ResultTable finalTable;
	finalTable.setInitialEmpty(true);

	//if select BOOLEAN
	if ((int)qt.getSelectParameter().size() == 1 && qt.getSelectParameter().at(0).getParaType() == BOOLEAN) {
		cout << "Boolean is selected" << endl;
		bool isAnyTableEmpty = false;
		for (ResultTable rt : resTableList) {
			if (rt.getTupleSize() == 0 && rt.getBoolean() == false)
				isAnyTableEmpty = true;
			cout << isAnyTableEmpty << endl;
		}

		if (isAnyTableEmpty == false)
			finalTable.setBoolean(true);
		else
			finalTable.setBoolean(false);
		return finalTable;
	}




	// if not select BOOLEAN, proceed
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
		if ((int)gSelectList.size() > 0) {
			resTableList.at(i) = resTableList.at(i).select(gSelectList);
		}
		else {
			resTableList.at(i) = ResultTable();
			resTableList.at(i).setInitialEmpty(true);
		}
		cout << " SUBTABLE FOR GROUP " << i << "IS " << endl;
		resTableList.at(i).printTable();
	}

	// merge all sub table, return final result
	for (int i = 0; i < (int)synGroup.size(); i++) {
		finalTable.join(resTableList.at(i));
	}

	// merge selected but unused synonym
	for (Parameter p : qt.getSelectParameter()) {
		if (finalTable.isSynInTable(p) == false)
			cout << "find select but not in clause synonym " << p.getParaName() << endl;
		finalTable.join(getAllValueForSyn(p));
	}



	cout << "FINAL TABLE FOR THE QUERY" << endl;
	finalTable.printTable();

	return finalTable.select(qt.getSelectParameter());


}

ResultTable QueryEvaluator::evaluateGroup2(vector<Parameter> usedSynList,
	vector<Clause*> clauseList, vector<Clause*> clause1SynList, vector<ResultTable> clause1SynResult)
{
	// this is to merge and peroduce a intermediate resulttable for a group

	/*
	within each group, start from the syn with highest degree.
	merge all clauses with that syn ( if any new syn have 1-clause,
	merge them first to shorten table)
	then merge clauses for lower degree syn. (TIE: pick arbitrage)

	for each synonym
	put all affect(*) and next(*) with 2 synonym at very last
	put with at very first, then parent
	then arbitrage order
	*/
	vector<bool> isClauseVisited;
	vector<bool> isSynVisited;
	vector<Clause*> gDeprioritizedClauseList; // affect and next with 2 synonyms
	unordered_map<string, int> gSynMap; // key: param.getname(), value: index of synonym
	vector<int> gSynDegree;   // index from usedSynList
	vector<vector<int>> clauseListForSyn; // one synonym contain list of clause index
	vector<int> withClauseList;
	ResultTable gResultTable;
	gResultTable.setInitialEmpty(true);

	// set gSynMap
	for (int i = 0; i < (int)usedSynList.size(); i++) {
		gSynMap.insert(make_pair(usedSynList.at(i).getParaName(), i));
		isSynVisited.push_back(false);
		clauseListForSyn.push_back({});
		gSynDegree.push_back({});
	}
	// set gSynDegree
	cout << "clause list size = " << (int)clauseList.size() << endl;
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

	for (int k = 0; k < (int)usedSynList.size(); k++) {
		cout << "synonym " << usedSynList.at(k).getParaName() << " has degree of " << gSynDegree.at(k) << endl;
		cout << "clauses of this synonym are " << endl;
		for (int c : clauseListForSyn.at(k))
			printClause(clauseList.at(c));
	}

	// loop through all param, from high degree to low degree
	// if any clause contain the current syn, but is affect/next with 2 syn.
	// push to deprior list
	for (int i = 0; i < (int)usedSynList.size(); i++) {
		// loop number of synonyms times
		// get the syn with highest occurance
		int maxOccurance = -1; int maxIdx = -1;
		for (int k = 0; k < (int)usedSynList.size(); k++) {
			if (gSynDegree.at(k) > maxOccurance && isSynVisited.at(k) == false) {
				maxOccurance = gSynDegree.at(k);
				maxIdx = k;
			}
		}
		// cuurent index = maxIdx 
		// first, check 1-syn list, see if any clause contain the synonym
		// if some does, merge it.

		isSynVisited.at(maxIdx) = true; // set synonym visited
		cout << "current processing synonym is " << usedSynList.at(maxIdx).getParaName() << endl;
		cout << "its degree is " << gSynDegree.at(maxIdx) << endl;
		cout << "---Clause with only one synonym---" << endl;
		for (int k = 0; k < (int)clause1SynList.size(); k++) {
			Clause* c = clause1SynList.at(k);

			string paraName = c->getSynList().at(0).getParaName();
			if (paraName.compare(usedSynList.at(maxIdx).getParaName()) == 0) {
				printClause(c);
				gResultTable.join(clause1SynResult.at(k));
				cout << "After join table is " << endl;
				gResultTable.printTable();
				if (gResultTable.getTupleSize() == 0) {
					// no result for this group, early termination
					ResultTable emptyTable;
					emptyTable.setSynList(usedSynList);
					return emptyTable;
				}
			}
			
		}
		// then loop through all clause that contain the synonym
		cout << "---Clause with two synonym---" << endl;
		// test with clause
		for (int k = 0; k < (int)withClauseList.size(); k++) {
			int clauseIdx = withClauseList.at(k);
			Clause* c = clauseList.at(clauseIdx);
			bool isClauseContainCurrentSyn = false;
			for (Parameter p : c->getSynList())
				if (p.getParaName().compare(usedSynList.at(maxIdx).getParaName()) == 0)
					isClauseContainCurrentSyn = true;
			if (isClauseContainCurrentSyn && isClauseVisited.at(clauseIdx) == false && (int)c->getSynList().size() == 2) {
				isClauseVisited.at(clauseIdx) = true;
				cout << "evaluate with clause " << endl;
				printClause(c);
				vector<Parameter> newlyIntroducedParam;
				for (Parameter p : c->getSynList()) {
					if (!gResultTable.isSynInTable(p))
						newlyIntroducedParam.push_back(p);
				}
				ResultTable queryResult = c->evaluate(pkb, ResultTable());
				gResultTable.join(queryResult);
				cout << "After join table is " << endl;
				gResultTable.printTable();
				if (gResultTable.getTupleSize() == 0) {
					// no result for this group, early termination
					ResultTable emptyTable;
					emptyTable.setSynList(usedSynList);
					return emptyTable;
				}
				for (Parameter p : newlyIntroducedParam) {
					cout << "Synonym " << p.getParaName() << "is firstly introduced to the intermediate table" << endl;
					for (int k = 0; k < (int)clause1SynList.size(); k++) {
						Clause* c = clause1SynList.at(k);
						if (c->getSynList().at(0).getParaName().compare(p.getParaName()) == 0) {
							cout << "found new clause that contains only the new synonym" << endl;
							printClause(c);
							gResultTable.join(clause1SynResult.at(k));
							cout << "After join table is " << endl;
							gResultTable.printTable();
							if (gResultTable.getTupleSize() == 0) {
								// no result for this group, early termination
								ResultTable emptyTable;
								emptyTable.setSynList(usedSynList);
								return emptyTable;
							}
						}
					}
				}
			}

		}

		for (int k = 0; k < (int)clauseListForSyn.at(maxIdx).size(); k++) {
			cout << "CLAUSE LIST SIZE = " << (int)clauseListForSyn.at(maxIdx).size() << endl;
			int clauseIdx = clauseListForSyn.at(maxIdx).at(k);
			Clause* c = clauseList.at(clauseIdx);
			printClause(c);
			if ((int)c->getSynList().size() == 1) {
				//if only contain this syn, already calcualted, marked as visited
				isClauseVisited.at(clauseIdx) = true;
				cout << "this clause (1_syn) is already calculated, so skipped " << endl;
			}
			if ((int)c->getSynList().size() == 2 && isClauseVisited.at(clauseIdx) == true) {
				cout << "this clause (2_syn) is already calculated, so skipped " << endl;
			}

			// if c contain one synonym skip, consider only two synonym
			if ((int)c->getSynList().size() == 2 && isClauseVisited.at(clauseIdx) == false) {
				// set clause as visited 
				isClauseVisited.at(clauseIdx) = true;
				// if affect / next, put into deprior list
				if (c->getClauseType() == AFFECTS || c->getClauseType() == NEXT || c->getClauseType() == AFFECTSSTAR || c->getClauseType() == NEXTSTAR) {
					gDeprioritizedClauseList.push_back(c);
					cout << "put into deprioritized list" << endl;
				}
				else {
					// else, process and merge 
					cout << "evaluting clause " << endl;
					vector<Parameter> cSynList = c->getSynList();
					vector<Parameter> restrictedSynList;
					for (Parameter p : cSynList)
						if (gResultTable.isSynInTable(p)) {
							restrictedSynList.push_back(p);
						}

					// check whether this clause introduce new paramter to intermediate table
					vector<Parameter> newlyIntroducedParam;
					for (Parameter p : c->getSynList()) {
						if (!gResultTable.isSynInTable(p))
							newlyIntroducedParam.push_back(p);
					}


					ResultTable queryResult = c->evaluate(pkb, gResultTable.select(restrictedSynList));
				
					gResultTable.join(queryResult);
					cout << "After join table is " << endl;
					gResultTable.printTable();
					if (gResultTable.getTupleSize() == 0) {
						// no result for this group, early termination
						ResultTable emptyTable;
						emptyTable.setSynList(usedSynList);
						return emptyTable;
					}

					/*
					IMPROVEMENT: FOR EACH NEW SYNONYM ADDED, CHECK WHETHER CLAUSE CONTAINS
					THAT SYNONYM ONLY, IF YES, EVALUATE AND MERGE.
					*/
					for (Parameter p : newlyIntroducedParam) {
						cout << "Synonym " << p.getParaName() << "is firstly introduced to the intermediate table" << endl;
						for (int k = 0; k < (int)clause1SynList.size(); k++) {
							Clause* c = clause1SynList.at(k);
							if (c->getSynList().at(0).getParaName().compare(p.getParaName()) == 0) {
								cout << "found new clause that contains only the new synonym" << endl;
								printClause(c);
								gResultTable.join(clause1SynResult.at(k));
								cout << "After join table is " << endl;
								gResultTable.printTable();
								if (gResultTable.getTupleSize() == 0) {
									// no result for this group, early termination
									ResultTable emptyTable;
									emptyTable.setSynList(usedSynList);
									return emptyTable;
								}
							}
						}
					}
				}
			}

		}

	}

	// now, evaluate and merge the deprioritized list 
	cout << "---Deprioritized Clause---" << endl;
	for (Clause* c : gDeprioritizedClauseList) {
		printClause(c);
		vector<Parameter> cSynList = c->getSynList();
		vector<Parameter> restrictedSynList;
		for (Parameter p : cSynList)
			if (gResultTable.isSynInTable(p)) {
				restrictedSynList.push_back(p);
			}

		ResultTable queryResult = c->evaluate(pkb, gResultTable.select(restrictedSynList));
		gResultTable.join(queryResult);
	}

	cout << "FINAL TABLE FOR GROUP " << endl;
	gResultTable.printTable();
	return gResultTable;
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
	put all affect(*) and next(*) with 2 synonym at very last
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
		gSynDegree.push_back({});
	}
	// set gSynDegree
	cout << "clause list size = " << (int)clauseList.size() << endl;
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
	}

	for (int k = 0; k < (int)usedSynList.size(); k++) {
		cout << "synonym " << usedSynList.at(k).getParaName() << " has degree of " << gSynDegree.at(k) << endl;
		cout << "clauses of this synonym are " << endl;
		for (int c : clauseListForSyn.at(k))
			printClause(clauseList.at(c));
	}

	// loop through all param, from high degree to low degree
	// if any clause contain the current syn, but is affect/next with 2 syn.
	// push to deprior list
	for (int i = 0; i < (int)usedSynList.size(); i++) {
		// loop number of synonyms times
		// get the syn with highest occurance
		int maxOccurance = -1; int maxIdx = -1;
		for (int k = 0; k < (int)usedSynList.size(); k++) {
			if (gSynDegree.at(k) > maxOccurance && isSynVisited.at(k) ==false) {
				maxOccurance = gSynDegree.at(k);
				maxIdx = k;
			}
		}
		// cuurent index = maxIdx 
		// first, check 1-syn list, see if any clause contain the synonym
		// if some does, merge it.

		isSynVisited.at(maxIdx) = true; // set synonym visited
		cout << "current processing synonym is " << usedSynList.at(maxIdx).getParaName() << endl;
		cout << "its degree is " << gSynDegree.at(maxIdx) << endl;
		cout << "---Clause with only one synonym---" << endl;
		for (int k = 0; k < (int)clause1SynList.size(); k++) {
			Clause* c = clause1SynList.at(k);

			string paraName = c->getSynList().at(0).getParaName();
			if (paraName.compare(usedSynList.at(maxIdx).getParaName()) == 0) {
				printClause(c);
				gResultTable.join(clause1SynResult.at(k));
				cout << "After join table is " << endl;
				gResultTable.printTable();
			}
		}
		// then loop through all clause that contain the synonym
		cout << "---Clause with two synonym---" << endl;
		for (int k = 0; k < (int)clauseListForSyn.at(maxIdx).size(); k++) {
			cout << "CLAUSE LIST SIZE = " << (int)clauseListForSyn.at(maxIdx).size() << endl;
			int clauseIdx = clauseListForSyn.at(maxIdx).at(k);
			Clause* c = clauseList.at(clauseIdx);
			printClause(c);
			if ((int)c->getSynList().size() == 1) {
				//if only contain this syn, already calcualted, marked as visited
				isClauseVisited.at(clauseIdx) = true;
				cout << "this clause (1_syn) is already calculated, so skipped " << endl;
			}
			if ((int)c->getSynList().size() == 2 && isClauseVisited.at(clauseIdx) == true) {
				cout << "this clause (2_syn) is already calculated, so skipped " << endl;
			}

			// if c contain one synonym skip, consider only two synonym
			if ((int)c->getSynList().size() == 2 && isClauseVisited.at(clauseIdx) == false) {
				// set clause as visited 
				isClauseVisited.at(clauseIdx) = true;
				// if affect / next, put into deprior list
				if (c->getClauseType() == AFFECTS || c->getClauseType() == NEXT) {
					gDeprioritizedClauseList.push_back(c);
					cout << "put into deprioritized list" << endl;
				}
				else {
					// else, process and merge 
					// MAYBE PRIORTIZE PARENT > FOLLOWS > MODIFIES > USES (not impmemented yet)
					cout << "evaluting clause " << endl;
					vector<Parameter> cSynList = c->getSynList();
					vector<Parameter> restrictedSynList;
					for (Parameter p : cSynList)
						if (gResultTable.isSynInTable(p)) {
							restrictedSynList.push_back(p);
						}

					ResultTable queryResult = c->evaluate(pkb, gResultTable.select(restrictedSynList));
					gResultTable.join(queryResult);
					cout << "After join table is " << endl;
					gResultTable.printTable();
					/*
					IMPROVEMENT: FOR EACH NEW SYNONYM ADDED, CHECK WHETHER CLAUSE CONTAINS
					THAT SYNONYM ONLY, IF YES, EVALUATE AND MERGE.
					*/
				}
			}

		}

	}

	// now, evaluate and merge the deprioritized list 
	cout << "---Deprioritized Clause---" << endl;
	for (Clause* c : gDeprioritizedClauseList) {
		printClause(c);
		vector<Parameter> cSynList = c->getSynList();
		vector<Parameter> restrictedSynList;
		for (Parameter p : cSynList)
			if (gResultTable.isSynInTable(p)) {
				restrictedSynList.push_back(p);
			}

		ResultTable queryResult = c->evaluate(pkb, gResultTable.select(restrictedSynList));
		gResultTable.join(queryResult);
	}

	cout << "FINAL TABLE FOR GROUP " << endl;
	gResultTable.printTable();

	return gResultTable;
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
		for (int k : pkb->getAllConst())
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
	resTable.join(rt);
	cout << "after joining, the table is " << endl;
	resTable.printTable();
	cout << endl;
}

void QueryEvaluator::printClause(Clause* c)
{
	string str;
	str += c->getClauseType();
	str = str + "(" + c->getLeftChild().getParaName() + ", " + c->getRightChild().getParaName() + ")";
	cout << "Clause is " << str << endl;
}
