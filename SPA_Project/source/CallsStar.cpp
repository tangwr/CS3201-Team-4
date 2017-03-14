#include "Type.h"
#include "CallsStar.h"
#include "Clause.h"

CallsStar::CallsStar(Parameter lc, Parameter rc) {
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

bool CallsStar::hasRel(PKB *pkbSource) {
	return true;
}

vector<int> CallsStar::getWithRelToLeft(PKB *pkb) {
	return vector<int>();
}

vector<int> CallsStar::getWithRelToRight(PKB *pkb) {
	return vector<int>();
}

Parameter CallsStar::getLeftChild() {
	return leftChild;
}
Parameter CallsStar::getRightChild() {
	return rightChild;
}

vector<Parameter> CallsStar::getSynList() {
	return synList;
}

ClauseType CallsStar::getClauseType() {
	return CALLSSTAR;
}

ResultTable CallsStar::evaluate(PKB* pkb, ResultTable intResultTable) {
	return ResultTable();
}