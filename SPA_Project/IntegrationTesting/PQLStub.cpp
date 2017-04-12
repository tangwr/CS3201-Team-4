#pragma once
#include "stdafx.h"
#include<stdio.h>
#include <iostream>
#include <string>
#include "PQLStub.h"
#define FALSE_OUTPUT "FALSE"

PQLStub::PQLStub(PKB *pkbSource) {
	pkb = pkbSource;
	preProcessor = new QueryParser();
	evaluator = new QueryEvaluatorStub(pkb);
	postProcessor = new QueryPostProcessor(pkb);
}

PQLStub::~PQLStub() {
	delete evaluator;
	delete preProcessor;
	delete postProcessor;
}

list<string> PQLStub::evaluateQuery(string querySource) {
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

	ResultTable *result = evaluator->evaluate(queryTree);
	list<string> resultList = postProcessor->processResult(result);
	return resultList;
}
