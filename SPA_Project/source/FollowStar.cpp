#include "ClauseType.h"
#include "Type.h"
#include "FollowStar.h"
#include "Clause.h"

FollowStar::FollowStar(string lc, Type lcType, string rc, Type rcType) {
	cltype = FOLLOWSTAR;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}
bool FollowStar::hasRel(PKB *pkbSource) {
	return isRel;
}

vector<int> FollowStar::getWithRelToLeft(PKB *pkb) {
	vector<int> result;
	return result;
}
vector<int> FollowStar::getWithRelToRight(PKB *pkb) {
	vector<int> result;
	return result;
}
string FollowStar::getLeftChild() {
	return leftChild;
}
string FollowStar::getRightChild() {
	return rightChild;
}
Type FollowStar::getLeftChildType() {
	return leftChildType;
}
Type FollowStar::getRightChildType() {
	return rightChildType;
}
