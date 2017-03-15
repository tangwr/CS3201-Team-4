#ifndef ParentStarH
#define ParentStarH

#include <string>
#include <unordered_set>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "ResultTable.h"

using namespace std;

class ParentStar : public Clause {
private:

	Parameter leftChild;
	Parameter rightChild;
	ResultTable result;
	bool isNumber(Parameter);
	bool isSynonym(Parameter);
	bool isValidStmtNo(int, PKB*);
	bool isLeftChild(Parameter);
	bool isParentStar(PKB*, int, int);
	bool isStmtType(int, Parameter, PKB*);
	ResultTable getAllParentStar(vector<int>, PKB*);
	ResultTable getAllChildrenStar(vector<int>, PKB*);
	unordered_set<int> getTypeStmt(Type, PKB*);
	ResultTable getParentStarNumNum(PKB*, int, int);
	ResultTable getParentStarNumSyn(PKB*, unordered_set<int>, int);
	ResultTable getParentStarSynNum(PKB*, unordered_set<int>, int);
	ResultTable getParentStarSynSyn(PKB*, unordered_set<int>, unordered_set<int>);
	ResultTable getParentStarSynSyn(PKB*, ResultTable*);
	ResultTable evaluateWithoutRestrictions(PKB*);
	ResultTable evaluateWithoutOneRestriction(PKB*, ResultTable*);
	vector<Parameter> synList;

public:

	ParentStar(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	ResultTable evaluate(PKB*, ResultTable);
	void insertSynList(Parameter);
	vector<Parameter> getSynList();
	ClauseType getClauseType();
};
#endif
