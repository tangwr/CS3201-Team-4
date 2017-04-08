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
	string test2 = "stmt s; Select BOOLEAN such that Follows(s, a)";
	const int EQUAL = 0;
	const string FALSE = "FALSE";
	QueryTree queryTree;

	try {
		queryTree = preProcessor->parse(querySource);
	}
	catch (const logic_error& e) {
		//cerr <<e.what();
		list<string> boolResult;
		boolResult.push_back(FALSE);
		return boolResult;
	}
	catch (string msg) {
		//cerr << "\n The error is: " + msg;
	    	return list<string>();
	}

	ResultTable result = evaluator->evaluate(queryTree);
	list<string> resultList = postProcessor->processResult(result);
	return resultList;
}
