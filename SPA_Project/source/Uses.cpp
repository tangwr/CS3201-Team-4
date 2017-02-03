#include "ClauseType.h"
#include "Type.h"
#include "Uses.h"
#include "Clause.h"

Uses::Uses(string lc, string rc, Type lcType, Type rcType) {
	cltype = USES;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}

void Uses::evaluate(PKB *pkbSource) {
	pkb = pkbSource;
}
bool Uses::hasRel(PKB *pkbSource) {
	return isRel;
}