#include "Type.h"
#include "FollowStar.h"
#include "Clause.h"

FollowStar::FollowStar(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;
}

ResultTable FollowStar::evaluate(PKB* pkb) {
	if (isNumber(leftChild)) {
		if (isNumber(rightChild)) {
			//return getFollowStarNumNum(pkb);
		}
		else if (isSynonym(rightChild)) {
			return getFollowStarNumSyn(pkb, getTypeStmt(rightChild.getParaType(), pkb), stoi(leftChild.getParaName()));
		}
	}
	else if (isSynonym(leftChild)) {
		if (isNumber(rightChild)) {
			return getFollowStarSynNum(pkb, getTypeStmt(leftChild.getParaType(), pkb), stoi(rightChild.getParaName()));
		}
		else if (isSynonym(rightChild)) {
			return getFollowStarSynSyn(pkb, getTypeStmt(leftChild.getParaType(), pkb), getTypeStmt(rightChild.getParaType(), pkb));
		}
	}
	return result;
}

ResultTable FollowStar::evaluate(PKB* pkb, ResultTable resultTable) {
	unordered_set<int> left = resultTable.getSynValue(leftChild);
	unordered_set<int> right = resultTable.getSynValue(rightChild);
	if (resultTable.getSynCount() == 0) {
		return evaluate(pkb);
	}
	else if (resultTable.getSynCount() == 1) {
		if (left.size() != 0) {
			return getFollowStarSynNum(pkb, left, stoi(rightChild.getParaName()));
		}
		else if (right.size() != 0) {
			return getFollowStarNumSyn(pkb, right, stoi(leftChild.getParaName()));
		}
	}
	else if (resultTable.getSynCount() == 2) {
		if (left.size() == 0) {
			return getFollowStarSynSyn(pkb, getTypeStmt(leftChild.getParaType(), pkb), right);
		}
		else if (right.size() == 0) {
			return getFollowStarSynSyn(pkb, left, getTypeStmt(rightChild.getParaType(), pkb));
		}
		else {
			return getFollowStarSynSyn(pkb, &resultTable);
		}
	}
	return result;
}

ResultTable FollowStar::getFollowStarSynNum(PKB* pkb, unordered_set<int> left, int right) {
	result.setSynList(vector<Parameter>({ leftChild }));
	if (isValidStmtNo(right, pkb)) { //if right is a valid statement number, follows(syn, num)
		unordered_set<int> followStar = pkb->getStmtFollowedByStarStmt(right);
		for (auto& it : followStar) {
			if (left.find(it) != left.end()) {
				result.insertTuple(vector<int>(it));
			}
		}
	}
	return result;
}

ResultTable FollowStar::getFollowStarNumSyn(PKB* pkb, unordered_set<int> right, int left) {
	result.setSynList(vector<Parameter>({ rightChild }));
	if (isValidStmtNo(left, pkb)) { //if right is a valid statement number, follows(syn, num)
		unordered_set<int> followedByStar = pkb->getStmtFollowStarStmt(left);
		for (auto& it : followedByStar) {
			if (right.find(it) != right.end()) {
				result.insertTuple(vector<int>(it));
			}
		}
	}
	return result;
}

ResultTable FollowStar::getFollowStarSynSyn(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		return result;
	}
	if (left.size() < right.size()) {
		for (auto& leftIterator : left) {
			unordered_set<int> followedByStar = pkb->getStmtFollowStarStmt(leftIterator);
			for (auto& it : followedByStar) {
				if (right.find(it) != right.end()) {
					result.insertTuple(vector<int>(leftIterator, it));
				}
			}
		}
	}
	else {
		for (auto& rightIterator : right) {
			unordered_set<int> followStar = pkb->getStmtFollowedByStarStmt(rightIterator);
			for (auto& it : followStar) {
				if (left.find(it) != left.end()) {
					result.insertTuple(vector<int>(it, rightIterator));
				}
			}
		}
	}
	return result;
}

ResultTable FollowStar::getFollowStarSynSyn(PKB* pkb, ResultTable* resultTable) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		return result;
	}
	vector<Parameter> synonyms = resultTable->getSynList();
	vector<vector<int>> tupleList = resultTable->getTupleList();

	if (isLeftChild(synonyms[0])) {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isFollowStar(pkb, tupleList[i][0], tupleList[i][1])) {
				result.insertTuple(vector<int>(tupleList[i][0], tupleList[i][1]));
			}
		}
	}
	else {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isFollowStar(pkb, tupleList[i][1], tupleList[i][0])) {
				result.insertTuple(vector<int>(tupleList[i][1], tupleList[i][0]));
			}
		}
	}
	return result;
}

