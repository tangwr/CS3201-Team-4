#pragma once

#include <string>
#include <list>

#include "PKB.h"
#include "ResultTable.h"

using namespace std;

class QueryPostProcessor {
public:
	QueryPostProcessor(PKB* pkb);
	list<string> processResult(ResultTable result);

private:
	PKB *pkb;

	list<string> formatBoolResult(ResultTable result);
	list<string> formatVarResult(ResultTable result);
	list<string> formatConstResult(ResultTable result);
	list<string> formatStmtResult(ResultTable result);
};