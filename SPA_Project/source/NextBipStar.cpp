#include "Type.h"
#include "Clause.h"
#include "NextBipStar.h"

#define ZERO 0
#define ONE 1
#define FIRST_SYNONYM_INDEX 0
#define NUM_PARAMETER_WITH_INTERMEDIATE_RESULTS_TWO 2

using namespace std;

NextBipStar::NextBipStar(Parameter lc, Parameter rc) {
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

ResultTable* NextBipStar::evaluate(PKB* pkb, ResultTable* resultTable) {
	if (resultTable->getSynCount() == NUM_PARAMETER_WITH_INTERMEDIATE_RESULTS_TWO) {
		getNextBipStarSynSyn(pkb, resultTable);
	}
	else if (isBooleanClause()) {
		result.setBoolean(isNextBipStar(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb)));
		return &result;
	}
	else {
		unordered_set<int> left = resultTable->getSynValue(leftChild);
		unordered_set<int> right = resultTable->getSynValue(rightChild);
		if (!left.empty()) {
			if (!right.empty()) {
				getNextBipStarSynSyn(pkb, resultTable);
			}
			else {
				getNextBipStar(pkb, left, getTypeStmt(rightChild, pkb));
			}
		}
		else if (!right.empty()) {
			getNextBipStar(pkb, getTypeStmt(leftChild, pkb), right);
		}
		else {
			getNextBipStar(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb));
		}
	}
	return &result;
}

vector<Parameter> NextBipStar::getSynList() {
	return synList;
}

ClauseType NextBipStar::getClauseType() {
	return NEXTBIPSTAR;
}

bool NextBipStar::isNextBipStar(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	for (auto& leftIterator : left) {
		unordered_set<int> nextBipStar;
		getAllNextBipStar(leftIterator, &nextBipStar, pkb);
		for (auto& it : nextBipStar) {
			if (right.find(it) != right.end()) {
				return true;
			}
		}
	}
	return false;
}

void NextBipStar::getNextBipStar(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	setSynList();
	if (isLeftChild(rightChild)) {
		isNextBipStarItself(pkb, getTypeStmt(leftChild, pkb));
		return;
	}

	for (auto& leftIterator : left) {
		unordered_set<int> nextBipStar;
		getAllNextBipStar(leftIterator, &nextBipStar, pkb);
		for (auto& it : nextBipStar) {
			if (right.find(it) != right.end()) {
				insertTuple(leftIterator, it);
			}
		}
	}
	return;
}

void NextBipStar::getNextBipStarSynSyn(PKB* pkb, ResultTable* resultTable) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		isNextBipStarItself(pkb, resultTable->getSynValue(leftChild));
		return;
	}
	vector<Parameter> synonyms = resultTable->getSynList();
	vector<vector<int>> tupleList = resultTable->getTupleList();
	unordered_set<int> left = resultTable->getSynValue(leftChild);
	unordered_set<int> right = resultTable->getSynValue(rightChild);
	if (isLeftChild(synonyms[FIRST_SYNONYM_INDEX])) {
		unordered_map<int, unordered_set<int>> allNextBipStars;
		for (auto& it : left) {
			unordered_set<int> allNextBipStar;
			getAllNextBipStar(it, &allNextBipStar, pkb);
			allNextBipStars.insert({ it, allNextBipStar });
		}
		for (int i = ZERO; i < tupleList.size(); i++) {
			auto& it = allNextBipStars.find(tupleList[i][ZERO]);
			if (it->second.find(tupleList[i][ONE]) != it->second.end()) {
				vector<int> tuple = { tupleList[i][ZERO], tupleList[i][ONE] };
				result.insertTuple(tuple);
			}
		}
	}
	else {
		unordered_map<int, unordered_set<int>> allNextBipStars;
		for (auto& it : left) {
			unordered_set<int> allNextBipStar;
			getAllNextBipStar(it, &allNextBipStar, pkb);
			allNextBipStars.insert({ it, allNextBipStar });
		}
		for (int i = ZERO; i < tupleList.size(); i++) {
			unordered_set<int> allNextBipStar = (allNextBipStars.find(tupleList[i][ONE])->second);
			if (allNextBipStar.find(tupleList[i][ZERO]) != allNextBipStar.end()) {
				vector<int> tuple = { tupleList[i][ONE], tupleList[i][ZERO] };
				result.insertTuple(tuple);
			}
		}
	}
	return ;
}

