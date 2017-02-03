#include "ClauseType.h"
#include "Type.h"
#include "FollowStar.h"
#include "Clause.h"

FollowStar::FollowStar(string lc, string rc, Type lcType, Type rcType) {
	cltype = FOLLOWSTAR;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}

void FollowStar::evaluate(PKB *pkbSource) {
	pkb = pkbSource;
}
bool FollowStar::hasRel(PKB *pkbSource) {
	return isRel;
}
