#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include "PQL.h"
#define FALSE_OUTPUT "FALSE"

PQL::PQL(PKB *pkbSource) {
	pkb = pkbSource;
	preProcessor = new QueryParser();
	evaluator = new QueryEvaluator(pkb);
	postProcessor = new QueryPostProcessor(pkb);
}

PQL::~PQL() {
	delete evaluator;
	delete preProcessor;
	delete postProcessor;
}

list<string> PQL::evaluateQuery(string querySource) {
	QueryTree queryTree;

	try {
		queryTree = preProcessor->parse(querySource);
	}
	catch (const logic_error& e) {
		list<string> boolResult;
		boolResult.push_back(FALSE_OUTPUT);
		return boolResult;
	}
	catch (const runtime_error& e) {
	    return list<string>();
	}

	ResultTable result = evaluator->evaluate(queryTree);
	list<string> resultList = postProcessor->processResult(result);
	return resultList;
}
