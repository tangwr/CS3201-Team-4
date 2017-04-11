#pragma once

#include <string>
#include <list>

#include "PKB.h"
#include "PQL.h"

using namespace std;

class Controller {
public:
	Controller();
	/**
	* Takes in the source code in string to set the relavant information into the PKB.
	* Program will be terminated if there is error found in source code
	*
	* @param sourceCode    string form of the source code
	*/
	void processSource(string sourceCode);
	/**
	* Return the result of the query.
	* If there is error found in query, it would return an empty list.
	* If it is a BOOLEAN query, a string of "true"/"false" will be return.
	*
	* @param querySource    string form of the query
	* @return    a list of string containing the results of the query
	*/
	list<string> processQuery(string querySource);
	~Controller();

private:
	PKB *pkb;
	PQL *pql;
};