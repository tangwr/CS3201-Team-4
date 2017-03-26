#include "Type.h"
#include "Clause.h"
#include "NextStar.h"

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

ResultTable NextStar::evaluate(PKB* pkb, ResultTable resultTable) {
	if (resultTable.getSynCount() == 2) {
		return getNextStarSynSyn(pkb, &resultTable);
	}
	else if (isBooleanClause()) {
		result.setBoolean(isNextStar(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb)));
		return result;
	}
	else {
		unordered_set<int> left = resultTable.getSynValue(leftChild);
		unordered_set<int> right = resultTable.getSynValue(rightChild);
		if (left.size() != 0) {
			if (right.size() != 0) {
				return getNextStarSynSyn(pkb, &resultTable);
			}
			return getNextStar(pkb, left, getTypeStmt(rightChild, pkb));
		}
		else if (right.size() != 0) {
			return getNextStar(pkb, getTypeStmt(leftChild, pkb), right);
		}
		else {
			return getNextStar(pkb, getTypeStmt(leftChild, pkb), getTypeStmt(rightChild, pkb));
		}
	}
	return result;
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

ResultTable NextStar::getNextStar(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	setSynList();
	if (isLeftChild(rightChild)) {
		return isNextStarItself(pkb, getTypeStmt(leftChild, pkb));
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
	return result;
}

ResultTable NextStar::getNextStarSynSyn(PKB* pkb, ResultTable* resultTable) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		return isNextStarItself(pkb, resultTable->getSynValue(leftChild));
	}
	vector<Parameter> synonyms = resultTable->getSynList();
	vector<vector<int>> tupleList = resultTable->getTupleList();
	if (isLeftChild(synonyms[0])) {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isNextStar(pkb, unordered_set<int>({ tupleList[i][0] }), unordered_set<int>({ tupleList[i][1] }))) {
				vector<int> tuple = { tupleList[i][0], tupleList[i][1] };
				result.insertTuple(tuple);
			}
		}
	}
	else {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isNextStar(pkb, unordered_set<int>({ tupleList[i][1] }), unordered_set<int>({ tupleList[i][0] }))) {
				vector<int> tuple = { tupleList[i][1], tupleList[i][0] };
				result.insertTuple(tuple);
			}
		}
	}
	return result;
}

ResultTable NextStar::isNextStarItself(PKB* pkb, unordered_set<int> stmts) {
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

bool NextStar::isLeftChild(Parameter parameter) {
	return (parameter.getParaName().compare(leftChild.getParaName()) == 0 && parameter.getParaType() == leftChild.getParaType());
}

bool NextStar::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == PROG_LINE || type == IF || type == CALL);
}

bool NextStar::isBooleanClause() {
	return (leftChild.getParaType() == ANYTHING || leftChild.getParaType() == INTEGER)
		&& (rightChild.getParaType() == ANYTHING || rightChild.getParaType() == INTEGER);
}

Parameter NextStar::getLeftChild() {
	return leftChild;
}
Parameter NextStar::getRightChild() {
	return rightChild;
}

vector<Parameter> NextStar::getSynList() {
	return synList;
}

ClauseType NextStar::getClauseType() {
	return FOLLOW;
}

