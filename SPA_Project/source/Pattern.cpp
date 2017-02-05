#include "ClauseType.h"
#include "Type.h"
#include "Pattern.h"
#include "Clause.h"

Pattern::Pattern(string lc, Type lcType, string rc, Type rcType, bool underscore, string f, Type ft) {
	cltype = PATTERN;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
	isUnderScore = underscore;
	factor = f;
	factorType = ft;
}
bool Pattern::hasRel(PKB *pkbSource) {
	return isRel;
}

void Pattern::setUnderScore(bool us) {
	isUnderScore = us;
}

void Pattern::setFactor(string f) {
	factor = f;
}

string Pattern::getFactor() {
	return factor;
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
Type Pattern::getFactorType() {
	return factorType;
}

