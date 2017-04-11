#include <unordered_map>

#include "stdafx.h"
#include "UsesPKBStub.h"

/*
procId:
0 : Example
1 : q
2 : p

varId:
0 : x
1 : z
2 : i
3 : y

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

UsesPKBStub::UsesPKBStub() {
	allStmts = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 };
	assignStmts = { 1, 2, 3, 5, 7, 8, 9, 11, 15, 17, 18, 19, 20, 21, 23, 24 };
	whileStmts = { 4, 14 };
	ifStmts = { 6, 13, 22 };
	callStmts = { 10, 12, 16 };
	procId = { 0,1,2 };
	varId = { 0,1,2,3 };

	useStmts = {4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,21,22,23,24 };
	procStmts = { "Example","p","q" };

	usesTable.insert({ 1,{} });
	usesTable.insert({ 2,{} });
	usesTable.insert({ 3,{} });
	usesTable.insert({ 4,{ 0,1,2 } });
	usesTable.insert({ 5,{ 0 } });
	usesTable.insert({ 6,{ 0,1 } });
	usesTable.insert({ 7,{ 0 } });
	usesTable.insert({ 8,{ 0,1 } });
	usesTable.insert({ 9,{ 0,1,2 } });
	usesTable.insert({ 10,{ 0,1 } });
	usesTable.insert({ 11,{ 2 } });
	usesTable.insert({ 12,{ 0,1,2,3 } });
	usesTable.insert({ 13,{ 0,1,2,3 } });
	usesTable.insert({ 14,{ 1,2,3 } });
	usesTable.insert({ 15,{ 1,3 } });
	usesTable.insert({ 16,{ 0,1 } });
	usesTable.insert({ 17,{ 2 } });
	usesTable.insert({ 18,{ 0 } });
	usesTable.insert({ 19,{ 0,1 } });
	usesTable.insert({ 20,{ } });
	usesTable.insert({ 21,{ 0,1,2 } });
	usesTable.insert({ 22,{ 0,1 } });
	usesTable.insert({ 23,{ 0 } });
	usesTable.insert({ 24,{ 0,1 } });

	varIdTable.insert({ "x",0 });
	varIdTable.insert({ "z",1 });
	varIdTable.insert({ "i",2 });
	varIdTable.insert({ "y",3 });

	procIdTable.insert({ "Example", 0 });
	procIdTable.insert({ "p", 1 });
	procIdTable.insert({ "q", 2 });

	usesStmtInProcTable.insert({ 0,{ 4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 } });
	usesStmtInProcTable.insert({ 1,{ 13,14,15,16,17,18,19,21,22,23,24 } });
	usesStmtInProcTable.insert({ 2,{ 22,23,24 } });

	stmtUseVarTable.insert({ 0,{ 4,5,6,7,8,9,10,12,13,14,16,18,19,21,22,23,24 } });
	stmtUseVarTable.insert({ 1,{ 4,6,8,9,10,12,13,14,15,16,19,21,22,24 } });
	stmtUseVarTable.insert({ 2,{ 4,9,11,12,13,14,17 } });
	stmtUseVarTable.insert({ 3,{ 12,13,14,15 } });

	procUseVarTable.insert({ 0,{ 0,1,2 } });
	procUseVarTable.insert({ 1,{ 0,1,2 } });
	procUseVarTable.insert({ 2,{ 0,1 } });
	procUseVarTable.insert({ 3,{ 1 } });
}

unordered_set<int> UsesPKBStub::getAllStmtId() {
	return allStmts;
}

unordered_set<int> UsesPKBStub::getAllAssignStmt() {
	return assignStmts;
}

unordered_set<int> UsesPKBStub::getAllWhileStmt() {
	return whileStmts;
}

unordered_set<int> UsesPKBStub::getAllIfId() {
	return ifStmts;
}

unordered_set<int> UsesPKBStub::getAllCallId() {
	return callStmts;
}

unordered_set<int> UsesPKBStub::getAllProcId() {
	return procId;
}

unordered_set<int> UsesPKBStub::getAllVarId() {
	return varId;
}

unordered_set<int> UsesPKBStub::getAllUseStmt() {
	return useStmts;
}

bool UsesPKBStub::checkStmtVarUseRelExist(int stmtId, int varId) {
	unordered_set<int> varSet = {};
	auto& it = usesTable.find(stmtId);
	if (it != usesTable.end())
		varSet = it->second;

	auto its = varSet.find(varId);
	if (its != varSet.end()) {
		return true;
	}
	return false;
}

bool UsesPKBStub::isProcInTable(string procName) {
	auto it = procStmts.find(procName);
	if (it != procStmts.end()) {
		return true;
	}
	return false;
}

bool UsesPKBStub::isStmtInUseTable(int stmtId) {
	auto it = useStmts.find(stmtId);
	if (it != useStmts.end()) {
		return true;
	}
	return false;
}

int UsesPKBStub::getVarIdByName(string varName) {
	auto& it = varIdTable.find(varName);
	if (it != varIdTable.end())
		return it->second;
	return -1;
}
int UsesPKBStub::getProcIdByName(string procName) {
	auto& it = procIdTable.find(procName);
	if (it != procIdTable.end())
		return it->second;
	return -1;
}

unordered_set<int> UsesPKBStub::getUseStmtInProc(int procId) {
	unordered_set<int> stmtSet;
	auto& it = usesStmtInProcTable.find(procId);
	if (it != usesStmtInProcTable.end())
		return it->second;
	return stmtSet;
}

unordered_set<int> UsesPKBStub::getStmtUseVar(int varId) {
	unordered_set<int> stmtSet;
	auto& it = stmtUseVarTable.find(varId);
	if (it != stmtUseVarTable.end())
		return it->second;
	return stmtSet;
}

unordered_set<int> UsesPKBStub::getProcUseVar(int varId) {
	unordered_set<int> procSet;
	auto& it = procUseVarTable.find(varId);
	if (it != procUseVarTable.end())
		return it->second;
	return procSet;
}

unordered_set<int> UsesPKBStub::getVarUsedByStmt(int stmtId) {
	unordered_set<int> varSet;
	auto& it = usesTable.find(stmtId);
	if (it != usesTable.end())
		return it->second;
	return varSet;
}