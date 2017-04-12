#pragma once
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <iterator>
#include "ResultTable.h"
#include "QueryTree.h"

using namespace std;

/*
Query evaluator is the component to evaluate a given PQL query.
After the PQL Query is parsed into queryTree by query parser,
Controller will interact with Query Evaluator to evaluate the query.
*/
class QueryEvaluatorStub {

public:
	QueryEvaluatorStub();
	QueryEvaluatorStub(PKB* pkbSource);

	/*
	set the pkb source for query evaluator

	@pkbInput: pkb souuce
	@return: none
	*/
	void setPKB(PKB* pkbInput);

	/*
	perform evaluation to the query and return the final result
	as a resultTable

	@qt: queryTree containing information of PQL query
	@return: resultTable containing the result of query
	*/
	ResultTable* evaluate(QueryTree qt);


private:
	PKB* pkb;
	ResultTable* resTable;

	/*
	Version 1 Optimization Query Evaluator
	*/
	ResultTable* evaluateWithOptimization2(QueryTree qt);

	/*
	Version 1 Optimization Evaluator for a synonym group
	*/
	ResultTable* evaluateGroup2(vector<Parameter> usedSynList, vector<Clause*> clauseList, vector<Clause*> clause1SynList, vector<ResultTable*> clause1SynResult);
	ResultTable* getAllValueForSyn(Parameter param);
	ResultTable* createEarlyTerminationTable(QueryTree qt);
	//void printClause(Clause* c);
};









