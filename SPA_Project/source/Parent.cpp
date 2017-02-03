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

list<string> Parent::evaluate(PKB *pkbSource, unordered_map<string, Type> select) {
	list<string> list;
	return list;
}
bool Parent::hasRel(PKB *pkbSource) {
	return isRel;
}
