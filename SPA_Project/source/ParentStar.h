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
	bool isBooleanClause();
	bool isSynonym(Parameter);
	bool isLeftChild(Parameter);
	bool isParentStar(PKB*, unordered_set<int>, unordered_set<int>);
	void setSynList();
	void insertTuple(int, int);
	vector<Parameter> synList;
	unordered_set<int> getTypeStmt(Parameter, PKB*);
	ResultTable getParentStarSynSyn(PKB*, ResultTable*);
	ResultTable getParentStar(PKB*, unordered_set<int>, unordered_set<int>);

public:

	ParentStar(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	ResultTable evaluate(PKB*, ResultTable);
	vector<Parameter> getSynList();
	ClauseType getClauseType();
};
#endif
