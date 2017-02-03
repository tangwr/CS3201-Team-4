#include "ClauseType.h"
#include "Type.h"
#include "Modifies.h"
#include "Clause.h"

Modifies::Modifies(string lc, string rc, Type lcType, Type rcType) {
	cltype = MODIFIES;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}

void Modifies::evaluate(PKB *pkbSource) {
	pkb = pkbSource;
}
bool Modifies::hasRel(PKB *pkbSource) {
	return isRel;
}