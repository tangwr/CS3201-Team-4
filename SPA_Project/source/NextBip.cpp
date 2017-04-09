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
	if (left.size() <= right.size()) {
		for (auto& leftIterator : left) {
			unordered_set<int> nextBip = computeNextBip(leftIterator, pkb);
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
			unordered_set<int> prev = computePrevBip(rightIterator, pkb);
			//unordered_set<int> prev = pkb->getPreviousStmt(rightIterator);
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
			//unordered_set<int> nextBip = pkb->getNextBipStmt(leftIterator);
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
			//unordered_set<int> prev = pkb->getPreviousStmt(rightIterator);
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

unordered_set<int> NextBip::computePrevBip(int curr, PKB* pkb) {
	unordered_set<int> prev = pkb->getPreviousStmt(curr);
	unordered_set<int> temp;
	stack<int> negatives;
	for (auto& it : prev) {
		if (it < 0) {
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
			if (it < 0) {
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
		stack<int> calls;
		unordered_set<int> allPrevious;
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
	//return prev;
}

unordered_set<int> NextBip::getLastStmts(int procId, PKB* pkb) {
	unordered_set<int> temp, visited, lastStmts;
	stack<int> negatives;
	int firstStmt = pkb->getStmtLstContainedInProc(procId)[0];
	DFS(firstStmt, &temp, &visited, pkb);

	for (auto& it : temp) {
		if (it < 0) {
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
			if (it < 0) {
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
	if (next.empty()) {
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
		int firstStmt = pkb->getStmtLstContainedInProc(calledProc)[0];
		next.insert(firstStmt);
	}
	else {
		unordered_set<int> temp = pkb->getNextStmt(curr);
		stack<int> negatives;

		for (auto& it : temp) {
			if (it < 0) {
				negatives.push(it);
			}
			else {
				next.insert(it);
			}
		}
		while (!negatives.empty()) {
			temp = pkb->getNextStmt(negatives.top());
			negatives.pop();
			for (auto& it : temp) {
				if (it < 0) {
					negatives.push(it);
				}
				else {
					next.insert(it);
				}
			}
		}
		if (next.empty()) {
			computeLastBip(curr, &next, pkb);
		}
	}
	return next;
}

void NextBip::computeLastBip(int curr, unordered_set<int>* allNextBip, PKB* pkb) {
	unordered_set<int> next = pkb->getNextStmt(curr);
	unordered_set<int> temp;
	stack<int> negatives;

	for (auto& it : next) {
		if (it < 0) {
			negatives.push(it);
		}
		else {
			temp.insert(it);
			allNextBip->insert(it);
		}
	}
	while (!negatives.empty()) {
		next = pkb->getNextStmt(negatives.top());
		negatives.pop();
		for (auto& it : next) {
			if (it < 0) {
				negatives.push(it);
			}
			else {
				temp.insert(it);
				allNextBip->insert(it);
			}
		}
	}

	if (temp.empty()) {
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
	return NEXTBIP;
}
