#ifndef QueryParser
#include <string>
#include <list>
#include <vector>
#include <unordered_map>

#include "QueryTree.h"

; using namespace std;

class QueryParser {
private:
	unordered_map<string, string> varMap;
	QueryTree queryTree;


	bool isValidDeclaration(string declaration);
	bool isValidQuery(string query);
	
	bool checkRelation(string subquery);
	bool checkChildren(string relType, vector<string> arrVariable);

	bool checkPattern(string relType, string syn, Type synType, string subquery);
	bool checkPattern2(string subquery);

	bool isValidVarName(string varName);
	bool isVarNameExists(string varName);

	string getVarType(string varName);
	bool isStringVar(string str);
	bool isInteger(string str);
	bool isPositiveInteger(string str);


	vector<string> QueryParser::splitTheString(string str, char c);
	vector<string> QueryParser::splitTheStringIntoParts(string str, char c, int num);
	string QueryParser::trim(string content);
	string QueryParser::removeSpaces(string line);
	string stringToLower(string str);
	
	//vector<string> parseExpression(string expression);
	//bool isValidExpression(string expression);
	
	Type getTypeOfChild(string input);
	bool isBothUnderScore(string str);
	bool isStringExpression(string str);

public:
	QueryParser();
	bool isValid(string query);
	QueryTree getQuery(); 
};
#endif