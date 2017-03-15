#include "Type.h"
#include "Clause.h"
#include "NextStar.h"

using namespace std;


NextStar::NextStar(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;
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
			return getNextStarSynNum(pkb, getTypeStmt(leftChild.getParaType(), pkb), stoi(rightChild.getParaName()));
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
			result.insertTuple(vector<int>(it, right));
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
			result.insertTuple(vector<int>(left, it));
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
				result.insertTuple(vector<int>(leftIterator, it));
			}
		}
	}
	else {
		for (auto& rightIterator : right) {
			unordered_set<int> allPrevStar;
			getAllPrevStar(rightIterator, &allPrevStar, pkb);
			for (auto& it : allPrevStar) {
				result.insertTuple(vector<int>(it, rightIterator));
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
				result.insertTuple(vector<int>(tupleList[i][0], tupleList[i][1]));
			}
		}
	}
	else {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isNextStar(pkb, tupleList[i][1], tupleList[i][0])) {
				result.insertTuple(vector<int>(tupleList[i][1], tupleList[i][0]));
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

bool NextStar::isStmtType(int stmtId, Parameter parameter, PKB* pkb) {
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

void NextStar::insertSynList(Parameter p) {
	synList.push_back(p);
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
		if (isStmtType(it, rightChild, pkb)) {
			allNextStar->insert(it);
		}
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
		if (isStmtType(it, leftChild, pkb)) {
			allPrevStar->insert(it);
		}
		getAllPrevStar(it, allPrevStar, visited, pkb);
	}
	return;
}
/*
ResultTable NextStar::execute(PKB* pkb) {
if (isNumber(leftChild)) {
if (isNumber(rightChild)) {
return getNextStarNumNum(pkb);
}
else if (isSynonym(rightChild)) {
return getNextStarNumSyn(pkb);
}
}
else if (isSynonym(leftChild)) {
if (isNumber(rightChild)) {
return getNextStarSynNum(pkb);
}
else if (isSynonym(rightChild)) {
return getNextStarSynSyn(pkb);
}
}
return result;
}

ResultTable NextStar::getNextStarNumNum(PKB* pkb) {
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
return result;
}
result.setBoolean(false);
return result;
}

ResultTable NextStar::getNextStarNumSyn(PKB* pkb) {
result.setSynList(vector<Parameter>({ rightChild }));
int leftArgument = stoi(leftChild.getParaName());
if (isValidStmtNo(leftArgument, pkb)) { //if left is a valid statement number, Next(num, syn)
unordered_set<int> allNextStar;
getAllNextStar(leftArgument, allNextStar, pkb);
}
return result;
}

ResultTable NextStar::getNextStarSynNum(PKB* pkb) {
result.setSynList(vector<Parameter>({ leftChild }));
int rightArgument = stoi(rightChild.getParaName());
if (isValidStmtNo(rightArgument, pkb)) { //if right is a valid statement number, Next(syn, num)
unordered_set<int> allPrevStar;
getAllPrevStar(rightArgument, allPrevStar, pkb);
}
return result;
}

ResultTable NextStar::getNextStarSynSyn(PKB* pkb) {
result.setSynList(vector<Parameter>({ leftChild, rightChild }));

vector<int> left = getTypeStmt(leftChild.getParaType(), pkb);
unordered_set<int> allNextStar;
for (int i = 0; i < left.size(); i++) {
getAllPrevStar(left[i], allNextStar, pkb);
}
/*
vector<int> right = getTypeStmt(rightChild.getParaType(), pkb);
return getAllPrevStar(right, pkb);*//*
return result;
}

vector<int> NextStar::getTypeStmt(Type type, PKB* pkb) {
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
//return pkb->getAllWhileStmt();
case ASSIGN:;
//return pkb->getAllAssignStmt();
}
return vector<int>();
}


void NextStar::getAllNextStar(int prev, unordered_set<int> allNextStar, PKB* pkb) {
if (allNextStar.find(prev) != allNextStar.end()) {
return;
}
allNextStar.insert(prev);
unordered_set<int> next = pkb->getNextStmt(prev);
for (auto& it : next) {
if (isStmtType(it, rightChild, pkb)) {
result.insertTuple(vector<int>(prev, it));
}
getAllNextStar(it, allNextStar, pkb);
}
return ;
}

void NextStar::getAllPrevStar(int next, unordered_set<int> allPrevStar, PKB* pkb) {
if (allPrevStar.find(next) != allPrevStar.end()) {
return;
}
allPrevStar.insert(next);
unordered_set<int> prev = pkb->getPreviousStmt(next);
for (auto& it : prev) {
if (isStmtType(it, leftChild, pkb)) {
result.insertTuple(vector<int>(it, next));
}
getAllPrevStar(it, allPrevStar, pkb);
}
return;
}

bool NextStar::isStmtType(int stmtId, Parameter parameter, PKB* pkb) {
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

void NextStar::insertSynList(Parameter p) {
synList.push_back(p);
}

bool NextStar::isNumber(Parameter parameter) {
Type type = parameter.getParaType();
return (type == INTEGER);
}

bool NextStar::isSynonym(Parameter parameter) {
Type type = parameter.getParaType();
return (type == ASSIGN || type == WHILE || type == STMT || type == ANYTHING || type == PROG_LINE);
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
return NEXTSTAR;
}

ResultTable NextStar::evaluate(PKB* pkb, ResultTable intResultTable) {
return ResultTable();
}*/
