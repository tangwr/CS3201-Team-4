#include "Type.h"
#include "Calls.h"
#include "Clause.h"

Calls::Calls(Parameter lc, Parameter rc){
	leftChild = lc;
	rightChild = rc;
	
	if (lc.getParaType() != Type::CONSTANT && lc.getParaType() != Type::BOOLEAN && lc.getParaType() != Type::ANYTHING
		&& lc.getParaType() != Type::STRINGVARIABLE && lc.getParaType() != Type::INTEGER) {
		synList.push_back(lc);
	}
	if (rc.getParaType() != Type::CONSTANT && rc.getParaType() != Type::BOOLEAN && rc.getParaType() != Type::ANYTHING
		&& rc.getParaType() != Type::STRINGVARIABLE && rc.getParaType() != Type::INTEGER) {
		synList.push_back(rc);
	}
}

bool Calls::hasRel(PKB *pkbSource) {
	
}

vector<int> Calls::getWithRelToLeft(PKB *pkb) {
	

}

vector<int> Calls::getWithRelToRight(PKB *pkb) {
	
}

Parameter Calls::getLeftChild() {
	return leftChild;
}
Parameter Calls::getRightChild() {
	return rightChild;
}

vector<Parameter> Calls::getSynList() {
	return synList;
}










