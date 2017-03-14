#include "Type.h"
#include "Clause.h"
#include "Next.h"

using namespace std;


Next::Next(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;
}


ResultTable Next::evaluate(PKB* pkb) {
	if (isNumber(leftChild)) {
		if (isNumber(rightChild)) {
			//return getNextNumNum(pkb);
		}
		else if (isSynonym(rightChild)) {
			return getNextNumSyn(pkb, getTypeStmt(rightChild.getParaType(), pkb), stoi(leftChild.getParaName()));
		}
	}
	else if (isSynonym(leftChild)) {
		if (isNumber(rightChild)) {
			return getNextSynNum(pkb, getTypeStmt(leftChild.getParaType(), pkb), stoi(rightChild.getParaName()));
		}
		else if (isSynonym(rightChild)) {
			return getNextSynSyn(pkb, getTypeStmt(leftChild.getParaType(), pkb), getTypeStmt(rightChild.getParaType(), pkb));
		}
	}
	return result;
}

ResultTable Next::evaluate(PKB* pkb, ResultTable resultTable) {
	unordered_set<int> left = resultTable.getSynValue(leftChild);
	unordered_set<int> right = resultTable.getSynValue(rightChild);
	if (resultTable.getSynCount() == 0) {
		return evaluate(pkb);
	}
	else if (resultTable.getSynCount() == 1) {
		if (left.size() != 0) {
			return getNextSynNum(pkb, left, stoi(rightChild.getParaName()));
		}
		else if (right.size() != 0) {
			return getNextNumSyn(pkb, right, stoi(leftChild.getParaName()));
		}
	}
	else if (resultTable.getSynCount() == 2) {
		if (left.size() == 0) {
			return getNextSynSyn(pkb, getTypeStmt(leftChild.getParaType(), pkb), right);
		}
		else if (right.size() == 0) {
			return getNextSynSyn(pkb, left, getTypeStmt(rightChild.getParaType(), pkb));
		}
		else {
			return getNextSynSyn(pkb, &resultTable);
		}
	}
	return result;
}

ResultTable Next::getNextSynNum(PKB* pkb, unordered_set<int> left, int right) {
	result.setSynList(vector<Parameter>({ leftChild }));
	if (isValidStmtNo(right, pkb)) {
		unordered_set<int> prev = pkb->getPreviousStmt(right);
		for (auto& it : prev) {
			if (left.find(it) != left.end()) {
				result.insertTuple(vector<int>(it));

			}
		}
	}
	return result;
}

ResultTable Next::getNextNumSyn(PKB* pkb, unordered_set<int> right, int left) {
	result.setSynList(vector<Parameter>({ rightChild }));
	if (isValidStmtNo(left, pkb)) {
		unordered_set<int> next = pkb->getNextStmt(left);
		for (auto& it : next) {
			if (right.find(it) != right.end()) {
				result.insertTuple(vector<int>(it));

			}
		}
	}
	return result;
}

ResultTable Next::getNextSynSyn(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (left.size() < right.size()) {
		for (auto& leftIterator : left) {
			unordered_set<int> next = pkb->getNextStmt(leftIterator);
			for (auto& it : next) {
				if (right.find(it) != right.end()) {
					result.insertTuple(vector<int>(leftIterator, it));

				}
			}
		}
	}
	else {
		for (auto& rightIterator : right) {
			unordered_set<int> prev = pkb->getPreviousStmt(rightIterator);
			for (auto& it : prev) {
				if (left.find(it) != left.end()) {
					result.insertTuple(vector<int>(it, rightIterator));

				}
			}
		}
	}
	return result;
}

ResultTable Next::getNextSynSyn(PKB* pkb, ResultTable* resultTable) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	vector<Parameter> synonyms = resultTable->getSynList();
	vector<vector<int>> tupleList = resultTable->getTupleList();
	if (leftChild.isSame(synonyms[0])) {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isNext(pkb, tupleList[i][0], tupleList[i][1])) {
				result.insertTuple(vector<int>(tupleList[i][0], tupleList[i][1]));
			}
		}
	}
	else {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isNext(pkb, tupleList[i][1], tupleList[i][0])) {
				result.insertTuple(vector<int>(tupleList[i][1], tupleList[i][0]));
			}
		}
	}
	return result;
}

ResultTable Next::getNextNumNum(PKB* pkb, int left, int right) {
	if (!isValidStmtNo(left, pkb)) {
		result.setBoolean(false);
		return result;
	}
	if (!isValidStmtNo(right, pkb)) {
		result.setBoolean(false);
		return result;
	}
	result.setBoolean(isNext(pkb, left, right));
	return result;
}

bool Next::isNext(PKB* pkb, int left, int right) {
	unordered_set<int> prev = pkb->getPreviousStmt(right);
	if (prev.find(left) != prev.end()) {
		return true;
	}
	return false;
}

