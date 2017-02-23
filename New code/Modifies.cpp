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

	vector<int> synList;
	result = getWithRelToLeft(pkbSource, synList);
	if (result.empty()) {
		isRel = false;
	}
	else {
		isRel = true;
	}

	return isRel;
}

vector<int> Modifies::getWithRelToLeft(PKB *pkb, vector<int> synList) {
	vector<int> result, leftList, rightList, varIdList, stmtList, parentList, callStmtList;

	switch (rightChildType) {
	case VARIABLE:
		if (synList.empty()) {
			varIdList = pkb->getAllVarId();
		}
		else {
			varIdList = synList;
		}

		rightList = getStmtListOfVarIdList(varIdList);
		break;
	case ANYTHING:
		if (synList.empty()) {
			varIdList = pkb->getAllVarId();
		}
		else {
			varIdList = synList;
		}
		rightList = getStmtListOfVarIdList(varIdList);
		break;
	case STRINGVARIABLE:
		int varId = pkb->getVarIdByName(rightChild);
		varIdList.push_back(varId);
		if (synList.empty()) {
			varIdList = pkb->getAllVarId();
		}
		else {
			varIdList = synList;
		}
		rightList = getStmtListOfVarIdList(varIdList);
		break;
	}


	switch (leftChildType) {
	case PROG_LINE:
	case STMT:
		leftList = pkb->getAllStmtId(); 
		parentList = getParentOfStmt(rightList);
		callStmtList = getModifyCallStmt(leftList, rightList);

		rightList = VectorSetOperation<int>::setUnion(rightList, parentList);
		rightList = VectorSetOperation<int>::setUnion(rightList, callStmtList);
		break;
	case ASSIGN:
		leftList = pkb->getAllAssignStmt();
		break;
	case WHILES:
		leftList = pkb->getAllWhileStmt();
		parentList = getParentOfStmt(rightList);
		rightList = VectorSetOperation<int>::setUnion(rightList, parentList);
		break;
	case IF:
		leftList = pkb->getAllIfStmt();
		parentList = getParentOfStmt(rightList);
		rightList = VectorSetOperation<int>::setUnion(rightList, parentList);
		break;
	case INTEGER:
		int stmtNo = stoi(leftChild);
		leftList.push_back(stmtNo);
		callStmtList = getModifyCallStmt(leftList, rightList);
		rightList = VectorSetOperation<int>::setUnion(rightList, callStmtList);
		break;
	case PROCS:
		leftList = pkb->getAllProcIdList;
		rightList = getModifyProcId(leftList, rightList);
		break;
	case STRINGPROCS:
		int procId = pkb->getProcIdByName(leftChild);
		leftList.push_back(procId);
		rightList = getModifyProcId(leftList, rightList);
		break;
	}
	
	//Get intersection of 2 list
	result = VectorSetOperation<int>::setIntersection(leftList, rightList);

	return result;
}

