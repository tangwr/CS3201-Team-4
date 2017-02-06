#include "Result.h"

Result::Result() {}

Result::Result(vector<int> vectorResult, Type selectType, bool boolResult) {
	resultVector = vectorResult;
	resultType = selectType;
	resultBool = boolResult;
}

bool Result::setResultVector(vector<int> vectorResult) {
	resultVector = vectorResult;
	return true;
}

bool Result::setResultType(Type selectType) {
	resultType = selectType;
	return true;
}

bool Result::setResultBool(bool boolResult) {
	resultBool = boolResult;
	return true;
}

vector<int> Result::getResultVector() {
	return resultVector;
}

Type Result::getResultType() {
	return resultType;
}

bool Result::getResultBool() {
	return resultBool;
}