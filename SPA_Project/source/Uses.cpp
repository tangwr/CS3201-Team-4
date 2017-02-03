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

list<string> Uses::evaluate(PKB *pkbSource, unordered_map<string, Type> map) {
	list<string> list;
	return list;
}
bool Uses::hasRel(PKB *pkbSource) {
	return isRel;
}