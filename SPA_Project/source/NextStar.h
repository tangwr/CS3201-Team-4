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
	bool isBooleanClause();
	bool isSynonym(Parameter parameter);
	bool isLeftChild(Parameter parameter);
	bool isNextStar(PKB* pkb, unordered_set<int> left, unordered_set<int> right);
	void setSynList();
	void insertTuple(int left, int right);
	vector<Parameter> synList;
	unordered_set<int> getTypeStmt(Parameter p, PKB* pkb);
	ResultTable getNextStarSynSyn(PKB* pkb, ResultTable* resultTable);
	ResultTable isNextStarItself(PKB* pkb, unordered_set<int> stmts);
	ResultTable getNextStar(PKB* pkb, unordered_set<int> left, unordered_set<int> right);
	void getAllNextStar(int prev, unordered_set<int>* allNextStar, PKB* pkb);
	void getAllNextStar(int prev, unordered_set<int>* allNextStar, unordered_set<int>* visited, PKB* pkb);
	void getAllPrevStar(int next, unordered_set<int>* allPrevStar, PKB* pkb);
	void getAllPrevStar(int next, unordered_set<int>* allPrevStar, unordered_set<int>* visited, PKB* pkb);
	
public:
	NextStar(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	vector<Parameter> getSynList();
	ClauseType getClauseType();
	ResultTable evaluate(PKB* pkb, ResultTable intResultTable);
};
#endif
