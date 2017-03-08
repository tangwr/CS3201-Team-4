#include "Type.h"
#include "Follow.h"
#include "Clause.h"
#include "With.h"

using namespace std;


With::With(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;
}

vector<Parameter>With::getSynList() {
	return synList;
}

Parameter With::getLeftChild() {
	return leftChild;
}
Parameter With::getRightChild() {
	return rightChild;
}
void With::insertSynList(Parameter p) {
	synList.push_back(p);
}