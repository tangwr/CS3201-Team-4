#pragma once

#include <string>

#include "PKB.h"
#include "Result.h"

using namespace std;

const string STRING_TRUE = "true";
const string STRING_FALSE = "false";
const string STRING_COMMA = ", ";
const string STRING_EMPTY = "";

const int FIRST_INDEX = 0;
const int SECOND_INDEX = 1;

class PostProcessor {
public:
	PostProcessor(PKB* pkb);
	string processResult(Result result);

private:
	PKB *pkb;

	string formatBoolResult(Result result);
	string formatVarResult(Result result);
	string formatConstResult(Result result);
	string formatStmtResult(Result result);
};