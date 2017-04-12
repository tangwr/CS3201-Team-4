#include "Type.h"
#include "Follow.h"
#include "Clause.h"

#define ZERO 0
#define ONE 1
#define FIRST_SYNONYM_INDEX 0
#define NUM_PARAMETER_WITH_INTERMEDIATE_RESULTS_TWO 2

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

ResultTable* Follow::evaluate(PKB* pkb, ResultTable* resultTable) {
	if (resultTable->getSynCount() == NUM_PARAMETER_WITH_INTERMEDIATE_RESULTS_TWO) {
		getFollowSynSyn(pkb, resultTable);
	}
	else if (isBooleanClause()) {
		result.setBoolean(isFollows(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb)));
		return &result;
	}
	else {
		unordered_set<int> left = resultTable->getSynValue(leftChild);
		unordered_set<int> right = resultTable->getSynValue(rightChild);
		if (!left.empty()) {
			getFollow(pkb, left, getTypeStmt(rightChild, pkb));
		}
		else if (!right.empty()) {
			getFollow(pkb, getTypeStmt(leftChild, pkb), right);
		}
		else {
			getFollow(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb));
		}
	}
	return &result;
}

vector<Parameter> Follow::getSynList() {
	return synList;
}

ClauseType Follow::getClauseType() {
	return FOLLOW;
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

void Follow::getFollow(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	setSynList();
	if (isLeftChild(rightChild)) {
		return;
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
	return ;
}

void Follow::getFollowSynSyn(PKB* pkb, ResultTable* resultTable) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		return;
	}
	vector<Parameter> synonyms = resultTable->getSynList();
	vector<vector<int>> tupleList = resultTable->getTupleList();
	if (isLeftChild(synonyms[FIRST_SYNONYM_INDEX])) {
		for (int i = ZERO; i < tupleList.size(); i++) {
			if (isFollows(pkb, unordered_set<int>({ tupleList[i][ZERO] }), unordered_set<int>({ tupleList[i][ONE] }))) {
				vector<int> tuple = { tupleList[i][ZERO], tupleList[i][ONE] };
				result.insertTuple(tuple);
			}
		}
	}
	else {
		for (int i = ZERO; i < tupleList.size(); i++) {
			if (isFollows(pkb, unordered_set<int>({ tupleList[i][ONE] }), unordered_set<int>({ tupleList[i][ZERO] }))) {
				vector<int> tuple = { tupleList[i][ONE], tupleList[i][ZERO] };
				result.insertTuple(tuple);
			}
		}
	}
	return;
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
	return (parameter.getParaName().compare(leftChild.getParaName()) == ZERO && parameter.getParaType() == leftChild.getParaType());
}

bool Follow::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == PROG_LINE || type == IF || type == CALL);
}

bool Follow::isBooleanClause() {
	return (leftChild.getParaType() == ANYTHING || leftChild.getParaType() == INTEGER)
		&& (rightChild.getParaType() == ANYTHING || rightChild.getParaType() == INTEGER);
}