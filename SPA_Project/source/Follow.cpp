#include "Type.h"
#include "Follow.h"
#include "Clause.h"

using namespace std;

Follow::Follow(string lc, Type lcType, string rc, Type rcType) {
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}

vector<int> Follow::getWithRelToRight(PKB* pkb) {
	cout << "RIGHT" << endl;
	if (isSynonym(rightChildType)) {
		if (isNumber(leftChildType)) {
			int leftArgument = stoi(leftChild);
			if (!isValidStmtNo(leftArgument, pkb)) {
				return result;
			}
			else { //if left is a valid statement number, follows(num, syn)
				int followedBy = pkb->getFollowDirect(leftArgument);
				if (isStmtType(followedBy, rightChildType, pkb)) {
					result.push_back(followedBy);
					return result;
				}
			}
		}
		else if (isSynonym(leftChildType)) {
			left = getTypeStmt(leftChildType, pkb);
			tempResult = getAllFollows(left, pkb);
			result = filterType(tempResult, rightChildType, pkb);
		}
		else {
			return result;
		}
	}
	else {
		return result;
	}
	return result;
}

vector<int> Follow::getWithRelToLeft(PKB* pkb) {
	cout << "LEFT" << endl;
	if (isSynonym(leftChildType)) {
		cout << "LEFT IS SYNONYM" << endl;
		if (isNumber(rightChildType)) {
			int rightArgument = stoi(rightChild);
			if (!isValidStmtNo(rightArgument, pkb)) {
				return result;
			}
			else { //if right is valid statement number, follows(syn, num)
				int follows = pkb->getFollowedByDirect(rightArgument);
				if (isStmtType(follows, leftChildType, pkb)) {
					result.push_back(follows);
					return result;
				}
			}
		}
		else if (isSynonym(rightChildType)) {
			cout << "RIGHT IS SYNONYM" << endl;
			right = getTypeStmt(rightChildType, pkb);
			cout << "NUMBER OF " << rightChildType << " is: " << right.size() << endl;
			tempResult = getAllFollowedBy(right, pkb);
			cout << "NUMBER OF TEMP RESULT is: " << tempResult.size() << endl;
			result = filterType(tempResult, leftChildType, pkb);
			cout << "NUMBER OF RESULT is: " << result.size() << endl;
			return result;
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

bool Follow::isValidStmtNo(int stmtId, PKB* pkb) {
	return ((stmtId > 0) && (stmtId <= pkb->getTotalStmtNum()));
}

vector<int> Follow::getAllFollows(vector<int> list, PKB* pkb) {
	vector<int> listFollows;
	int follows;
	for (int i = 0; i < list.size(); i++) {
		follows = pkb->getFollowDirect(list[i]);
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
		followedBy = pkb->getFollowedByDirect(list[i]);
		if (followedBy != -1) {
			cout << followedBy << " added bcuz it follows " << list[i] << endl;
			listFollowedBy.push_back(followedBy);
		}
		else {
			cout << list[i] << " is not followed by anything" << endl;
		}
	}
	return listFollowedBy;
}

vector<int> Follow::filterType(vector<int> list, Type type, PKB* pkb) {
	if (type == STMT || type == ANYTHING) {
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
	switch (type) {
	case WHILES:
		cout << stmtId << " " << pkb->isStmtInWhileTable(stmtId) << endl;
		return pkb->isStmtInWhileTable(stmtId);
	case ASSIGN:
		return pkb->isStmtInAssignTable(stmtId);
	case STMT:
	case ANYTHING:
		return true;
	}
	//cout << stmtId << " false" << endl;
	return false;
}

vector<int> Follow::getTypeStmt(Type type, PKB* pkb) {
	switch (type) {
	case STMT:
	case ANYTHING: {
		int numOfStmt = pkb->getTotalStmtNum();
		vector<int> stmtList(numOfStmt);
		for (int i = 0; i < numOfStmt; i++) {
			stmtList[i] = i+1;
		}
		return stmtList;
	}
	case WHILES:
		return pkb->getAllWhileStmtId();
	case ASSIGN:
		return pkb->getAllAssignStmtId();
	}
	vector<int> result;
	return result;
}

bool Follow::isNumber(Type type) {
	return (type == PROG_LINE);
}

bool Follow::isSynonym(Type type) {
	return (type == ASSIGN || type == WHILES || type == STMT || type == ANYTHING);
}

bool Follow::hasRel(PKB *pkbSource) {
	if (isSynonym(leftChildType)) {
		if (isNumber(rightChildType)) {
			int rightArgument = stoi(rightChild);
			if (!isValidStmtNo(rightArgument, pkb)) {
				return false; // return what!??!!??!?!?!?!?!?!?!?!?!?!?!?!
			}
			else { //if right is valid statement number, follows(syn, num)
				int follows = pkb->getFollowedByDirect(rightArgument);
				if (isStmtType(follows, leftChildType, pkb)) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		else if (isSynonym(rightChildType)) { // follows(syn,syn)
			//if (pkb->getFollowDirect()) {
				return true;
			//}
			//else {
				return false;
			//}
		}
		else { // follows(synonym, invalid)
			return false; // return what!??!?!?!?!?!?!?!??!
		}
	}
	else if (isNumber(leftChildType)) {
		int leftArgument = stoi(leftChild);
		if (!isValidStmtNo(leftArgument, pkb)) {
			return false; // return what!??!!??!?!?!?!?!?!?!?!?!?!?!?!
		}
		if (isNumber(rightChildType)) {
			int rightArgument = stoi(rightChild);
			if (!isValidStmtNo(rightArgument, pkb)) {
				return false; // return what!??!!??!?!?!?!?!?!?!?!?!?!?!?!
			}
			else { //if right is valid statement number, follows(num, num)
				int follows = pkb->getFollowedByDirect(rightArgument);
				if (follows == leftArgument) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		else if (isSynonym(rightChildType)) { //follows(num , syn)
			int followedBy = pkb->getFollowDirect(leftArgument);
			if (isStmtType(followedBy, rightChildType, pkb)) {
				return true;
			}
			else {
				return false;
			}
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
