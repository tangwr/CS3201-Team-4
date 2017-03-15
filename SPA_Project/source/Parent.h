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
	bool isNumber(Parameter);
	bool isSynonym(Parameter);
	bool isValidStmtNo(int, PKB*);
	bool isLeftChild(Parameter);
	bool isParent(PKB*, int, int);
	//bool isStmtType(int, Parameter, PKB*);
	unordered_set<int> getTypeStmt(Type, PKB*);
	ResultTable getParentNumNum(PKB*, int, int);
	ResultTable getParentNumSyn(PKB*, unordered_set<int>, int);
	ResultTable getParentSynNum(PKB*, unordered_set<int>, int);
	ResultTable getParentSynSyn(PKB*, unordered_set<int>, unordered_set<int>);
	ResultTable getParentSynSyn(PKB*, ResultTable*);
	ResultTable evaluateWithoutRestrictions(PKB*);
	ResultTable evaluateWithoutOneRestriction(PKB*, ResultTable*);
	vector<Parameter> synList;

public:
	Parent(Parameter, Parameter);
	Parameter getLeftChild();
	Parameter getRightChild();
	ResultTable evaluate(PKB*, ResultTable);
	void insertSynList(Parameter);
	vector<Parameter> getSynList();
	ClauseType getClauseType();
};
#endif
