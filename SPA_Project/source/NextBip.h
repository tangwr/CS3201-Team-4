#ifndef NextBipH
#define NextBipH

#include <string>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include <stack>
#include "unordered_set"
#include "ResultTable.h"

using namespace std;

class NextBip : public Clause {

public:
	NextBip(Parameter lc, Parameter rc);
	ResultTable* evaluate(PKB* pkb, ResultTable* resultTable);
	vector<Parameter> getSynList();
	ClauseType getClauseType();

private:

	Parameter leftChild;
	Parameter rightChild;
	ResultTable result;
	vector<Parameter> synList;
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
	executed immediately before any elements in the right list. Returns 
	true if	there exists one such valid relationship, false otherwise

	@pkb: the storage from which we retrieve information
	@left: the left list
	@right: the right list
	@return: whether any elements in the left list is executed immediately 
			before any elements in the right list
	*/
	bool isNextBip(PKB* pkb, unordered_set<int> left, unordered_set<int> right);
	void setSynList();
	/*
	inserts the result tuple into the result table

	@left: the left value of the tuple
	@right: the right value of the tuple
	*/
	void insertTuple(int left, int right);
	void DFS(int currStmt, unordered_set<int>* lastStmts, unordered_set<int>* visited, PKB* pkb);
	void computeLastBip(int curr, unordered_set<int>* allNextBip, PKB* pkb);
	/*
	Returns the list of tuples where the left value is executed
	immediately before the right value based on the intermediate results.

	@pkb: the storage from which we retrieve information
	@resultTable: the table which stores the intermediate results
	@return: the table which contains the results
	*/
	void getNextBipSynSyn(PKB* pkb, ResultTable* resultTable);
	/*
	Returns the list of tuples where any statement in the left list
	is executed immediately before any statement in the right list

	@pkb: the storage from which we retrieve information
	@left: the left list
	@right: the right list
	@return: the table which contains the list of tuples
	*/
	void getNextBip(PKB* pkb, unordered_set<int> left, unordered_set<int> right);
	/*
	returns a list of statements based on the argument parameter

	@pkb: the storage from which we retrieve information
	@p: the parameter
	@return: the list of statements
	*/
	unordered_set<int> getTypeStmt(Parameter p, PKB* pkb);
	unordered_set<int> getNextStmt(int a, PKB* pkb);
	unordered_set<int> computeNextBip(int curr, PKB* pkb);
	unordered_set<int> computePrevBip(int curr, PKB* pkb);
	unordered_set<int> getLastStmts(int procId, PKB* pkb);
};
#endif
