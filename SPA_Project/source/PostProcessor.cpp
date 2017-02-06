#include "PostProcessor.h"
#include "Type.h"

PostProcessor::PostProcessor(PKB *pkbSource) {
	pkb = pkbSource;
}

string PostProcessor::processResult(Result result) {
	switch (result.getResultType()) {
	case BOOLEAN:
		return formatBoolResult(result);
		break;

	case VARIABLE:
		return formatVarResult(result);
		break;

	case CONSTANT:
		return formatConstResult(result);
		break;

	default:
		return formatStmtResult(result);
		break;
	}
}

string PostProcessor::formatBoolResult(Result result) {
	if (result.getResultBool()) {
		return STRING_TRUE;
	}
	else {
		return STRING_FALSE;
	}
}

string PostProcessor::formatVarResult(Result result) {
	vector<int> resultVector = result.getResultVector();
	if (resultVector.empty()) {
		return STRING_EMPTY;
	}

	string resultStr = pkb->getVarName(resultVector[FIRST_INDEX]);
	for (int index = SECOND_INDEX; index < (int)resultVector.size(); index++) {
		resultStr += STRING_COMMA + pkb->getVarName(resultVector[index]);
	}
	return resultStr;
}

string PostProcessor::formatConstResult(Result result) {
	vector<int> resultVector = result.getResultVector();
	if (resultVector.empty()) {
		return STRING_EMPTY;
	}

	string resultStr = to_string(pkb->getConstValueById(resultVector[FIRST_INDEX]));
	for (int index = SECOND_INDEX; index < (int)resultVector.size(); index++) {
		resultStr += STRING_COMMA + to_string(pkb->getConstValueById(resultVector[index]));
	}
	return resultStr;
}

string PostProcessor::formatStmtResult(Result result) {
	vector<int> resultVector = result.getResultVector();
	if (resultVector.empty()) {
		return STRING_EMPTY;
	}

	string resultStr = to_string(resultVector[FIRST_INDEX]);
	for (int index = SECOND_INDEX; index < (int)resultVector.size(); index++) {
		resultStr += STRING_COMMA + to_string(resultVector[index]);
	}
	return resultStr;
}