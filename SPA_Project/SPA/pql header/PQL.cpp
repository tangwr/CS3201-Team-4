#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

#include "PQL.h"
#include "QueryParser.h"
#include "QueryTree.h"
#include "QueryEvaluator.h"
#include "QueryForamtter.h"

QueryTree PQL::getQuery(String query) {
	QueryParser qp = new QueryParser();
	QueryTree qt = new QueryTree();
	if(qp.isValid(query)) {
		qt = qp.getQuery();
	}
	else {
		print("invalid query");
	}
	return qt;
}

std::list<string> PQL::evaluate(QueryTree qt){
	QueryEvaluator qe = new QueryEvaluator();
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
