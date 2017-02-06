#pragma once

#include <string>
#include <list>

#include "PKB.h"
#include "Result.h"

using namespace std;

const string STRING_TRUE = "true";
const string STRING_FALSE = "false";

const int INITIAL_INDEX = 0;

class PostProcessor {
public:
	PostProcessor(PKB* pkb);
	list<string> processResult(Result result);

private:
	PKB *pkb;

	list<string> formatBoolResult(Result result);
	list<string> formatVarResult(Result result);
	list<string> formatConstResult(Result result);
	list<string> formatStmtResult(Result result);
};