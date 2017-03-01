#include "Type.h"
#include "Follow.h"
#include "Clause.h"

using namespace std;


Follow::Follow(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;
}

ResultTable* Follow::execute(PKB* pkb) {
	if (isNumber(leftChild)) {
		if (isNumber(rightChild)) {
			return getFollowNumNum(pkb);
		}
		else if (isSynonym(rightChild)) {
			return getFollowNumSyn(pkb);
		}
	}
	else if (isSynonym(leftChild)) {
		if (isNumber(rightChild)) {
			return getFollowSynNum(pkb);
		}
		else if (isSynonym(rightChild)) {
			return getFollowSynSyn(pkb);
		}
	}
	return result;
}

ResultTable* Follow::getFollowNumNum(PKB* pkb) {
	int leftArgument = stoi(leftChild.getParaName());
	int rightArgument = stoi(rightChild.getParaName());
	if (!isValidStmtNo(leftArgument, pkb)) {
		result->setBoolean(false);
		return result;
	}
	if (!isValidStmtNo(rightArgument, pkb)) {
		result->setBoolean(false);
		return result;
	}

	int follows = pkb->getStmtFollowedByStmt(rightArgument);
	vector<int> tuple;
	if (follows == leftArgument) {
		result->setBoolean(true);
	}
	else {
		result->setBoolean(false);
	}
	return result;
}

ResultTable* Follow::getFollowNumSyn(PKB* pkb) {
	int leftArgument = stoi(leftChild.getParaName());
	if (!isValidStmtNo(leftArgument, pkb)) {
		return result;
	}
	else { //if left is a valid statement number, follows(num, syn)
		result->setSynList(vector<Parameter>({rightChild}));
		vector<int> tuple;
		int followedBy = pkb->getStmtFollowStmt(leftArgument);

		if (isStmtType(followedBy, rightChild, pkb)) {
			tuple.push_back(followedBy);
			result->insertTuple(tuple);
			return result;
		}
	}
}

ResultTable* Follow::getFollowSynNum(PKB* pkb) {
	int rightArgument = stoi(rightChild.getParaName());
	if (!isValidStmtNo(rightArgument, pkb)) {
		return result;
	}
	else { //if right is a valid statement number, follows(syn, num)
		result->setSynList(vector<Parameter>({ leftChild }));
		vector<int> tuple;
		int follows = pkb->getStmtFollowedByStmt(rightArgument);

		if (isStmtType(follows, rightChild, pkb)) {
			tuple.push_back(follows);
			result->insertTuple(tuple);
			return result;
		}
	}
}

ResultTable* Follow::getFollowSynSyn(PKB* pkb) {
	if (leftChild.getParaName().compare(rightChild.getParaName()) == 0) {
		return result;
	}


	result->setSynList(vector<Parameter>({ leftChild, rightChild }));
	vector<int> right = getTypeStmt(rightChild.getParaType(), pkb);
	for (int i = 0; i < right.size(); i++) {
		int follows = pkb->getStmtFollowedByStmt(right[i]);
		if (isStmtType(follows, leftChild, pkb))
			result->insertTuple(vector<int>(follows, right[i]));
	}
	return result;
}

vector<int> Follow::getTypeStmt(Type type, PKB* pkb) {
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

bool Follow::isStmtType(int stmtId, Parameter parameter, PKB* pkb) {
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

bool Follow::isNumber(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == INTEGER);
}

bool Follow::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == ANYTHING || type == PROG_LINE);
}

bool Follow::isValidStmtNo(int stmtId, PKB* pkb) {
	return ((stmtId > 0) && (stmtId <= pkb->getNumOfStmt()));
}

Parameter Follow::getLeftChild() {
	return leftChild;
}
Parameter Follow::getRightChild() {
	return rightChild;
}

