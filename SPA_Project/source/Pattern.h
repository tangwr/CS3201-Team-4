#ifndef PatternH
#define PatternH

#include <string>
#include "Clause.h"
#include "ClauseType.h"
#include "Type.h"
#include "PKB.h"

using namespace std;

class Pattern : public Clause {
private:
	ClauseType cltype;
	string leftChild;
	string rightChild;
	Type leftChildType;
	Type rightChildType;
	PKB *pkb;
	bool isRel;
	bool isUnderScore;
	string factor;
	Type factorType;


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
};
#endif
