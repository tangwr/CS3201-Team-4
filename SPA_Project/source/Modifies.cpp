#include "ClauseType.h"
#include "Type.h"
#include "Modifies.h"
#include "Clause.h"

Modifies::Modifies(string lc, Type lcType, string rc, Type rcType) {
	cltype = MODIFIES;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}
bool Modifies::hasRel(PKB *pkbSource) {
	return isRel;
}
vector<int> Modifies::getWithRelToLeft(PKB *pkb) {
	vector<int> result;
	return result;
}
vector<int> Modifies::getWithRelToRight(PKB *pkb) {
	vector<int> result;
	return result;
}
string Modifies::getLeftChild() {
	return leftChild;
}
string Modifies::getRightChild() {
	return rightChild;
}
Type Modifies::getLeftChildType() {
	return leftChildType;
}
Type Modifies::getRightChildType() {
	return rightChildType;
}