unordered_set<int> Next::getTypeStmt(Type type, PKB* pkb) {
	switch (type) {
	case PROG_LINE:
	case STMT:
	case ANYTHING: {
		int numOfStmt = pkb->getNumOfStmt();
		unordered_set<int> stmtList(numOfStmt);
		for (int i = 0; i < numOfStmt; i++) {
			//stmtList[i] = i + 1;
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

bool Next::isNumber(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == INTEGER);
}

bool Next::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == ANYTHING || type == PROG_LINE || type == IF || type == CALL);
}

bool Next::isValidStmtNo(int stmtId, PKB* pkb) {
	return ((stmtId > 0) && (stmtId <= pkb->getNumOfStmt()));
}

void Next::insertSynList(Parameter p) {
	synList.push_back(p);
}

Parameter Next::getLeftChild() {
	return leftChild;
}
Parameter Next::getRightChild() {
	return rightChild;
}
vector<Parameter> Next::getSynList() {
	return synList;
}

ClauseType Next::getClauseType() {
	return NEXT;
}

/*

ResultTable Next::execute(PKB* pkb) {
	if (isNumber(leftChild)) {
		if (isNumber(rightChild)) {
			return getNextNumNum(pkb);
		}
		else if (isSynonym(rightChild)) {
			return getNextNumSyn(pkb);
		}
	}
	else if (isSynonym(leftChild)) {
		if (isNumber(rightChild)) {
			return getNextSynNum(pkb);
		}
		else if (isSynonym(rightChild)) {
			return getNextSynSyn(pkb);
		}
	}
	return result;
}

ResultTable Next::getNextNumNum(PKB* pkb) {
	int leftArgument = stoi(leftChild.getParaName());
	int rightArgument = stoi(rightChild.getParaName());
	if (!isValidStmtNo(leftArgument, pkb)) {
		result.setBoolean(false);
		return result;
	}
	if (!isValidStmtNo(rightArgument, pkb)) {
		result.setBoolean(false);
		return result;
	}

	unordered_set<int> prev = pkb->getPreviousStmt(rightArgument);
	if (prev.find(leftArgument) != prev.end()) {
		result.setBoolean(true);
	}
	else {
		result.setBoolean(false);
	}
	return result;
}

ResultTable Next::getNextNumSyn(PKB* pkb) {
	result.setSynList(vector<Parameter>({ rightChild }));
	int leftArgument = stoi(leftChild.getParaName());
	if (isValidStmtNo(leftArgument, pkb)) { //if left is a valid statement number, Next(num, syn)
		unordered_set<int> next = pkb->getNextStmt(leftArgument);
		for (auto& it : next) {
			if (isStmtType(it, rightChild, pkb)) {
				result.insertTuple(vector<int>(it));
				return result;
			}
		}
	}
	return result;
}

ResultTable Next::getNextSynNum(PKB* pkb) {
	result.setSynList(vector<Parameter>({ leftChild }));
	int rightArgument = stoi(rightChild.getParaName());
	if (isValidStmtNo(rightArgument, pkb)) { //if right is a valid statement number, follows(syn, num)
		unordered_set<int> prev = pkb->getPreviousStmt(rightArgument);
		for (auto& it : prev) {
			if (isStmtType(it, leftChild, pkb)) {
				result.insertTuple(vector<int>(it));
				return result;
			}
		}
	}
	return result;
}

ResultTable Next::getNextSynSyn(PKB* pkb) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (leftChild.getParaName().compare(rightChild.getParaName()) == 0) {
		return result;
	}


	vector<int> right = getTypeStmt(rightChild.getParaType(), pkb);
	for (int i = 0; i < right.size(); i++) {
		unordered_set<int> prev = pkb->getPreviousStmt(rightArgument);
		for (auto& it : prev) {
			if (isStmtType(it, leftChild, pkb)) {
				result.insertTuple(vector<int>(it, right[i]));
				return result;
			}
		}
	}
	return result;
}

vector<int> Next::getTypeStmt(Type type, PKB* pkb) {
	switch (type) {
	case PROG_LINE:
	case STMT:
	case ANYTHING: {
		int numOfStmt = pkb->getNumOfStmt();
		vector<int> stmtList(numOfStmt);
		for (int i = 0; i < numOfStmt; i++) {
			stmtList[i] = i + 1;
		}
		return stmtList;
	}
	case WHILE:
		return pkb->getAllWhileStmt();
	case ASSIGN:
		return pkb->getAllAssignStmt();
	}
	return vector<int>();
}

bool Next::isStmtType(int stmtId, Parameter parameter, PKB* pkb) {
	Type type = parameter.getParaType();
	if (stmtId < 1)
		return false;
	switch (type) {
	case WHILE:
		return pkb->isStmtInWhileTable(stmtId);
	case ASSIGN:
		return pkb->isStmtInAssignTable(stmtId);
	case PROG_LINE:
	case STMT:
	case ANYTHING:
		return true;
	}
	return false;
}

void Next::insertSynList(Parameter p) {
	synList.push_back(p);
}

bool Next::isNumber(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == INTEGER);
}

bool Next::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == ANYTHING || type == PROG_LINE);
}

bool Next::isLeftChild(Parameter parameter) {
	return (parameter.getParaName().compare(leftChild.getParaName()) == 0 && parameter.getParaType == leftChild.getParaType());
}

bool Next::isRightChild(Parameter parameter) {
	return (parameter.getParaName().compare(rightChild.getParaName()) == 0 && parameter.getParaType == rightChild.getParaType());
}

bool Next::isValidStmtNo(int stmtId, PKB* pkb) {
	return ((stmtId > 0) && (stmtId <= pkb->getNumOfStmt()));
}

Parameter Next::getLeftChild() {
	return leftChild;
}
Parameter Next::getRightChild() {
	return rightChild;
}
vector<Parameter> Next::getSynList() {
	return synList;
}*/
