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
	bool isSynonym(Parameter parameter);
	bool isLeftChild(Parameter parameter);
	bool isNextBip(PKB* pkb, unordered_set<int> left, unordered_set<int> right);
	void setSynList();
	void insertTuple(int left, int right);
	void DFS(int currStmt, unordered_set<int>* lastStmts, unordered_set<int>* visited, PKB* pkb);
	void computeLastBip(int curr, unordered_set<int>* allNextBip, PKB* pkb);
	ResultTable getNextBipSynSyn(PKB* pkb, ResultTable* resultTable);
	ResultTable getNextBip(PKB* pkb, unordered_set<int> left, unordered_set<int> right);
	unordered_set<int> getTypeStmt(Parameter p, PKB* pkb);
	unordered_set<int> getNextStmt(int a, PKB* pkb);
	unordered_set<int> computeNextBip(int curr, PKB* pkb);
	unordered_set<int> computePrevBip(int curr, PKB* pkb);
	unordered_set<int> getLastStmts(int procId, PKB* pkb);

public:
	NextBip(Parameter lc, Parameter rc);
	ResultTable evaluate(PKB* pkb, ResultTable resultTable);
	Parameter getLeftChild();
	Parameter getRightChild();
	vector<Parameter> getSynList();
	ClauseType getClauseType();
};
#endif