unordered_set<int> NextBipStar::computeNextBip(int curr, PKB* pkb) {
	unordered_set<int> next;
	if (pkb->isStmtInCallTable(curr)) {
		int calledProc = pkb->getProcCalledByStmt(curr);
		int firstStmt = pkb->getStmtLstContainedInProc(calledProc)[0];
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

unordered_set<int> NextBipStar::getNextStmt(int a, PKB* pkb) {
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

void NextBipStar::computeLastBip(int curr, unordered_set<int>* allNextBip, PKB* pkb) {
	unordered_set<int> temp = getNextStmt(curr, pkb);
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

void NextBipStar::isNextBipStarItself(PKB* pkb, unordered_set<int> stmts) {
	for (auto& it : stmts) {
		unordered_set<int> allNextBipStar;
		getAllNextBipStar(it, &allNextBipStar, pkb);
		if (allNextBipStar.find(it) != allNextBipStar.end()) {
			insertTuple(it, it);
		}
	}
	return;
}

void NextBipStar::getAllNextBipStar(int prev, unordered_set<int>* allNextBipStar, PKB* pkb) {
	unordered_set<int> visited;
	stack<int> callingStmts;
	getAllNextBipStar(prev, allNextBipStar, &visited, callingStmts, pkb, ZERO);

	return;
}
void NextBipStar::getAllNextBipStar(int curr, unordered_set<int>* allNextBipStar, unordered_set<int>* visited, stack<int> callingStmts, PKB* pkb, int count) {
	if (visited->find(curr) != visited->end()) {
		return;
	}
	unordered_set<int> nextBip = computeNextBip(curr, pkb);
	int currProc = pkb->getProcContainingStmt(curr);
	visited->insert(curr);
	if (count == ZERO) {
		visited->clear();
		count++;
	}

	for (auto& it : nextBip) {
		int nextProc = pkb->getProcContainingStmt(it);
		if (currProc == nextProc) {
			allNextBipStar->insert(it);
			if (pkb->isStmtInIfTable(curr)) {
				stack<int> copiedStack = callingStmts;
				getAllNextBipStar(it, allNextBipStar, visited, copiedStack, pkb, count);
			}
			else {
				getAllNextBipStar(it, allNextBipStar, visited, callingStmts, pkb, count);
			}
		}
		else if (pkb->isStmtInCallTable(curr)) { // next is different proc and curr stmt is call stmt
			int calledProc = pkb->getProcCalledByStmt(curr);
			if (calledProc == nextProc) {
				if (visited->find(it) != visited->end()) {
					unordered_set<int> withinProcNext = pkb->getNextStmt(curr);
					if (!withinProcNext.empty()) {
						int next = *withinProcNext.begin();
						allNextBipStar->insert(next);
						getAllNextBipStar(next, allNextBipStar, visited, callingStmts, pkb, count);
					}
					else {
						unordered_set<int> lastBip;
						computeLastBip(curr, &lastBip, pkb);
						if (!lastBip.empty()) {
							int myLastBip = *lastBip.begin();
							allNextBipStar->insert(myLastBip);
							getAllNextBipStar(myLastBip, allNextBipStar, visited, callingStmts, pkb, count);
						}
					}
				}
				else {
					allNextBipStar->insert(it);
					callingStmts.push(curr);
					getAllNextBipStar(it, allNextBipStar, visited, callingStmts, pkb, count);
				}
			}
		}
		else if(!callingStmts.empty()){ // next is diff proc and curr is not call stmt, and stack is not empty
			stack<int> copiedStack = callingStmts;
			int callingStmt = copiedStack.top();
			copiedStack.pop();
			unordered_set<int> callNext = getNextStmt(callingStmt,pkb);
			while (callNext.empty() && !copiedStack.empty()) {
				callingStmt = copiedStack.top();
				callNext = getNextStmt(callingStmt, pkb);
				copiedStack.pop();
			}
			if (!callNext.empty()) {
				int callsNext = *callNext.begin();
				if (callsNext == it) {
					allNextBipStar->insert(it);
					getAllNextBipStar(it, allNextBipStar, visited, copiedStack, pkb, count);
				}
			}
			else {
				unordered_set<int> lastBip;
				computeLastBip(callingStmt, &lastBip, pkb);
				if (lastBip.empty())
					return;
				int callingStmtNext = *lastBip.begin();
				if (it == callingStmtNext) {
					allNextBipStar->insert(it);
					getAllNextBipStar(it, allNextBipStar, visited, copiedStack, pkb, count);
				}
			}
			
		}
		else if(callingStmts.empty()){
			allNextBipStar->insert(it);
			getAllNextBipStar(it, allNextBipStar, visited, callingStmts, pkb, count);
		}
	}
}

void NextBipStar::setSynList() {
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

void NextBipStar::insertTuple(int left, int right) {
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

unordered_set<int> NextBipStar::getTypeStmt(Parameter p, PKB* pkb) {
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

bool NextBipStar::isLeftChild(Parameter parameter) {
	return (parameter.getParaName().compare(leftChild.getParaName()) == ZERO && parameter.getParaType() == leftChild.getParaType());
}

bool NextBipStar::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == PROG_LINE || type == IF || type == CALL);
}

bool NextBipStar::isBooleanClause() {
	return (leftChild.getParaType() == ANYTHING || leftChild.getParaType() == INTEGER)
		&& (rightChild.getParaType() == ANYTHING || rightChild.getParaType() == INTEGER);
}