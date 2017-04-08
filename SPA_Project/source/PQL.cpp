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
	delete preProcessor;
}

list<string> PQL::evaluateQuery(string querySource) {
	string test = "procedure p1; assign a2; variable v3; stmt s; while w; if ifs; Select a2 such that Next*(a2, w) and Modifies(a2, v3)";
	const string ERROR_SELECT_BOOLEAN = "The result is false";
	const int EQUAL = 0;
	const string FALSE = "FALSE";
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
		if (msg.compare(ERROR_SELECT_BOOLEAN) == EQUAL) {
			list<string> boolResult;
			boolResult.push_back(FALSE);
			return boolResult;
		}
		else {
			return list<string>();
		}
	}

	ResultTable result = evaluator->evaluate(queryTree);
	list<string> resultList = postProcessor->processResult(result);
	return resultList;
}
