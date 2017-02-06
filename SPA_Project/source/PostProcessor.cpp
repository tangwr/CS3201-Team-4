#include "PostProcessor.h"
#include "Type.h"

PostProcessor::PostProcessor(PKB *pkbSource) {
	pkb = pkbSource;
}

list<string> PostProcessor::processResult(Result result) {
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

list<string> PostProcessor::formatBoolResult(Result result) {
	list<string> resultLists;
	if (result.getResultBool()) {
		resultLists.push_back(STRING_TRUE);
	}
	else {
		resultLists.push_back(STRING_FALSE);
	}
	return resultLists;
}

list<string> PostProcessor::formatVarResult(Result result) {
	list<string> resultLists;
	vector<int> resultVector = result.getResultVector();

	for (int index = INITIAL_INDEX; index < (int)resultVector.size(); index++) {
		resultLists.push_back(pkb->getVarName(resultVector[index]));
	}
	return resultLists;
}

list<string> PostProcessor::formatConstResult(Result result) {
	list<string> resultLists;
	vector<int> resultVector = result.getResultVector();

	for (int index = INITIAL_INDEX; index < (int)resultVector.size(); index++) {
		resultLists.push_back(to_string(pkb->getConstValueById(resultVector[index])));
	}
	return resultLists;
}

list<string> PostProcessor::formatStmtResult(Result result) {
	list<string> resultLists;
	vector<int> resultVector = result.getResultVector();

	string resultStr = to_string(resultVector[INITIAL_INDEX]);
	for (int index = INITIAL_INDEX; index < (int)resultVector.size(); index++) {
		resultLists.push_back(to_string(resultVector[index]));
	}
	return resultLists;
}