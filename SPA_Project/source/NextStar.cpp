#include "Type.h"
#include "Clause.h"
#include "NextStar.h"

using namespace std;


NextStar::NextStar(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;
}

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
	return getAllPrevStar(right, pkb);*/
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
}