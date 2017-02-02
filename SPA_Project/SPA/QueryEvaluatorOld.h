#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <unordered_map>

using namespace std;


enum clauseString{
	MODIFIES,
	USES,
	PARENT,
	PARENT_S,
	FOLLOW,
	FOLLOW_S
};

enum varType {
	STR,
	INT,
	STMT,
	ASSIGN,
	WHILE,
	VARIABLE
};

enum declareType {
	STMT,
	ASSIGN,
	WHILE,
	VARIABLE,
	UNKNOWN,
	STR,
	INT
};


class QueryEvaluator {
private:
	std::string getLeftValue(std::string);
	std::string getRightValue(std::string);
	std::string removeSpaces(std::string);
	bool isInteger(std::string);
	int getDelimPos(std::string, char);
	bool checkCondition(std::string, std::string, std::string, declareType, declareType);
	bool checkModifies(std::string, std::string, declareType, declareType);
	bool checkUses(std::string, std::string, declareType, declareType);
	bool checkParent(std::string, std::string, declareType, declareType);
	bool checkParent_s(std::string, std::string, declareType, declareType);
	bool checkFollow(std::string, std::string, declareType, declareType);
	bool checkFollow_s(std::string, std::string, declareType, declareType);
	clauseString getClauseType(std::string);

	////////////////////////////////////////////////
	std::string dummy = "unknown";
	std::list<std::string> evaluateQuery(QueryTree);
	bool validateQuery(<datatype_table>, std::string);

public:
	QueryEvaluator();
	std::list<std::string> evaluate(QueryTree);
	
	
};
