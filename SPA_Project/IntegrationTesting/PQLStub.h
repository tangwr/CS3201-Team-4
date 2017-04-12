#pragma once
#include <string>
#include <list>

using namespace std;

#include "PKB.h"

#include "QueryParser.h"
#include "QueryEvaluatorStub.h"
#include "QueryPostProcessor.h"

#include "QueryTree.h"
#include "ResultTable.h"

class PQLStub {
public:
	PQLStub(PKB *pkb);
	~PQLStub();
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
	QueryEvaluatorStub *evaluator;
	QueryPostProcessor *postProcessor;
};
