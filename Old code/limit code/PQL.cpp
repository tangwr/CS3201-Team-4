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

	Parameter leftPara = Parameter("3", WHILE);
	Parameter rightPara = Parameter("v", VARIABLE);
	
	Uses mod(leftPara, rightPara);
	vector<Parameter> vp;
	vector<vector<int>> value;
	mod.setPKB(pkb);

	ResultTable rt;
	rt = mod.evaluate(pkb, vp, value);

	//2
	leftPara = Parameter("3", WHILE);
	rightPara = Parameter("b", ANYTHING);

	Uses mod1(leftPara, rightPara);
	mod1.setPKB(pkb);
	rt = mod1.evaluate(pkb, vp, value);

	//3
	leftPara = Parameter("3", WHILE);
	rightPara = Parameter("b", STRINGVARIABLE);

	Uses mod2(leftPara, rightPara);
	mod2.setPKB(pkb);
	rt = mod2.evaluate(pkb, vp, value);

	//4
	/*
	leftPara = Parameter("3", INTEGER);
	rightPara = Parameter("x", STRINGVARIABLE);

	Uses mod3(leftPara, rightPara);
	mod3.setPKB(pkb);
	rt = mod3.evaluate(pkb, vp, value);
	*/
	/*
	vector<Parameter> synList = rt.getSynList();
	vector<vector<int>> tuple = rt.getTupleList();

	for (Parameter p : synList) {
		cout << p.getParaName() << endl;
		cout << p.getParaType() << endl;
	}

	int tupleSize = tuple.size();
	for (vector<int> tup : tuple) {
		vector<int> vTup = tup;
		int k = 0;
	}

	cout << "pig" << endl;

	int x = pkb->getVarIdByName("x");
	int a = pkb->getVarIdByName("a");
	int b = pkb->getVarIdByName("b");
	int c = pkb->getVarIdByName("c");
	int d = pkb->getVarIdByName("d");
	int e = pkb->getVarIdByName("e");
	int f = pkb->getVarIdByName("f");

	vector<int> v = pkb->getAllVarId();
	cout << "variable: " << v.size() << endl;
	cout << "x: " << x << endl;
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	cout << "c: " << c << endl;
	cout << "d: " << d << endl;
	cout << "e: " << e << endl;
	cout << "f: " << f << endl;

	*/
	//mod.ResultsTable();
	
	


	Result result = evaluator->evaluate(queryTree);
	return postProcessor->processResult(result);
}
