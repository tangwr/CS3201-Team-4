#include "ClauseType.h"
#include "Type.h"
#include "Modifies.h"
#include "Clause.h"

Modifies::Modifies(string lc, Type lcType, string rc, Type rcType) {
	cltype = MODIFIES;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}
bool Modifies::hasRel(PKB *pkbSource) {
	vector<int> result;

	result = getWithRelToLeft(pkbSource);
	if (result.empty()) {
		isRel = false;
	}
	else {
		isRel = true;
	}

	return isRel;
}

vector<int> Modifies::getWithRelToLeft(PKB *pkb) {
	vector<int> result, leftList, rightList, varIdList, stmtList;

	switch (leftChildType) {
	case STMT:
		leftList = pkb->getAllStmtId(); 
		break;
	case ASSIGN:
		leftList = pkb->getAllAssignStmtId();

		break;
	case WHILES:
		leftList = pkb->getAllWhileStmtId();
		break;
	case INTEGER:
		int stmtNo = stoi(leftChild);
		leftList.push_back(stmtNo);
		break;
	}


	switch (rightChildType) {

	case VARIABLE:
		varIdList = pkb->getAllVarId();
		for (int varId : varIdList) {
			stmtList = pkb->getModifiedByStmt(varId);
			rightList = getUnionList(rightList, stmtList);
		}
		break;
	case ANYTHING:
		rightList = pkb->getAllVarId();
		for (int varId : varIdList) {
			stmtList = pkb->getModifiedByStmt(varId);
			rightList = getUnionList(rightList, stmtList);
		}
		break;
	case STRINGVARIABLE:
		int varId = pkb->getVarId(rightChild);
		rightList = pkb->getModifiedByStmt(varId);
		break;
	}

	//Get intersection of 2 list
	result = getIntersectionList(leftList, rightList);

	return result;
}

vector<int> Modifies::getWithRelToRight(PKB *pkb) {
	vector<int> result, leftList, rightList, varIdList, stmtList;

	switch (rightChildType) {
	case VARIABLE:
		varIdList = pkb->getAllVarId();
		for (int varId : varIdList) {
			stmtList = pkb->getModifiedByStmt(varId);
			rightList = getUnionList(rightList, stmtList);
		}
		break;
	}
	
	switch (leftChildType) {
	case STMT:
		leftList = pkb->getAllStmtId();
		break;
	case ASSIGN:
		leftList = pkb->getAllAssignStmtId();
		break;
	case WHILES:
		leftList = pkb->getAllWhileStmtId();
		break;
	case INTEGER:
		int stmtNo = stoi(leftChild);
		leftList.push_back(stmtNo);
		break;
	}

	//Get intersection of 2 list
	result = getIntersectionList(leftList, rightList);

	return result;
}

string Modifies::getLeftChild() {
	return leftChild;
}
string Modifies::getRightChild() {
	return rightChild;
}
Type Modifies::getLeftChildType() {
	return leftChildType;
}
Type Modifies::getRightChildType() {
	return rightChildType;
}

/*Private methods*/
vector<int> Modifies::getUnionList(vector<int> v1, vector<int> v2) {
	vector<int> v3;
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));

	return v3;
}

vector<int> Modifies::getIntersectionList(vector<int> v1, vector<int> v2) {
	vector<int> v3;
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));

	return v3;
}