#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "QueryTree.h"
#include "ModifiesTable.h"
#include "UsesTable.h"
#include "ParentsTable.h"
#include "FollowsTable.h"


class QueryEvaluator {
private:
	std::string getLeftValue(std::string);
	std::string getRightValue(std::string);
	std::string removeSpaces(std::string);
	int getDelimPos(std::string, char);
	std::string dummy = "unknown";
	std::list<std::string> evaluateQuery(QueryTree);
	bool validateQuery(<datatype_table>, std::string);

public:
	QueryEvaluator();
	std::list<std::string> evaluate(QueryTree);
	
	
};
