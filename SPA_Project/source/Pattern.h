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
	bool isRel;
	bool hasUnderScore;
	string factor;
	Type factorType;

	string getPrefix(string infixString);
	vector<int> getFirstPatternStmts(PKB* pkb);
	vector<int> getSecondPatternStmts(PKB* pkb);
	vector<int> getAllTypeStmts(PKB *pkb);
	vector<int> getTypeStmtModifiedByVar(PKB* pkb, int varId);
	vector<int> getVarFromStmts(PKB *pkb, vector<int> stmts);
	vector<int> getAssignStmtWithPrefix(PKB* pkb, string prefix);
	
public:

	Pattern(string lc, Type lcType, string rc, Type rcType, string factor, Type factorType, bool underscore);
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
