#include "ClauseType.h"
#include "Type.h"
#include "FollowStar.h"
#include "Clause.h"

FollowStar::FollowStar(string lc, Type lcType, string rc, Type rcType) {
	cltype = FOLLOWSTAR;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}

//select synonym is right argument

vector<int> FollowStar::getWithRelToRight(PKB* pkb) {
	cout << "RIGHT" << endl;
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
			cout << endl << "FOLLOWSTAR: " << endl;
			pkb->printFollows();
			cout << endl << endl;
			cout << " LEFT IS SYNONYM" << endl;
			left = getTypeStmt(leftChildType, pkb);
			cout << "NUMBER OF LEFT IS " << left.size() << endl;
			tempResult = getAllFollowsStar(left, pkb);
			cout << "NUMBER OF TEMP IS " << tempResult.size() << endl;
			for (auto& it : tempResult) {
				cout << it << " " << endl;
			}
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
				right.push_back(rightArgument);
				tempResult = getAllFollowedByStar(right, pkb);
				result = filterType(tempResult, leftChildType, pkb);
				return result;
			}
		}
		else if (isSynonym(rightChildType)) { // follows(syn,syn)
			cout << " RIGHT IS SYNONYM" << endl;
			right = getTypeStmt(rightChildType, pkb);
			cout << "NUMBER OF RIGHT IS " << right.size() << endl;
			tempResult = getAllFollowedByStar(right, pkb);
			cout << "NUMBER OF TEMP IS " << tempResult.size() << endl;
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
	return ((stmtId > 0) && (stmtId <= pkb->getTotalStmtNum()));
}

unordered_set<int> FollowStar::getAllFollowsStar(vector<int> list, PKB* pkb) {
	unordered_set<int> result;
	vector<int> followsStar;
	for (int i = 0; i < list.size(); i++) {
		followsStar = pkb->getFollowStar(list[i]);
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
		followedByStar = pkb->getFollowedByStar(list[i]);
		for (int j = 0; j < followedByStar.size(); j++) {
			result.insert(followedByStar[j]);
		}
	}
	return result;
}

vector<int> FollowStar::filterType(unordered_set<int> list, Type type, PKB* pkb) {
	if (type == STMT || type == ANYTHING) {
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
	switch (type) {
	case WHILES:
		return pkb->isStmtInWhileTable(stmtId);
	case ASSIGN:
		return pkb->isStmtInAssignTable(stmtId);
	case STMT:
	case ANYTHING:
		return true;
	}
	return false;
}

vector<int> FollowStar::getTypeStmt(Type type, PKB* pkb) {
	switch (type) {
	case STMT:
	case ANYTHING: {
		int numOfStmt = pkb->getTotalStmtNum();
		vector<int> stmtList(numOfStmt);
		for (int i = 0; i < numOfStmt; i++) {
			stmtList[i] = i + 1;
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

bool FollowStar::isNumber(Type type) {
	return (type == PROG_LINE);
}

bool FollowStar::isSynonym(Type type) {
	return (type == ASSIGN || type == WHILES || type == STMT || type == ANYTHING);
}

bool FollowStar::hasRel(PKB *pkb) {
	if (isSynonym(leftChildType)) {
		if (isNumber(rightChildType)) {
			int rightArgument = stoi(rightChild);
			if (!isValidStmtNo(rightArgument, pkb)) {
				return false; // return what!??!!??!?!?!?!?!?!?!?!?!?!?!?!
			}
			else { //if right is valid statement number, follows*(syn, num)
				vector<int> follows = pkb->getFollowedByStar(rightArgument);
				for (int i = 0; i < follows.size(); i++) {
					if (isStmtType(follows[i], leftChildType, pkb)) {
						return true;
					}
				}
				return false;
			}
		}
		else if (isSynonym(rightChildType)) { // follows*(syn,syn)
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
			else { //if right is valid statement number, follows*(num, num)
				vector<int> follows = pkb->getFollowedByStar(rightArgument);
				for (int i = 0; i < follows.size(); i++) {
					if (follows[i] == leftArgument) {
						return true;
					}
				}
				return false;
			}
		}
		else if (isSynonym(rightChildType)) { //follows(num , syn)
			vector<int> followedByStar = pkb->getFollowedByStar(leftArgument);
			for (int i = 0; i < followedByStar.size(); i++) {
				if (isStmtType(followedByStar[i], rightChildType, pkb)) {
					return true;
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
