#ifndef NextH
#define NextH

#include <string>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include <stack>
#include "unordered_set"
#include "ResultTable.h"

using namespace std;

class Next : public Clause {
private:

	Parameter leftChild;
	Parameter rightChild;
	ResultTable result;
	bool isBooleanClause();
	bool isSynonym(Parameter);
	bool isLeftChild(Parameter);
	bool isNext(PKB*, unordered_set<int>, unordered_set<int>);
	void setSynList();
	void insertTuple(int, int);
	vector<Parameter> synList;
	unordered_set<int> getNextStmt(int, PKB*);
	unordered_set<int> getPreviousStmt(int, PKB*);
	unordered_set<int> getTypeStmt(Parameter, PKB*);
	ResultTable getNextSynSyn(PKB*, ResultTable*);
	ResultTable getNext(PKB*, unordered_set<int>, unordered_set<int>);

public:
	Next(Parameter lc, Parameter rc);
	ResultTable evaluate(PKB*, ResultTable);
	Parameter getLeftChild();
	Parameter getRightChild();
	vector<Parameter> getSynList();
	ClauseType getClauseType();

};
#endif
