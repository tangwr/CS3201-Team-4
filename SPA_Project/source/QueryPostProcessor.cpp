#pragma once
#include "QueryPostProcessor.h"
#include "Type.h"
#define STRING_TRUE "TRUE"
#define STRING_FALSE "FALSE"
#define STRING_EMPTY ""
#define SYMBOL_SPACE " "
#define SIZE_ZERO 0
#define START 0
#define LAST 1

QueryPostProcessor::QueryPostProcessor(PKB *pkbSource) {
	pkb = pkbSource;
}

list<string> QueryPostProcessor::processResult(ResultTable* result) {
	vector<Parameter> select = result->getSynList();
	vector<vector<int>> resultVector = result->getTupleList();
	list<string> resultLists;

	if (select.size() == SIZE_ZERO) {
		resultLists.push_back(formatBoolResult(result->getBoolean()));
		return resultLists;
	}

	for (int i = 0; i < resultVector.size(); i++) {
		vector<int> instance = resultVector.at(i);
		string res = processSingleResult(instance, select);
		resultLists.push_back(res);
	}

	delete result;
	return resultLists;
}

string QueryPostProcessor::processSingleResult(vector<int> vectorInt, vector<Parameter> select) {
	string result = STRING_EMPTY;
	for (int i = 0; i < vectorInt.size(); i++) {
		int value = vectorInt.at(i);
		Type vauleType = select.at(i).getParaType();
		bool attribute = select.at(i).getAttributeProc();
		string res = processResultType(value, vauleType, attribute);
		result += res + SYMBOL_SPACE;
	}

	result = result.substr(START, result.size() - LAST);
	return result;
}

string  QueryPostProcessor::processResultType(int value, Type valueType, bool attribute) {
	switch (valueType) {

	case VARIABLE:
		return formatVarResult(value);
		break;

	case CONSTANT:
		return formatConstResult(value);
		break;

	case PROCEDURE:
		return formatProcedureResult(value);
		break;

	case CALL:
		return formatCallResult(value, attribute);
		break;

	default:
		return formatStmtResult(value);
		break;
	}
}

string QueryPostProcessor::formatBoolResult(bool result) {
	if (result) {
		return STRING_TRUE;
	}
	else
	{
		return STRING_FALSE;
	}
}

string QueryPostProcessor::formatVarResult(int result) {
	return pkb->getVarNameById(result);
}

string QueryPostProcessor::formatConstResult(int result) {
	return to_string(result);
}

string QueryPostProcessor::formatStmtResult(int result) {
	return to_string(result);
}

string QueryPostProcessor::formatProcedureResult(int result) {
	return pkb->getProcNameById(result);
}

string QueryPostProcessor::formatCallResult(int result, bool attribute) {
	if (attribute) {
		int id = pkb->getProcCalledByStmt(result);
		return pkb->getProcNameById(id);
	}
	else {
		return to_string(result);
	}
}
