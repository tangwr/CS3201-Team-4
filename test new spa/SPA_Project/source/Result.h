#pragma once

#include <vector>

#include "Type.h"

using namespace std;

class Result {
public:
	Result();
	Result(vector<int> vectorResult, Type selectType, bool boolResult = true);
	bool setResultVector(vector<int> vectorResult);
	bool setResultType(Type selectType);
	bool setResultBool(bool boolResult);

	vector<int> getResultVector();
	Type getResultType();
	bool getResultBool();

private:
	vector<int> resultVector;
	Type resultType;
	bool resultBool;
};