ResultTable FollowStar::getFollowStarNumNum(PKB* pkb, int left, int right) {
	if (!isValidStmtNo(left, pkb)) {
		result.setBoolean(false);
		return result;
	}
	if (!isValidStmtNo(right, pkb)) {
		result.setBoolean(false);
		return result;
	}
	result.setBoolean(isFollowStar(pkb, left, right));
	return result;
}

bool FollowStar::isFollowStar(PKB* pkb, int left, int right) {
	unordered_set<int> followStar = pkb->getStmtFollowedByStarStmt(right);
	if (followStar.find(left) != followStar.end()) {
		return true;
	}
	else {
		return false;
	}
}

unordered_set<int> FollowStar::getTypeStmt(Type type, PKB* pkb) {
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

bool FollowStar::isNumber(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == INTEGER);
}

bool FollowStar::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == ANYTHING || type == PROG_LINE || type == IF || type == CALL);
}

bool FollowStar::isLeftChild(Parameter parameter) {
	return (parameter.getParaName().compare(leftChild.getParaName()) == 0 && parameter.getParaType() == leftChild.getParaType());
}

bool FollowStar::isValidStmtNo(int stmtId, PKB* pkb) {
	return ((stmtId > 0) && (stmtId <= pkb->getNumOfStmt()));
}

void FollowStar::insertSynList(Parameter p) {
	synList.push_back(p);
}

Parameter FollowStar::getLeftChild() {
	return leftChild;
}
Parameter FollowStar::getRightChild() {
	return rightChild;
}
vector<Parameter> FollowStar::getSynList() {
	return synList;
}

