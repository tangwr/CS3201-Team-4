#include "Type.h"
#include "ParentStar.h"
#include "Clause.h"

ParentStar::ParentStar(string lc, Type lcType, string rc, Type rcType) {
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}

vector<int> ParentStar::getWithRelToRight(PKB* pkb) {
	//cout << "RIGHT" << endl;
	if (isSynonym(rightChildType)) {
		//cout << "RIGHT IS SYNONYM" << endl;
		if (isNumber(leftChildType)) {
			int leftArgument = stoi(leftChild);
			if (!isValidStmtNo(leftArgument, pkb)) {
				return result;
			}
			else { //if left is a valid statement number, parent*(num, syn)
				vector<int> children = pkb->getStmtChildrenStarStmt(leftArgument);
				result = filterType(children, rightChildType, pkb);
				return result;
			}
		}
		else if (isSynonym(leftChildType)) { //parent(syn,syn)
											 //cout << "LEFT IS SYNONYM" << endl;
			left = getTypeStmt(leftChildType, pkb);
			//cout << "LEFT SIZE IS " << left.size() << endl;
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

vector<int> ParentStar::getWithRelToLeft(PKB* pkb) {
	//cout << "LEFT" << endl;
	if (isSynonym(leftChildType)) {
		//cout << "LEFT IS SYNONYM" << endl;
		if (isNumber(rightChildType)) {
			int rightArgument = stoi(rightChild);
			if (!isValidStmtNo(rightArgument, pkb)) {
				return result;
			}
			else { //if right is valid statement number, parent(syn, num)
				vector<int> parents = pkb->getStmtParentStarStmt(rightArgument);
				result = filterType(parents, leftChildType, pkb);
				return result;
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

bool ParentStar::isValidStmtNo(int stmtId, PKB* pkb) {
	return ((stmtId > 0) && (stmtId <= pkb->getNumOfStmt()));
}

vector<int> ParentStar::getAllChildren(vector<int> list, PKB* pkb) {
	vector<int> children;
	unordered_set<int> allChildren;
	for (int i = 0; i < list.size(); i++) {
		children = pkb->getStmtChildrenStarStmt(list[i]);
		for (int j = 0; j < children.size(); j++) {
			allChildren.insert(children[j]);
		}
	}
	vector<int> result(allChildren.size());
	copy(allChildren.begin(), allChildren.end(), result.begin());

	return result;
}

vector<int> ParentStar::getAllParents(vector<int> list, PKB* pkb) {
	vector<int> parents;
	unordered_set<int> allParents;
	for (int i = 0; i < list.size(); i++) {
		parents = pkb->getStmtParentStarStmt(list[i]);
		//cout << "Iteration: " << i << endl;
		for (int j = 0; j < parents.size(); j++) {
			allParents.insert(parents[j]);
		}
	}
	//cout << "HERE" << endl;
	vector<int> listParent(allParents.size());
	copy(allParents.begin(), allParents.end(), listParent.begin());
	return listParent;
}

vector<int> ParentStar::filterType(vector<int> list, Type type, PKB* pkb) {
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

bool ParentStar::isStmtType(int stmtId, Type type, PKB* pkb) {
	if (stmtId < 1)
		return false;
	switch (type) {
	case WHILES:
		//	cout << stmtId << " " << pkb->isStmtInWhileTable(stmtId) << endl;
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

vector<int> ParentStar::getTypeStmt(Type type, PKB* pkb) {
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
	case WHILES:
		return pkb->getAllWhileStmt();
	case ASSIGN:
		return pkb->getAllAssignStmt();
	}
	vector<int> result;
	return result;
}

bool ParentStar::isNumber(Type type) {
	return (type == INTEGER);
}

bool ParentStar::isSynonym(Type type) {
	return (type == ASSIGN || type == WHILES || type == STMT || type == ANYTHING || type == PROG_LINE);
}

bool ParentStar::hasRel(PKB *pkb) {
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
				vector<int> parent = pkb->getStmtParentStarStmt(rightArgument);
				for (int i = 0; i < parent.size(); i++) {
					if (parent[i] == leftArgument)
						return true;
				}
				return false;
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

string ParentStar::getLeftChild() {
	return leftChild;
}
string ParentStar::getRightChild() {
	return rightChild;
}
Type ParentStar::getLeftChildType() {
	return leftChildType;
}
Type ParentStar::getRightChildType() {
	return rightChildType;
}
ClauseType ParentStar::getClauseType() {
	return PARENTSTAR;
}