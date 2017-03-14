#pragma once
#include <string>
#include <list>

using namespace std;

#include "PKB.h"

#include "QueryParser.h"
#include "QueryEvaluator.h"
#include "QueryPostProcessor.h"

#include "QueryTree.h"
#include "ResultTable.h"

class PQL {
private:
	PKB *pkb;
	QueryParser preProcessor;
	QueryEvaluator *evaluator;
	QueryPostProcessor *postProcessor;

public:
	PQL(PKB *pkb);
	~PQL();
	list<string> evaluateQuery(string querySource);
};