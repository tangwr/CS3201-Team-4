#include "Type.h"
#include "Parent.h"
#include "Clause.h"
#include "unordered_set"




Parent::Parent(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;
	if (leftChild.isSynonym()) {
		synList.push_back(leftChild);
	}
	if (rightChild.isSynonym()) {
		synList.push_back(rightChild);
	}
}


ResultTable Parent::evaluateWithoutRestrictions(PKB* pkb) {
	if (isNumber(leftChild)) {
		if (isNumber(rightChild)) {
			return getParentNumNum(pkb, stoi(leftChild.getParaName()), stoi(rightChild.getParaName()));
		}
		else if (isSynonym(rightChild)) {
			return getParentNumSyn(pkb, getTypeStmt(rightChild.getParaType(), pkb), stoi(leftChild.getParaName()));
		}
	}
	else if (isSynonym(leftChild)) {
		if (isNumber(rightChild)) {
			return getParentSynNum(pkb, getTypeStmt(leftChild.getParaType(), pkb), stoi(rightChild.getParaName()));
		}
		else if (isSynonym(rightChild)) {
			return getParentSynSyn(pkb, getTypeStmt(leftChild.getParaType(), pkb), getTypeStmt(rightChild.getParaType(), pkb));
		}
	}
	return result;
}

ResultTable Parent::evaluateWithoutOneRestriction(PKB* pkb, ResultTable* resultTable) {
	unordered_set<int> left = resultTable->getSynValue(leftChild);
	unordered_set<int> right = resultTable->getSynValue(rightChild);
	if (isNumber(leftChild)) {
		if (isSynonym(rightChild)) {
			return getParentNumSyn(pkb, right, stoi(leftChild.getParaName()));
		}
	}
	else if (isSynonym(leftChild)) {
		if (isNumber(rightChild)) {
			return getParentSynNum(pkb, left, stoi(rightChild.getParaName()));
		}
		else if (isSynonym(rightChild)) {
			if (left.size() == 0) {
				return getParentSynSyn(pkb, getTypeStmt(leftChild.getParaType(), pkb), right);
			}
			else if (right.size() == 0) {
				return getParentSynSyn(pkb, left, getTypeStmt(rightChild.getParaType(), pkb));
			}
		}
	}
	return result;
}

ResultTable Parent::evaluate(PKB* pkb, ResultTable resultTable) {
	unordered_set<int> left = resultTable.getSynValue(leftChild);
	unordered_set<int> right = resultTable.getSynValue(rightChild);
	if (resultTable.getSynCount() == 0) {
		return evaluateWithoutRestrictions(pkb);
	}
	else if (resultTable.getSynCount() == 1) {
		return evaluateWithoutOneRestriction(pkb, &resultTable);
	}
	else if (resultTable.getSynCount() == 2) {
		return getParentSynSyn(pkb, &resultTable);
	}
	return result;
}

ResultTable Parent::getParentSynNum(PKB* pkb, unordered_set<int> left, int right) {
	result.setSynList(vector<Parameter>({ leftChild }));
	if (isValidStmtNo(right, pkb)) {
		int parent = pkb->getStmtParentStmt(right);
		if (left.find(parent) != left.end()) {
			result.insertTuple(vector<int>(1, parent));
		}
	}
	return result;
}

ResultTable Parent::getParentNumSyn(PKB* pkb, unordered_set<int> right, int left) {
	result.setSynList(vector<Parameter>({ rightChild }));
	if (isValidStmtNo(left, pkb)) {
		unordered_set<int> children = pkb->getStmtChildrenStmt(left);
		for (auto& childIterator : children) {
			if (right.find(childIterator) != right.end()) {
				result.insertTuple(vector<int>(1, childIterator));

			}
		}
	}
	return result;
}

ResultTable Parent::getParentSynSyn(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		return result;
	}
	for (auto& rightIterator : right) {
		int parent = pkb->getStmtParentStmt(rightIterator);
		if (left.find(parent) != left.end()) {
			vector<int> tuple = { parent, rightIterator };
			result.insertTuple(tuple);
		}
	}
	return result;
}

ResultTable Parent::getParentSynSyn(PKB* pkb, ResultTable* resultTable) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		return result;
	}
	vector<Parameter> synonyms = resultTable->getSynList();
	vector<vector<int>> tupleList = resultTable->getTupleList();
	if (isLeftChild(synonyms[0])) {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isParent(pkb, tupleList[i][0], tupleList[i][1])) {
				vector<int> tuple = { tupleList[i][0], tupleList[i][1] };
				result.insertTuple(tuple);
			}
		}
	}
	else {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isParent(pkb, tupleList[i][1], tupleList[i][0])) {
				vector<int> tuple = { tupleList[i][1], tupleList[i][0] };
				result.insertTuple(tuple);
			}
		}
	}
	return result;
}

ResultTable Parent::getParentNumNum(PKB* pkb, int left, int right) {
	if (!isValidStmtNo(left, pkb)) {
		result.setBoolean(false);
		return result;
	}
	if (!isValidStmtNo(right, pkb)) {
		result.setBoolean(false);
		return result;
	}
	result.setBoolean(isParent(pkb, left, right));
	return result;
}

bool Parent::isParent(PKB* pkb, int left, int right) {
	int parent = pkb->getStmtParentStmt(right);
	if (parent == left) {
		return true;
	}
	else {
		return false;
	}
}

unordered_set<int> Parent::getTypeStmt(Type type, PKB* pkb) {
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

bool Parent::isNumber(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == INTEGER);
}

bool Parent::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == ANYTHING || type == PROG_LINE || type == IF || type == CALL);
}

bool Parent::isLeftChild(Parameter parameter) {
	return (parameter.getParaName().compare(leftChild.getParaName()) == 0 && parameter.getParaType() == leftChild.getParaType());
}

bool Parent::isValidStmtNo(int stmtId, PKB* pkb) {
	return ((stmtId > 0) && (stmtId <= pkb->getNumOfStmt()));
}

Parameter Parent::getLeftChild() {
	return leftChild;
}
Parameter Parent::getRightChild() {
	return rightChild;
}
vector<Parameter> Parent::getSynList() {
	return synList;
}

ClauseType Parent::getClauseType() {
	return PARENT;
}

