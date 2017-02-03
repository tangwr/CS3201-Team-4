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

list<string> FollowStar::evaluate(PKB *pkbSource , unordered_map<string, Type> select) {
	pkb = pkbSource;
}
bool FollowStar::hasRel(PKB *pkbSource) {
	return isRel;
}
