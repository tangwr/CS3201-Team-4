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
	case PROG_LINE:
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
			rightList = VectorSetOperation<int>::setUnion(rightList, stmtList); 
		}
		break;

	case ANYTHING:
		varIdList = pkb->getAllVarId();
		for (int varId : varIdList) {
			stmtList = pkb->getStmtUsesVar(varId);
			rightList = VectorSetOperation<int>::setUnion(rightList, stmtList);
		}
		break;
	case STRINGVARIABLE:
		int varId = pkb->getVarId(rightChild);
		rightList = pkb->getStmtUsesVar(varId);
		int i = 0;
		break;
	}

	if (leftChildType == STMT || leftChildType == PROG_LINE) {
		vector<int> parentList;
		vector<int> temp;
		
		for (int stmtId : leftList) {
			parentList = pkb->getParentStar(stmtId);
			temp = VectorSetOperation<int>::setUnion(temp, parentList);
		}
		leftList = VectorSetOperation<int>::setUnion(leftList, temp);
		
	}


	if (leftChildType == ASSIGN ) {
		vector<int> parentList;
		vector<int> temp;
		if (rightChildType != VARIABLE && rightChildType != ANYTHING) {
			for (int stmtId : leftList) {
				parentList = pkb->getParentStar(stmtId);
				temp = VectorSetOperation<int>::setUnion(temp, parentList);
			}
			leftList = VectorSetOperation<int>::setUnion(leftList, temp);
		}
	}



	if ((leftChildType != ASSIGN ) && (rightChildType == STRINGVARIABLE || rightChildType == VARIABLE || rightChildType == ANYTHING)) {
		vector<int> parentList;
		vector<int> temp;
		for (int stmtId : rightList) {
			parentList = pkb->getParentStar(stmtId);
			temp = VectorSetOperation<int>::setUnion(temp, parentList);
		}
		rightList = VectorSetOperation<int>::setUnion(rightList, temp);
	
	}
	
	if ((leftChildType == ASSIGN) && (rightChildType == VARIABLE || rightChildType == ANYTHING)) {
		vector<int> parentList;
		vector<int> temp;
		for (int stmtId : rightList) {
			parentList = pkb->getParentStar(stmtId);
			temp = VectorSetOperation<int>::setUnion(temp, parentList);
		}
		rightList = VectorSetOperation<int>::setUnion(rightList, temp);

	}
	

	//Get intersection of 2 list
	result = VectorSetOperation<int>::setIntersection(leftList, rightList);


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
	case PROG_LINE:
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


	

	//Convert stmtId to varId
	for (int stmtId : leftList) {
		varIdList = pkb->getVarUsedByStmt(stmtId);
		tempList = VectorSetOperation<int>::setUnion(tempList, varIdList);
	}
	leftList = tempList; //all converted to varId

	//Get intersection of 2 list
	result = VectorSetOperation<int>::setIntersection(leftList, rightList);
	//return variable Id results
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

