#include "Type.h"
#include "Clause.h"
#include "NextBipStar.h"

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

ResultTable NextBipStar::evaluate(PKB* pkb, ResultTable resultTable) {
	if (resultTable.getSynCount() == 2) {
		return getNextBipStarSynSyn(pkb, &resultTable);
	}
	else if (isBooleanClause()) {
		result.setBoolean(isNextBipStar(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb)));
		return result;
	}
	else {
		unordered_set<int> left = resultTable.getSynValue(leftChild);
		unordered_set<int> right = resultTable.getSynValue(rightChild);
		if (left.size() != 0) {
			if (right.size() != 0) {
				return getNextBipStarSynSyn(pkb, &resultTable);
			}
			return getNextBipStar(pkb, left, getTypeStmt(rightChild, pkb));
		}
		else if (right.size() != 0) {
			return getNextBipStar(pkb, getTypeStmt(leftChild, pkb), right);
		}
		else {
			return getNextBipStar(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb));
		}
	}
	return result;
}

bool NextBipStar::isNextBipStar(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	if (left.size() <= right.size()) {
		for (auto& leftIterator : left) {
			unordered_set<int> nextBipStar;
			getAllNextBipStar(leftIterator, &nextBipStar, pkb);
			for (auto& it : nextBipStar) {
				if (right.find(it) != right.end()) {
					return true;
				}
			}
		}
	}
	else {
		for (auto& rightIterator : right) {
			unordered_set<int> prevStar;
			getAllPrevStar(rightIterator, &prevStar, pkb);
			for (auto& it : prevStar) {
				if (left.find(it) != left.end()) {
					return true;
				}
			}
		}
	}
	return false;
}

ResultTable NextBipStar::getNextBipStar(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	setSynList();
	if (isLeftChild(rightChild)) {
		return isNextBipStarItself(pkb, getTypeStmt(leftChild, pkb));
	}

	if (left.size() <= right.size()) {
		for (auto& leftIterator : left) {
			unordered_set<int> nextBipStar;
			getAllNextBipStar(leftIterator, &nextBipStar, pkb);
			for (auto& it : nextBipStar) {
				if (right.find(it) != right.end()) {
					insertTuple(leftIterator, it);
				}
			}
		}
	}
	else {
		for (auto& rightIterator : right) {
			unordered_set<int> prevStar;
			getAllPrevStar(rightIterator, &prevStar, pkb);
			for (auto& it : prevStar) {
				if (left.find(it) != left.end()) {
					insertTuple(it, rightIterator);
				}
			}
		}
	}
	return result;
}

ResultTable NextBipStar::getNextBipStarSynSyn(PKB* pkb, ResultTable* resultTable) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		return isNextBipStarItself(pkb, resultTable->getSynValue(leftChild));
	}
	vector<Parameter> synonyms = resultTable->getSynList();
	vector<vector<int>> tupleList = resultTable->getTupleList();
	unordered_set<int> left = resultTable->getSynValue(leftChild);
	unordered_set<int> right = resultTable->getSynValue(rightChild);
	if (isLeftChild(synonyms[0])) {
		if (left.size() <= right.size()) {
			unordered_map<int, unordered_set<int>> allNextBipStars;
			for (auto& it : left) {
				unordered_set<int> allNextBipStar;
				getAllNextBipStar(it, &allNextBipStar, pkb);
				allNextBipStars.insert({ it, allNextBipStar });
			}
			for (int i = 0; i < tupleList.size(); i++) {
				auto& it = allNextBipStars.find(tupleList[i][0]);
				if (it->second.find(tupleList[i][1]) != it->second.end()) {
					vector<int> tuple = { tupleList[i][0], tupleList[i][1] };
					result.insertTuple(tuple);
				}
			}
		}
		else {
			unordered_map<int, unordered_set<int>> allPrevStars;
			for (auto& it : right) {
				unordered_set<int> allPrevStar;
				getAllPrevStar(it, &allPrevStar, pkb);
				allPrevStars.insert({ it, allPrevStar });
			}
			for (int i = 0; i < tupleList.size(); i++) {
				auto& it = allPrevStars.find(tupleList[i][1]);
				if (it->second.find(tupleList[i][0]) != it->second.end()) {
					vector<int> tuple = { tupleList[i][0], tupleList[i][1] };
					result.insertTuple(tuple);
				}
			}
		}
	}
	else {
		if (left.size() <= right.size()) {
			unordered_map<int, unordered_set<int>> allNextBipStars;
			for (auto& it : left) {
				unordered_set<int> allNextBipStar;
				getAllNextBipStar(it, &allNextBipStar, pkb);
				allNextBipStars.insert({ it, allNextBipStar });
			}
			for (int i = 0; i < tupleList.size(); i++) {
				unordered_set<int> allNextBipStar = (allNextBipStars.find(tupleList[i][1])->second);
				if (allNextBipStar.find(tupleList[i][0]) != allNextBipStar.end()) {
					vector<int> tuple = { tupleList[i][1], tupleList[i][0] };
					result.insertTuple(tuple);
				}
			}
		}
		else {
			unordered_map<int, unordered_set<int>> allPrevStars;
			for (auto& it : right) {
				unordered_set<int> allPrevStar;
				getAllPrevStar(it, &allPrevStar, pkb);
				allPrevStars.insert({ it, allPrevStar });
			}
			for (int i = 0; i < tupleList.size(); i++) {
				auto& it = allPrevStars.find(tupleList[i][0]);
				int a = tupleList[i][0];
				int b = tupleList[i][1];
				if (it->second.find(tupleList[i][1]) != it->second.end()) {
					vector<int> tuple = { tupleList[i][1], tupleList[i][0] };
					result.insertTuple(tuple);
				}
			}
		}
	}
	return result;
}

