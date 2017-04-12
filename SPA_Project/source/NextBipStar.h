#ifndef NextBipStarH
#define NextBipStarH

#include <string>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "unordered_set"
#include <stack>
#include "ResultTable.h"

using namespace std;

class NextBipStar : public Clause {

public:
	NextBipStar(Parameter lc, Parameter rc);
	vector<Parameter> getSynList();
	ClauseType getClauseType();
	ResultTable* evaluate(PKB* pkb, ResultTable* intResultTable);

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
	bool isSynonym(Parameter);
	/*
	Checks if the argument is the clause's left parameter,
	returns true if it is, false otherwise.

	@parameter: the parameter to be checked
	@return: whether the argument is the left parameter
	*/
	bool isLeftChild(Parameter);
	/*
	Checks if the argument any of the elements in the left list 
	is executed before any elements in the right list. Returns 
	true if	there exists one such valid relationship, false otherwise

	@pkb: the storage from which we retrieve information
	@left: the left list
	@right: the right list
	@return: whether any elements in the left list is executed before 
			 any elements in the right list
	*/
	bool isNextBipStar(PKB* pkb, unordered_set<int> left, unordered_set<int> right);
	void setSynList();
	/*
	inserts the result tuple into the result table

	@left: the left value of the tuple
	@right: the right value of the tuple
	*/
	void insertTuple(int left, int right);
	void getAllNextBipStar(int prev, unordered_set<int>* allNextBipStar, PKB* pkb);
	void getAllNextBipStar(int curr, unordered_set<int>* allNextBipStar, unordered_set<int>* visited, stack<int> callingStmts, PKB* pkb, int count);
	void computeLastBip(int curr, unordered_set<int>* allNextBip, PKB* pkb);
	unordered_set<int> getNextStmt(int a, PKB* pkb);
	unordered_set<int> computeNextBip(int curr, PKB* pkb);
	/*
	returns a list of statements based on the argument parameter

	@pkb: the storage from which we retrieve information
	@p: the parameter
	@return: the list of statements
	*/
	unordered_set<int> getTypeStmt(Parameter p, PKB* pkb);
	/*
	Returns the list of tuples where the left value is executed
	before the right value based on the intermediate results.

	@pkb: the storage from which we retrieve information
	@resultTable: the table which stores the intermediate results
	@return: the table which contains the results
	*/
	void getNextBipStarSynSyn(PKB* pkb, ResultTable* resultTable);
	void isNextBipStarItself(PKB* pkb, unordered_set<int> stmts);
	/*
	Returns the list of tuples where any statement in the left list
	is executed before any statement in the right list

	@pkb: the storage from which we retrieve information
	@left: the left list
	@right: the right list
	@return: the table which contains the list of tuples
	*/
	void getNextBipStar(PKB* pkb, unordered_set<int> left, unordered_set<int> right);
};
#endif
