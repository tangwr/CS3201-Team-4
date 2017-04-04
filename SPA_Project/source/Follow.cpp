#include "Type.h"
#include "Follow.h"
#include "Clause.h"

using namespace std;


Follow::Follow(Parameter lc, Parameter rc) {
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

ResultTable Follow::evaluate(PKB* pkb, ResultTable resultTable) {
	if (resultTable.getSynCount() == 2) {
		return getFollowSynSyn(pkb, &resultTable);
	}
	else if (isBooleanClause()) {
		result.setBoolean(isFollows(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb)));
		return result;
	}
	else {
		unordered_set<int> left = resultTable.getSynValue(leftChild);
		unordered_set<int> right = resultTable.getSynValue(rightChild);
		if (left.size() != 0) {
			return getFollow(pkb, left, getTypeStmt(rightChild, pkb));
		}
		else if (right.size() != 0) {
			return getFollow(pkb, getTypeStmt(leftChild, pkb), right);
		}
		else {
			return getFollow(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb));
		}
	}
	return result;
}

bool Follow::isFollows(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	if (left.size() < right.size()) {
		for (auto& it : left) {
			int followedBy = pkb->getStmtFollowStmt(it);
			if (right.find(followedBy) != right.end()) {
				return true;
			}
		}
	}
	else {
		for (auto& it : right) {
			int follows = pkb->getStmtFollowedByStmt(it);
			if (left.find(follows) != left.end()) {
				return true;
			}
		}
	}
	return false;
}

ResultTable Follow::getFollow(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	setSynList();
	if (isLeftChild(rightChild)) {
		return result;
	}
	if (left.size() < right.size()) {
		for (auto& leftIterator : left) {
			int followedBy = pkb->getStmtFollowStmt(leftIterator);
			if (right.find(followedBy) != right.end()) {
				insertTuple(leftIterator, followedBy);
			}
		}
	}
	else {
		for (auto& rightIterator : right) {
			int follows = pkb->getStmtFollowedByStmt(rightIterator);
			if (left.find(follows) != left.end()) {
				insertTuple(follows, rightIterator);
			}
		}
	}
	return result;
}

ResultTable Follow::getFollowSynSyn(PKB* pkb, ResultTable* resultTable) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		return result;
	}
	vector<Parameter> synonyms = resultTable->getSynList();
	vector<vector<int>> tupleList = resultTable->getTupleList();
	if (isLeftChild(synonyms[0])) {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isFollows(pkb, unordered_set<int>({ tupleList[i][0] }), unordered_set<int>({ tupleList[i][1] }))) {
				vector<int> tuple = { tupleList[i][0], tupleList[i][1] };
				result.insertTuple(tuple);
			}
		}
	}
	else {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isFollows(pkb, unordered_set<int>({ tupleList[i][1] }), unordered_set<int>({ tupleList[i][0] }))) {
				vector<int> tuple = { tupleList[i][1], tupleList[i][0] };
				result.insertTuple(tuple);
			}
		}
	}
	return result;
}

void Follow::setSynList() {
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

void Follow::insertTuple(int left, int right) {
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

unordered_set<int> Follow::getTypeStmt(Parameter p, PKB* pkb) {
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

bool Follow::isLeftChild(Parameter parameter) {
	return (parameter.getParaName().compare(leftChild.getParaName()) == 0 && parameter.getParaType() == leftChild.getParaType());
}

bool Follow::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == PROG_LINE || type == IF || type == CALL);
}

bool Follow::isBooleanClause() {
	return (leftChild.getParaType() == ANYTHING || leftChild.getParaType() == INTEGER)
		&& (rightChild.getParaType() == ANYTHING || rightChild.getParaType() == INTEGER);
}

Parameter Follow::getLeftChild() {
	return leftChild;
}
Parameter Follow::getRightChild() {
	return rightChild;
}

vector<Parameter> Follow::getSynList() {
	return synList;
}

ClauseType Follow::getClauseType() {
	return FOLLOW;
}