ResultTable NextBipStar::isNextBipStarItself(PKB* pkb, unordered_set<int> stmts) {
	if (leftChild.getParaType() == WHILE) {
		for (auto& it : stmts) {
			insertTuple(it, it);
			return result;
		}
	}
	for (auto& it : stmts) {
		//cout << "IT1: " << it << endl;
		if (pkb->isStmtInWhileTable(it)) {
			cout << "IT2: " << it << endl;
			insertTuple(it, it);
		}
		else {
			unordered_set<int> parentStar = pkb->getStmtParentStarStmt(it);
			for (auto& parent : parentStar) {
				if (pkb->isStmtInWhileTable(parent)) {
					cout << "IT3: " << it << endl;
					insertTuple(it, it);
					break;
				}
			}
		}
	}
	return result;
}

void NextBipStar::getAllNextBipStar(int prev, unordered_set<int>* allNextBipStar, PKB* pkb) {
	//unordered_set<int> visited;
	stack<int> callingStmts;
	getWithinProc(prev, allNextBipStar, &callingStmts, pkb);

	//getAllNextBipStar(prev, allNextBipStar, &visited, pkb);
	return;
}

void NextBipStar::getWithinProc(int curr, unordered_set<int>* allNextBipStar, stack<int>* callingStmts, PKB* pkb) {
	//visited->insert(curr);
	unordered_set<int> next;
	if (pkb->isStmtInCallTable(curr)) {
		int calledProc = pkb->getProcCalledByStmt(curr);
		int firstStmt = pkb->getStmtLstContainedInProc(calledProc)[0];
		if (allNextBipStar->find(firstStmt) != allNextBipStar->end()) {
			next = getNextStmt(curr, pkb);
			//next = pkb->getNextStmt(curr);
		}
		else {
			next.insert(firstStmt);
			callingStmts->push(curr);
		}
	}
	else {
		next = getNextStmt(curr, pkb);
		//next = pkb->getNextStmt(curr);
	}
	while (next.empty()) {
		if (!callingStmts->empty()) {
			int callingStmt = callingStmts->top();
			callingStmts->pop();
			next = getNextStmt(callingStmt, pkb);
			//next = pkb->getNextStmt(callingStmt);
		}
		else {
			break;
		}
	}

	if (next.empty()) {
		// stack must be empty at this point
		int currProc = pkb->getProcContainingStmt(curr);
		unordered_set<int> stmtsCallingProc = pkb->getStmtCallProc(currProc);
		for (auto& stmtCallingProc : stmtsCallingProc) {
			unordered_set<int> nexts = getNextStmt(stmtCallingProc, pkb);
			//unordered_set<int> nexts = pkb->getNextStmt(stmtCallingProc);
			for (auto& it : nexts) {
				if (allNextBipStar->find(it) == allNextBipStar->end()) {
					if (it > 0)
						allNextBipStar->insert(it);
					getWithinProc(it, allNextBipStar, callingStmts, pkb);
				}
			}
		}
	}
	else {
		for (auto& it : next) {
			if (allNextBipStar->find(it) == allNextBipStar->end()) {
				if (it > 0)
					allNextBipStar->insert(it);
				if (pkb->isStmtInIfTable(curr)) {
					stack<int> copiedStack = *callingStmts;
					getWithinProc(it, allNextBipStar, &copiedStack, pkb);
				}
				else {
					getWithinProc(it, allNextBipStar, callingStmts, pkb);
				}
			}
		}
	}
	return;
}

