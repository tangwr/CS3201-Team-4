#ifndef NextBipH
#define NextBipH

#include <string>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "unordered_set"
#include "ResultTable.h"

using namespace std;

class NextBip : public Clause {
private:

	Parameter leftChild;
	Parameter rightChild;
	ResultTable result;
	bool isSynonym(Parameter);
	bool isLeftChild(Parameter);
	bool isNextBip(PKB*, unordered_set<int>, unordered_set<int>);
	unordered_set<int> getTypeStmt(Parameter, PKB*);
	ResultTable getNextBipSynSyn(PKB*, ResultTable*);
	vector<Parameter> synList;
	void setSynList();
	void insertTuple(int, int);
	ResultTable getNextBip(PKB*, unordered_set<int>, unordered_set<int>);
	bool isBooleanClause();

public:
	NextBip(Parameter lc, Parameter rc);
	ResultTable evaluate(PKB*, ResultTable);
	Parameter getLeftChild();
	Parameter getRightChild();
	vector<Parameter> getSynList();
	ClauseType getClauseType();
};
#endif
