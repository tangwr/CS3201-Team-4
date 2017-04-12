#include "Type.h"
#include "Parent.h"
#include "Clause.h"
#include "unordered_set"

#define ZERO 0
#define ONE 1
#define FIRST_SYNONYM_INDEX 0
#define NUM_PARAMETER_WITH_INTERMEDIATE_RESULTS_TWO 2

Parent::Parent(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;
	if (leftChild.isSynonym()) {
		synList.push_back(leftChild);
	}
	if (rightChild.isSynonym()) {
		if (!isLeftChild(rightChild)) {
			synList.push_back(rightChild);
		}
	}
}

ResultTable* Parent::evaluate(PKB* pkb, ResultTable* resultTable) {
	if (resultTable->getSynCount() == NUM_PARAMETER_WITH_INTERMEDIATE_RESULTS_TWO) {
		getParentSynSyn(pkb, resultTable);
	}
	else if (isBooleanClause()) {
		result.setBoolean(isParent(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb)));
		return &result;
	}
	else {
		unordered_set<int> left = resultTable->getSynValue(leftChild);
		unordered_set<int> right = resultTable->getSynValue(rightChild);
		if (!left.empty()) {
			getParent(pkb, left, getTypeStmt(rightChild, pkb));
		}
		else if (!right.empty()) {
			getParent(pkb, getTypeStmt(leftChild, pkb), right);
		}
		else {
			getParent(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb));
		}
	}
	return &result;
}

vector<Parameter> Parent::getSynList() {
	return synList;
}

ClauseType Parent::getClauseType() {
	return PARENT;
}

bool Parent::isParent(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	for (auto& rightIterator : right) {
		int parent = pkb->getStmtParentStmt(rightIterator);
		if (left.find(parent) != left.end()) {
			return true;
		}
	}
	return false;
}

void Parent::getParent(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	setSynList();
	if (isLeftChild(rightChild)) {
		return;
	}
	if (left.size() == ONE) {
		for (auto& leftIterator : left) {
			unordered_set<int> children = pkb->getStmtChildrenStmt(leftIterator);
			for (auto& it : children) {
				if (right.find(it) != right.end()) {
					insertTuple(leftIterator, it);
				}
			}
		}
	}
	else {
		for (auto& rightIterator : right) {
			int parent = pkb->getStmtParentStmt(rightIterator);
			if (left.find(parent) != left.end()) {
				insertTuple(parent, rightIterator);
			}
		}
	}
	return;
}

void Parent::getParentSynSyn(PKB* pkb, ResultTable* resultTable) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		return;
	}
	vector<Parameter> synonyms = resultTable->getSynList();
	vector<vector<int>> tupleList = resultTable->getTupleList();
	if (isLeftChild(synonyms[FIRST_SYNONYM_INDEX])) {
		for (int i = ZERO; i < tupleList.size(); i++) {
			if (isParent(pkb, unordered_set<int>({ tupleList[i][ZERO] }), unordered_set<int>({ tupleList[i][ONE] }))) {
				vector<int> tuple = { tupleList[i][ZERO], tupleList[i][ONE] };
				result.insertTuple(tuple);
			}
		}
	}
	else {
		for (int i = ZERO; i < tupleList.size(); i++) {
			if (isParent(pkb, unordered_set<int>({ tupleList[i][ONE] }), unordered_set<int>({ tupleList[i][ZERO] }))) {
				vector<int> tuple = { tupleList[i][ONE], tupleList[i][ZERO] };
				result.insertTuple(tuple);
			}
		}
	}
	return;
}

void Parent::setSynList() {
	vector<Parameter> v;
	if (isSynonym(leftChild)) {
		v.push_back(leftChild);
	}
	if (isSynonym(rightChild)) {
		if (!isLeftChild(rightChild)) {
			v.push_back(rightChild);
		}
	}
	result.setSynList(v);
}

void Parent::insertTuple(int left, int right) {
	vector<int> v;
	if (isSynonym(leftChild)) {
		if (isSynonym(rightChild)) {
			if (isLeftChild(rightChild)) {
				v = { left };
			}
			else {
				v = { left, right };
			}
		}
		else {
			v = { left };
		}
	}
	else {
		v = { right };
	}
	result.insertTuple(v);
}

unordered_set<int> Parent::getTypeStmt(Parameter p, PKB* pkb) {
	Type type = p.getParaType();
	switch (type) {
	case PROG_LINE:
	case STMT:
	case ANYTHING:
		return pkb->getAllStmtId();
	case WHILE:
		return pkb->getAllWhileStmt();
	case ASSIGN:
		return pkb->getAllAssignStmt();
	case IF:
		return pkb->getAllIfId();
	case CALL:
		return pkb->getAllCallId();
	case INTEGER:
		return unordered_set<int>({ stoi(p.getParaName()) });
	}
	return unordered_set<int>();
}

bool Parent::isLeftChild(Parameter parameter) {
	return (parameter.getParaName().compare(leftChild.getParaName()) == ZERO && parameter.getParaType() == leftChild.getParaType());
}

bool Parent::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == PROG_LINE || type == IF || type == CALL);
}

bool Parent::isBooleanClause() {
	return (leftChild.getParaType() == ANYTHING || leftChild.getParaType() == INTEGER)
		&& (rightChild.getParaType() == ANYTHING || rightChild.getParaType() == INTEGER);
}