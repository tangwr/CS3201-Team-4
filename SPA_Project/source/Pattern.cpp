#include "ClauseType.h"
#include "Type.h"
#include "Pattern.h"
#include "Clause.h"

Pattern::Pattern() {
	cltype = PATTERN;
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