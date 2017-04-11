#include "Type.h"
#include "Clause.h"
#include "NextBip.h"

#define ZERO 0
#define ONE 1
#define FIRST_SYNONYM_INDEX 0
#define NUM_PARAMETER_WITH_INTERMEDIATE_RESULTS_TWO 2

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
	if (resultTable.getSynCount() == NUM_PARAMETER_WITH_INTERMEDIATE_RESULTS_TWO) {
		return getNextBipSynSyn(pkb, &resultTable);
	}
	else if (isBooleanClause()) {
		result.setBoolean(isNextBip(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb)));
		return result;
	}
	else {
		unordered_set<int> left = resultTable.getSynValue(leftChild);
		unordered_set<int> right = resultTable.getSynValue(rightChild);
		if (!left.empty()) {
			return getNextBip(pkb, left, getTypeStmt(rightChild, pkb));
		}
		else if (!right.empty()) {
			return getNextBip(pkb, getTypeStmt(leftChild, pkb), right);
		}
		else {
			return getNextBip(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb));
		}
	}
	return result;
}

bool NextBip::isNextBip(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	if (left.size() <= right.size()) {
		for (auto& leftIterator : left) {
			unordered_set<int> nextBip = computeNextBip(leftIterator, pkb);
			for (auto& it : nextBip) {
				if (right.find(it) != right.end()) {
					return true;
				}
			}
		}
	}
	else {
		for (auto& rightIterator : right) {
			unordered_set<int> prev = computePrevBip(rightIterator, pkb);
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
	if (left.size() <= right.size()) {
		for (auto& leftIterator : left) {
			unordered_set<int> nextBip = computeNextBip(leftIterator, pkb);
			for (auto& it : nextBip) {
				if (right.find(it) != right.end()) {
					insertTuple(leftIterator, it);
				}
			}
		}
	}
	else {
		for (auto& rightIterator : right) {
			unordered_set<int> prev = computePrevBip(rightIterator, pkb);
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
	if (isLeftChild(synonyms[ZERO])) {
		for (int i = ZERO; i < tupleList.size(); i++) {
			if (isNextBip(pkb, unordered_set<int>({ tupleList[i][ZERO] }), unordered_set<int>({ tupleList[i][ONE] }))) {
				vector<int> tuple = { tupleList[i][ZERO], tupleList[i][ONE] };
				result.insertTuple(tuple);
			}
		}
	}
	else {
		for (int i = ZERO; i < tupleList.size(); i++) {
			if (isNextBip(pkb, unordered_set<int>({ tupleList[i][ONE] }), unordered_set<int>({ tupleList[i][ZERO] }))) {
				vector<int> tuple = { tupleList[i][ONE], tupleList[i][ZERO] };
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

unordered_set<int> NextBip::computePrevBip(int curr, PKB* pkb) {
	unordered_set<int> prev = pkb->getPreviousStmt(curr);
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

	if (temp.empty()) {
		int currProc = pkb->getProcContainingStmt(curr);
		unordered_set<int> callingStmts = pkb->getStmtCallProc(currProc);
		return callingStmts;
	}
	else {
		unordered_set<int> allPrevious;
		if (temp.size() == ONE && pkb->isStmtInWhileTable(curr)) {
			int currProc = pkb->getProcContainingStmt(curr);
			allPrevious = pkb->getStmtCallProc(currProc);
		}
		stack<int> calls;
		for (auto& it : temp) {
			if (pkb->isStmtInCallTable(it)) {
				calls.push(it);
			}
			else {
				allPrevious.insert(it);
			}
		}

		while (!calls.empty()) {
			int calledProc = pkb->getProcCalledByStmt(calls.top());
			temp = getLastStmts(calledProc, pkb);
			calls.pop();
			for (auto& it : temp) {
				if (pkb->isStmtInCallTable(it)) {
					calls.push(it);
				}
				else {
					allPrevious.insert(it);
				}
			}
		}
		return allPrevious;
	}
}

unordered_set<int> NextBip::getLastStmts(int procId, PKB* pkb) {
	unordered_set<int> temp, visited, lastStmts;
	stack<int> negatives;
	int firstStmt = pkb->getStmtLstContainedInProc(procId)[ZERO];
	DFS(firstStmt, &temp, &visited, pkb);

	for (auto& it : temp) {
		if (it < ZERO) {
			negatives.push(it);
		}
		else {
			lastStmts.insert(it);
		}
	}
	while (!negatives.empty()) {
		temp = pkb->getPreviousStmt(negatives.top());
		negatives.pop();
		for (auto& it : temp) {
			if (it < ZERO) {
				negatives.push(it);
			}
			else {
				lastStmts.insert(it);
			}
		}
	}
	return lastStmts;
}

void NextBip::DFS(int currStmt, unordered_set<int>* lastStmts, unordered_set<int>* visited, PKB* pkb) {
	if (!lastStmts->empty()) {
		return;
	}
	if (visited->find(currStmt) != visited->end()) {
		return;
	}
	visited->insert(currStmt);
	unordered_set<int> next = pkb->getNextStmt(currStmt);
	if (next.empty() || (pkb->isStmtInWhileTable(currStmt) && next.size() == ONE)) {
		lastStmts->insert(currStmt);
		return;
	}
	for (auto& it : next) {
		DFS(it, lastStmts, visited, pkb);
	}
}

unordered_set<int> NextBip::computeNextBip(int curr, PKB* pkb) {
	unordered_set<int> next;
	if (pkb->isStmtInCallTable(curr)) {
		int calledProc = pkb->getProcCalledByStmt(curr);
		int firstStmt = pkb->getStmtLstContainedInProc(calledProc)[ZERO];
		next.insert(firstStmt);
	}
	else {
		next = getNextStmt(curr, pkb);
		if (next.empty()) {
			computeLastBip(curr, &next, pkb);
		}
		else if (pkb->isStmtInWhileTable(curr)) {
			if (next.size() == ONE) {
				computeLastBip(curr, &next, pkb);
			}
		}
	}
	return next;
}

unordered_set<int> NextBip::getNextStmt(int a, PKB* pkb) {
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

void NextBip::computeLastBip(int curr, unordered_set<int>* allNextBip, PKB* pkb) {
	unordered_set<int> temp = getNextStmt(curr, pkb);
	stack<int> negatives;
	for (auto& it : temp) {
		allNextBip->insert(it);
	}

	if (temp.empty()) {
		int currProc = pkb->getProcContainingStmt(curr);
		unordered_set<int> callingStmts = pkb->getStmtCallProc(currProc);
		for (auto& it : callingStmts) {
			computeLastBip(it, allNextBip, pkb);
		}
	}
	else if ((pkb->isStmtInWhileTable(curr) && temp.size() == ONE)) {
		int currProc = pkb->getProcContainingStmt(curr);
		unordered_set<int> callingStmts = pkb->getStmtCallProc(currProc);
		for (auto& it : callingStmts) {
			computeLastBip(it, allNextBip, pkb);
		}
	}
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
	return (parameter.getParaName().compare(leftChild.getParaName()) == ZERO && parameter.getParaType() == leftChild.getParaType());
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
	return NEXTBIP;
}
