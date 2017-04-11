#ifndef ParentH
#define ParentH

#include <string>
#include <unordered_map>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "ResultTable.h"

using namespace std;

class Parent : public Clause {
private:

	Parameter leftChild;
	Parameter rightChild;
	ResultTable result;
	bool isBooleanClause();
	bool isSynonym(Parameter parameter);
	bool isLeftChild(Parameter parameter);
	bool isParent(PKB* pkb, unordered_set<int> left, unordered_set<int> right);
	void setSynList();
	void insertTuple(int left, int right);
	vector<Parameter> synList;
	unordered_set<int> getTypeStmt(Parameter p, PKB* pkb);
	ResultTable getParentSynSyn(PKB* pkb, ResultTable* resultTable);
	ResultTable getParent(PKB* pkb, unordered_set<int> left, unordered_set<int> right);

public:
	Parent(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	ResultTable evaluate(PKB* pkb, ResultTable resultTable);
	vector<Parameter> getSynList();
	ClauseType getClauseType();
};
#endif
