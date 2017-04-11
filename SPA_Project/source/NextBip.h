#ifndef NextBipH
#define NextBipH

#include <string>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include <stack>
#include "unordered_set"
#include "ResultTable.h"

using namespace std;

class NextBip : public Clause {
private:

	Parameter leftChild;
	Parameter rightChild;
	ResultTable result;
	vector<Parameter> synList;
	bool isBooleanClause();
	bool isSynonym(Parameter);
	bool isLeftChild(Parameter);
	bool isNextBip(PKB*, unordered_set<int>, unordered_set<int>);
	void setSynList();
	void insertTuple(int, int);
	void DFS(int, unordered_set<int>*, unordered_set<int>*, PKB*);
	void computeLastBip(int, unordered_set<int>*, PKB*);
	ResultTable getNextBipSynSyn(PKB*, ResultTable*);
	ResultTable getNextBip(PKB*, unordered_set<int>, unordered_set<int>);
	unordered_set<int> getTypeStmt(Parameter, PKB*);
	unordered_set<int> getNextStmt(int, PKB*);
	unordered_set<int> computeNextBip(int, PKB*);
	unordered_set<int> computePrevBip(int, PKB*);
	unordered_set<int> getLastStmts(int, PKB*);

public:
	NextBip(Parameter lc, Parameter rc);
	ResultTable evaluate(PKB*, ResultTable);
	Parameter getLeftChild();
	Parameter getRightChild();
	vector<Parameter> getSynList();
	ClauseType getClauseType();
};
#endif
