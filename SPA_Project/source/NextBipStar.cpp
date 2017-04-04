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
	if (left.size() < right.size()) {
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

	if (left.size() < right.size()) {
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
		if (left.size() < right.size()) {
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
		if (left.size() < right.size()) {
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
	unordered_set<int> visited;
	getAllNextBipStar(prev, allNextBipStar, &visited, pkb);
	return;
}

void NextBipStar::getAllNextBipStar(int prev, unordered_set<int>* allNextBipStar, unordered_set<int>* visited, PKB* pkb) {
	if (visited->find(prev) != visited->end()) {
		return;
	}
	visited->insert(prev);
	unordered_set<int> next = pkb->getNextStmt(prev);
	for (auto& it : next) {
		allNextBipStar->insert(it);
		getAllNextBipStar(it, allNextBipStar, visited, pkb);
	}
	return;
}

void NextBipStar::getAllPrevStar(int next, unordered_set<int>* allPrevStar, PKB* pkb) {
	unordered_set<int> visited;
	getAllPrevStar(next, allPrevStar, &visited, pkb);
	return;
}

void NextBipStar::getAllPrevStar(int next, unordered_set<int>* allPrevStar, unordered_set<int>* visited, PKB* pkb) {
	if (visited->find(next) != visited->end()) {
		return;
	}
	visited->insert(next);
	unordered_set<int> prev = pkb->getPreviousStmt(next);
	for (auto& it : prev) {
		allPrevStar->insert(it);
		getAllPrevStar(it, allPrevStar, visited, pkb);
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
	return FOLLOW;
}