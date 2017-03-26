#include<stdio.h>
#include <iostream>
#include <string>

#include "PQL.h"

PQL::PQL(PKB *pkbSource) {
	pkb = pkbSource;
	preProcessor = new QueryParser();
	evaluator = new QueryEvaluator(pkb);
	postProcessor = new QueryPostProcessor(pkb);
}

PQL::~PQL() {
	delete evaluator;
	delete postProcessor;
}

list<string> PQL::evaluateQuery(string querySource) {
	string test = "procedure p1; assign a2; variable v3; stmt s; while w; if ifs; Select a2 such that Next*(a2, w) and Modifies(a2, v3)";
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
	try {
		queryTree = preProcessor->parse(querySource);
	}
	catch (string msg) {
		cerr << "\n error is: " + msg << endl;
		return list<string>();
	}

	ResultTable result = evaluator->evaluate(queryTree);
	list<string> resultList = postProcessor->processResult(result);
	return resultList;
}
