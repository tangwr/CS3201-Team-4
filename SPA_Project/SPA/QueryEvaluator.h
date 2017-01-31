#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "QueryTree.h"

class QueryEvaluator {
private:
	std::string dummy = "unknown";
	std::list<std::string> evaluateQuery(QueryTree);
	bool validateQuery(<datatype_table>, std::string);

public:
	QueryEvaluator();
	std::list<std::string> evaluate(QueryTree);
	
	
};
