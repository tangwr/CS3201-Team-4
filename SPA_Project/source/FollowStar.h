#ifndef FollowStarH
#define FollowStarH

#include <string>
#include <unordered_set>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "ResultTable.h"

using namespace std;

class FollowStar : public Clause {
private:

	Parameter leftChild;
	Parameter rightChild;
	ResultTable result;
	bool isNumber(Parameter);
	bool isSynonym(Parameter);
	bool isValidStmtNo(int, PKB*);
	bool isFollowStar(PKB*, int, int);
	bool isLeftChild(Parameter);
	ResultTable getAllFollowsStar(vector<int>, PKB*);
	ResultTable getAllFollowedByStar(vector<int>, PKB*);

	unordered_set<int> getTypeStmt(Type, PKB*);
	ResultTable getFollowStarNumNum(PKB*, int, int);
	ResultTable getFollowStarNumSyn(PKB*, unordered_set<int>, int);
	ResultTable getFollowStarSynNum(PKB*, unordered_set<int>, int);
	ResultTable getFollowStarSynSyn(PKB*, unordered_set<int>, unordered_set<int>);
	ResultTable getFollowStarSynSyn(PKB*, ResultTable*);

	ResultTable getFollowStar(PKB*, unordered_set<int>, unordered_set<int>);
	ResultTable evaluateWithoutRestrictions(PKB*);
	ResultTable evaluateWithoutOneRestriction(PKB*, ResultTable*);
	vector<Parameter> synList;

public:

	FollowStar(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	ResultTable evaluate(PKB*, ResultTable);
	vector<Parameter> getSynList();
	ClauseType getClauseType();
};
#endif
