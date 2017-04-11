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
	void insertTuple(int left, int right);
	bool isSynonym(Parameter parameter);
	bool isBooleanClause();
	bool isLeftChild(Parameter parameter);
	bool isFollows(PKB* pkb, unordered_set<int> left, unordered_set<int> right);
	vector<Parameter> synList;
	unordered_set<int> getTypeStmt(Parameter p, PKB* pkb);
	ResultTable getFollowSynSyn(PKB* pkb, ResultTable* resultTable);
	ResultTable getFollow(PKB* pkb, unordered_set<int> left, unordered_set<int> right);

public:
	Follow(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	vector<Parameter> getSynList();
	ResultTable evaluate(PKB* pkb, ResultTable resultTable);
	ClauseType getClauseType();
};
#endif
