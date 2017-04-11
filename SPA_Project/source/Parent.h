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
	bool isSynonym(Parameter);
	bool isLeftChild(Parameter);
	bool isParent(PKB*, unordered_set<int>, unordered_set<int>);
	void setSynList();
	void insertTuple(int, int);
	vector<Parameter> synList;
	unordered_set<int> getTypeStmt(Parameter, PKB*);
	ResultTable getParentSynSyn(PKB*, ResultTable*);
	ResultTable getParent(PKB*, unordered_set<int>, unordered_set<int>);

public:
	Parent(Parameter, Parameter);
	Parameter getLeftChild();
	Parameter getRightChild();
	ResultTable evaluate(PKB*, ResultTable);
	vector<Parameter> getSynList();
	ClauseType getClauseType();
};
#endif
