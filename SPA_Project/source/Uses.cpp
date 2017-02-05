#include "ClauseType.h"
#include "Type.h"
#include "Uses.h"
#include "Clause.h"

Uses::Uses(string lc, Type lcType, string rc, Type rcType) {
	cltype = USES;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}
bool Uses::hasRel(PKB *pkbSource) {
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

vector<int> Uses::getWithRelToLeft(PKB *pkb) {
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
			stmtList = pkb->getStmtUsesVar(varId);
			rightList = getUnionList(rightList, stmtList);
		}
		break;

	case ANYTHING:
		varIdList = pkb->getAllVarId();
		for (int varId : varIdList) {
			stmtList = pkb->getStmtUsesVar(varId);
			rightList = getUnionList(rightList, stmtList);
		}
		break;
	case STRINGVARIABLE:
		int varId = pkb->getVarId(rightChild);
		rightList = pkb->getStmtUsesVar(varId);

		break;
	}

	if (leftChildType == STMT || leftChildType == WHILES) {//&& (rightChildType== VARIABLE || rightChildType == ANYTHING)) {
		vector<int> parentList;
		vector<int> temp;
		for (int stmtId : rightList) {
			parentList = pkb->getParentStar(stmtId);
			temp = getUnionList(temp, parentList);
		}
		rightList = getUnionList(rightList, temp);
	}

	//Get intersection of 2 list
	result = getIntersectionList(leftList, rightList);

	return result;
}

vector<int> Uses::getWithRelToRight(PKB *pkb) {
	vector<int> result, leftList, rightList, varIdList, stmtList, tempList;

	switch (rightChildType) {
	case VARIABLE:
		rightList = pkb->getAllVarId();
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
		int stmtId = stoi(leftChild);
		leftList.push_back(stmtId);
		break;
	}


	if (leftChildType == WHILES) {
		vector<int> childrenList;
		vector<int> temp;
		for (int stmtId : leftList) {
			childrenList = pkb->getChildrenStar(stmtId);
			temp = getUnionList(temp, childrenList);
		}
		leftList = temp;
	}

	//Convert stmtId to varId
	for (int stmtId : leftList) {
		varIdList = pkb->getVarUsedByStmt(stmtId);
		tempList = getUnionList(tempList, varIdList);
	}
	leftList = tempList; //all converted to varId



						 //Get intersection of 2 list
	result = getIntersectionList(leftList, rightList);
	//return variable Id
	return result;
}

string Uses::getLeftChild() {
	return leftChild;
}
string Uses::getRightChild() {
	return rightChild;
}
Type Uses::getLeftChildType() {
	return leftChildType;
}
Type Uses::getRightChildType() {
	return rightChildType;
}

/*Private methods*/
vector<int> Uses::getUnionList(vector<int> v1, vector<int> v2) {
	vector<int> v3;
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));

	return v3;
}

vector<int> Uses::getIntersectionList(vector<int> v1, vector<int> v2) {
	vector<int> v3;
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));

	return v3;
}