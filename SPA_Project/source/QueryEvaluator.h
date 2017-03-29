#pragma once
//#ifndef QueryEvaluatorH
//#define QueryEvaluatorH
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <iterator>
#include "QueryTree.h"
#include "PKB.h"
#include "Clause.h"
#include "VectorSetOperation.h"
#include "Modifies.h"
#include "Uses.h"
#include "Pattern.h"

using namespace std;

class QueryEvaluator {

public:
	QueryEvaluator();
	void setPKB(PKB* pkbInput);
	QueryEvaluator(PKB* pkbSource);
	ResultTable evaluate(QueryTree qt);

private:
	PKB* pkb;
	ResultTable resTable;
	ResultTable evaluateGroup(vector<Parameter> usedSynList, vector<Clause*> clauseList, vector<Clause*> clause1SynList, vector<ResultTable> clause1SynResult);
	ResultTable getAllValueForSyn(Parameter param);
	void joinResultTable(ResultTable rt);
	void printClause(Clause* c);
	ResultTable evaluateWithOptimization(QueryTree qt);
	ResultTable evaluateWithoutOptimization(QueryTree qt);
};









