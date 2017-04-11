#ifndef NextStarH
#define NextStarH

#include <string>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "unordered_set"
#include "ResultTable.h"

using namespace std;

class NextStar : public Clause {
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
	executed before	any elements in the right list. Returns true if
	there exists one such valid relationship, false otherwise

	@pkb: the storage from which we retrieve information
	@left: the left list
	@right: the right list
	@return: whether any elements in the left list is executed  
			before any elements in the right list
	*/
	bool isNextStar(PKB* pkb, unordered_set<int> left, unordered_set<int> right);
	void setSynList();
	/*
	inserts the result tuple into the result table

	@left: the left value of the tuple
	@right: the right value of the tuple
	*/
	void insertTuple(int left, int right);
	vector<Parameter> synList;
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
	ResultTable getNextStarSynSyn(PKB* pkb, ResultTable* resultTable);
	/*
	compute the list of statements that can be executed after itself

	@pkb: the storage from which we retrieve information
	@stmts: the stmts that we want to check that can be executed after themselves
	@return: the table which contains the list of statements that can be executed
			after themselves
	*/
	ResultTable isNextStarItself(PKB* pkb, unordered_set<int> stmts);
	/*
	Returns the list of tuples where any statement in the left list
	is executed before any statement in the right list

	@pkb: the storage from which we retrieve information
	@left: the left list
	@right: the right list
	@return: the table which contains the list of tuples
	*/
	ResultTable getNextStar(PKB* pkb, unordered_set<int> left, unordered_set<int> right);
	/*
	Creates a visited set to use in the computation of next* statements

	@pkb: the storage from which we retrieve information
	@allNextStar: the set which to store the next* statements in
	@prev: the statement which we want to retrieve the next* statements of
	*/
	void getAllNextStar(int prev, unordered_set<int>* allNextStar, PKB* pkb);
	/*
	Uses depth-first-search to compute all next* statements

	@prev: the statement which we want to retrieve the next* statements of
	@allNextStar: the set which to store the next* statements in
	@visited: the list of statements that have been traversed before
	@pkb: the storage from which we retrieve information
	*/
	void getAllNextStar(int prev, unordered_set<int>* allNextStar, unordered_set<int>* visited, PKB* pkb);
	/*
	Creates a visited set to use in the computation of 
	previous*(statements executed before a statement) statements

	@pkb: the storage from which we retrieve information
	@allPrevStar: the set which to store the previous* statements in
	@next: the statement which we want to retrieve the previous* statements of
	*/
	void getAllPrevStar(int next, unordered_set<int>* allPrevStar, PKB* pkb);
	/*
	Uses depth-first-search to compute all previous* statements

	@next: the statement which we want to retrieve the previous* statements of
	@allPrevStar: the set which to store the previous* statements in
	@visited: the list of statements that have been traversed before
	@pkb: the storage from which we retrieve information
	*/
	void getAllPrevStar(int next, unordered_set<int>* allPrevStar, unordered_set<int>* visited, PKB* pkb);
	
public:
	NextStar(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	vector<Parameter> getSynList();
	ClauseType getClauseType();
	ResultTable evaluate(PKB* pkb, ResultTable intResultTable);
};
#endif
