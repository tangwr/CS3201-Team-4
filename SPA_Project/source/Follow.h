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
private:

	Parameter leftChild;
	Parameter rightChild;
	ResultTable result;
	bool isSynonym(Parameter);
	bool isLeftChild(Parameter);
	bool isValidStmtNo(int, PKB*);
	bool isFollows(PKB*, unordered_set<int>, unordered_set<int>);
	unordered_set<int> getTypeStmt(Parameter, PKB*);
	ResultTable getFollowSynSyn(PKB*, ResultTable*);
	vector<Parameter> synList;
	void setSynList();
	void insertTuple(int, int);
	ResultTable getFollow(PKB*, unordered_set<int>, unordered_set<int>);
	bool isBooleanClause();
	/*
	bool isNumber(Parameter);
	bool isRightChild(Parameter);
	bool isFollows(PKB*, int, int);
	ResultTable getFollowNumNum(PKB*, int, int);
	ResultTable getFollowNumSyn(PKB*, unordered_set<int>, int);
	ResultTable getFollowSynNum(PKB*, unordered_set<int>, int);
	ResultTable getFollowSynSyn(PKB*, unordered_set<int>, unordered_set<int>);
	ResultTable evaluateWithoutRestrictions(PKB*);
	ResultTable evaluateWithoutOneRestriction(PKB*, ResultTable*);
	*/
	//bool isBothInt();

public:
	Follow(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	vector<Parameter> getSynList();
	ResultTable evaluate(PKB*, ResultTable);
	ClauseType getClauseType();
};
#endif
