#include "Type.h"
#include "Modifies.h"
#include "Clause.h"
/*
Modifies::Modifies(string lc, Type lcType, string rc, Type rcType) {
	//cltype = MODIFIES;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}*/
Modifies::Modifies(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;

	if (lc.getParaType() != Type::CONSTANT && lc.getParaType() != Type::BOOLEAN && lc.getParaType() != Type::ANYTHING
		&& lc.getParaType() != Type::STRINGVARIABLE && lc.getParaType() != Type::INTEGER) {
		synList.push_back(lc);
	}
	if (rc.getParaType() != Type::CONSTANT && rc.getParaType() != Type::BOOLEAN && rc.getParaType() != Type::ANYTHING
		&& rc.getParaType() != Type::STRINGVARIABLE && rc.getParaType() != Type::INTEGER) {
		synList.push_back(rc);
	}
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

	switch (leftChild.getParaType()) {
	case PROG_LINE:
	case STMT:
		//leftList = pkb->getAllStmtId(); 
		break;
	case ASSIGN:
		//leftList = pkb->getAllAssignStmt();
		break;
	case WHILE:
		//leftList = pkb->getAllWhileStmt();
		break;
	case INTEGER:
		int stmtNo = stoi(leftChild.getParaName());
		leftList.push_back(stmtNo);
		break;
	}


	switch (rightChild.getParaType()) {

	case VARIABLE:
		//varIdList = pkb->getAllVarId();
		for (int varId : varIdList) {
			//stmtList = pkb->getStmtModifyVar(varId);
			rightList = VectorSetOperation<int>::setUnion(rightList, stmtList);
		}
		break;

	case ANYTHING:
		//varIdList = pkb->getAllVarId();
		for (int varId : varIdList) {
			//stmtList = pkb->getStmtModifyVar(varId);
			rightList = VectorSetOperation<int>::setUnion(rightList, stmtList);
		}
		break;
	case STRINGVARIABLE:
		int varId = pkb->getVarIdByName(rightChild.getParaName());
		//rightList = pkb->getStmtModifyVar(varId);
		int i = 0;
		break;
	}

	if (leftChild.getParaType() == STMT || leftChild.getParaType() == PROG_LINE || leftChild.getParaType() == WHILE){
		vector<int> parentList;
		vector<int> temp;
		for (int stmtId : rightList) {
			//parentList = pkb->getStmtParentStarStmt(stmtId);
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

	switch (rightChild.getParaType()) {
	case VARIABLE:
		//rightList = pkb->getAllVarId();
		break;
	}
	
	switch (leftChild.getParaType()) {
	case PROG_LINE:
	case STMT:
		//leftList = pkb->getAllStmtId();
		break;
	case ASSIGN:
		//leftList = pkb->getAllAssignStmt();
		break;
	case WHILE:
		//leftList = pkb->getAllWhileStmt();
		break;
	case INTEGER:
		int stmtId = stoi(leftChild.getParaName());
		leftList.push_back(stmtId);
		break;
	}


	if (leftChild.getParaType() == WHILE) {
		vector<int> childrenList;
		vector<int> temp;
		for (int stmtId : leftList) {
			//childrenList = pkb->getStmtChildrenStarStmt(stmtId);
			temp = VectorSetOperation<int>::setUnion(temp, childrenList);
		}
		leftList = temp;
	}

	//Convert stmtId to varId
	for (int stmtId : leftList) {
		//varIdList = pkb->getVarModifiedInStmt(stmtId);
		tempList = VectorSetOperation<int>::setUnion(tempList, varIdList);
	}
	leftList = tempList; //all converted to varId



	//Get intersection of 2 list
	result = VectorSetOperation<int>::setIntersection(leftList, rightList);
	//return variable Id
	return result;
}
/*
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
*/
Parameter Modifies::getLeftChild() {
	return leftChild;
}
Parameter Modifies::getRightChild() {
	return rightChild;
}
vector<Parameter> Modifies::getSynList() {
	return synList;
}

ClauseType Modifies::getClauseType() {
	return MODIFIES;
}

ResultTable Modifies::evaluate(PKB* pkb, ResultTable intResultTable) {
	return ResultTable();
}