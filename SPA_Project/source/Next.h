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
	bool isSynonym(Parameter parameter);
	bool isLeftChild(Parameter parameter);
	bool isNext(PKB* pkb, unordered_set<int> left, unordered_set<int> right);
	void setSynList();
	void insertTuple(int left, int right);
	vector<Parameter> synList;
	unordered_set<int> getNextStmt(int a, PKB* pkb);
	unordered_set<int> getPreviousStmt(int a, PKB* pkb);
	unordered_set<int> getTypeStmt(Parameter p, PKB* pkb);
	ResultTable getNextSynSyn(PKB* pkb, ResultTable* resultTable);
	ResultTable getNext(PKB* pkb, unordered_set<int> left, unordered_set<int> right);

public:
	Next(Parameter lc, Parameter rc);
	ResultTable evaluate(PKB* pkb, ResultTable resultTable);
	Parameter getLeftChild();
	Parameter getRightChild();
	vector<Parameter> getSynList();
	ClauseType getClauseType();

};
#endif
