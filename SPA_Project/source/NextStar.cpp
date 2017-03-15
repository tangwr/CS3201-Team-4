#include "Type.h"
#include "Clause.h"
#include "NextStar.h"

using namespace std;


NextStar::NextStar(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;
}

ResultTable NextStar::evaluate(PKB* pkb, ResultTable resultTable) {
	return result;
}

Parameter NextStar::getLeftChild() {
	return leftChild;
}
Parameter NextStar::getRightChild() {
	return rightChild;
}

void NextStar::insertSynList(Parameter p) {
	synList.push_back(p);
}

vector<Parameter> NextStar::getSynList() {
	return synList;
}

ClauseType NextStar::getClauseType() {
	return FOLLOW;
}