/*
ResultTable FollowStar::execute(PKB* pkb) {
	if (isNumber(leftChild)) {
		if (isNumber(rightChild)) {
			return getFollowStarNumNum(pkb);
		}
		else if (isSynonym(rightChild)) {
			return getFollowStarNumSyn(pkb);
		}
	}
	else if (isSynonym(leftChild)) {
		if (isNumber(rightChild)) {
			return getFollowStarSynNum(pkb);
		}
		else if (isSynonym(rightChild)) {
			return getFollowStarSynSyn(pkb);
		}
	}
	return result;
}

ResultTable FollowStar::getFollowStar(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	if (left.size() < right.size()) {
		for (auto& leftIterator : left) {
			unordered_set<int> followedByStar = pkb->getStmtFollowStarStmt(leftIterator);
			for (auto& it : followedByStar) {
				if (right.find(it) != right.end()) { //if contains
					result.insertTuple(vector<int>(leftIterator, it));
				}
			}
		}
	}
	else {
		for (auto& rightIterator : right) {
			unordered_set<int> followStar = pkb->getStmtFollowedByStmt(rightIterator);
			for (auto& it : followStar) {
				if (left.find(it) != left.end()) {
					result.insertTuple(vector<int>(it, rightIterator));
				}
			}
		}
	}
}

/*

ResultTable FollowStar::getFollowStarNumNum(PKB* pkb) {
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

	vector<int> follows = pkb->getStmtFollowedByStarStmt(rightArgument);
	for (int i = 0; i < follows.size(); i++) {
		if (follows[i] == leftArgument) {
			result.setBoolean(true);
			return result;
		}
	}
	result.setBoolean(false);
	return result;
}

ResultTable FollowStar::getFollowStarNumSyn(PKB* pkb) {
	int leftArgument = stoi(leftChild.getParaName());
	if (!isValidStmtNo(leftArgument, pkb)) {
		return result;
	}
	else { //if left is a valid statement number, follows(num, syn)

		result.setSynList(vector<Parameter>({ rightChild }));
		return getAllFollowsStar(vector<int>(leftArgument), pkb);
		//result = filterType(tempResult, rightChildType, pkb);
		//return result;
	}
}

ResultTable FollowStar::getFollowStarSynNum(PKB* pkb) {
	int rightArgument = stoi(rightChild.getParaName());
	if (!isValidStmtNo(rightArgument, pkb)) {
		return result;
	}
	else { //if right is a valid statement number, follows(syn, num)
		result.setSynList(vector<Parameter>({ leftChild }));
		return getAllFollowedByStar(vector<int>(rightArgument), pkb);
	}
}

ResultTable FollowStar::getFollowStarSynSyn(PKB* pkb) {
	if (leftChild.getParaName().compare(rightChild.getParaName()) == 0) {
		return result;
	}


	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	vector<int> right = getTypeStmt(rightChild.getParaType(), pkb);
	return getAllFollowedByStar(right, pkb);
	//return result;
}
*/
/*
vector<int> FollowStar::getTypeStmt(Type type, PKB* pkb) {
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


ResultTable FollowStar::getAllFollowsStar(vector<int> list, PKB* pkb) {
	vector<int> followsStar;
	for (int i = 0; i < list.size(); i++) {
		followsStar = pkb->getStmtFollowStarStmt(list[i]);
		for (int j = 0; j < followsStar.size(); j++) {
			if (isStmtType(followsStar[j], rightChild, pkb)) {
				result.insertTuple(vector<int>(list[i], followsStar[j]));
			}
		}

	}
	return result;
}

ResultTable FollowStar::getAllFollowedByStar(vector<int> list, PKB* pkb) {
	vector<int> followedByStar;
	for (int i = 0; i < list.size(); i++) {
		followedByStar = pkb->getStmtFollowedByStarStmt(list[i]);
		for (int j = 0; j < followedByStar.size(); j++) {
			if (isStmtType(followedByStar[j], leftChild, pkb)) {
				result.insertTuple(vector<int>(followedByStar[j], list[i]));
			}
		}
	}
	return result;
}

bool FollowStar::isStmtType(int stmtId, Parameter parameter, PKB* pkb) {
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

void FollowStar::insertSynList(Parameter p) {
	synList.push_back(p);
}

bool FollowStar::isNumber(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == INTEGER);
}

bool FollowStar::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == ANYTHING || type == PROG_LINE);
}

bool FollowStar::isValidStmtNo(int stmtId, PKB* pkb) {
	return ((stmtId > 0) && (stmtId <= pkb->getNumOfStmt()));
}

Parameter FollowStar::getLeftChild() {
	return leftChild;
}
Parameter FollowStar::getRightChild() {
	return rightChild;
}
vector<Parameter> FollowStar::getSynList() {
	return synList;
}*/
/*
vector<int> FollowStar::getWithRelToRight(PKB* pkb) {
//cout << "RIGHT" << endl;
if (isSynonym(rightChildType)) {
if (isNumber(leftChildType)) {
int leftArgument = stoi(leftChild);
if (!isValidStmtNo(leftArgument, pkb)) {
return result;
}
else { //if left is a valid statement number, follows(num, syn)
left.push_back(leftArgument);
tempResult = getAllFollowsStar(left, pkb);
result = filterType(tempResult, rightChildType, pkb);
return result;
}
}
else if (isSynonym(leftChildType)) {
//cout << endl << "FOLLOWSTAR: " << endl;
//pkb->printFollows();
//cout << endl << endl;
//cout << " LEFT IS SYNONYM" << endl;
left = getTypeStmt(leftChildType, pkb);
//cout << "NUMBER OF LEFT IS " << left.size() << endl;
tempResult = getAllFollowsStar(left, pkb);
//cout << "NUMBER OF TEMP IS " << tempResult.size() << endl;
//for (auto& it : tempResult) {
//cout << it << " " << endl;
//}
result = filterType(tempResult, rightChildType, pkb);
return result;
}
else {
return result;
}
}
else {
return result;
}
}


//select synonym is left argument
vector<int> FollowStar::getWithRelToLeft(PKB* pkb) {
cout << "LEFT" << endl;
if (isSynonym(leftChildType)) {
if (isNumber(rightChildType)) {
int rightArgument = stoi(rightChild);
if (!isValidStmtNo(rightArgument, pkb)) {
return result;
}
else { //if right is valid statement number, follows(syn, num)
cout << "SYN NUM" << endl;
right.push_back(rightArgument);
tempResult = getAllFollowedByStar(right, pkb);
cout << "tempResult SIZE " << tempResult.size() << endl;
result = filterType(tempResult, leftChildType, pkb);
cout << "result SIZE " << result.size() << endl;
return result;
}
}
else if (isSynonym(rightChildType)) { // follows(syn,syn)
//cout << " RIGHT IS SYNONYM" << endl;
right = getTypeStmt(rightChildType, pkb);
//cout << "NUMBER OF RIGHT IS " << right.size() << endl;
tempResult = getAllFollowedByStar(right, pkb);
//cout << "NUMBER OF TEMP IS " << tempResult.size() << endl;
result = filterType(tempResult, leftChildType, pkb);
return result;
}
else { // follows(synonym, invalid)
return result;
}
}
else { //invalid left argument
return result;
}
}

bool FollowStar::isValidStmtNo(int stmtId, PKB* pkb) {
return ((stmtId > 0) && (stmtId <= pkb->getNumOfStmt()));
}

unordered_set<int> FollowStar::getAllFollowsStar(vector<int> list, PKB* pkb) {
unordered_set<int> result;
vector<int> followsStar;
for (int i = 0; i < list.size(); i++) {
followsStar = pkb->getStmtFollowStarStmt(list[i]);
for (int j = 0; j < followsStar.size(); j++) {
result.insert(followsStar[j]);
}

}
return result;
}

unordered_set<int> FollowStar::getAllFollowedByStar(vector<int> list, PKB* pkb) {
unordered_set<int> result;
vector<int> followedByStar;
for (int i = 0; i < list.size(); i++) {
followedByStar = pkb->getStmtFollowedByStarStmt(list[i]);
for (int j = 0; j < followedByStar.size(); j++) {
result.insert(followedByStar[j]);
}
}
return result;
}

vector<int> FollowStar::filterType(unordered_set<int> list, Type type, PKB* pkb) {
if (type == STMT || type == ANYTHING || type == PROG_LINE) {
vector<int> result(list.size());
copy(list.begin(), list.end(), result.begin());
return result;
}
else {
vector<int> result;
for (auto& it : list) {
if (isStmtType(it, type, pkb)) {
result.push_back(it);
}
}
return result;
}
}

bool FollowStar::isStmtType(int stmtId, Type type, PKB* pkb) {
if (stmtId < 1)
return false;
switch (type) {
case WHILE:
return pkb->isStmtInWhileTable(stmtId);
case ASSIGN:
return pkb->isStmtInAssignTable(stmtId);
case STMT:
case PROG_LINE:
case ANYTHING:
return true;
}
return false;
}

vector<int> FollowStar::getTypeStmt(Type type, PKB* pkb) {
switch (type) {
case STMT:
case PROG_LINE:
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
vector<int> result;
return result;
}

bool FollowStar::isNumber(Type type) {
return (type == INTEGER);
}

bool FollowStar::isSynonym(Type type) {
return (type == ASSIGN || type == WHILE || type == STMT || type == ANYTHING || type == PROG_LINE);
}

bool FollowStar::hasRel(PKB *pkb) {
if (isSynonym(leftChildType)) {
if (isNumber(rightChildType)) {
int rightArgument = stoi(rightChild);
if (!isValidStmtNo(rightArgument, pkb)) {
return false; // return what!??!!??!?!?!?!?!?!?!?!?!?!?!?!
}
else { //if right is valid statement number, follows*(syn, num)
vector<int> follows = pkb->getStmtFollowedByStarStmt(rightArgument);
for (int i = 0; i < follows.size(); i++) {
if (isStmtType(follows[i], leftChildType, pkb)) {
return true;
}
}
return false;
}
}
else if (isSynonym(rightChildType)) { // follows*(syn,syn)
right = getTypeStmt(rightChildType, pkb);
//cout << "NUMBER OF RIGHT IS " << right.size() << endl;
tempResult = getAllFollowedByStar(right, pkb);
//cout << "NUMBER OF TEMP IS " << tempResult.size() << endl;
result = filterType(tempResult, leftChildType, pkb);
return (result.size() != 0);
}
else { // follows(synonym, invalid)
return false; // return what!??!?!?!?!?!?!?!??!
}
}
else if (isNumber(leftChildType)) {
int leftArgument = stoi(leftChild);
//	cout << "LEFT ARGUMENT: " << leftArgument << endl;
if (!isValidStmtNo(leftArgument, pkb)) {
return false; // return what!??!!??!?!?!?!?!?!?!?!?!?!?!?!
}
//	cout << "LEFT ARGUMENT VALID" << endl;
if (isNumber(rightChildType)) {
int rightArgument = stoi(rightChild);
if (!isValidStmtNo(rightArgument, pkb)) {
return false; // return what!??!!??!?!?!?!?!?!?!?!?!?!?!?!
}
else { //if right is valid statement number, follows*(num, num)
vector<int> follows = pkb->getStmtFollowedByStarStmt(rightArgument);
for (int i = 0; i < follows.size(); i++) {
if (follows[i] == leftArgument) {
return true;
}
}
return false;
}
}
else if (isSynonym(rightChildType)) { //follows(num , syn)

//cout << "RIGHT SYNONYM" << endl;
vector<int> followedByStar = pkb->getStmtFollowStarStmt(leftArgument);
//cout << "RESULT SIZE: " << followedByStar.size() << endl;
for (int i = 0; i < followedByStar.size(); i++) {
if (isStmtType(followedByStar[i], rightChildType, pkb)) {
// << followedByStar[i] << " is valid type" << endl;
return true;
}
else {
//cout << followedByStar[i] << " is invalid type" << endl;
}
}
return false;
}
else {
return false; // return what!?! ?!?!? !? !??! ?
}
}
else { //invalid left argument
return false;
}
return isRel;
}
string FollowStar::getLeftChild() {
return leftChild;
}
string FollowStar::getRightChild() {
return rightChild;
}
Type FollowStar::getLeftChildType() {
return leftChildType;
}
Type FollowStar::getRightChildType() {
return rightChildType;
}
*/
ClauseType FollowStar::getClauseType() {
	return FOLLOWSTAR;
}
