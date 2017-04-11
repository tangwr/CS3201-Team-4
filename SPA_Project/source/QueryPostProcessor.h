#pragma once

#include <string>
#include <list>

#include "PKB.h"
#include "ResultTable.h"

using namespace std;

class QueryPostProcessor {
public:
	QueryPostProcessor(PKB* pkb);
	/**
	* take in the resultTable and process the result to the list of string
	*
	* @param the ResultTable object
	* @return the processed result in a list of string
	*/
	list<string> processResult(ResultTable result);

private:
	PKB *pkb;
	string processSingleResult(vector<int> vectorInt, vector<Parameter> select);
	string processResultType(int value, Type valueType, bool attribute);
	string formatBoolResult(bool result);
	string formatVarResult(int result);
	string formatConstResult(int result);
	string formatStmtResult(int value);
	string formatProcedureResult(int value);
	string formatCallResult(int value , bool attribute);
};
