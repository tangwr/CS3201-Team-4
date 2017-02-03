#include "ClauseType.h"
#include "Type.h"
#include "Parent.h"
#include "Clause.h"

Parent::Parent(string lc, string rc, Type lcType, Type rcType) {
	cltype = PARENT;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}

void Parent::evaluate(PKB *pkbSource) {
	pkb = pkbSource;
}
bool Parent::hasRel(PKB *pkbSource) {
	return isRel;
}
