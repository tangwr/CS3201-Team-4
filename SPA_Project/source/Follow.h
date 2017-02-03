#ifndef FollowH
#define FollowH

#include <string>
#include "Clause.h"
#include "ClauseType.h"
#include "Type.h"
#include "PKB.h"

using namespace std;

class Follow : public Clause {
private:
	ClauseType cltype;
	string leftChild;
	string rightChild;
	Type leftChildType;
	Type rightChildType;
	PKB *pkb;
	bool isRel;

public:

	Follow(string, string, Type, Type);
	void evaluate(PKB *pkb);
	bool hasRel(PKB *pkb);

};
#endif