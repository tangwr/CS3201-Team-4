#include "ClauseType.h"
#include "Type.h"
#include "ParentStar.h"
#include "Clause.h"

ParentStar::ParentStar(string lc, string rc, Type lcType, Type rcType) {
	cltype = PARENTSTAR;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}

void ParentStar::evaluate(PKB *pkbSource) {
	pkb = pkbSource;
}
bool ParentStar::hasRel(PKB *pkbSource) {
	return isRel;
}

