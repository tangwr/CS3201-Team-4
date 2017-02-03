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

list<string> ParentStar::evaluate(PKB *pkbSource, unordered_map<string, Type> select) {
	list<string> list;
	return list;
}
bool ParentStar::hasRel(PKB *pkbSource) {
	return isRel;
}

