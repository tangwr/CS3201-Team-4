#include "ClauseType.h"
#include "Type.h"
#include "Parent.h"
#include "Clause.h"

Parent::Parent(string lc, Type lcType, string rc, Type rcType) {
	cltype = PARENT;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}
bool Parent::hasRel(PKB *pkbSource) {
	return isRel;
}

vector<int> Parent::getWithRelToLeft(PKB *pkb) {
	vector<int> result;
	return result;
}
vector<int> Parent::getWithRelToRight(PKB *pkb) {
	vector<int> result;
	return result;
}
string Parent::getLeftChild() {
	return leftChild;
}
string Parent::getRightChild() {
	return rightChild;
}
Type Parent::getLeftChildType() {
	return leftChildType;
}
Type Parent::getRightChildType() {
	return rightChildType;
}
