#ifndef PatternH
#define PatternH

#include <string>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"

using namespace std;

class Pattern : public Clause {
private:
	string leftChild;
	string rightChild;
	Type leftChildType;
	Type rightChildType;
	PKB *pkb;
	bool isRel;
	bool isUnderScore;
	string factor;
	Type factorType;

	string getPrefix(string infixString);
	vector<int> getFirstPatternStmts(PKB* pkb);
	vector<int> getSecondPatternStmts(PKB* pkb);
	vector<int> getAssignStmtModifiedByVar(PKB* pkb, int varId);
	vector<int> getVarFromAssignStmts(PKB *pkb, vector<int> stmts);
	
public:

	Pattern(string lc, Type lcType, string rc, Type rcType, bool underscore, string factor, Type factorType);
	bool hasRel(PKB *pkb);
	void setUnderScore(bool);
	void setFactor(string);
	bool getUnderScore();
	vector<int> getWithRelToLeft(PKB *pkb);
	vector<int> getWithRelToRight(PKB *pkb);
	string getLeftChild();
	string getRightChild();
	string getFactor();
	Type getLeftChildType();
	Type getRightChildType();
	Type getFactorType();
	ClauseType getClauseType();
};
#endif