/*
NextStar::NextStar(Parameter lc, Parameter rc) {
leftChild = lc;
rightChild = rc;
if (isSynonym(leftChild) && leftChild.getParaType() != ANYTHING) {
synList.push_back(leftChild);
}
if (isSynonym(rightChild) && rightChild.getParaType() != ANYTHING) {
synList.push_back(rightChild);
}
}

ResultTable NextStar::evaluateWithoutRestrictions(PKB* pkb) {
if (isNumber(leftChild)) {
if (isNumber(rightChild)) {
return getNextStarNumNum(pkb, stoi(leftChild.getParaName()), stoi(rightChild.getParaName()));
}
else if (isSynonym(rightChild)) {
return getNextStarNumSyn(pkb, getTypeStmt(rightChild.getParaType(), pkb), stoi(leftChild.getParaName()));
}
}
else if (isSynonym(leftChild)) {
if (isNumber(rightChild)) {
return getNextStarSynNum(pkb, getTypeStmt(leftChild.getParaType(), pkb), stoi(rightChild.getParaName()));
}
else if (isSynonym(rightChild)) {
return getNextStarSynSyn(pkb, getTypeStmt(leftChild.getParaType(), pkb), getTypeStmt(rightChild.getParaType(), pkb));
}
}
return result;
}

ResultTable NextStar::evaluateWithoutOneRestriction(PKB* pkb, ResultTable* resultTable) {
unordered_set<int> left = resultTable->getSynValue(leftChild);
unordered_set<int> right = resultTable->getSynValue(rightChild);
if (isNumber(leftChild)) {
if (isSynonym(rightChild)) {
return getNextStarNumSyn(pkb, right, stoi(leftChild.getParaName()));
}
}
else if (isSynonym(leftChild)) {
if (isNumber(rightChild)) {
return getNextStarSynNum(pkb, left, stoi(rightChild.getParaName()));
}
else if (isSynonym(rightChild)) {
if (left.size() == 0) {
return getNextStarSynSyn(pkb, getTypeStmt(leftChild.getParaType(), pkb), right);
}
else if (right.size() == 0) {
return getNextStarSynSyn(pkb, left, getTypeStmt(rightChild.getParaType(), pkb));
}
}
}
return result;
}

ResultTable NextStar::evaluate(PKB* pkb, ResultTable resultTable) {
if (resultTable.getSynCount() == 0) {
return evaluateWithoutRestrictions(pkb);
}
else if (resultTable.getSynCount() == 1) {
return evaluateWithoutOneRestriction(pkb, &resultTable);
}
else if (resultTable.getSynCount() == 2) {
return getNextStarSynSyn(pkb, &resultTable);

}
return result;
}

ResultTable NextStar::getNextStarSynNum(PKB* pkb, unordered_set<int> left, int right) {
result.setSynList(vector<Parameter>({ leftChild }));
if (isValidStmtNo(right, pkb)) {
unordered_set<int> allPrevStar;
getAllPrevStar(right, &allPrevStar, pkb);
for (auto& it : allPrevStar) {
if (left.find(it) != left.end()) {
result.insertTuple(vector<int>(1, it));
}
}
}
return result;
}

ResultTable NextStar::getNextStarNumSyn(PKB* pkb, unordered_set<int> right, int left) {
result.setSynList(vector<Parameter>({ rightChild }));
int leftArgument = stoi(leftChild.getParaName());
if (isValidStmtNo(leftArgument, pkb)) {
unordered_set<int> allNextStar;
getAllNextStar(leftArgument, &allNextStar, pkb);
for (auto& it : allNextStar) {
if (right.find(it) != right.end()) {
result.insertTuple(vector<int>(1, it));
}
}
}
return result;
}

ResultTable NextStar::getNextStarSynSyn(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
result.setSynList(vector<Parameter>({ leftChild, rightChild }));
if (isLeftChild(rightChild)) {
return result;
}
if (left.size() < right.size()) {
for (auto& leftIterator : left) {
unordered_set<int> allNextStar;
getAllNextStar(leftIterator, &allNextStar, pkb);
for (auto& it : allNextStar) {
if (right.find(it) != right.end()) {
vector<int> tuple = { leftIterator, it };
result.insertTuple(tuple);
}
}
}
}
else {
for (auto& rightIterator : right) {
unordered_set<int> allPrevStar;
getAllPrevStar(rightIterator, &allPrevStar, pkb);
for (auto& it : allPrevStar) {
if (left.find(it) != left.end()) {
vector<int> tuple = { it, rightIterator };
result.insertTuple(tuple);
}
}
}
}
return result;
}

ResultTable NextStar::getNextStarSynSyn(PKB* pkb, ResultTable* resultTable) {
result.setSynList(vector<Parameter>({ leftChild, rightChild }));
vector<Parameter> synonyms = resultTable->getSynList();
vector<vector<int>> tupleList = resultTable->getTupleList();
if (isLeftChild(synonyms[0])) {
for (int i = 0; i < tupleList.size(); i++) {
if (isNextStar(pkb, tupleList[i][0], tupleList[i][1])) {
vector<int> tuple = { tupleList[i][0], tupleList[i][1] };
result.insertTuple(tuple);
}
}
}
else {
for (int i = 0; i < tupleList.size(); i++) {
if (isNextStar(pkb, tupleList[i][1], tupleList[i][0])) {
vector<int> tuple = { tupleList[i][1], tupleList[i][0] };
result.insertTuple(tuple);
}
}
}
return result;
}

ResultTable NextStar::getNextStarNumNum(PKB* pkb, int left, int right) {
if (!isValidStmtNo(left, pkb)) {
result.setBoolean(false);
return result;
}
if (!isValidStmtNo(right, pkb)) {
result.setBoolean(false);
return result;
}
/*
if (pkb->getProcId(left) != pkb->getProcId(right)) {
result.setBoolean(false);
return result;
}*/
/*

result.setBoolean(isNextStar(pkb, left, right));
return result;
}

bool NextStar::isNextStar(PKB* pkb, int start, int target) {
if (start == target) {
return true;
}
else {
unordered_set<int> visited;
visited.insert(start);
return isNextStar(pkb, start, target, &visited);
}
}


bool NextStar::isNextStar(PKB* pkb, int start, int target, unordered_set<int>* visited) {
if (start == target) {
return true;
}
unordered_set<int> next = pkb->getNextStmt(start);
bool found = false;
for (auto& it : next) {
if (visited->find(it) == visited->end()) {
visited->insert(it);
found = isNextStar(pkb, it, target, visited);
if (found) {
return true;
}
}
}
return false;
}

unordered_set<int> NextStar::getTypeStmt(Type type, PKB* pkb) {
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

bool NextStar::isNumber(Parameter parameter) {
Type type = parameter.getParaType();
return (type == INTEGER);
}

bool NextStar::isSynonym(Parameter parameter) {
Type type = parameter.getParaType();
return (type == ASSIGN || type == WHILE || type == STMT || type == ANYTHING || type == PROG_LINE || type == IF || type == CALL);
}

bool NextStar::isLeftChild(Parameter parameter) {
return (parameter.getParaName().compare(leftChild.getParaName()) == 0 && parameter.getParaType() == leftChild.getParaType());
}

bool NextStar::isRightChild(Parameter parameter) {
return (parameter.getParaName().compare(rightChild.getParaName()) == 0 && parameter.getParaType() == rightChild.getParaType());
}

bool NextStar::isValidStmtNo(int stmtId, PKB* pkb) {
return ((stmtId > 0) && (stmtId <= pkb->getNumOfStmt()));
}

Parameter NextStar::getLeftChild() {
return leftChild;
}
Parameter NextStar::getRightChild() {
return rightChild;
}

vector<Parameter> NextStar::getSynList() {
return synList;
}

ClauseType NextStar::getClauseType() {
return FOLLOW;
}

void NextStar::getAllNextStar(int prev, unordered_set<int>* allNextStar, PKB* pkb) {
unordered_set<int> visited;
getAllNextStar(prev, allNextStar, &visited, pkb);
return ;
}

void NextStar::getAllNextStar(int prev, unordered_set<int>* allNextStar, unordered_set<int>* visited, PKB* pkb) {
if (visited->find(prev) != visited->end()) {
return;
}
visited->insert(prev);
unordered_set<int> next = pkb->getNextStmt(prev);
for (auto& it : next) {
//if (isStmtType(it, rightChild, pkb)) {
allNextStar->insert(it);
//}
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
//if (isStmtType(it, leftChild, pkb)) {
allPrevStar->insert(it);
//}
getAllPrevStar(it, allPrevStar, visited, pkb);
}
return;
}
*/
