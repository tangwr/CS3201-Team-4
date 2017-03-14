#include "Type.h"
#include "Follow.h"
#include "Clause.h"

using namespace std;


Follow::Follow(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;
}

ResultTable Follow::evaluate(PKB* pkb) {
	if (isNumber(leftChild)) {
		if (isNumber(rightChild)) {
			//return getFollowNumNum(pkb);
		}
		else if (isSynonym(rightChild)) {
			return getFollowNumSyn(pkb, getTypeStmt(rightChild.getParaType(), pkb), stoi(leftChild.getParaName()));
		}
	}
	else if (isSynonym(leftChild)) {
		if (isNumber(rightChild)) {
			return getFollowSynNum(pkb, getTypeStmt(leftChild.getParaType(), pkb), stoi(rightChild.getParaName()));
		}
		else if (isSynonym(rightChild)) {
			return getFollowSynSyn(pkb, getTypeStmt(leftChild.getParaType(), pkb), getTypeStmt(rightChild.getParaType(), pkb));
		}
	}
	return result;
}

ResultTable Follow::evaluate(PKB* pkb, ResultTable resultTable) {
	unordered_set<int> left = resultTable.getSynValue(leftChild);
	unordered_set<int> right = resultTable.getSynValue(rightChild);
	if (resultTable.getSynCount() == 0) {
		return evaluate(pkb);
	}
	else if (resultTable.getSynCount() == 1) {
		if (left.size() != 0) {
			return getFollowSynNum(pkb, left, stoi(rightChild.getParaName()));
		}
		else if (right.size() != 0) {
			return getFollowNumSyn(pkb, right, stoi(leftChild.getParaName()));
		}
	}
	else if (resultTable.getSynCount() == 2) {
		if (left.size() == 0) {
			return getFollowSynSyn(pkb, getTypeStmt(leftChild.getParaType(), pkb), right);
		}
		else if (right.size() == 0) {
			return getFollowSynSyn(pkb, left, getTypeStmt(rightChild.getParaType(), pkb));
		}
		else {
			return getFollowSynSyn(pkb, &resultTable);
		}
	}
	return result;
}

ResultTable Follow::getFollowSynNum(PKB* pkb, unordered_set<int> left, int right) {
	result.setSynList(vector<Parameter>({ leftChild }));
	if (isValidStmtNo(right, pkb)) { //if right is a valid statement number, follows(syn, num)
		int follows = pkb->getStmtFollowedByStmt(right);
		if (left.find(follows) != left.end()) {
			result.insertTuple(vector<int>(follows));
		}
	}
	return result;
}

ResultTable Follow::getFollowNumSyn(PKB* pkb, unordered_set<int> right, int left) {
	result.setSynList(vector<Parameter>({ rightChild }));
	if (isValidStmtNo(left, pkb)) { //if right is a valid statement number, follows(syn, num)
		int followedBy = pkb->getStmtFollowStmt(left);
		if (right.find(followedBy) != right.end()) {
			result.insertTuple(vector<int>(followedBy));
		}
	}
	return result;
}

ResultTable Follow::getFollowSynSyn(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		return result;
	}
	if (left.size() < right.size()) {
		for (auto& leftIterator : left) {
			int followedBy = pkb->getStmtFollowStmt(leftIterator);
			if (right.find(followedBy) != right.end()) {
				result.insertTuple(vector<int>(leftIterator, followedBy));
			}
		}
	}
	else {
		for (auto& rightIterator : right) {
			int follows = pkb->getStmtFollowedByStmt(rightIterator);
			if (left.find(follows) != left.end()) {
				result.insertTuple(vector<int>(follows, rightIterator));
			}
		}
	}
	return result;
}

ResultTable Follow::getFollowSynSyn(PKB* pkb, ResultTable* resultTable) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		return result;
	}
	vector<Parameter> synonyms = resultTable->getSynList();
	vector<vector<int>> tupleList = resultTable->getTupleList();
	if (isLeftChild(synonyms[0])) {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isFollows(pkb, tupleList[i][0], tupleList[i][1])) {
				result.insertTuple(vector<int>(tupleList[i][0], tupleList[i][1]));
			}
		}
	}
	else {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isFollows(pkb, tupleList[i][1], tupleList[i][0])) {
				result.insertTuple(vector<int>(tupleList[i][1], tupleList[i][0]));
			}
		}
	}
	return result;
}

