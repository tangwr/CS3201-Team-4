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
#include "ClauseType.h"
#include "Modifies.h"




using namespace std;

class QueryEvaluator {

public:
	QueryEvaluator();
	void setPKB(PKB* pkbInput);
	QueryEvaluator(PKB*);
	vector<int> evaluate(QueryTree);

private:
	PKB* pkb;

	bool evaluateUnlimitList(vector<Clause*>);
	vector<int> evaluateLimitList(vector<Clause*>, Type);
	vector<int> QueryEvaluator::getAllSelectResults(Type);

	vector<int> getIntersection(vector<int>, vector<int>);
	vector<int> getUnion(vector<int>, vector<int>);

	////
	list<int> getUnionList(list<int>, list<int>);

	
};









