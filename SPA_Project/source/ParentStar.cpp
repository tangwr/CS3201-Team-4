#include "Type.h"
#include "ParentStar.h"
#include "Clause.h"


ParentStar::ParentStar(Parameter lc, Parameter rc) {
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

ResultTable ParentStar::evaluate(PKB* pkb, ResultTable resultTable) {
	if (resultTable.getSynCount() == 2) {
		return getParentStarSynSyn(pkb, &resultTable);
	}
	else if (isBooleanClause()) {
		result.setBoolean(isParentStar(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb)));
		return result;
	}
	else {
		unordered_set<int> left = resultTable.getSynValue(leftChild);
		unordered_set<int> right = resultTable.getSynValue(rightChild);
		if (left.size() != 0) {
			return getParentStar(pkb, left, getTypeStmt(rightChild, pkb));
		}
		else if (right.size() != 0) {
			return getParentStar(pkb, getTypeStmt(leftChild, pkb), right);
		}
		else {
			return getParentStar(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb));
		}
	}
	return result;
}

bool ParentStar::isParentStar(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	for (auto& rightIterator : right) {
		unordered_set<int> parentStar = pkb->getStmtParentStarStmt(rightIterator);
		for (auto& it : parentStar) {
			if (left.find(it) != left.end()) {
				return true;
			}
		}
	}
	return false;
}

ResultTable ParentStar::getParentStar(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	setSynList();
	if (isLeftChild(rightChild)) {
		return result;
	}
	if (left.size() == 1) {
		for (auto& leftIterator : left) {
			unordered_set<int> childrenStar = pkb->getStmtChildrenStarStmt(leftIterator);
			for (auto& it : childrenStar) {
				if (right.find(it) != right.end()) {
					insertTuple(leftIterator, it);
				}
			}
		}
	}
	else {
		for (auto& rightIterator : right) {
			unordered_set<int> parentStar = pkb->getStmtParentStarStmt(rightIterator);
			for (auto& it : parentStar) {
				if (left.find(it) != left.end()) {
					insertTuple(it, rightIterator);
				}
			}
		}
	}
	return result;
}

ResultTable ParentStar::getParentStarSynSyn(PKB* pkb, ResultTable* resultTable) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		return result;
	}
	vector<Parameter> synonyms = resultTable->getSynList();
	vector<vector<int>> tupleList = resultTable->getTupleList();
	if (isLeftChild(synonyms[0])) {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isParentStar(pkb, unordered_set<int>({ tupleList[i][0] }), unordered_set<int>({ tupleList[i][1] }))) {
				vector<int> tuple = { tupleList[i][0], tupleList[i][1] };
				result.insertTuple(tuple);
			}
		}
	}
	else {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isParentStar(pkb, unordered_set<int>({ tupleList[i][1] }), unordered_set<int>({ tupleList[i][0] }))) {
				vector<int> tuple = { tupleList[i][1], tupleList[i][0] };
				result.insertTuple(tuple);
			}
		}
	}
	return result;
}

