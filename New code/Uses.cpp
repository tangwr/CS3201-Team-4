#include "Type.h"
#include "Uses.h"
#include "Clause.h"

Uses::Uses(string lc, Type lcType, string rc, Type rcType) {
	//cltype = USES;
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}
bool Uses::hasRel(PKB *pkbSource) {
	vector<int> result;

	vector<int> synList;
	result = getWithRelToLeft(pkbSource);
	if (result.empty()) {
		isRel = false;
	}
	else {
		isRel = true;
	}

	return isRel;
}

vector<int> Uses::getWithRelToLeft(PKB *pkb, vector<int> synList) {
	vector<int> result, leftList, rightList, varIdList, stmtList;


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
		leftList = VectorSetOperation<int>::setUnion(leftList, getParentOfStmt(leftList));
		rightList = VectorSetOperation<int>::setUnion(rightList, getParentOfStmt(rightList));
		rightList = VectorSetOperation<int>::setUnion(rightList, getUsesCallStmt(leftList, rightList));
		break;
	case ASSIGN:
		leftList = pkb->getAllAssignStmt();
		if(rightChildType == VARIABLE || rightChildType == ANYTHING) {
			rightList = VectorSetOperation<int>::setUnion(rightList, getParentOfStmt(rightList));
		}
		break;
	case WHILES:
		leftList = pkb->getAllWhileStmt();
		rightList = VectorSetOperation<int>::setUnion(rightList, getParentOfStmt(rightList));
		break;
	case IF:
		leftList = pkb->getAllIfStmt();
		rightList = VectorSetOperation<int>::setUnion(rightList, getParentOfStmt(rightList));
		break;
	case INTEGER:
		int stmtNo = stoi(leftChild);
		leftList.push_back(stmtNo);
		rightList = VectorSetOperation<int>::setUnion(rightList, getParentOfStmt(rightList));
		rightList = VectorSetOperation<int>::setUnion(rightList, getUsesCallStmt(leftList, rightList));
		break;
	case PROCS:
		leftList = pkb->getAllProcIdList;
		rightList = getUsesProcId(leftList, rightList);
		break;
	case STRINGPROCS:
		int procId = pkb->getProcIdByName(leftChild);
		leftList.push_back(procId);
		rightList = getUsesProcId(leftList, rightList);
		break;
	}

	//Get intersection of 2 list
	result = VectorSetOperation<int>::setIntersection(leftList, rightList);


	return result;
}

vector<int> Uses::getWithRelToRight(PKB *pkb, vector<int> synList) {
	vector<int> result, leftList, rightList, varIdList, stmtList, tempList, varStmtList;

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
		break;
	case IF:
		if (synList.empty()) {
			leftList = synList;
		}
		else {
			leftList = pkb->getAllWhileStmt();
		}
		break;
	case INTEGER:
		int stmtId = stoi(leftChild);
		leftList.push_back(stmtId);
		varStmtList = getStmtListOfVarIdList(rightList);
		leftList = getUsesVarStmt(leftList, varStmtList);
		break;
	case PROCS:
		if (synList.empty()) {
			leftList = synList;
		}
		else {
			leftList = pkb->getAllProcIdList;
		}
		varStmtList = getStmtListOfVarIdList(rightList);
		leftList = getUsesProcStmt(leftList, varStmtList);
		break;
	case STRINGPROCS:
		int procId =  pkb->getProcIdByName(leftChild);
		leftList.push_back(procId);
		varStmtList = getStmtListOfVarIdList(rightList);
		leftList = getUsesProcStmt(leftList, varStmtList);
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

vector<int> Uses::getReverseRelToLeft(PKB *pkb, vector<int> synList) {
	return getWithRelToLeft(pkb, synList);
}


vector<int> Uses::getReverseRelToRight(PKB *pkb, vector<int> synList) {
	return getWithRelToRight(pkb, synList);
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
ClauseType Uses::getClauseType() {
	return USES;
}

//Private methods
vector<int> Uses::getStmtListOfVarIdList(vector<int> varIdList) {
	vector<int> stmtList, allStmtList;
	for (int varId : varIdList) {
		stmtList = pkb->getStmtModifyVar(varId);
		allStmtList = VectorSetOperation<int>::setUnion(allStmtList, stmtList);
	}

	return allStmtList;
}

vector<int> Uses::getParentOfStmt(vector<int> stmtList) {
	vector<int> parentList, allParentList;
	vector<int> temp;
	for (int stmtId : stmtList) {
		parentList = pkb->getStmtParentStarStmt(stmtId);
		allParentList = VectorSetOperation<int>::setUnion(allParentList, parentList);
	}

	return allParentList;
}

vector<int> Uses::getUsesCallStmt(vector<int> stmtList, vector<int> varStmtList) {
	vector<int> allResults;
	for (int varStmtId : varStmtList) {
		vector<int> results = getStmtOfCallStmt(stmtList, varStmtId, varStmtId);
		allResults = VectorSetOperation<int>::setUnion(allResults, results);
	}
	return allResults;
}



vector<int> Uses::getStmtOfCallStmt(vector<int> stmtList, int varStmtId, int callStmtId) {


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

vector<int> Uses::getUsesProcId(vector<int> procIdList, vector<int> varStmtList) {
	vector<int> results;

	for (int procId : procIdList) {
		vector<int> procStmtList = pkb->getProcStmtByProcId(procId);

		vector<int> usesStmt = VectorSetOperation<int>::setUnion(procStmtList, varStmtList);

		if (usesStmt.empty()) {
			usesStmt = getUsesCallStmt(procStmtList, varStmtList);
		}

		if (!usesStmt.empty()) {
			results.push_back(procId);
		}

	}
	return results;
}


vector<int> Uses::getUsesVarStmt(vector<int> stmtList, vector<int> varStmtList) {
	vector<int> allResults;
	for (int varStmtId : varStmtList) {
		vector<int> results = getStmtOfCallStmt(stmtList, varStmtId, varStmtId);
		allResults = VectorSetOperation<int>::setUnion(allResults, results);
	}
	return allResults;
}



vector<int> Uses::getStmtOfVarStmt(vector<int> stmtList, int varStmtId, int callStmtId) {

	vector<int> callStmt = pkb->getAllCallStmt();
	vector<int> callResults;

	for (int stmtId : stmtList) {
		if (find(callStmt.begin(), callStmt.end(), stmtId) != callStmt.end()) {
			int procId = pkb->getCallStmtProcId(stmdId);
			vector<int> procStmtList = pkb->getProcStmtByProcId(procId);
			vector<int> callResults = getStmtOfVarStmt(procStmtList, varStmtId, stmtId);
		}
	}
	if (find(stmtList.begin(), stmtList.end(), varStmtId) != stmtList.end()) {
		callResults.push_back(varStmtId);
	}

	return callResults;
}

vector<int> Uses::getUsesProcStmt(vector<int> procIdList, vector<int> varStmtList) {
	vector<int> results;

	for (int procId : procIdList) {
		vector<int> procStmtList = pkb->getProcStmtByProcId(procId);

		vector<int> usesStmt = VectorSetOperation<int>::setUnion(procStmtList, varStmtList);

		if (usesStmt.empty()) {
			usesStmt = getUsesVarStmt(procStmtList, varStmtList);
		}

		if (!usesStmt.empty()) {
			results = VectorSetOperation<int>::setUnion(results, usesStmt);
		}

	}

	return results;
