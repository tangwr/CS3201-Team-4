#include "Type.h"
#include "FollowStar.h"
#include "Clause.h"

FollowStar::FollowStar(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;
}



ResultTable* FollowStar::execute(PKB* pkb) {
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

ResultTable* FollowStar::getFollowStarNumNum(PKB* pkb) {
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

	vector<int> follows = pkb->getStmtFollowedByStarStmt(rightArgument);
	for (int i = 0; i < follows.size(); i++) {
		if (follows[i] == leftArgument) {
			result->setBoolean(true);
			break;
		}
	}
	return false;
}

ResultTable* FollowStar::getFollowStarNumSyn(PKB* pkb) {
	int leftArgument = stoi(leftChild.getParaName());
	if (!isValidStmtNo(leftArgument, pkb)) {
		return result;
	}
	else { //if left is a valid statement number, follows(num, syn)

		result->setSynList(vector<Parameter>({ rightChild }));
		return getAllFollowsStar(vector<int>(leftArgument), pkb);
		//result = filterType(tempResult, rightChildType, pkb);
		//return result;
	}
}

ResultTable* FollowStar::getFollowStarSynNum(PKB* pkb) {
	int rightArgument = stoi(rightChild.getParaName());
	if (!isValidStmtNo(rightArgument, pkb)) {
		return result;
	}
	else { //if right is a valid statement number, follows(syn, num)
		result->setSynList(vector<Parameter>({ leftChild }));
		return getAllFollowedByStar(vector<int>(rightArgument), pkb);
	}
}

ResultTable* FollowStar::getFollowStarSynSyn(PKB* pkb) {
	if (leftChild.getParaName().compare(rightChild.getParaName()) == 0) {
		return result;
	}


	result->setSynList(vector<Parameter>({ leftChild, rightChild }));
	vector<int> right = getTypeStmt(rightChild.getParaType(), pkb);
	return getAllFollowedByStar(right, pkb);
	//return result;
}

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


ResultTable* FollowStar::getAllFollowsStar(vector<int> list, PKB* pkb) {
	vector<int> followsStar;
	for (int i = 0; i < list.size(); i++) {
		followsStar = pkb->getStmtFollowStarStmt(list[i]);
		for (int j = 0; j < followsStar.size(); j++) {
			if (isStmtType(followsStar[j], rightChild, pkb)) {
				result->insertTuple(vector<int>(list[i], followsStar[j]));
			}
		}

	}
	return result;
}

ResultTable* FollowStar::getAllFollowedByStar(vector<int> list, PKB* pkb) {
	vector<int> followedByStar;
	for (int i = 0; i < list.size(); i++) {
		followedByStar = pkb->getStmtFollowedByStarStmt(list[i]);
		for (int j = 0; j < followedByStar.size(); j++) {
			if (isStmtType(followedByStar[j], leftChild, pkb)) {
				result->insertTuple(vector<int>(followedByStar[j], list[i]));
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
ClauseType FollowStar::getClauseType() {
	return FOLLOWSTAR;
}
*/
