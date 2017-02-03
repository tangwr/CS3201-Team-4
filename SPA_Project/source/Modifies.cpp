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

list<string> Modifies::evaluate(PKB *pkbSource, unordered_map<string, Type> select) {
	list<string> list;
	return list;
}
bool Modifies::hasRel(PKB *pkbSource) {
	return isRel;
}