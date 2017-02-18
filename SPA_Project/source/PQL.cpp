#include<stdio.h>
#include <iostream>
#include <string>

#include "PQL.h"

PQL::PQL(PKB *pkbSource) {
	pkb = pkbSource;
	evaluator = new QueryEvaluator(pkb);
	postProcessor = new QueryPostProcessor(pkb);
}

PQL::~PQL() {
	delete evaluator;
	delete postProcessor;
}

list<string> PQL::evaluateQuery(string querySource) {
	QueryTree queryTree;
	/*
	if (preProcessor.isValid(querySource)) {
		queryTree = preProcessor.getQuery();
	}
	else {
		cout << "invalid query";
		return list<string>();
	}
	*/
	Result result = evaluator->evaluate(queryTree);
	return postProcessor->processResult(result);
}
