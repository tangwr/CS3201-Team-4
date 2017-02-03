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
	string prefix;

public:

	Pattern(string, string, Type, Type);
	void evaluate(PKB *pkb);
	bool hasRel(PKB *pkb);
	void setUnderScore(bool);
	void setPrefix(string);
	string getPrefix();
	bool getUnderScore();

};
#endif