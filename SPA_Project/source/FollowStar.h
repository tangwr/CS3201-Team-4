#ifndef FollowStarH
#define FollowStarH

#include <string>
#include "Clause.h"
#include "ClauseType.h"
#include "Type.h"
#include "PKB.h"

using namespace std;

class FollowStar : public Clause {
private:
	ClauseType cltype;
	string leftChild;
	string rightChild;
	Type leftChildType;
	Type rightChildType;
	PKB *pkb;
	bool isRel;

public:

	FollowStar(string, string, Type, Type);
	list<string> evaluate(PKB *pkb, unordered_map<string, Type> select);
	bool hasRel(PKB *pkb);

};
#endif