#ifndef FollowH
#define FollowH

#include <string>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "unordered_set"
#include "ResultTable.h"

using namespace std;

class Follow : public Clause {

public:
	Follow(Parameter lc, Parameter rc);
	vector<Parameter> getSynList();
	ResultTable evaluate(PKB* pkb, ResultTable resultTable);
	ClauseType getClauseType();

private:

	Parameter leftChild;
	Parameter rightChild;
	ResultTable result;
	vector<Parameter> synList;
	void setSynList();
	
	/*
	inserts the result tuple into the result table

	@left: the left value of the tuple
	@right: the right value of the tuple
	*/
	void insertTuple(int left, int right);

	/*
	Checks if the parameter is the is a synonym, 
	returns true if it is, false otherwise.

	@parameter: the parameter to be checked
	@return: whether the argument is a synonym
	*/
	bool isSynonym(Parameter parameter);
	bool isBooleanClause();
	/*
	Checks if the argument is the clause's left parameter, 
	returns true if it is, false otherwise.

	@parameter: the parameter to be checked
	@return: whether the argument is the left parameter
	*/
	bool isLeftChild(Parameter parameter);
	/*
	Checks if the argument any of the elements in the left list
	is followed by any elements in the right list. Returns true 
	if there exists one such valid relationship, false otherwise

	@pkb: the storage from which we retrieve information
	@left: the left list
	@right: the right list
	@return: whether any elements in the left list is followedBy any
			elements in the right list
	*/
	bool isFollows(PKB* pkb, unordered_set<int> left, unordered_set<int> right);
	/*
	returns a list of statements based on the argument parameter

	@pkb: the storage from which we retrieve information
	@p: the parameter
	@return: the list of statements
	*/
	unordered_set<int> getTypeStmt(Parameter p, PKB* pkb);
	/*
	Returns the list of tuples where the left value is followedBy 
	the right value	based on the intermediate results.

	@pkb: the storage from which we retrieve information
	@resultTable: the table which stores the intermediate results
	@return: the table which contains the results
	*/
	ResultTable getFollowSynSyn(PKB* pkb, ResultTable* resultTable);
	/*
	Returns the list of tuples where any statement in the left list
	is followedBy any statement in the right list

	@pkb: the storage from which we retrieve information
	@left: the left list
	@right: the right list
	@return: the table which contains the list of tuples
	*/
	ResultTable getFollow(PKB* pkb, unordered_set<int> left, unordered_set<int> right);

};
#endif