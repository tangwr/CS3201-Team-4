#ifndef ClauseH
#define ClauseH

#include <string>
#include <list>
#include <unordered_map>

#include "Type.h"
#include "ClauseType.h"
#include "PKB.h"
#include "Parameter.h"
#include "ResultTable.h"

using namespace std;

class Clause {
public:
	virtual vector<Parameter> getSynList() = 0;
	virtual Parameter getLeftChild() = 0;
	virtual Parameter getRightChild() = 0;
    virtual ClauseType getClauseType() = 0;
	virtual ResultTable evaluate(PKB* pkb, ResultTable intResultTable) = 0;
};
#endif
