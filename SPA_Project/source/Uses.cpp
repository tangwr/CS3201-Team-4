#include "Type.h"
#include "Uses.h"
#include "Clause.h"

Uses::Uses(string lc, Type lcType, string rc, Type rcType) {
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}
bool Uses::hasRel(PKB *pkbSource) {
	return isRel;
}
vector<int> Uses::getWithRelToLeft(PKB *pkb) {
	vector<int> result;
	return result;
}
vector<int> Uses::getWithRelToRight(PKB *pkb) {
	vector<int> result;
	return result;
}
string Uses::getLeftChild() {
	return leftChild;
}
string Uses::getRightChild() {
	return rightChild;
}
Type Uses::getLeftChildType() {
	return leftChildType;
}
Type Uses::getRightChildType() {
	return rightChildType;
}