/*
Follow::Follow(string lc, Type lcType, string rc, Type rcType) {
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}

vector<int> Follow::getWithRelToRight(PKB* pkb) {
	//cout << "RIGHT" << endl;
	if (isSynonym(rightChildType)) {
		if (isNumber(leftChildType)) {
			return getWithRelToRightNumSyn(pkb);
		}
		else if (isSynonym(leftChildType)) {
			return getWithRelToRightSynSyn(pkb);
		}
	}
	return result;
}

vector<int> Follow::getWithRelToRightSynSyn(PKB* pkb) {
	left = getTypeStmt(leftChildType, pkb);
	tempResult = getAllFollows(left, pkb);
	result = filterType(tempResult, rightChildType, pkb);
	return result;
}

vector<int> Follow::getWithRelToRightNumSyn(PKB* pkb) {
	int leftArgument = stoi(leftChild);
	if (!isValidStmtNo(leftArgument, pkb)) {
		return result;
	}
	else { //if left is a valid statement number, follows(num, syn)
		int followedBy = pkb->getStmtFollowStmt(leftArgument);
		if (isStmtType(followedBy, rightChildType, pkb)) {
			result.push_back(followedBy);
			return result;
		}
	}
	return result;
}

vector<int> Follow::getWithRelToLeft(PKB* pkb) {
	if (isSynonym(leftChildType)) {
		if (isNumber(rightChildType)) {
			return getWithRelToLeftSynNum(pkb);
		}
		else if (isSynonym(rightChildType)) {
			return getWithRelToLeftSynSyn(pkb);
		}
		else { // follows(synonym, invalid)
			return result;
		}
	}
	else { //invalid left argument
		return result;
	}
	return result;
}

vector<int> Follow::getWithRelToLeftSynSyn(PKB* pkb) {
	right = getTypeStmt(rightChildType, pkb);
	tempResult = getAllFollowedBy(right, pkb);
	result = filterType(tempResult, leftChildType, pkb);
	return result;
}

vector<int> Follow::getWithRelToLeftSynNum(PKB* pkb) {
	int rightArgument = stoi(rightChild);
	if (!isValidStmtNo(rightArgument, pkb)) {
		return result;
	}
	else { //if right is valid statement number, follows(syn, num)
		int follows = pkb->getStmtFollowedByStmt(rightArgument);
		if (isStmtType(follows, leftChildType, pkb)) {
			result.push_back(follows);
			return result;
		}
	}
}

bool Follow::isValidStmtNo(int stmtId, PKB* pkb) {
	return ((stmtId > 0) && (stmtId <= pkb->getNumOfStmt()));
}

vector<int> Follow::getAllFollows(vector<int> list, PKB* pkb) {
	vector<int> listFollows;
	int follows;
	for (int i = 0; i < list.size(); i++) {
		follows = pkb->getStmtFollowStmt(list[i]);
		if (follows != -1) {
			listFollows.push_back(follows);
		}
	}
	return listFollows;
}

vector<int> Follow::getAllFollowedBy(vector<int> list, PKB* pkb) {
	vector<int> listFollowedBy;
	int followedBy;
	for (int i = 0; i < list.size(); i++) {
		followedBy = pkb->getStmtFollowedByStmt(list[i]);
		if (followedBy != -1) {
			listFollowedBy.push_back(followedBy);
		}
		else {
			//cout << list[i] << " is not followed by anything" << endl;
		}
	}
	return listFollowedBy;
}

vector<int> Follow::filterType(vector<int> list, Type type, PKB* pkb) {
	if (type == STMT || type == ANYTHING || type == PROG_LINE) {
		return list;
	}
	vector<int> result;
	for (int i = 0; i < list.size(); i++) {
		if (isStmtType(list[i], type, pkb)) {
			result.push_back(list[i]);
		}
	}
	return result;
}

bool Follow::isStmtType(int stmtId, Type type, PKB* pkb) {
	if (stmtId < 1)
		return false;
	switch (type) {
	case WHILES:
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

vector<int> Follow::getTypeStmt(Type type, PKB* pkb) {
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
	case WHILES:
		return pkb->getAllWhileStmt();
	case ASSIGN:
		return pkb->getAllAssignStmt();
	}
	vector<int> result;
	return result;
}

bool Follow::isNumber(Type type) {
	return (type == INTEGER);
}

bool Follow::isSynonym(Type type) {
	return (type == ASSIGN || type == WHILES || type == STMT || type == ANYTHING || type == PROG_LINE);
}

bool Follow::hasRel(PKB *pkb) {
	if (isSynonym(leftChildType)) {
		if (isNumber(rightChildType)) {
			return hasRelSynNum(pkb);
		}
		else if (isSynonym(rightChildType)) { // follows(syn,syn)
			return hasRelSynSyn(pkb);
		}
	}
	else if (isNumber(leftChildType)) {
		int leftArgument = stoi(leftChild);
		if (!isValidStmtNo(leftArgument, pkb)) {
			return false;
		}
		if (isNumber(rightChildType)) {
			return hasRelNumNum(pkb, leftArgument);
		}
		else if (isSynonym(rightChildType)) { //follows(num , syn)
			return hasRelNumSyn(pkb, leftArgument);
		}
	}
	return false;
}

bool Follow::hasRelNumSyn(PKB *pkb, int leftArgument) {
	int followedBy = pkb->getStmtFollowStmt(leftArgument);
	if (isStmtType(followedBy, rightChildType, pkb)) {
		return true;
	}
	else {
		return false;
	}
}

bool Follow::hasRelNumNum(PKB *pkb, int leftArgument) {
	int rightArgument = stoi(rightChild);
	if (!isValidStmtNo(rightArgument, pkb)) {
		return false;
	}
	else { //if right is valid statement number, follows(num, num)
		int follows = pkb->getStmtFollowedByStmt(rightArgument);
		if (follows == leftArgument) {
			return true;
		}
		else {
			return false;
		}
	}
}

bool Follow::hasRelSynSyn(PKB *pkb) {
	right = getTypeStmt(rightChildType, pkb);
	tempResult = getAllFollowedBy(right, pkb);
	result = filterType(tempResult, leftChildType, pkb);
	return (result.size() != 0);
}

bool Follow::hasRelSynNum(PKB *pkb) {
	int rightArgument = stoi(rightChild);
	if (!isValidStmtNo(rightArgument, pkb)) {
		return false;
	}
	else { //if right is valid statement number, follows(syn, num)
		int follows = pkb->getStmtFollowedByStmt(rightArgument);
		if (isStmtType(follows, leftChildType, pkb)) {
			return true;
		}
		else {
			return false;
		}
	}
}

string Follow::getLeftChild() {
	return leftChild;
}
string Follow::getRightChild() {
	return rightChild;
}
Type Follow::getLeftChildType() {
	return leftChildType;
}
Type Follow::getRightChildType() {
	return rightChildType;
}
*/
