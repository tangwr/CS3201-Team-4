#include "ClauseType.h"
#include "Type.h"
#include "Follow.h"
#include "Clause.h"

Follow::Follow(string lc, string rc, Type lcType, Type rcType) {
	cltype = FOLLOW;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}

list<string> Follow::evaluate(PKB *pkbSource, unordered_map<string, Type> select) {
	pkb = pkbSource;
}
bool Follow::hasRel(PKB *pkbSource) {
	return isRel;
}

