#include "Type.h"
#include "CallsStar.h"
#include "Clause.h"

CallsStar::CallsStar(string lc, Type lcType, string rc, Type rcType) {
	leftChild = lc;
	rightChild = rc;
	leftChildType = lcType;
	rightChildType = rcType;
}
bool CallsStar::hasRel(PKB *pkbSource) {
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

vector<int> CallsStar::getWithRelToLeft(PKB *pkb, vector<int> synList) {
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

	switch (leftChildType) {
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

vector<int> CallsStar::getWithRelToRight(PKB *pkb, vector<int> synList) {
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


vector<int> CallsStar::getReverseRelToLeft(PKB *pkb, vector<int> synList) {
	return getWithRelToLeft(pkb, synList);
}


vector<int> CallsStar::getReverseRelToRight(PKB *pkb, vector<int> synList) {
	return getWithRelToRight(pkb, synList);
}




string CallsStar::getLeftChild() {
	return leftChild;
}
string CallsStar::getRightChild() {
	return rightChild;
}
Type CallsStar::getLeftChildType() {
	return leftChildType;
}
Type CallsStar::getRightChildType() {
	return rightChildType;
}
ClauseType CallsStar::getClauseType() {
	return CALLSTAR;
}

//Private methos
vector<int> CallsStar::getCallProc(vector<int> mainProcList, vector<int> compareProcList) {

	vector<int> results;

	for (int procId : mainProcList) {
		if (hasRelCall(procId, compareProcList)) {
			results.push_back(procId);
		}
	}

	return results;
}

bool CallsStar::hasRelCall(int procId, vector<int> procList) {

	vector<int> stmtList = pkb->getStmtByProcId(procId);
	vector<int> callStmt = pkb->getAllCallStmt();
	vector<int> callList, emptyList, commonProcId;

	for (int stmtId : stmtList) {
		if (find(callStmt.begin(), callStmt.end(), stmtId) != callStmt.end()) {
			callList.push_back(stmtId);
		}
	}

	if (!callList.empty()) {
		for (int callStmtId : callList) {
			int callProcId = pkb->getCallStmtProcId(callStmtId);
			vector<int> relCallStmt = getRelCallStmt(callProcId, emptyList);
			commonProcId = VectorSetOperation<int>::setIntersection(relCallStmt, procList);
			if (!commonProcId.empty()) {
				return true;
			}
		}
	}
	return false;

}

vector<int> CallsStar::getRelCallStmt(int procId, vector<int> procList) {
	vector<int> stmtList = pkb->getStmtByProcId(procId);
	vector<int> allCall = pkb->getAllCallStmt();
	vector<int> callStmt, results;

	for (int stmtId : stmtList) {
		if (find(allCall.begin(), allCall.end(), stmtId) != allCall.end()) {
			callStmt.push_back(stmtId);
		}
	}

	if (!callStmt.empty()) {
		for (int callStmtId : callStmt) {
			int callProcId = pkb->getCallStmtProcId(callStmtId);
			procList.push_back(callProcId);
			procList = getRelCallStmt(callProcId, procList);
		}
	}

	results = procList;

	return results;
}





