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
public:
	PQL(PKB *pkb);
	~PQL();
	/**
	* Take in the query and evaluate it
	*
	* @param query string from queries code
	* @return a list of string which contains the result
	* @throws if the query is invalid, the corresponding exception
	* will be thrown
	*/
	list<string> evaluateQuery(string querySource);

private:
	PKB *pkb;
	QueryParser *preProcessor;
	QueryEvaluator *evaluator;
	QueryPostProcessor *postProcessor;
};
