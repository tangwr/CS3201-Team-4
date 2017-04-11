#include "Type.h"
#include "Clause.h"
#include "Next.h"

#define ZERO 0
#define ONE 1
#define FIRST_SYNONYM_INDEX 0
#define NUM_PARAMETER_WITH_INTERMEDIATE_RESULTS_TWO 2

using namespace std;

Next::Next(Parameter lc, Parameter rc) {
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

ResultTable Next::evaluate(PKB* pkb, ResultTable resultTable) {
	if (resultTable.getSynCount() == NUM_PARAMETER_WITH_INTERMEDIATE_RESULTS_TWO) {
		return getNextSynSyn(pkb, &resultTable);
	}
	else if (isBooleanClause()) {
		result.setBoolean(isNext(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb)));
		return result;
	}
	else {
		unordered_set<int> left = resultTable.getSynValue(leftChild);
		unordered_set<int> right = resultTable.getSynValue(rightChild);
		if (!left.empty()) {
			return getNext(pkb, left, getTypeStmt(rightChild, pkb));
		}
		else if (!right.empty()) {
			return getNext(pkb, getTypeStmt(leftChild, pkb), right);
		}
		else {
			return getNext(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb));
		}
	}
	return result;
}

vector<Parameter> Next::getSynList() {
	return synList;
}

ClauseType Next::getClauseType() {
	return NEXT;
}

bool Next::isNext(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	if (left.size() < right.size()) {
		for (auto& leftIterator : left) {
			unordered_set<int> next = getNextStmt(leftIterator, pkb);
			for (auto& it : next) {
				if (right.find(it) != right.end()) {
					return true;
				}
			}
		}
	}
	else {
		for (auto& rightIterator : right) {
			unordered_set<int> prev = getPreviousStmt(rightIterator, pkb);
			for (auto& it : prev) {
				if (left.find(it) != left.end()) {
					return true;
				}
			}
		}
	}
	return false;
}

ResultTable Next::getNext(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	setSynList();
	if (isLeftChild(rightChild)) {
		return result;
	}
	if (left.size() < right.size()) {
		for (auto& leftIterator : left) {
			unordered_set<int> next = getNextStmt(leftIterator, pkb);
			for (auto& it : next) {
				if (right.find(it) != right.end()) {
					insertTuple(leftIterator, it);
				}
			}
		}
	}
	else {
		for (auto& rightIterator : right) {
			unordered_set<int> prev = getPreviousStmt(rightIterator, pkb);
			for (auto& it : prev) {
				if (left.find(it) != left.end()) {
					insertTuple(it, rightIterator);
				}
			}
		}
	}
	return result;
}

ResultTable Next::getNextSynSyn(PKB* pkb, ResultTable* resultTable) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		return result;
	}
	vector<Parameter> synonyms = resultTable->getSynList();
	vector<vector<int>> tupleList = resultTable->getTupleList();
	if (isLeftChild(synonyms[FIRST_SYNONYM_INDEX])) {
		for (int i = ZERO; i < tupleList.size(); i++) {
			if (isNext(pkb, unordered_set<int>({ tupleList[i][ZERO] }), unordered_set<int>({ tupleList[i][ONE] }))) {
				vector<int> tuple = { tupleList[i][ZERO], tupleList[i][ONE] };
				result.insertTuple(tuple);
			}
		}
	}
	else {
		for (int i = ZERO; i < tupleList.size(); i++) {
			if (isNext(pkb, unordered_set<int>({ tupleList[i][ONE] }), unordered_set<int>({ tupleList[i][ZERO] }))) {
				vector<int> tuple = { tupleList[i][ONE], tupleList[i][ZERO] };
				result.insertTuple(tuple);
			}
		}
	}
	return result;
}

void Next::setSynList() {
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

void Next::insertTuple(int left, int right) {
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

unordered_set<int> Next::getTypeStmt(Parameter p, PKB* pkb) {
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

unordered_set<int> Next::getNextStmt(int a, PKB* pkb) {
	unordered_set<int> next = pkb->getNextStmt(a);
	unordered_set<int> temp;
	stack<int> negatives;
	for (auto& it : next) {
		if (it < ZERO) {
			negatives.push(it);
		}
		else {
			temp.insert(it);
		}
	}

	while (!negatives.empty()) {
		next = pkb->getNextStmt(negatives.top());
		negatives.pop();
		for (auto& it : next) {
			if (it < ZERO) {
				negatives.push(it);
			}
			else {
				temp.insert(it);
			}
		}
	}
	return temp;
}

unordered_set<int> Next::getPreviousStmt(int a, PKB* pkb) {
	unordered_set<int> prev = pkb->getPreviousStmt(a);
	unordered_set<int> temp;
	stack<int> negatives;
	for (auto& it : prev) {
		if (it < ZERO) {
			negatives.push(it);
		}
		else {
			temp.insert(it);
		}
	}

	while (!negatives.empty()) {
		prev = pkb->getPreviousStmt(negatives.top());
		negatives.pop();
		for (auto& it : prev) {
			if (it < ZERO) {
				negatives.push(it);
			}
			else {
				temp.insert(it);
			}
		}
	}
	return temp;
}

bool Next::isLeftChild(Parameter parameter) {
	return (parameter.getParaName().compare(leftChild.getParaName()) == ZERO && parameter.getParaType() == leftChild.getParaType());
}

bool Next::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == PROG_LINE || type == IF || type == CALL);
}

bool Next::isBooleanClause() {
	return (leftChild.getParaType() == ANYTHING || leftChild.getParaType() == INTEGER)
		&& (rightChild.getParaType() == ANYTHING || rightChild.getParaType() == INTEGER);
}