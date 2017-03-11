#include "Type.h"
#include "Clause.h"
#include "Next.h"

using namespace std;


Next::Next(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;
}

ResultTable Next::execute(PKB* pkb) {
	if (isNumber(leftChild)) {
		if (isNumber(rightChild)) {
			return getNextNumNum(pkb);
		}
		else if (isSynonym(rightChild)) {
			return getNextNumSyn(pkb);
		}
	}
	else if (isSynonym(leftChild)) {
		if (isNumber(rightChild)) {
			return getNextSynNum(pkb);
		}
		else if (isSynonym(rightChild)) {
			return getNextSynSyn(pkb);
		}
	}
	return result;
}
/*
ResultTable Follow::execute(PKB* pkb, vector<Parameter> parameter, vector<vector<int>> statements) {
	if (parameter.size() == 1) {
		if (isLeftChild(parameter[0])) {
			return getFollowSynNum(pkb, statements);
		}
		else if (isRightChild(parameter[0])) {
			return getFollowNumSyn(pkb, statements);
		}
	}
	else if (parameter.size() == 2) {
		return getFollowSynSyn(pkb, statements);
	}
	return result;
}*/

ResultTable Next::getNextNumNum(PKB* pkb) {
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
	}
	else {
		result.setBoolean(false);
	}
	return result;
}

ResultTable Next::getNextNumSyn(PKB* pkb) {
	result.setSynList(vector<Parameter>({ rightChild }));
	int leftArgument = stoi(leftChild.getParaName());
	if (isValidStmtNo(leftArgument, pkb)) { //if left is a valid statement number, Next(num, syn)
		unordered_set<int> next = pkb->getNextStmt(leftArgument);
		for (auto& it : next) {
			if (isStmtType(it, rightChild, pkb)) {
				result.insertTuple(vector<int>(it));
				return result;
			}
		}
	}
	return result;
}
/*
ResultTable Follow::getFollowNumSyn(PKB* pkb, vector<vector<int>> statements) {
	result.setSynList(vector<Parameter>({ rightChild }));
	int leftArgument = stoi(leftChild.getParaName());
	if (isValidStmtNo(leftArgument, pkb)) { //if left is a valid statement number, follows(num, syn)
		int followedBy = pkb->getStmtFollowStmt(leftArgument);
		if (find(statements[0].begin(), statements[0].end(), followedBy) != statements[0].end()) {
			if (isStmtType(followedBy, rightChild, pkb)) {
				result.insertTuple(vector<int>(followedBy));
				return result;
			}
		}
	}
	return result;
}*/

ResultTable Next::getNextSynNum(PKB* pkb) {
	result.setSynList(vector<Parameter>({ leftChild }));
	int rightArgument = stoi(rightChild.getParaName());
	if (isValidStmtNo(rightArgument, pkb)) { //if right is a valid statement number, follows(syn, num)
		unordered_set<int> prev = pkb->getPreviousStmt(rightArgument);
		for (auto& it : prev) {
			if (isStmtType(it, leftChild, pkb)) {
				result.insertTuple(vector<int>(it));
				return result;
			}
		}
	}
	return result;
}
/*
ResultTable Follow::getFollowSynNum(PKB* pkb, vector<vector<int>> statements) {
	int rightArgument = stoi(rightChild.getParaName());
	if (isValidStmtNo(rightArgument, pkb)) { //if right is a valid statement number, follows(syn, num)
		result.setSynList(vector<Parameter>({ leftChild }));
		int follows = pkb->getStmtFollowedByStmt(rightArgument);
		if (find(statements[0].begin(), statements[0].end(), follows) != statements[0].end()) {
			if (isStmtType(follows, rightChild, pkb)) {
				result.insertTuple(vector<int>(follows));
				return result;
			}
		}
	}
	return result;
}*/

ResultTable Next::getNextSynSyn(PKB* pkb) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (leftChild.getParaName().compare(rightChild.getParaName()) == 0) {
		return result;
	}


	vector<int> right = getTypeStmt(rightChild.getParaType(), pkb);
	for (int i = 0; i < right.size(); i++) {
		unordered_set<int> prev = pkb->getPreviousStmt(rightArgument);
		for (auto& it : prev) {
			if (isStmtType(it, leftChild, pkb)) {
				result.insertTuple(vector<int>(it, right[i]));
				return result;
			}
		}
	}
	return result;
}
/*
ResultTable Follow::getFollowSynSyn(PKB* pkb, vector<vector<int>> statements) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (leftChild.getParaName().compare(rightChild.getParaName()) == 0) {
		return result;
	}
	if (statements.size() == 0) {
		return result;
	}
	if (statements[0].size() == 0) {
		vector<int> right = statements[1];
		for (int i = 0; i < right.size(); i++) {
			int follows = pkb->getStmtFollowedByStmt(right[i]);
			if (isStmtType(follows, leftChild, pkb)) {
				result.insertTuple(vector<int>(follows, right[i]));
			}
		}
		return result;
	}
	else if (statements[1].size() == 0) {
		vector<int> left = statements[0];
		for (int i = 0; i < left.size(); i++) {
			int follows = pkb->getStmtFollowStmt(left[i]);
			if (isStmtType(follows, rightChild, pkb)) {
				result.insertTuple(vector<int>(left[i], follows));
			}
		}
		return result;
	}
	else {
		unordered_set<int> left(statements[0].begin(), statements[0].end());
		vector<int> right = statements[1];
		for (int i = 0; i < right.size(); i++) {
			int follows = pkb->getStmtFollowedByStmt(right[i]);
			if (left.find(follows) != left.end()) {
				if (isStmtType(follows, leftChild, pkb)) {
					result.insertTuple(vector<int>(follows, right[i]));
				}
			}
		}
		return result;
	}
}
*/

vector<int> Next::getTypeStmt(Type type, PKB* pkb) {
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
		return pkb->getAllWhileStmt();
	case ASSIGN:
		return pkb->getAllAssignStmt();
	}
	return vector<int>();
}

bool Next::isStmtType(int stmtId, Parameter parameter, PKB* pkb) {
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

void Next::insertSynList(Parameter p) {
	synList.push_back(p);
}

bool Next::isNumber(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == INTEGER);
}

bool Next::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == ANYTHING || type == PROG_LINE);
}

bool Next::isLeftChild(Parameter parameter) {
	return (parameter.getParaName().compare(leftChild.getParaName()) == 0 && parameter.getParaType == leftChild.getParaType());
}

bool Next::isRightChild(Parameter parameter) {
	return (parameter.getParaName().compare(rightChild.getParaName()) == 0 && parameter.getParaType == rightChild.getParaType());
}

bool Next::isValidStmtNo(int stmtId, PKB* pkb) {
	return ((stmtId > 0) && (stmtId <= pkb->getNumOfStmt()));
}

Parameter Next::getLeftChild() {
	return leftChild;
}
Parameter Next::getRightChild() {
	return rightChild;
}
vector<Parameter> Next::getSynList() {
	return synList;
}
