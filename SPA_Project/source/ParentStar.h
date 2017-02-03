#ifndef ParentStarH
#define ParentStarH

#include <string>
#include "Clause.h"
#include "ClauseType.h"
#include "Type.h"
#include "PKB.h"

using namespace std;

class ParentStar : public Clause {
private:
	ClauseType cltype;
	string leftChild;
	string rightChild;
	Type leftChildType;
	Type rightChildType;
	PKB *pkb;
	bool isRel;

public:

	ParentStar(string, string, Type, Type);
	void evaluate(PKB *pkb);
	bool hasRel(PKB *pkb);

};
#endif