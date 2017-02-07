#include "Type.h"
#include "Modifies.h"
#include "Clause.h"

Modifies::Modifies(string lc, Type lcType, string rc, Type rcType) {
	//cltype = MODIFIES;
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
	case PROG_LINE:
	case STMT:
		leftList = pkb->getAllStmtId(); 
		break;
	case ASSIGN:
		leftList = pkb->getAllAssignStmt();
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
			stmtList = pkb->getStmtModifyVar(varId);
			rightList = VectorSetOperation<int>::setUnion(rightList, stmtList);
		}
		break;

	case ANYTHING:
		varIdList = pkb->getAllVarId();
		for (int varId : varIdList) {
			stmtList = pkb->getStmtModifyVar(varId);
			rightList = VectorSetOperation<int>::setUnion(rightList, stmtList);
		}
		break;
	case STRINGVARIABLE:
		int varId = pkb->getVarIdByName(rightChild);
		rightList = pkb->getStmtModifyVar(varId);
		int i = 0;
		break;
	}

	if (leftChildType == STMT || leftChildType == PROG_LINE || leftChildType == WHILES){
		vector<int> parentList;
		vector<int> temp;
		for (int stmtId : rightList) {
			parentList = pkb->getStmtParentStarStmt(stmtId);
			temp = VectorSetOperation<int>::setUnion(temp, parentList);
		}
		rightList = VectorSetOperation<int>::setUnion(rightList, temp);
	}
	
	//Get intersection of 2 list
	result = VectorSetOperation<int>::setIntersection(leftList, rightList);

	return result;
}

vector<int> Modifies::getWithRelToRight(PKB *pkb) {
	vector<int> result, leftList, rightList, varIdList, stmtList, tempList;

	switch (rightChildType) {
	case VARIABLE:
		rightList = pkb->getAllVarId();
		break;
	}
	
	switch (leftChildType) {
	case PROG_LINE:
	case STMT:
		leftList = pkb->getAllStmtId();
		break;
	case ASSIGN:
		leftList = pkb->getAllAssignStmt();
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
			childrenList = pkb->getStmtChildrenStarStmt(stmtId);
			temp = VectorSetOperation<int>::setUnion(temp, childrenList);
		}
		leftList = temp;
	}

	//Convert stmtId to varId
	for (int stmtId : leftList) {
		varIdList = pkb->getVarModifiedInStmt(stmtId);
		tempList = VectorSetOperation<int>::setUnion(tempList, varIdList);
	}
	leftList = tempList; //all converted to varId



	//Get intersection of 2 list
	result = VectorSetOperation<int>::setIntersection(leftList, rightList);
	//return variable Id
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

