#include "Type.h"
#include "Clause.h"
#include "NextBip.h"

using namespace std;

NextBip::NextBip(Parameter lc, Parameter rc) {
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

ResultTable NextBip::evaluate(PKB* pkb, ResultTable resultTable) {
	if (resultTable.getSynCount() == 2) {
		return getNextBipSynSyn(pkb, &resultTable);
	}
	else if (isBooleanClause()) {
		result.setBoolean(isNextBip(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb)));
		return result;
	}
	else {
		unordered_set<int> left = resultTable.getSynValue(leftChild);
		unordered_set<int> right = resultTable.getSynValue(rightChild);
		if (left.size() != 0) {
			return getNextBip(pkb, left, getTypeStmt(rightChild, pkb));
		}
		else if (right.size() != 0) {
			return getNextBip(pkb, getTypeStmt(leftChild, pkb), right);
		}
		else {
			return getNextBip(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb));
		}
	}
	return result;
}

bool NextBip::isNextBip(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	if (left.size() < right.size()) {
		for (auto& leftIterator : left) {
			unordered_set<int> nextBip = pkb->getNextStmt(leftIterator);
			//unordered_set<int> nextBip = pkb->getNextBipStmt(leftIterator);
			for (auto& it : nextBip) {
				if (right.find(it) != right.end()) {
					return true;
				}
			}
		}
	}
	else {
		for (auto& rightIterator : right) {
			unordered_set<int> prev = pkb->getPreviousStmt(rightIterator);
			for (auto& it : prev) {
				if (left.find(it) != left.end()) {
					return true;
				}
			}
		}
	}
	return false;
}

ResultTable NextBip::getNextBip(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	setSynList();
	if (isLeftChild(rightChild)) {
		return result;
	}
	if (left.size() < right.size()) {
		for (auto& leftIterator : left) {
			//unordered_set<int> nextBip = pkb->getNextBipStmt(leftIterator);
			unordered_set<int> nextBip = pkb->getNextStmt(leftIterator);
			for (auto& it : nextBip) {
				if (right.find(it) != right.end()) {
					insertTuple(leftIterator, it);
				}
			}
		}
	}
	else {
		for (auto& rightIterator : right) {
			unordered_set<int> prev = pkb->getPreviousStmt(rightIterator);
			for (auto& it : prev) {
				if (left.find(it) != left.end()) {
					insertTuple(it, rightIterator);
				}
			}
		}
	}
	return result;
}

ResultTable NextBip::getNextBipSynSyn(PKB* pkb, ResultTable* resultTable) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		return result;
	}
	vector<Parameter> synonyms = resultTable->getSynList();
	vector<vector<int>> tupleList = resultTable->getTupleList();
	if (isLeftChild(synonyms[0])) {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isNextBip(pkb, unordered_set<int>({ tupleList[i][0] }), unordered_set<int>({ tupleList[i][1] }))) {
				vector<int> tuple = { tupleList[i][0], tupleList[i][1] };
				result.insertTuple(tuple);
			}
		}
	}
	else {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isNextBip(pkb, unordered_set<int>({ tupleList[i][1] }), unordered_set<int>({ tupleList[i][0] }))) {
				vector<int> tuple = { tupleList[i][1], tupleList[i][0] };
				result.insertTuple(tuple);
			}
		}
	}
	return result;
}

void NextBip::setSynList() {
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

void NextBip::insertTuple(int left, int right) {
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

unordered_set<int> NextBip::getTypeStmt(Parameter p, PKB* pkb) {
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

bool NextBip::isLeftChild(Parameter parameter) {
	return (parameter.getParaName().compare(leftChild.getParaName()) == 0 && parameter.getParaType() == leftChild.getParaType());
}

bool NextBip::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == PROG_LINE || type == IF || type == CALL);
}

bool NextBip::isBooleanClause() {
	return (leftChild.getParaType() == ANYTHING || leftChild.getParaType() == INTEGER)
		&& (rightChild.getParaType() == ANYTHING || rightChild.getParaType() == INTEGER);
}

Parameter NextBip::getLeftChild() {
	return leftChild;
}
Parameter NextBip::getRightChild() {
	return rightChild;
}

vector<Parameter> NextBip::getSynList() {
	return synList;
}

ClauseType NextBip::getClauseType() {
	return FOLLOW;
}