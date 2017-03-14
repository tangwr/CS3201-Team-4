#include "Type.h"
#include "Uses.h"
#include "Clause.h"

/*Uses::Uses(string lc, Type lcType, string rc, Type rcType) {
	//cltype = USES;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}
*/
Uses::Uses(Parameter lc, Parameter rc) {
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
			//stmtList = pkb->getStmtUseVar(varId);
			rightList = VectorSetOperation<int>::setUnion(rightList, stmtList); 
		}
		break;

	case ANYTHING:
		//varIdList = pkb->getAllVarId();
		for (int varId : varIdList) {
			//stmtList = pkb->getStmtUseVar(varId);
			rightList = VectorSetOperation<int>::setUnion(rightList, stmtList);
		}
		break;
	case STRINGVARIABLE:
		int varId = pkb->getVarIdByName(rightChild.getParaName());
		//rightList = pkb->getStmtUseVar(varId);
		
		break;
	}

	if (leftChild.getParaType() == STMT || leftChild.getParaType() == PROG_LINE) {
		vector<int> parentList;
		vector<int> temp;
		
		for (int stmtId : leftList) {
			//parentList = pkb->getStmtParentStarStmt(stmtId);
			temp = VectorSetOperation<int>::setUnion(temp, parentList);
		}
		leftList = VectorSetOperation<int>::setUnion(leftList, temp);
		
	}

	/*
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
	*/


	if ((leftChild.getParaType() != ASSIGN ) && (rightChild.getParaType() == STRINGVARIABLE || rightChild.getParaType() == VARIABLE || rightChild.getParaType() == ANYTHING)) {
		vector<int> parentList;
		vector<int> temp;
		for (int stmtId : rightList) {
			//parentList = pkb->getStmtParentStarStmt(stmtId);
			temp = VectorSetOperation<int>::setUnion(temp, parentList);
		}
		rightList = VectorSetOperation<int>::setUnion(rightList, temp);
	
	}
	
	if ((leftChild.getParaType() == ASSIGN) && (rightChild.getParaType() == VARIABLE || rightChild.getParaType() == ANYTHING)) {
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

vector<int> Uses::getWithRelToRight(PKB *pkb) {
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


	

	//Convert stmtId to varId
	for (int stmtId : leftList) {
		//varIdList = pkb->getVarUsedByStmt(stmtId);
		tempList = VectorSetOperation<int>::setUnion(tempList, varIdList);
	}
	leftList = tempList; //all converted to varId

	//Get intersection of 2 list
	result = VectorSetOperation<int>::setIntersection(leftList, rightList);
	//return variable Id results
	return result;
}
/*
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
*/

Parameter Uses::getLeftChild() {
	return leftChild;
}
Parameter Uses::getRightChild() {
	return rightChild;
}
vector<Parameter> Uses::getSynList() {
	return synList;
}

ClauseType Uses::getClauseType() {
	return USES;
}

ResultTable Uses::evaluate(PKB* pkb, ResultTable intResultTable) {
	return ResultTable();
}
