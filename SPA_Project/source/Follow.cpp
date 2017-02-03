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

void Follow::evaluate(PKB *pkbSource) {
	pkb = pkbSource;
}
bool Follow::hasRel(PKB *pkbSource) {
	return isRel;
}

