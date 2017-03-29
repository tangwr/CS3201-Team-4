#include "QueryPostProcessor.h"
#include "Type.h"

const string STRING_TRUE = "true";
const string STRING_FALSE = "false";
const string SYMBOL_SPACE = " ";
const int SIZE_ZERO = 0;
//const int INITIAL_INDEX = 0;

QueryPostProcessor::QueryPostProcessor(PKB *pkbSource) {
	pkb = pkbSource;
}

list<string> QueryPostProcessor::processResult(ResultTable result) {
	vector<Parameter> select = result.getSynList();
	vector<vector<int>> resultVector = result.getTupleList();
	list<string> resultLists;

	if (select.size() == SIZE_ZERO) {
		resultLists.push_back(formatBoolResult(result.getBoolean()));
		return resultLists;
	}

	for (int i = 0; i < resultVector.size(); i++) {
		vector<int> instance = resultVector.at(i);
		string res = processSingleResult(instance, select);
		resultLists.push_back(res);
	}

	return resultLists;
}

string QueryPostProcessor::processSingleResult(vector<int> vectorInt, vector<Parameter> select) {
	string result = "";
	for (int i = 0; i < vectorInt.size(); i++) {
		int value = vectorInt.at(i);
		Type vauleType = select.at(i).getParaType();
		bool attribute = select.at(i).getAttributeProc();
		string res = processResultType(value, vauleType, attribute);
		result += res + SYMBOL_SPACE;
	}

	result = result.substr(0, result.size() - 1);
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
