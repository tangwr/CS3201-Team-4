#include "Type.h"
#include "Clause.h"
#include "NextStar.h"

#define ZERO 0
#define ONE 1
#define FIRST_SYNONYM_INDEX 0
#define NUM_PARAMETER_WITH_INTERMEDIATE_RESULTS_TWO 2

using namespace std;

NextStar::NextStar(Parameter lc, Parameter rc) {
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

ResultTable* NextStar::evaluate(PKB* pkb, ResultTable* resultTable) {
	if (resultTable->getSynCount() == NUM_PARAMETER_WITH_INTERMEDIATE_RESULTS_TWO) {
		getNextStarSynSyn(pkb, resultTable);
	}
	else if (isBooleanClause()) {
		result.setBoolean(isNextStar(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb)));
		return &result;
	}
	else {
		unordered_set<int> left = resultTable->getSynValue(leftChild);
		unordered_set<int> right = resultTable->getSynValue(rightChild);
		if (!left.empty()) {
			if (!right.empty()) {
				getNextStarSynSyn(pkb, resultTable);
			}
			else {
				getNextStar(pkb, left, getTypeStmt(rightChild, pkb));
			}
		}
		else if (!right.empty()) {
			getNextStar(pkb, getTypeStmt(leftChild, pkb), right);
		}
		else {
			getNextStar(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb));
		}
	}
	return &result;
}

vector<Parameter> NextStar::getSynList() {
	return synList;
}

ClauseType NextStar::getClauseType() {
	return NEXTSTAR;
}

bool NextStar::isNextStar(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	if (left.size() < right.size()) {
		for (auto& leftIterator : left) {
			unordered_set<int> nextStar;
			getAllNextStar(leftIterator, &nextStar, pkb);
			for (auto& it : nextStar) {
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

void NextStar::getNextStar(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	setSynList();
	if (isLeftChild(rightChild)) {
		isNextStarItself(pkb, getTypeStmt(leftChild, pkb));
		return;
	}

	if (left.size() < right.size()) {
		for (auto& leftIterator : left) {
			unordered_set<int> nextStar;
			getAllNextStar(leftIterator, &nextStar, pkb);
			for (auto& it : nextStar) {
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
	return;
}

void NextStar::getNextStarSynSyn(PKB* pkb, ResultTable* resultTable) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		isNextStarItself(pkb, resultTable->getSynValue(leftChild));
		return;
	}
	vector<Parameter> synonyms = resultTable->getSynList();
	vector<vector<int>> tupleList = resultTable->getTupleList();
	unordered_set<int> left = resultTable->getSynValue(leftChild);
	unordered_set<int> right = resultTable->getSynValue(rightChild);
	if (isLeftChild(synonyms[FIRST_SYNONYM_INDEX])) {
		if (left.size() < right.size()) {
			unordered_map<int, unordered_set<int>> allNextStars;
			for (auto& it : left) {
				unordered_set<int> allNextStar;
				getAllNextStar(it, &allNextStar, pkb);
				allNextStars.insert({ it, allNextStar });
			}
			for (int i = ZERO; i < tupleList.size(); i++) {
				auto& it = allNextStars.find(tupleList[i][ZERO]);
				if (it->second.find(tupleList[i][ONE]) != it->second.end()) {
					vector<int> tuple = { tupleList[i][ZERO], tupleList[i][ONE] };
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
			for (int i = ZERO; i < tupleList.size(); i++) {
				auto& it = allPrevStars.find(tupleList[i][ONE]);
				if (it->second.find(tupleList[i][ZERO]) != it->second.end()) {
					vector<int> tuple = { tupleList[i][ZERO], tupleList[i][ONE] };
					result.insertTuple(tuple);
				}
			}
		}
	}
	else {
		if (left.size() < right.size()) {
			unordered_map<int, unordered_set<int>> allNextStars;
			for (auto& it : left) {
				unordered_set<int> allNextStar;
				getAllNextStar(it, &allNextStar, pkb);
				allNextStars.insert({ it, allNextStar });
			}
			for (int i = ZERO; i < tupleList.size(); i++) {
				unordered_set<int> allNextStar = (allNextStars.find(tupleList[i][ONE]) -> second);
				if (allNextStar.find(tupleList[i][ZERO]) != allNextStar.end()) {
					vector<int> tuple = { tupleList[i][ONE], tupleList[i][ZERO] };
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
			for (int i = ZERO; i < tupleList.size(); i++) {
				auto& it = allPrevStars.find(tupleList[i][ZERO]);
				int a = tupleList[i][ZERO];
				int b = tupleList[i][ONE];
				if (it->second.find(tupleList[i][ONE]) != it->second.end()) {
					vector<int> tuple = { tupleList[i][ONE], tupleList[i][ZERO] };
					result.insertTuple(tuple);
				}
			}
		}
	}
	return;
}

void NextStar::isNextStarItself(PKB* pkb, unordered_set<int> stmts) {
	for (auto& it : stmts) {
		if (pkb->isStmtInWhileTable(it)) {
			insertTuple(it, it);
		}
		else {
			unordered_set<int> parentStar = pkb->getStmtParentStarStmt(it);
			for (auto& parent : parentStar) {
				if (pkb->isStmtInWhileTable(parent)) {
					insertTuple(it, it);
					break;
				}
			}
		}
	}
	return;
}

void NextStar::getAllNextStar(int prev, unordered_set<int>* allNextStar, PKB* pkb) {
	unordered_set<int> visited;
	getAllNextStar(prev, allNextStar, &visited, pkb);
	return;
}

void NextStar::getAllNextStar(int prev, unordered_set<int>* allNextStar, unordered_set<int>* visited, PKB* pkb) {
	if (visited->find(prev) != visited->end()) {
		return;
	}
	visited->insert(prev);
	unordered_set<int> next = pkb->getNextStmt(prev);
	for (auto& it : next) {
		allNextStar->insert(it);
		getAllNextStar(it, allNextStar, visited, pkb);
	}
	return;
}

void NextStar::getAllPrevStar(int next, unordered_set<int>* allPrevStar, PKB* pkb) {
	unordered_set<int> visited;
	getAllPrevStar(next, allPrevStar, &visited, pkb);
	return;
}

void NextStar::getAllPrevStar(int next, unordered_set<int>* allPrevStar, unordered_set<int>* visited, PKB* pkb) {
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

void NextStar::setSynList() {
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

void NextStar::insertTuple(int left, int right) {
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

unordered_set<int> NextStar::getTypeStmt(Parameter p, PKB* pkb) {
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

bool NextStar::isLeftChild(Parameter parameter) {
	return (parameter.getParaName().compare(leftChild.getParaName()) == ZERO && parameter.getParaType() == leftChild.getParaType());
}

bool NextStar::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == PROG_LINE || type == IF || type == CALL);
}

bool NextStar::isBooleanClause() {
	return (leftChild.getParaType() == ANYTHING || leftChild.getParaType() == INTEGER)
		&& (rightChild.getParaType() == ANYTHING || rightChild.getParaType() == INTEGER);
}