#include "Type.h"
#include "Parent.h"
#include "Clause.h"
#include "unordered_set"

Parent::Parent(string lc, Type lcType, string rc, Type rcType) {
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}

vector<int> Parent::getWithRelToRight(PKB* pkb) {
	//	cout << "RIGHT" << endl;
	if (isSynonym(rightChildType)) {
		//cout << "RIGHT IS SYNONYM" << endl;
		if (isNumber(leftChildType)) {
			int leftArgument = stoi(leftChild);
			if (!isValidStmtNo(leftArgument, pkb)) {
				return result;
			}
			else { //if left is a valid statement number, parent(num, syn)
				vector<int> children = pkb->getStmtChildrenStmt(leftArgument);
				result = filterType(children, rightChildType, pkb);
				return result;
			}
		}
		else if (isSynonym(leftChildType)) { //parent(syn,syn)
											 //	cout << "LEFT IS SYNONYM" << endl;
			left = getTypeStmt(leftChildType, pkb);
			//	cout << "LEFT SIZE IS " << left.size() << endl;
			tempResult = getAllChildren(left, pkb);
			//cout << "TEMP SIZE IS " << tempResult.size() << endl;
			//cout << endl;
			result = filterType(tempResult, rightChildType, pkb);
			//cout << "RESULT SIZE IS " << result.size() << endl;
			//cout << endl;
			return result;
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

vector<int> Parent::getWithRelToLeft(PKB* pkb) {
	//cout << "LEFT" << endl;
	if (isSynonym(leftChildType)) {
		//cout << "LEFT IS SYNONYM" << endl;
		if (isNumber(rightChildType)) {
			int rightArgument = stoi(rightChild);
			if (!isValidStmtNo(rightArgument, pkb)) {
				return result;
			}
			else { //if right is valid statement number, parent(syn, num)
				int parent = pkb->getStmtParentStmt(rightArgument);
			//	cout << "PARENT" << parent << endl;
				if (isStmtType(parent, leftChildType, pkb)) {
					result.push_back(parent);
					return result;
				}
			}
		}
		else if (isSynonym(rightChildType)) { //parent(syn, syn)
											  //cout << "RIGHT IS SYNONYM" << endl;
			right = getTypeStmt(rightChildType, pkb);
			//cout << "NUMBER OF " << rightChildType << " is: " << right.size() << endl;
			tempResult = getAllParents(right, pkb);
			//cout << "NUMBER OF TEMP RESULT is: " << tempResult.size() << endl;
			result = filterType(tempResult, leftChildType, pkb);
			//cout << "NUMBER OF RESULT is: " << result.size() << endl;
			return result;
		}
		else { // parent(synonym, invalid)
			return result;
		}
	}
	else { //invalid left argument
		return result;
	}
	return result;
}

bool Parent::isValidStmtNo(int stmtId, PKB* pkb) {
	return ((stmtId > 0) && (stmtId <= pkb->getNumOfStmt()));
}

vector<int> Parent::getAllChildren(vector<int> list, PKB* pkb) {
	vector<int> children;
	unordered_set<int> allChildren;
	for (int i = 0; i < list.size(); i++) {
		children = pkb->getStmtChildrenStmt(list[i]);
		for (int j = 0; j < children.size(); j++) {
			if (children[j] != -1) {
				allChildren.insert(children[j]);
			}
		}
	}
	vector<int> result(allChildren.size());
	copy(allChildren.begin(), allChildren.end(), result.begin());

	return result;
}

vector<int> Parent::getAllParents(vector<int> list, PKB* pkb) {
	int parent;
	unordered_set<int> allParents;
	for (int i = 0; i < list.size(); i++) {
		parent = pkb->getStmtParentStmt(list[i]);
		if (parent != -1) {
			//cout << parent << " added bcuz it is parent of " << list[i] << endl;
			allParents.insert(parent);
		}
		else {
			//cout << list[i] << " is not parent" << endl;
		}
	}
	vector<int> listParent(allParents.size());
	copy(allParents.begin(), allParents.end(), listParent.begin());
	return listParent;
}

vector<int> Parent::filterType(vector<int> list, Type type, PKB* pkb) {
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

bool Parent::isStmtType(int stmtId, Type type, PKB* pkb) {
	if (stmtId < 1)
		return false;
	switch (type) {
	case WHILE:
		//cout << stmtId << " " << pkb->isStmtInWhileTable(stmtId) << endl;
		return pkb->isStmtInWhileTable(stmtId);
	case ASSIGN:
		return pkb->isStmtInAssignTable(stmtId);
	case STMT:
	case PROG_LINE:
	case ANYTHING:
		return true;
	}
	//cout << stmtId << " false" << endl;
	return false;
}

vector<int> Parent::getTypeStmt(Type type, PKB* pkb) {
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

bool Parent::isNumber(Type type) {
	return (type == INTEGER);
}

bool Parent::isSynonym(Type type) {
	return (type == ASSIGN || type == WHILE || type == STMT || type == ANYTHING || type == PROG_LINE);
}

bool Parent::hasRel(PKB *pkb) {
	if (isSynonym(leftChildType)) {
		if (isNumber(rightChildType)) {
			int rightArgument = stoi(rightChild);
			if (!isValidStmtNo(rightArgument, pkb)) {
				return false; // return what!??!!??!?!?!?!?!?!?!?!?!?!?!?!
			}
			else { //if right is valid statement number, parent(syn, num)
				int parent = pkb->getStmtParentStmt(rightArgument);
				if (isStmtType(parent, leftChildType, pkb)) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		else if (isSynonym(rightChildType)) { // parent(syn,syn)
			right = getTypeStmt(rightChildType, pkb);
			//cout << "NUMBER OF RIGHT IS " << right.size() << endl;
			tempResult = getAllParents(right, pkb);
			//cout << "NUMBER OF TEMP IS " << tempResult.size() << endl;
			result = filterType(tempResult, leftChildType, pkb);
			return (result.size() != 0);
		}
		else { // parent(synonym, invalid)
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
			else { //if right is valid statement number, parent(num, num)
				int parent = pkb->getStmtParentStmt(rightArgument);
				if (parent == leftArgument) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		else if (isSynonym(rightChildType)) { //parent(num , syn)
			vector<int> children = pkb->getStmtChildrenStmt(leftArgument);
			result = filterType(children, rightChildType, pkb);
			return (result.size() != 0);
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

string Parent::getLeftChild() {
	return leftChild;
}
string Parent::getRightChild() {
	return rightChild;
}
Type Parent::getLeftChildType() {
	return leftChildType;
}
Type Parent::getRightChildType() {
	return rightChildType;
}
ClauseType Parent::getClauseType() {
	return PARENT;
}