void NextBipStar::getCallNextBipStar(int curr, unordered_set<int>* allNextBipStar, stack<int>* callingStmts, unordered_set<int>* visited, unordered_set<int>* visitedProc, PKB* pkb) {
	visited->insert(curr);
	unordered_set<int> next;
	if (pkb->isStmtInCallTable(curr)) {
		int calledProc = pkb->getProcCalledByStmt(curr);
		visitedProc->insert(calledProc);
		int firstStmt = pkb->getStmtLstContainedInProc(calledProc)[0];
		if (visited->find(firstStmt) != visited->end()) {
			next = getNextStmt(curr, pkb);
			//next = pkb->getNextStmt(curr);
		}
		else {
			next.insert(firstStmt);
			callingStmts->push(curr);
		}
	}
	else {
		next = getNextStmt(curr, pkb);
		//next = pkb->getNextStmt(curr);
	}
	while (next.empty()) {
		if (!callingStmts->empty()) {
			int callingStmt = callingStmts->top();
			callingStmts->pop();
			next = getNextStmt(callingStmt, pkb);
			//next = pkb->getNextStmt(callingStmt);
		}
		else {
			break;
		}
	}
	for (auto& it : next) {
		if (visited->find(it) == visited->end()) {
			if (it > 0)
				allNextBipStar->insert(it);
			if (pkb->isStmtInIfTable(curr)) {
				stack<int> copiedStack = *callingStmts;
				getCallNextBipStar(it, allNextBipStar, &copiedStack, visited, visitedProc, pkb);
			}
			else {
				getCallNextBipStar(it, allNextBipStar, callingStmts, visited, visitedProc, pkb);
			}
		}
	}
	return;
}

unordered_set<int> NextBipStar::getNextStmt(int a, PKB* pkb) {
	unordered_set<int> next = pkb->getNextStmt(a);
	unordered_set<int> temp;
	stack<int> negatives;
	for (auto& it : next) {
		if (it < 0) {
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
			if (it < 0) {
				negatives.push(it);
			}
			else {
				temp.insert(it);
			}
		}
	}
	return temp;
}

unordered_set<int> NextBipStar::getPreviousStmt(int a, PKB* pkb) {
	unordered_set<int> prev = pkb->getPreviousStmt(a);
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
	return temp;
}

void NextBipStar::getAllPrevStar(int next, unordered_set<int>* allPrevStar, PKB* pkb) {
	unordered_set<int> visited, visitedProc;
	getAllPrevStar(next, allPrevStar, &visited, &visitedProc, pkb);
	return;
}

void NextBipStar::getAllPrevStar(int curr, unordered_set<int>* allPrevStar, unordered_set<int>* visited, unordered_set<int>* visitedProc, PKB* pkb) {
	unordered_set<int> prev;
	if (visited->find(curr) != visited->end()) {
		if (pkb->isStmtInCallTable(curr)) {
			int calledProc = pkb->getProcCalledByStmt(curr);
			if (visitedProc->find(calledProc) != visitedProc->end()) {
				return;
			}
			else {
				int firstStmt = pkb->getStmtLstContainedInProc(calledProc)[0];
				prev.insert(firstStmt);
			}
		}
		else {
			return;
		}
	}
	else {
		prev = getPreviousStmt(curr, pkb);
		//prev = pkb->getPreviousStmt(curr);
	}
	visited->insert(curr);

	if (prev.empty()) {
		int currProc = pkb->getProcContainingStmt(curr);
		unordered_set<int> stmtsCallingProc = pkb->getStmtCallProc(currProc);
		for (auto& stmtCallingProc : stmtsCallingProc) {
			allPrevStar->insert(stmtCallingProc);
			getAllPrevStar(stmtCallingProc, allPrevStar, visited, visitedProc, pkb);
		}
	}
	else {
		for (auto& it : prev) {
			if (pkb->isStmtInCallTable(it)) {
				stack<int> callingStmts;
				unordered_set<int> callVisited;
				int calledProc = pkb->getProcCalledByStmt(it);
				int firstStmt = pkb->getStmtLstContainedInProc(calledProc)[0];
				visitedProc->insert(calledProc);
				allPrevStar->insert(firstStmt);
				getCallNextBipStar(firstStmt, allPrevStar, &callingStmts, &callVisited, visitedProc, pkb);
				//getCallNextBipStar(firstStmt, allPrevStar, &callingStmts, visited, visitedProc, pkb);
			}
			allPrevStar->insert(it);
			getAllPrevStar(it, allPrevStar, visited, visitedProc, pkb);
		}
	}
	return;
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
	return (parameter.getParaName().compare(leftChild.getParaName()) == 0 && parameter.getParaType() == leftChild.getParaType());
}

bool NextBipStar::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == PROG_LINE || type == IF || type == CALL);
}

bool NextBipStar::isBooleanClause() {
	return (leftChild.getParaType() == ANYTHING || leftChild.getParaType() == INTEGER)
		&& (rightChild.getParaType() == ANYTHING || rightChild.getParaType() == INTEGER);
}

Parameter NextBipStar::getLeftChild() {
	return leftChild;
}
Parameter NextBipStar::getRightChild() {
	return rightChild;
}

vector<Parameter> NextBipStar::getSynList() {
	return synList;
}

ClauseType NextBipStar::getClauseType() {
	return NEXTBIPSTAR;
}