ResultTable Follow::getFollowNumNum(PKB* pkb, int left, int right) {
	if (!isValidStmtNo(left, pkb)) {
		result.setBoolean(false);
		return result;
	}
	if (!isValidStmtNo(right, pkb)) {
		result.setBoolean(false);
		return result;
	}
	result.setBoolean(isFollows(pkb, left, right));
	return result;
}

bool Follow::isFollows(PKB* pkb, int left, int right) {
	int follows = pkb->getStmtFollowedByStmt(right);
	if (follows == left) {
		return true;
	}
	else {
		return false;
	}
}

unordered_set<int> Follow::getTypeStmt(Type type, PKB* pkb) {
	switch (type) {
	case PROG_LINE:
	case STMT:
	case ANYTHING: {
		int numOfStmt = pkb->getNumOfStmt();
		unordered_set<int> stmtList(numOfStmt);
		for (int i = 0; i < numOfStmt; i++) {
			//stmtList[i] = i + 1;
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
/*
ResultTable Follow::getFollowNumSyn(PKB* pkb) {
	result.setSynList(vector<Parameter>({ rightChild }));
	int leftArgument = stoi(leftChild.getParaName());
	if (isValidStmtNo(leftArgument, pkb)) { //if left is a valid statement number, follows(num, syn)
		int followedBy = pkb->getStmtFollowStmt(leftArgument);
		if (isStmtType(followedBy, rightChild, pkb)) {
			result.insertTuple(vector<int>(followedBy));
			return result;
		}
	}
	return result;
}

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
}

ResultTable Follow::getFollowSynNum(PKB* pkb) {
	result.setSynList(vector<Parameter>({ leftChild }));
	int rightArgument = stoi(rightChild.getParaName());
	if (isValidStmtNo(rightArgument, pkb)) { //if right is a valid statement number, follows(syn, num)
		int follows = pkb->getStmtFollowedByStmt(rightArgument);
		if (isStmtType(follows, rightChild, pkb)) {
			result.insertTuple(vector<int>(follows));
			return result;
		}
	}
	return result;
}

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
}

ResultTable Follow::getFollowSynSyn(PKB* pkb) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (leftChild.getParaName().compare(rightChild.getParaName()) == 0) {
		return result;
	}


	vector<int> right = getTypeStmt(rightChild.getParaType(), pkb);
	for (int i = 0; i < right.size(); i++) {
		int follows = pkb->getStmtFollowedByStmt(right[i]);
		if (isStmtType(follows, leftChild, pkb))
			result.insertTuple(vector<int>(follows, right[i]));
	}
	return result;
}

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
	}else if (statements[1].size() == 0) {
		vector<int> left = statements[0];
		for (int i = 0; i < left.size(); i++) {
			int follows = pkb->getStmtFollowStmt(left[i]);
			if (isStmtType(follows, rightChild, pkb)) {
				result.insertTuple(vector<int>(left[i], follows));
			}
		}
		return result;
	}else {
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
}*/

bool Follow::isNumber(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == INTEGER);
}

bool Follow::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == ANYTHING || type == PROG_LINE || type == IF || type == CALL);
}

bool Follow::isLeftChild(Parameter parameter) {
	return (parameter.getParaName().compare(leftChild.getParaName()) == 0 && parameter.getParaType() == leftChild.getParaType());
}

bool Follow::isRightChild(Parameter parameter) {
	return (parameter.getParaName().compare(rightChild.getParaName()) == 0 && parameter.getParaType() == rightChild.getParaType());
}

bool Follow::isValidStmtNo(int stmtId, PKB* pkb) {
	return ((stmtId > 0) && (stmtId <= pkb->getNumOfStmt()));
}

void Follow::insertSynList(Parameter p) {
	synList.push_back(p);
}

Parameter Follow::getLeftChild() {
	return leftChild;
}
Parameter Follow::getRightChild() {
	return rightChild;
}
vector<Parameter> Follow::getSynList() {
	return synList;
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

ClauseType Follow::getClauseType() {
	return FOLLOW;
}