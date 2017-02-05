#include "ClauseType.h"
#include "Type.h"
#include "Pattern.h"
#include "Clause.h"

Pattern::Pattern(string lc, Type lcType, string rc, Type rcType, bool underscore) {
	cltype = PATTERN;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
	isUnderScore = underscore;
}
bool Pattern::hasRel(PKB *pkbSource) {
	return isRel;
}

void Pattern::setUnderScore(bool us) {
	isUnderScore = us;
}

void Pattern::setSynonym(string x) {
	syn = x;
}

string Pattern::getSynonym() {
	return syn;
}

bool Pattern::getUnderScore() {
	return isUnderScore;
}

vector<int> Pattern::getWithRelToLeft(PKB *pkb) {
	vector<int> result;
	return result;
}
vector<int> Pattern::getWithRelToRight(PKB *pkb) {
	vector<int> result;
	return result;
}
string Pattern::getLeftChild() {
	return leftChild;
}
string Pattern::getRightChild() {
	return rightChild;
}
Type Pattern::getLeftChildType() {
	return leftChildType;
}
Type Pattern::getRightChildType() {
	return rightChildType;
}
Type Pattern::getSynType() {
	return synType;
}

