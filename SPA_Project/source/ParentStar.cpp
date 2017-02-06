#include "ClauseType.h"
#include "Type.h"
#include "ParentStar.h"
#include "Clause.h"

ParentStar::ParentStar(string lc, Type lcType, string rc, Type rcType) {
	cltype = PARENTSTAR;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}

vector<int> ParentStar::getWithRelToRight(PKB* pkb) {
	cout << "RIGHT" << endl;
	if (isSynonym(rightChildType)) {
		cout << "RIGHT IS SYNONYM" << endl;
		if (isNumber(leftChildType)) {
			int leftArgument = stoi(leftChild);
			if (!isValidStmtNo(leftArgument, pkb)) {
				return result;
			}
			else { //if left is a valid statement number, parent*(num, syn)
				vector<int> children = pkb->getChildrenStar(leftArgument);
				result = filterType(children, rightChildType, pkb);
				return result;
			}
		}
		else if (isSynonym(leftChildType)) { //parent(syn,syn)
			cout << "LEFT IS SYNONYM" << endl;
			left = getTypeStmt(leftChildType, pkb);
			cout << "LEFT SIZE IS " << left.size() << endl;
			tempResult = getAllChildren(left, pkb);
			cout << "TEMP SIZE IS " << tempResult.size() << endl;
			cout << endl;
			result = filterType(tempResult, rightChildType, pkb);
			cout << "RESULT SIZE IS " << result.size() << endl;
			cout << endl;
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
	cout << "LEFT" << endl;
	if (isSynonym(leftChildType)) {
		cout << "LEFT IS SYNONYM" << endl;
		if (isNumber(rightChildType)) {
			int rightArgument = stoi(rightChild);
			if (!isValidStmtNo(rightArgument, pkb)) {
				return result;
			}
			else { //if right is valid statement number, parent(syn, num)
				vector<int> parents = pkb->getParentStar(rightArgument);
				result = filterType(parents, leftChildType, pkb);
				return result;
			}
		}
		else if (isSynonym(rightChildType)) { //parent(syn, syn)
			cout << "RIGHT IS SYNONYM" << endl;
			right = getTypeStmt(rightChildType, pkb);
			cout << "NUMBER OF " << rightChildType << " is: " << right.size() << endl;
			tempResult = getAllParents(right, pkb);
			cout << "NUMBER OF TEMP RESULT is: " << tempResult.size() << endl;
			result = filterType(tempResult, leftChildType, pkb);
			cout << "NUMBER OF RESULT is: " << result.size() << endl;
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
	return ((stmtId > 0) && (stmtId <= pkb->getTotalStmtNum()));
}

vector<int> ParentStar::getAllChildren(vector<int> list, PKB* pkb) {
	vector<int> children;
	unordered_set<int> allChildren;
	for (int i = 0; i < list.size(); i++) {
		children = pkb->getChildrenStar(list[i]);
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
		parents = pkb->getParentStar(list[i]);
		cout << "Iteration: " << i << endl;
		for (int j = 0; j < parents.size(); j++) {
			allParents.insert(parents[j]);
		}
	}
	cout << "HERE" << endl;
	vector<int> listParent(allParents.size());
	copy(allParents.begin(), allParents.end(), listParent.begin());
	return listParent;
}

vector<int> ParentStar::filterType(vector<int> list, Type type, PKB* pkb) {
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

bool ParentStar::isStmtType(int stmtId, Type type, PKB* pkb) {
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

vector<int> ParentStar::getTypeStmt(Type type, PKB* pkb) {
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

bool ParentStar::isNumber(Type type) {
	return (type == PROG_LINE);
}

bool ParentStar::isSynonym(Type type) {
	return (type == ASSIGN || type == WHILES || type == STMT || type == ANYTHING);
}

bool ParentStar::hasRel(PKB *pkbSource) {
	if (isSynonym(leftChildType)) {
		if (isNumber(rightChildType)) {
			int rightArgument = stoi(rightChild);
			if (!isValidStmtNo(rightArgument, pkb)) {
				return false; // return what!??!!??!?!?!?!?!?!?!?!?!?!?!?!
			}
			else { //if right is valid statement number, parent(syn, num)
				int parent = pkb->getParentDirect(rightArgument);
				if (isStmtType(parent, leftChildType, pkb)) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		else if (isSynonym(rightChildType)) { // parent(syn,sy
			return pkb->hasParentRel();
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
				int parent = pkb->getParentDirect(rightArgument);
				if (parent == leftArgument) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		else if (isSynonym(rightChildType)) { //parent(num , syn)
			vector<int> children = pkb->getChildren(leftArgument);
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