vector<int> Modifies::getWithRelToRight(PKB *pkb, vector<int> synList) {
	vector<int> result, leftList, rightList, varIdList, stmtList, tempList, callStmtList, varStmtList;

	switch (rightChildType) {
	case VARIABLE:
		rightList = pkb->getAllVarId();
		break;
	}
	
	switch (leftChildType) {
	case PROG_LINE:
	case STMT:
		if (synList.empty()) {
			leftList = synList;
		}
		else {
			leftList = pkb->getAllStmtId();
		}
		break;
	case ASSIGN:
		if (synList.empty()) {
			leftList = synList;
		}
		else {
			leftList = pkb->getAllAssignStmt();
		}
		break;
	case WHILES:
		if (synList.empty()) {
			leftList = synList;
		}
		else {
			leftList = pkb->getAllWhileStmt();
		}
		leftList = getChildrenOfStmt(leftList);
		break;
	case IF:
		if (synList.empty()) {
			leftList = synList;
		}
		else {
			leftList = pkb->getAllIfStmt();
		}
		leftList = getChildrenOfStmt(leftList);
		break;
	case INTEGER:
		int stmtId = stoi(leftChild);
		leftList.push_back(stmtId);
		varStmtList = getStmtListOfVarIdList(rightList);
		leftList = getModifyVarStmt(leftList, varStmtList);
		break;
	case PROCS:
		if (synList.empty()) {
			leftList = synList;
		}
		else {
			leftList = pkb->getAllProcIdList;
		}
		varStmtList = getStmtListOfVarIdList(rightList);
		leftList = getModifyProcStmt(leftList, varStmtList);
		break;
	case STRINGPROCS:
		int procId = pkb->getProcIdByName(leftChild);
		leftList.push_back(procId);
		varStmtList = getStmtListOfVarIdList(rightList);
		leftList = getModifyProcStmt(leftList, varStmtList);
		break;
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


vector<int> Modifies::getReverseRelToLeft(PKB *pkb, vector<int> synList) {
	return getWithRelToLeft(pkb, synList);
}


vector<int> Modifies::getReverseRelToRight(PKB *pkb, vector<int> synList) {
	return getWithRelToRight(pkb, synList);
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
ClauseType Modifies::getClauseType() {
	return MODIFIES;
}

//Private methods
vector<int> Modifies::getStmtListOfVarIdList(vector<int> varIdList) {
	vector<int> stmtList, allStmtList;
	for (int varId : varIdList) {
		stmtList = pkb->getStmtModifyVar(varId);
		allStmtList = VectorSetOperation<int>::setUnion(allStmtList, stmtList);
	}

	return allStmtList;
}

vector<int> Modifies::getParentOfStmt(vector<int> stmtList) {
	vector<int> parentList, allParentList;
	vector<int> temp;
	for (int stmtId : stmtList) {
		parentList = pkb->getStmtParentStarStmt(stmtId);
		allParentList = VectorSetOperation<int>::setUnion(allParentList, parentList);
	}

	return allParentList;
}

vector<int> Modifies::getChildrenOfStmt(vector<int> stmtList) {
	vector<int> childrenList;
	vector<int> results;
	for (int stmtId : stmtList) {
		childrenList = pkb->getStmtChildrenStarStmt(stmtId);
		results = VectorSetOperation<int>::setUnion(results, childrenList);
	}
	return results;
}


vector<int> Modifies::getModifyCallStmt(vector<int> stmtList, vector<int> varStmtList) {
	vector<int> allResults;
	for (int varStmtId : varStmtList) {
		vector<int> results = getStmtOfCallStmt(stmtList, varStmtId, varStmtId);
		allResults = VectorSetOperation<int>::setUnion(allResults, results);
	}
	return allResults;
}



vector<int> Modifies::getStmtOfCallStmt(vector<int> stmtList, int varStmtId, int callStmtId) {


	vector<int> callStmt = pkb->getAllCallStmt();
	vector<int> callResults;

	for (int stmtId : stmtList) {
		if (find(callStmt.begin(), callStmt.end(), stmtId) != callStmt.end()) {
			int procId = pkb->getCallStmtProcId(stmdId);
			vector<int> procStmtList = pkb->getProcStmtByProcId(procId);
			vector<int> callResults = getStmtOfCallStmt(procStmtList, varStmtId, stmtId);
			if (find(callResults.begin(), callResults.end(), stmtId) != callResults.end()) {
				callResults.push_back(callStmtId);
			}
		}
	}
	if (find(stmtList.begin(), stmtList.end(), varStmtId) != stmtList.end()) {
		callResults.push_back(callStmtId);
	}

	return callResults;
}


vector<int> Modifies::getModifyProcId(vector<int> procIdList, vector<int> varStmtList) {
	vector<int> results;

	for (int procId : procIdList) {
		vector<int> procStmtList = pkb->getProcStmtByProcId(procId);

		vector<int> modifyStmt = VectorSetOperation<int>::setUnion(procStmtList, varStmtList);

		if (modifyStmt.empty()) {
			modifyStmt = getModifyCallStmt(procStmtList, varStmtList);
		}

		if (!modifyStmt.empty()) {
			results.push_back(procId);
		}
	
	}

	return results;

}


vector<int> Modifies::getModifyVarStmt(vector<int> stmtList, vector<int> varStmtList) {
	vector<int> allResults;
	for (int varStmtId : varStmtList) {
		vector<int> results = getStmtOfCallStmt(stmtList, varStmtId, varStmtId);
		allResults = VectorSetOperation<int>::setUnion(allResults, results);
	}
	return allResults;
}



vector<int> Modifies::getStmtOfVarStmt(vector<int> stmtList, int varStmtId, int callStmtId) {

	vector<int> callStmt = pkb->getAllCallStmt();
	vector<int> callResults;

	for (int stmtId : stmtList) {
		if (find(callStmt.begin(), callStmt.end(), stmtId) != callStmt.end()) {
			int procId = pkb->getCallStmtProcId(stmtId);
			vector<int> procStmtList = pkb->getProcStmtByProcId(procId);
			vector<int> callResults = getStmtOfVarStmt(procStmtList, varStmtId, stmtId);
		}
	}
	if (find(stmtList.begin(), stmtList.end(), varStmtId) != stmtList.end()) {
		callResults.push_back(varStmtId);
	}

	return callResults;
}


vector<int> Modifies::getModifyProcStmt(vector<int> procIdList, vector<int> varStmtList) {
	vector<int> results;

	for (int procId : procIdList) {
		vector<int> procStmtList = pkb->getProcStmtByProcId(procId);

		vector<int> modifyStmt = VectorSetOperation<int>::setUnion(procStmtList, varStmtList);

		if (modifyStmt.empty()) {
			modifyStmt = getModifyVarStmt(procStmtList, varStmtList);
		}

		if (!modifyStmt.empty()) {
			results = VectorSetOperation<int>::setUnion(results, modifyStmt);
		}

	}

	return results;

}