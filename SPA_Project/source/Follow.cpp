#include "Type.h"
#include "Follow.h"
#include "Clause.h"

using namespace std;


Follow::Follow(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;
}

ResultTable Follow::evaluateWithoutRestrictions(PKB* pkb) {
	if (isNumber(leftChild)) {
		if (isNumber(rightChild)) {
			return getFollowNumNum(pkb, stoi(leftChild.getParaName()), stoi(rightChild.getParaName()));
		}
		else if (isSynonym(rightChild)) {
			return getFollowNumSyn(pkb, getTypeStmt(rightChild.getParaType(), pkb), stoi(leftChild.getParaName()));
		}
	}
	else if (isSynonym(leftChild)) {
		if (isNumber(rightChild)) {
			return getFollowSynNum(pkb, getTypeStmt(leftChild.getParaType(), pkb), stoi(rightChild.getParaName()));
		}
		else if (isSynonym(rightChild)) {
			return getFollowSynSyn(pkb, getTypeStmt(leftChild.getParaType(), pkb), getTypeStmt(rightChild.getParaType(), pkb));
		}
	}
	return result;
}

ResultTable Follow::evaluateWithoutOneRestriction(PKB* pkb, ResultTable* resultTable) {
	unordered_set<int> left = resultTable->getSynValue(leftChild);
	unordered_set<int> right = resultTable->getSynValue(rightChild);
	if (isNumber(leftChild)) {
		if (isSynonym(rightChild)) {
			return getFollowNumSyn(pkb, right, stoi(leftChild.getParaName()));
		}
	}
	else if (isSynonym(leftChild)) {
		if (isNumber(rightChild)) {
			return getFollowSynNum(pkb, left, stoi(rightChild.getParaName()));
		}
		else if (isSynonym(rightChild)) {
			if (left.size() == 0) {
				return getFollowSynSyn(pkb, getTypeStmt(leftChild.getParaType(), pkb), right);
			}
			else if (right.size() == 0) {
				return getFollowSynSyn(pkb, left, getTypeStmt(rightChild.getParaType(), pkb));
			}
		}
	}
	return result;
}

ResultTable Follow::evaluate(PKB* pkb, ResultTable resultTable) {
	if (resultTable.getSynCount() == 0) {
		return evaluateWithoutRestrictions(pkb);
	}
	else if (resultTable.getSynCount() == 1) {
		return evaluateWithoutOneRestriction(pkb, &resultTable);
	}
	else if (resultTable.getSynCount() == 2) {
		return getFollowSynSyn(pkb, &resultTable);
		
	}
	return result;
}

ResultTable Follow::getFollowSynNum(PKB* pkb, unordered_set<int> left, int right) {
	result.setSynList(vector<Parameter>({ leftChild }));
	if (isValidStmtNo(right, pkb)) {
		int follows = pkb->getStmtFollowedByStmt(right);
		if (left.find(follows) != left.end()) {
			result.insertTuple(vector<int>(1,follows));
		}
	}
	return result;
}

ResultTable Follow::getFollowNumSyn(PKB* pkb, unordered_set<int> right, int left) {
	result.setSynList(vector<Parameter>({ rightChild }));
	if (isValidStmtNo(left, pkb)) {
		int followedBy = pkb->getStmtFollowStmt(left);
		if (right.find(followedBy) != right.end()) {
			result.insertTuple(vector<int>(1, followedBy));
		}
	}
	return result;
}

ResultTable Follow::getFollowSynSyn(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		return result;
	}
	if (left.size() < right.size()) {
		for (auto& leftIterator : left) {
			int followedBy = pkb->getStmtFollowStmt(leftIterator);
			if (right.find(followedBy) != right.end()) {
				vector<int> tuple = { leftIterator, followedBy };
				result.insertTuple(tuple);
			}
		}
	}
	else {
		for (auto& rightIterator : right) {
			int follows = pkb->getStmtFollowedByStmt(rightIterator);
			if (left.find(follows) != left.end()) {
				vector<int> tuple = { follows, rightIterator };
				result.insertTuple(tuple);
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
			if (isFollows(pkb, tupleList[i][0], tupleList[i][1])) {
				vector<int> tuple = { tupleList[i][0], tupleList[i][1] };
				result.insertTuple(tuple);
			}
		}
	}
	else {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isFollows(pkb, tupleList[i][1], tupleList[i][0])) {
				vector<int> tuple = { tupleList[i][1], tupleList[i][0] };
				result.insertTuple(tuple);
			}
		}
	}
	return result;
}

ResultTable Follow::getFollowNumNum(PKB* pkb, int left, int right) {
	if (!isValidStmtNo(left, pkb)) {
		result.setBoolean(false);
		return result;
	}
	if (!isValidStmtNo(right, pkb)) {
		result.setBoolean(false);
		return result;
	}
	result.setBoolean(isFollows(pkb, left, right));
	return result;
}

bool Follow::isFollows(PKB* pkb, int left, int right) {
	int follows = pkb->getStmtFollowedByStmt(right);
	if (follows == left) {
		return true;
	}
	else {
		return false;
	}
}

unordered_set<int> Follow::getTypeStmt(Type type, PKB* pkb) {
	switch (type) {
	case PROG_LINE:
	case STMT:
	case ANYTHING: {
		int numOfStmt = pkb->getNumOfStmt();
		unordered_set<int> stmtList(numOfStmt);
		for (int i = 0; i < numOfStmt; i++) {
			stmtList.insert(i + 1);
		}
		return stmtList;
	}
	case WHILE:
		return pkb->getAllWhileStmt();
	case ASSIGN:
		return pkb->getAllAssignStmt();
	case IF:
		return pkb->getAllIfId();
	case CALL:
		return pkb->getAllCallId();
	}
	return unordered_set<int>();
}

bool Follow::isNumber(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == INTEGER);
}

bool Follow::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == ANYTHING || type == PROG_LINE || type == IF || type == CALL);
}

bool Follow::isLeftChild(Parameter parameter) {
	return (parameter.getParaName().compare(leftChild.getParaName()) == 0 && parameter.getParaType() == leftChild.getParaType());
}

bool Follow::isRightChild(Parameter parameter) {
	return (parameter.getParaName().compare(rightChild.getParaName()) == 0 && parameter.getParaType() == rightChild.getParaType());
}

bool Follow::isValidStmtNo(int stmtId, PKB* pkb) {
	return ((stmtId > 0) && (stmtId <= pkb->getNumOfStmt()));
}

Parameter Follow::getLeftChild() {
	return leftChild;
}
Parameter Follow::getRightChild() {
	return rightChild;
}

void Follow::insertSynList(Parameter p) {
	synList.push_back(p);
}

vector<Parameter> Follow::getSynList() {
	return synList;
}

ClauseType Follow::getClauseType() {
	return FOLLOW;
}
