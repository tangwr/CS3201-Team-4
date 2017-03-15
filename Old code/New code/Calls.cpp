#include "Type.h"
#include "Calls.h"
#include "Clause.h"

Calls::Calls(string lc, Type lcType, string rc, Type rcType) {
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}
bool Calls::hasRel(PKB *pkbSource) {
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

vector<int> Calls::getWithRelToLeft(PKB *pkb, vector<int> synList) {
	vector<int> leftProcList, rightProcList, leftStmtList, rightStmtList;


	switch (rightChildType) {
	case PROCS:
		if (synList.empty()) {
			rightProcList = pkb->getAllProcId();
		}
		else {
			rightProcList = synList;
		}
		break;
	case STRINGPROCS:
		int procId = pkb->getProcIdByName(leftChild);
		leftProcList.push_back(procId);
		break;
	case ANYTHING:
		leftProcList = pkb->getAllProcId();
		break;
	}

	switch(leftChildType) {
	case PROCS:
		leftProcList = pkb->getAllProcId();
		break;
	case STRINGPROCS:
		int procId = pkb->getProcIdByName(leftChild);
		leftProcList.push_back(procId);
		break;
	case ANYTHING:
		leftProcList = pkb->getAllProcId();
		break;
	}

	return getCallProc(leftProcList, rightProcList);

}

vector<int> Calls::getWithRelToRight(PKB *pkb, vector<int> synList) {
	vector<int> leftProcList, rightProcList, leftStmtList, rightStmtList;

	switch (leftChildType) {
	case PROCS:
		if (synList.empty()) {
			rightProcList = pkb->getAllProcId();
		}
		else {
			rightProcList = synList;
		}
		break;
	case STRINGPROCS:
		int procId = pkb->getProcIdByName(leftChild);
		leftProcList.push_back(procId);
		break;
	case ANYTHING:
		leftProcList = pkb->getAllProcId();
		break;
	}

	switch (rightChildType) {
	case PROCS:
		leftProcList = pkb->getAllProcId();
		break;
	case STRINGPROCS:
		int procId = pkb->getProcIdByName(leftChild);
		leftProcList.push_back(procId);
		break;
	case ANYTHING:
		leftProcList = pkb->getAllProcId();
		break;
	}

	return getCallProc(rightProcList, leftProcList);
}


vector<int> Calls::getReverseRelToLeft(PKB *pkb, vector<int> synList) {
	return getWithRelToLeft(pkb, synList);
}


vector<int> Calls::getReverseRelToRight(PKB *pkb, vector<int> synList) {
	return getWithRelToRight(pkb, synList);
}




string Calls::getLeftChild() {
	return leftChild;
}
string Calls::getRightChild() {
	return rightChild;
}
Type Calls::getLeftChildType() {
	return leftChildType;
}
Type Calls::getRightChildType() {
	return rightChildType;
}
ClauseType Calls::getClauseType() {
	return CALL;
}

//Private methos
vector<int> Calls::getCallProc(vector<int> mainProcList, vector<int> compareProcList) {

	vector<int> results;

	for (int procId : mainProcList) {
		if (hasDirectCall(procId, compareProcList)) {
			results.push_back(procId);
		}
	}

	return results;
}

bool Calls::hasDirectCall(int procId, vector<int> procList) {

	vector<int> stmtList = pkb->getStmtByProcId(procId);
	vector<int> callStmt = pkb->getAllCallStmt();
	vector<int> callList;

	for (int stmtId : stmtList) {
		if (find(callStmt.begin(), callStmt.end(), stmtId) != callStmt.end()) {
			callList.push_back(stmtId);
		}
	}

	if (!callList.empty()) {
		for (int callStmtId : callList){
			int callProcId = pkb->getCallStmtProcId(callStmtId);
			if (find(procList.begin(), procList.end(), callProcId) != procList.end()) {
				return true;
			}
		}
	}
	

	return false;

}