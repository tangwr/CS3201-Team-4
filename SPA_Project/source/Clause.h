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

/*
This is the interface that acts as a command. All clauses will implement
this interface so that the invoker does not need to know anything concrete
about a specific command, except the interface.
*/
class Clause {
public:
	/*
	Returns the arguments of the clause

	@return: the list of arguments in the clause
	*/
	virtual vector<Parameter> getSynList() = 0;
	/*
	Returns the clause type
	@return: the clause type
	*/
    virtual ClauseType getClauseType() = 0;
	/*
	Returns results of the clause

	@pkb: the storage from which we retrieve information
	@intResultTable: the table that stores intermediate results
	@return: the table which contains the results of the clause
	*/
	virtual ResultTable* evaluate(PKB* pkb, ResultTable* intResultTable) = 0;
};
#endif