void ParentStar::setSynList() {
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

void ParentStar::insertTuple(int left, int right) {
	vector<int> v;
	if (isSynonym(leftChild)) {
		if (isSynonym(rightChild)) {
			cout << "Parent: " << left << " Child: " << right << endl;
			v = { left, right };
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

unordered_set<int> ParentStar::getTypeStmt(Parameter p, PKB* pkb) {
	Type type = p.getParaType();
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
	case INTEGER:
		return unordered_set<int>({ stoi(p.getParaName()) });
	}
	return unordered_set<int>();
}

bool ParentStar::isLeftChild(Parameter parameter) {
	return (parameter.getParaName().compare(leftChild.getParaName()) == 0 && parameter.getParaType() == leftChild.getParaType());
}

bool ParentStar::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == PROG_LINE || type == IF || type == CALL);
}

bool ParentStar::isBooleanClause() {
	return (leftChild.getParaType() == ANYTHING || leftChild.getParaType() == INTEGER)
		&& (rightChild.getParaType() == ANYTHING || rightChild.getParaType() == INTEGER);
}

Parameter ParentStar::getLeftChild() {
	return leftChild;
}
Parameter ParentStar::getRightChild() {
	return rightChild;
}

vector<Parameter> ParentStar::getSynList() {
	return synList;
}

ClauseType ParentStar::getClauseType() {
	return PARENTSTAR;
}
/*
ParentStar::ParentStar(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;
	if (isSynonym(leftChild) && leftChild.getParaType() != ANYTHING) {
		synList.push_back(leftChild);
	}
	if (isSynonym(rightChild) && rightChild.getParaType() != ANYTHING) {
		synList.push_back(rightChild);
	}
}

ResultTable ParentStar::evaluateWithoutRestrictions(PKB* pkb) {
	if (isNumber(leftChild)) {
		if (isNumber(rightChild)) {
			return getParentStarNumNum(pkb, stoi(leftChild.getParaName()), stoi(rightChild.getParaName()));
		}
		else if (isSynonym(rightChild)) {
			return getParentStarNumSyn(pkb, getTypeStmt(rightChild.getParaType(), pkb), stoi(leftChild.getParaName()));
		}
	}
	else if (isSynonym(leftChild)) {
		if (isNumber(rightChild)) {
			return getParentStarSynNum(pkb, getTypeStmt(leftChild.getParaType(), pkb), stoi(rightChild.getParaName()));
		}
		else if (isSynonym(rightChild)) {
			return getParentStarSynSyn(pkb, getTypeStmt(leftChild.getParaType(), pkb), getTypeStmt(rightChild.getParaType(), pkb));
		}
	}
	return result;
}

ResultTable ParentStar::evaluateWithoutOneRestriction(PKB* pkb, ResultTable* resultTable) {
	unordered_set<int> left = resultTable->getSynValue(leftChild);
	unordered_set<int> right = resultTable->getSynValue(rightChild);
	if (isNumber(leftChild)) {
		if (isSynonym(rightChild)) {
			return getParentStarNumSyn(pkb, right, stoi(leftChild.getParaName()));
		}
	}
	else if (isSynonym(leftChild)) {
		if (isNumber(rightChild)) {
			return getParentStarSynNum(pkb, left, stoi(rightChild.getParaName()));
		}
		else if (isSynonym(rightChild)) {
			if (left.size() == 0) {
				return getParentStarSynSyn(pkb, getTypeStmt(leftChild.getParaType(), pkb), right);
			}
			else if (right.size() == 0) {
				return getParentStarSynSyn(pkb, left, getTypeStmt(rightChild.getParaType(), pkb));
			}
		}
	}
	return result;
}

ResultTable ParentStar::evaluate(PKB* pkb, ResultTable resultTable) {
	unordered_set<int> left = resultTable.getSynValue(leftChild);
	unordered_set<int> right = resultTable.getSynValue(rightChild);
	if (resultTable.getSynCount() == 0) {
		return evaluateWithoutRestrictions(pkb);
	}
	else if (resultTable.getSynCount() == 1) {
		return evaluateWithoutOneRestriction(pkb, &resultTable);
	}
	else if (resultTable.getSynCount() == 2) {
		return getParentStarSynSyn(pkb, &resultTable);
	}
	return result;
}

ResultTable ParentStar::getParentStarSynNum(PKB* pkb, unordered_set<int> left, int right) {
	result.setSynList(vector<Parameter>({ leftChild }));
	if (isValidStmtNo(right, pkb)) {
		unordered_set<int> parentStar = pkb->getStmtParentStarStmt(right);
		for (auto& it : parentStar) {
			if (left.find(it) != left.end()) {
				result.insertTuple(vector<int>(1, it));
			}
		}
	}
	return result;
}

ResultTable ParentStar::getParentStarNumSyn(PKB* pkb, unordered_set<int> right, int left) {
	result.setSynList(vector<Parameter>({ rightChild }));
	if (isValidStmtNo(left, pkb)) {
		unordered_set<int> childrenStar = pkb->getStmtChildrenStarStmt(left);
		for (auto& it : childrenStar) {
			if (right.find(it) != right.end()) {
				result.insertTuple(vector<int>(1, it));
			}
		}
	}
	return result;
}

ResultTable ParentStar::getParentStarSynSyn(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		return result;
	}
	for (auto& rightIterator : right) {
		unordered_set<int> parentStar = pkb->getStmtParentStarStmt(rightIterator);
		for (auto& it : parentStar) {
			if (left.find(it) != left.end()) {
				vector<int> tuple = { it, rightIterator };
				result.insertTuple(tuple);
			}
		}
	}

	return result;
}

ResultTable ParentStar::getParentStarSynSyn(PKB* pkb, ResultTable* resultTable) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		return result;
	}
	vector<Parameter> synonyms = resultTable->getSynList();
	vector<vector<int>> tupleList = resultTable->getTupleList();

	if (isLeftChild(synonyms[0])) {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isParentStar(pkb, tupleList[i][0], tupleList[i][1])) {
				vector<int> tuple = { tupleList[i][0], tupleList[i][1] };
				result.insertTuple(tuple);
			}
		}
	}
	else {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isParentStar(pkb, tupleList[i][1], tupleList[i][0])) {
				vector<int> tuple = { tupleList[i][1], tupleList[i][0] };
				result.insertTuple(tuple);
			}
		}
	}
	return result;
}

ResultTable ParentStar::getParentStarNumNum(PKB* pkb, int left, int right) {
	if (!isValidStmtNo(left, pkb)) {
		result.setBoolean(false);
		return result;
	}
	if (!isValidStmtNo(right, pkb)) {
		result.setBoolean(false);
		return result;
	}
	result.setBoolean(isParentStar(pkb, left, right));
	return result;
}

bool ParentStar::isParentStar(PKB* pkb, int left, int right) {
	unordered_set<int> parentStar = pkb->getStmtParentStarStmt(right);
	if (parentStar.find(left) != parentStar.end()) {
		return true;
	}
	else {
		return false;
	}
}

unordered_set<int> ParentStar::getTypeStmt(Type type, PKB* pkb) {
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

bool ParentStar::isNumber(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == INTEGER);
}

bool ParentStar::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == ANYTHING || type == PROG_LINE || type == IF || type == CALL);
}

bool ParentStar::isLeftChild(Parameter parameter) {
	return (parameter.getParaName().compare(leftChild.getParaName()) == 0 && parameter.getParaType() == leftChild.getParaType());
}

bool ParentStar::isValidStmtNo(int stmtId, PKB* pkb) {
	return ((stmtId > 0) && (stmtId <= pkb->getNumOfStmt()));
}

Parameter ParentStar::getLeftChild() {
	return leftChild;
}
Parameter ParentStar::getRightChild() {
	return rightChild;
}
vector<Parameter> ParentStar::getSynList() {
	return synList;
}
ClauseType ParentStar::getClauseType() {
	return PARENTSTAR;
}
*/