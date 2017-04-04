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
	bool isSynonym(Parameter);
	bool isLeftChild(Parameter);
	bool isValidStmtNo(int, PKB*);
	bool isFollowStar(PKB*, unordered_set<int>, unordered_set<int>);
	unordered_set<int> getTypeStmt(Parameter, PKB*);
	ResultTable getFollowStarSynSyn(PKB*, ResultTable*);
	vector<Parameter> synList;
	void setSynList();
	void insertTuple(int, int);
	ResultTable getFollowStar(PKB*, unordered_set<int>, unordered_set<int>);
	bool isBooleanClause();

public:

	FollowStar(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	ResultTable evaluate(PKB*, ResultTable);
	vector<Parameter> getSynList();
	ClauseType getClauseType();
};
#endif
