#include "ClauseType.h"
#include "Type.h"
#include "Follow.h"
#include "Clause.h"

Follow::Follow(string lc,Type lcType, string rc, Type rcType) {
	cltype = FOLLOW;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}
bool Follow::hasRel(PKB *pkbSource) {
	return isRel;
}
vector<int> Follow::getWithRelToLeft(PKB *pkb) {
	vector<int> result;
	return result;
}
vector<int> Follow::getWithRelToRight(PKB *pkb) {
	vector<int> result;
	return result;
}
string Follow::getLeftChild() {
	return leftChild;
}
string Follow::getRightChild() {
	return rightChild;
}
Type Follow::getLeftChildType() {
	return leftChildType;
}
Type Follow::getRightChildType() {
	return rightChildType;
}

