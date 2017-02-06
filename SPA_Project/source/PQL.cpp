#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

#include "PQL.h"
#include "QueryParser.h"
#include "QueryTree.h"
//#include "QueryEvaluator.h"
//#include "QueryForamtter.h"

PQL::PQL(PKB *pkbSource){
	pkb = pkbSource;
}

QueryTree PQL::getQuery(string query) {
	QueryParser qp;
	QueryTree qt;
	if(qp.isValid(query)) {
		qt = qp.getQuery();
	}
	else {
		cout<<"invalid query";
	}
	return qt;
}
/*
std::list<string> PQL::evaluate(PKB *pkb,QueryTree qt){
	QueryEvaluator qe = new QueryEvaluator(pkb);
	std::list<string> result;
	result = qe.evaluate(qt);
	return result;
}

std::list<string> PQL::getResult(std::list<string> rs) {
	std::list<string> result;
	QueryForamtter qf = new QueryForamtter();
	result = qf.format(rs);
	return result;
}
*/
