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
	bool isSynonym(Parameter);
	bool isLeftChild(Parameter);
	ResultTable isNextBipStarItself(PKB*, unordered_set<int>);
	bool isNextBipStar(PKB*, unordered_set<int>, unordered_set<int>);
	unordered_set<int> getTypeStmt(Parameter, PKB*);
	ResultTable getNextBipStarSynSyn(PKB*, ResultTable*);
	vector<Parameter> synList;
	void setSynList();
	void insertTuple(int, int);
	ResultTable getNextBipStar(PKB*, unordered_set<int>, unordered_set<int>);
	bool isBooleanClause();
	void getAllNextBipStar(int, unordered_set<int>*, PKB*);
	void getAllNextBipStar(int, unordered_set<int>*, unordered_set<int>*, PKB*);
	void getCallNextBipStar(int, unordered_set<int>*, stack<int>*, unordered_set<int>*, unordered_set<int>*, PKB*);
	void getWithinProc(int, unordered_set<int>*, stack<int>*, PKB*);
	void getAllPrevStar(int, unordered_set<int>*, PKB*);
	void getAllPrevStar(int, unordered_set<int>*, unordered_set<int>*, unordered_set<int>*, PKB*);
	unordered_set<int> getNextStmt(int, PKB*);
	unordered_set<int> getPreviousStmt(int, PKB*);
	void computeLastBip(int, unordered_set<int>*, PKB*);

public:
	NextBipStar(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	vector<Parameter> getSynList();
	ClauseType getClauseType();
	ResultTable evaluate(PKB* pkb, ResultTable intResultTable);
};
#endif
