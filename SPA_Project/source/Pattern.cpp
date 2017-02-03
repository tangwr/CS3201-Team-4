#include "ClauseType.h"
#include "Type.h"
#include "Pattern.h"
#include "Clause.h"

Pattern::Pattern(string lc, string rc, Type lcType, Type rcType) {
	cltype = PATTERN;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}

list<string> Pattern::evaluate(PKB *pkbSource, unordered_map<string, Type> select) {
	list<string> list;
	return list;
}
bool Pattern::hasRel(PKB *pkbSource) {
	return isRel;
}

void Pattern::setUnderScore(bool us) {
	isUnderScore = us;
}

void Pattern::setPrefix(string x) {
	prefix = x;
}

string Pattern::getPrefix() {
	return prefix;
}

bool Pattern::getUnderScore() {
	return isUnderScore;
}