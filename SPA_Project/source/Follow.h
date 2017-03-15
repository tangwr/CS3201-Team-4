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
	bool isNumber(Parameter);
	bool isSynonym(Parameter);
	bool isLeftChild(Parameter);
	bool isRightChild(Parameter);
	bool isValidStmtNo(int, PKB*);
	bool isFollows(PKB*, int, int);
	unordered_set<int> getTypeStmt(Type, PKB*);
	ResultTable getFollowNumNum(PKB*, int, int);
	ResultTable getFollowNumSyn(PKB*, unordered_set<int>, int);
	ResultTable getFollowSynNum(PKB*, unordered_set<int>, int);
	ResultTable getFollowSynSyn(PKB*, unordered_set<int>, unordered_set<int>);
	ResultTable getFollowSynSyn(PKB*, ResultTable*);
	ResultTable evaluateWithoutRestrictions(PKB*);
	ResultTable evaluateWithoutOneRestriction(PKB*, ResultTable*);
	vector<Parameter> synList;

public:
	Follow(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	void insertSynList(Parameter);
	vector<Parameter> getSynList();
	ResultTable evaluate(PKB*, ResultTable);
	ClauseType getClauseType();
};
#endif
