#ifndef NextStarH
#define NextStarH

#include <string>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "unordered_set"
#include "ResultTable.h"

using namespace std;

class NextStar : public Clause {
private:

	Parameter leftChild;
	Parameter rightChild;
	ResultTable result;
	bool isSynonym(Parameter);
	bool isLeftChild(Parameter);
	ResultTable isNextStarItself(PKB*, unordered_set<int>);
	bool isNextStar(PKB*, unordered_set<int>, unordered_set<int>);
	unordered_set<int> getTypeStmt(Parameter, PKB*);
	ResultTable getNextStarSynSyn(PKB*, ResultTable*);
	vector<Parameter> synList;
	void setSynList();
	void insertTuple(int, int);
	ResultTable getNextStar(PKB*, unordered_set<int>, unordered_set<int>);
	bool isBooleanClause();
	void getAllNextStar(int, unordered_set<int>*, PKB*);
	void getAllNextStar(int, unordered_set<int>*, unordered_set<int>*, PKB*);
	void getAllPrevStar(int, unordered_set<int>*, PKB*);
	void getAllPrevStar(int, unordered_set<int>*, unordered_set<int>*, PKB*);
	
public:
	NextStar(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	vector<Parameter> getSynList();
	ClauseType getClauseType();
	ResultTable evaluate(PKB* pkb, ResultTable intResultTable);
};
#endif
