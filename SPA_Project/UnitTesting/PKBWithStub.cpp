#include <unordered_map>

#include "stdafx.h"
#include "PKBWithStub.h"
#include "UnorderedSetOperation.h"

/*
procedure Example {
x = 2;						//1
z = 3;						//2
i = 5;						//3
while i {					//4
x = x - 1;				//5
if x then {				//6
z = x + 1; }		//7
else {
y = z + x; }		//8
z = z + x + i;		//9
call q;					//10
i = i - 1; }			//11
call p; }				//12

procedure p {
if x then {					//13
while i {				//14
x = z * 3 + 2 * y;	//15
call q;				//16
i = i - 1; }		//17
x = x + 1;				//18
z = x + z; }			//19
else {
z = 1; }				//20
z = z + x + i; }		//21

procedure q {
if x then {					//22
z = x + 1; }			//23
else {
x = z + x; } }			//24
*/

PKBWithStub::PKBWithStub() {
	varTable = { "x", "z", "i", "y" };
	procTable = { "Example", "p", "q" };
	constTable = { 2, 3, 5, 1 };

	callStmts = { 10, 12, 16 };
	callTable = { { 10, 2 },{ 12, 1 },{ 16, 2 } };

	assignStmts = { 1, 2, 3, 5, 7, 8, 9, 11, 15, 17, 18, 19, 20, 21, 23, 24 };
	whileStmts = { 4, 14 };
	ifStmts = { 6, 13, 22 };
}

unordered_set<int> PKBWithStub::getAllVarId() {
	unordered_set<int> vars;
	for (int varId = 0; varId < varTable.size(); varId++) {
		vars.insert(varId);
	}
	return vars;
}

int PKBWithStub::getVarIdByName(string varName) {
	for (int i = 0; i < (int)varTable.size(); i++) {
		if (varTable[i].compare(varName) == 0) {
			return i;
		}
	}
	return -1;
}

string PKBWithStub::getVarNameById(int varId) {
	if (varId < 0 || varId >(int)varTable.size()) {
		return "";
	}
	return varTable[varId];
}

bool PKBWithStub::isVarInTable(string varName) {
	for (int index = 0; index < (int)varTable.size(); index++) {
		if (varTable[index].compare(varName) == 0) {
			return true;
		}
	}
	return false;
}

unordered_set<int> PKBWithStub::getAllProcId() {
	unordered_set<int> procs;
	for (int procId = 0; procId < procTable.size(); procId++) {
		procs.insert(procId);
	}
	return procs;
}

int PKBWithStub::getProcIdByName(string varName) {
	for (int i = 0; i < (int)procTable.size(); i++) {
		if (procTable[i].compare(varName) == 0) {
			return i;
		}
	}
	return -1;
}

string PKBWithStub::getProcNameById(int procId) {
	if (procId < 0 || procId >(int)procTable.size()) {
		return "";
	}
	return procTable[procId];
}

bool PKBWithStub::isProcInTable(string procName) {
	for (int index = 0; index < (int)procTable.size(); index++) {
		if (procTable[index].compare(procName) == 0) {
			return true;
		}
	}
	return false;
}

unordered_set<int> PKBWithStub::getAllConstId() {
	unordered_set<int> consts;
	for (int constId = 0; constId < constTable.size(); constId++) {
		consts.insert(constId);
	}
	return consts;
}

bool PKBWithStub::isConstInTable(int constValue) {
	for (int index = 0; index < (int)constTable.size(); index++) {
		if (constTable[index] == constValue) {
			return true;
		}
	}
	return false;
}

int PKBWithStub::getConstIdByValue(int constValue) {
	for (int i = 0; i < (int)constTable.size(); i++) {
		if (constTable[i] == constValue) {
			return i;
		}
	}
	return -1;
}

int PKBWithStub::getConstValueById(int constId) {
	if (constId < 0 || constId >(int)constTable.size()) {
		return -1;
	}
	return constTable[constId];
}

unordered_set<int> PKBWithStub::getAllStmtId() {
	unordered_set<int> stmts = assignStmts;
	stmts = UnorderedSetOperation<int>::setUnion(stmts, whileStmts);
	stmts = UnorderedSetOperation<int>::setUnion(stmts, ifStmts);
	stmts = UnorderedSetOperation<int>::setUnion(stmts, callStmts);

	return stmts;
}

unordered_set<int> PKBWithStub::getAllAssignStmt() {
	return assignStmts;
}

unordered_set<int> PKBWithStub::getAllWhileStmt() {
	return whileStmts;
}

unordered_set<int> PKBWithStub::getAllIfId() {
	return ifStmts;
}

unordered_set<int> PKBWithStub::getAllCallId() {
	return callStmts;
}

int PKBWithStub::getProcCalledByStmt(int callstmtId) {
	if (callTable.find(callstmtId) == callTable.end()) {
		return -1;
	}
	return callTable.at(callstmtId);
}

unordered_set<int> PKBWithStub::getStmtCallProc(int procId) {
	unordered_set<int> calledProcStmts;
	for (auto callRel : callTable) {
		if (callRel.second == procId) {
			calledProcStmts.insert(callRel.first);
		}
	}
	return calledProcStmts;
}