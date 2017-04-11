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
	void setSynList();
	void insertTuple(int, int);
	bool isSynonym(Parameter);
	bool isBooleanClause();
	bool isLeftChild(Parameter);
	bool isFollows(PKB*, unordered_set<int>, unordered_set<int>);
	vector<Parameter> synList;
	unordered_set<int> getTypeStmt(Parameter, PKB*);
	ResultTable getFollowSynSyn(PKB*, ResultTable*);
	ResultTable getFollow(PKB*, unordered_set<int>, unordered_set<int>);

public:
	Follow(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	vector<Parameter> getSynList();
	ResultTable evaluate(PKB*, ResultTable);
	ClauseType getClauseType();
};
#endif
