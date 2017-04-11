#ifndef NextH
#define NextH

#include <string>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include <stack>
#include "unordered_set"
#include "ResultTable.h"

using namespace std;

class Next : public Clause {

public:
	Next(Parameter lc, Parameter rc);
	ResultTable evaluate(PKB* pkb, ResultTable resultTable);
	vector<Parameter> getSynList();
	ClauseType getClauseType();

private:

	Parameter leftChild;
	Parameter rightChild;
	ResultTable result;
	bool isBooleanClause();
	/*
	Checks if the parameter is the is a synonym,
	returns true if it is, false otherwise.

	@parameter: the parameter to be checked
	@return: whether the argument is a synonym
	*/
	bool isSynonym(Parameter parameter);
	/*
	Checks if the argument is the clause's left parameter,
	returns true if it is, false otherwise.

	@parameter: the parameter to be checked
	@return: whether the argument is the left parameter
	*/
	bool isLeftChild(Parameter parameter);
	/*
	Checks if the argument any of the elements in the left list is 
	executed immediately before	any elements in the right list. Returns 
	true if	there exists one such valid relationship, false otherwise

	@pkb: the storage from which we retrieve information
	@left: the left list
	@right: the right list
	@return: whether any elements in the left list is executed immediately 
			before any elements in the right list
	*/
	bool isNext(PKB* pkb, unordered_set<int> left, unordered_set<int> right);
	void setSynList();
	/*
	inserts the result tuple into the result table

	@left: the left value of the tuple
	@right: the right value of the tuple
	*/
	void insertTuple(int left, int right);
	vector<Parameter> synList;
	/*
	Returns a list of statements executed immediately after
	a statement such that the list of statements do not contain
	any dummy statements that connects if else.

	@pkb: the storage from which we retrieve information
	@a: the statement which we want to retrieve the next statements of
	@return: the list of statements executed after the argument statement
	*/
	unordered_set<int> getNextStmt(int a, PKB* pkb);
	/*
	Returns a list of statements executed immediately before
	a statement such that the list of statements do not contain
	any dummy statements that connects if else.

	@pkb: the storage from which we retrieve information
	@a: the statement which we want to retrieve the previous of
	@return: the list of statements executed before the argument statement
	*/
	unordered_set<int> getPreviousStmt(int a, PKB* pkb);
	/*
	returns a list of statements based on the argument parameter

	@pkb: the storage from which we retrieve information
	@p: the parameter
	@return: the list of statements
	*/
	unordered_set<int> getTypeStmt(Parameter p, PKB* pkb);
	/*
	Returns the list of tuples where the left value is executed
	immediately before the right value based on the intermediate results.

	@pkb: the storage from which we retrieve information
	@resultTable: the table which stores the intermediate results
	@return: the table which contains the results
	*/
	ResultTable getNextSynSyn(PKB* pkb, ResultTable* resultTable);
	/*
	Returns the list of tuples where any statement in the left list
	is executed immediately before any statement in the right list

	@pkb: the storage from which we retrieve information
	@left: the left list
	@right: the right list
	@return: the table which contains the list of tuples
	*/
	ResultTable getNext(PKB* pkb, unordered_set<int> left, unordered_set<int> right);

};
#endif
