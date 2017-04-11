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
	bool isNextBipStar(PKB*, unordered_set<int>, unordered_set<int>);
	void setSynList();
	void insertTuple(int, int);
	void getAllNextBipStar(int, unordered_set<int>*, PKB*);
	void getAllNextBipStar(int, unordered_set<int>*, unordered_set<int>*, stack<int>*, PKB*, int);
	void computeLastBip(int, unordered_set<int>*, PKB*);
	unordered_set<int> getNextStmt(int, PKB*);
	unordered_set<int> computeNextBip(int, PKB*);
	unordered_set<int> getTypeStmt(Parameter, PKB*);
	ResultTable getNextBipStarSynSyn(PKB*, ResultTable*);
	ResultTable isNextBipStarItself(PKB*, unordered_set<int>);
	ResultTable getNextBipStar(PKB*, unordered_set<int>, unordered_set<int>);

public:
	NextBipStar(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	vector<Parameter> getSynList();
	ClauseType getClauseType();
	ResultTable evaluate(PKB* pkb, ResultTable intResultTable);
};
#endif
