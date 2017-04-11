#ifndef NextBipStarH
#define NextBipStarH

#include <string>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "unordered_set"
#include <stack>
#include "ResultTable.h"

using namespace std;

class NextBipStar : public Clause {
private:

	Parameter leftChild;
	Parameter rightChild;
	ResultTable result;
	vector<Parameter> synList;
	bool isBooleanClause();
	bool isSynonym(Parameter);
	bool isLeftChild(Parameter);
	bool isNextBipStar(PKB* pkb, unordered_set<int> left, unordered_set<int> right);
	void setSynList();
	void insertTuple(int left, int right);
	void getAllNextBipStar(int prev, unordered_set<int>* allNextBipStar, PKB* pkb);
	void getAllNextBipStar(int curr, unordered_set<int>* allNextBipStar, unordered_set<int>* visited, stack<int>* callingStmts, PKB* pkb, int count);
	void computeLastBip(int curr, unordered_set<int>* allNextBip, PKB* pkb);
	unordered_set<int> getNextStmt(int a, PKB* pkb);
	unordered_set<int> computeNextBip(int curr, PKB* pkb);
	unordered_set<int> getTypeStmt(Parameter p, PKB* pkb);
	ResultTable getNextBipStarSynSyn(PKB* pkb, ResultTable* resultTable);
	ResultTable isNextBipStarItself(PKB* pkb, unordered_set<int> stmts);
	ResultTable getNextBipStar(PKB* pkb, unordered_set<int> left, unordered_set<int> right);

public:
	NextBipStar(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	vector<Parameter> getSynList();
	ClauseType getClauseType();
	ResultTable evaluate(PKB* pkb, ResultTable intResultTable);
};
#endif
