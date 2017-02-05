#include "ClauseType.h"
#include "Type.h"
#include "ParentStar.h"
#include "Clause.h"

ParentStar::ParentStar(string lc, Type lcType, string rc, Type rcType) {
	cltype = PARENTSTAR;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}
bool ParentStar::hasRel(PKB *pkbSource) {
	return isRel;
}
vector<int> ParentStar::getWithRelToLeft(PKB *pkb) {
	vector<int> result;
	return result;
}
vector<int> ParentStar::getWithRelToRight(PKB *pkb) {
	vector<int> result;
	return result;
}
string ParentStar::getLeftChild() {
	return leftChild;
}
string ParentStar::getRightChild() {
	return rightChild;
}
Type ParentStar::getLeftChildType() {
	return leftChildType;
}
Type ParentStar::getRightChildType() {
	return rightChildType;
}

