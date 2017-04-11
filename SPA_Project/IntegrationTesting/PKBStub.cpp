#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKBStub.h"
#include <unordered_map>

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

PKBStub::PKBStub() {
	allStmts = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 };

	usesStmtInProcTable.insert({ 0,{ 4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 } });
	usesStmtInProcTable.insert({ 1,{ 13,14,15,16,17,18,19,21,22,23,24 } });
	usesStmtInProcTable.insert({ 2,{ 22,23,24 } });

	modifiesStmtInProcTable.insert({ 0,{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 } });
	modifiesStmtInProcTable.insert({ 1,{ 13,14,15,16,17,18,19,20,21,22,23,24 } });
	modifiesStmtInProcTable.insert({ 2,{ 22,23,24 } });

	procIdTable.insert({ "Example", 0 });
	procIdTable.insert({ "p", 1 });
	procIdTable.insert({ "q", 2 });

	procStmts = { "Example","p","q" };
	procId = { 0,1,2 };
	varId = { 0,1,2,3 };

	varTable = { "x", "z", "i", "y" };
	varIdTable.insert({ "x",0 });
	varIdTable.insert({ "z",1 });
	varIdTable.insert({ "i",2 });
	varIdTable.insert({ "y",3 });

	constValues = { 2, 3, 5, 1 };

	parentTable.insert({ 5, 4 });
	parentTable.insert({ 6, 4 });
	parentTable.insert({ 7, 6 });
	parentTable.insert({ 8, 6 });
	parentTable.insert({ 9, 4 });
	parentTable.insert({ 10, 4 });
	parentTable.insert({ 11, 4 });
	parentTable.insert({ 14, 13 });
	parentTable.insert({ 15, 14 });
	parentTable.insert({ 16, 14 });
	parentTable.insert({ 17, 14 });
	parentTable.insert({ 18, 13 });
	parentTable.insert({ 19, 13 });
	parentTable.insert({ 20, 13 });
	parentTable.insert({ 23, 22 });
	parentTable.insert({ 24, 22 });

	parentStarTable.insert({ 5, unordered_set<int>({ 4 }) });
	parentStarTable.insert({ 6, unordered_set<int>({ 4 }) });
	parentStarTable.insert({ 7, unordered_set<int>({ 4, 6 }) });
	parentStarTable.insert({ 8, unordered_set<int>({ 4, 6 }) });
	parentStarTable.insert({ 9, unordered_set<int>({ 4 }) });
	parentStarTable.insert({ 10, unordered_set<int>({ 4 }) });
	parentStarTable.insert({ 11, unordered_set<int>({ 4 }) });

	parentStarTable.insert({ 14, unordered_set<int>({ 13 }) });
	parentStarTable.insert({ 15, unordered_set<int>({ 13, 14 }) });
	parentStarTable.insert({ 16, unordered_set<int>({ 13, 14 }) });
	parentStarTable.insert({ 17, unordered_set<int>({ 13, 14 }) });
	parentStarTable.insert({ 18, unordered_set<int>({ 13 }) });
	parentStarTable.insert({ 19, unordered_set<int>({ 13 }) });
	parentStarTable.insert({ 20, unordered_set<int>({ 13 }) });
	parentStarTable.insert({ 21, unordered_set<int>({ 13 }) });

	parentStarTable.insert({ 23, unordered_set<int>({ 22 }) });
	parentStarTable.insert({ 24, unordered_set<int>({ 22 }) });

	childrenTable.insert({ 4, unordered_set<int>({ 5,6,10,11 }) });
	childrenTable.insert({ 6, unordered_set<int>({ 7, 8 }) });
	childrenTable.insert({ 13, unordered_set<int>({ 14,18,19,20 }) });
	childrenTable.insert({ 14, unordered_set<int>({ 15, 16, 17 }) });
	childrenTable.insert({ 22, unordered_set<int>({ 23, 24 }) });

	childrenStarTable.insert({ 4, unordered_set<int>({ 5,6,7,8,9,10,11 }) });
	childrenStarTable.insert({ 6, unordered_set<int>({ 7, 8 }) });
	childrenStarTable.insert({ 13, unordered_set<int>({ 14,15,16,17,18,19,20,21 }) });
	childrenStarTable.insert({ 14, unordered_set<int>({ 15, 16, 17 }) });
	childrenStarTable.insert({ 22, unordered_set<int>({ 23, 24 }) });

	followsTable.insert({ 1, 2 });
	followsTable.insert({ 2, 3 });
	followsTable.insert({ 3, 4 });
	followsTable.insert({ 4, 12 });
	followsTable.insert({ 5, 6 });
	followsTable.insert({ 6, 9 });
	followsTable.insert({ 9, 10 });
	followsTable.insert({ 10, 11 });
	followsTable.insert({ 13, 21 });
	followsTable.insert({ 14, 18 });
	followsTable.insert({ 15, 16 });
	followsTable.insert({ 16, 17 });
	followsTable.insert({ 18, 19 });

	followedByTable.insert({ 2, 1 });
	followedByTable.insert({ 3, 2 });
	followedByTable.insert({ 4, 3 });
	followedByTable.insert({ 12, 4 });
	followedByTable.insert({ 6, 5 });
	followedByTable.insert({ 9, 6 });
	followedByTable.insert({ 10, 9 });
	followedByTable.insert({ 11, 10 });
	followedByTable.insert({ 21, 13 });
	followedByTable.insert({ 18, 14 });
	followedByTable.insert({ 16, 15 });
	followedByTable.insert({ 17, 16 });
	followedByTable.insert({ 19, 18 });

	followsStarTable.insert({ 1, unordered_set<int>({ 2,3,4,12 }) });
	followsStarTable.insert({ 2, unordered_set<int>({ 3,4,12 }) });
	followsStarTable.insert({ 3, unordered_set<int>({ 4,12 }) });
	followsStarTable.insert({ 4, unordered_set<int>({ 12 }) });
	followsStarTable.insert({ 5, unordered_set<int>({ 6,9,10,11 }) });
	followsStarTable.insert({ 6, unordered_set<int>({ 9,10,11 }) });
	followsStarTable.insert({ 9, unordered_set<int>({ 10,11 }) });
	followsStarTable.insert({ 10, unordered_set<int>({ 11 }) });
	followsStarTable.insert({ 13, unordered_set<int>({ 21 }) });
	followsStarTable.insert({ 14, unordered_set<int>({ 18,19 }) });
	followsStarTable.insert({ 15, unordered_set<int>({ 16,17 }) });
	followsStarTable.insert({ 16, unordered_set<int>({ 17 }) });
	followsStarTable.insert({ 18, unordered_set<int>({ 19 }) });

	followedByStarTable.insert({ 2, unordered_set<int>({ 1 }) });
	followedByStarTable.insert({ 3, unordered_set<int>({ 1, 2 }) });
	followedByStarTable.insert({ 4, unordered_set<int>({ 1,2,3 }) });
	followedByStarTable.insert({ 12, unordered_set<int>({ 1,2,3,4 }) });
	followedByStarTable.insert({ 6, unordered_set<int>({ 5 }) });
	followedByStarTable.insert({ 9, unordered_set<int>({ 5,6 }) });
	followedByStarTable.insert({ 10, unordered_set<int>({ 5,6,9 }) });
	followedByStarTable.insert({ 11, unordered_set<int>({ 5,6,9,10 }) });
	followedByStarTable.insert({ 21, unordered_set<int>({ 13 }) });
	followedByStarTable.insert({ 18, unordered_set<int>({ 14 }) });
	followedByStarTable.insert({ 16, unordered_set<int>({ 15 }) });
	followedByStarTable.insert({ 17, unordered_set<int>({ 15,16 }) });
	followedByStarTable.insert({ 19, unordered_set<int>({ 14,18 }) });

	stmtModifyVarTable.insert({ 0,{ 1,4,5,10,12,13,14,15,16,18,22,24 } });
	stmtModifyVarTable.insert({ 1,{ 2,4,6,7,9,10,12,13,14,16,19,20,21,22,23 } });
	stmtModifyVarTable.insert({ 2,{ 3,4,11,12,13,14,17 } });
	stmtModifyVarTable.insert({ 3,{ 4,6,8 } });

	modifiesTable.insert({ 1,{ 0 } });
	modifiesTable.insert({ 2,{ 1 } });
	modifiesTable.insert({ 3,{ 2 } });
	modifiesTable.insert({ 4,{ 0,1,2,3 } });
	modifiesTable.insert({ 5,{ 0 } });
	modifiesTable.insert({ 6,{ 1,3 } });
	modifiesTable.insert({ 7,{ 1 } });
	modifiesTable.insert({ 8,{ 3 } });
	modifiesTable.insert({ 9,{ 1 } });
	modifiesTable.insert({ 10,{ 0,1 } });
	modifiesTable.insert({ 11,{ 2 } });
	modifiesTable.insert({ 12,{ 0,1,2 } });
	modifiesTable.insert({ 13,{ 0,1,2 } });
	modifiesTable.insert({ 14,{ 0,1,2 } });
	modifiesTable.insert({ 15,{ 0 } });
	modifiesTable.insert({ 16,{ 0,1 } });
	modifiesTable.insert({ 17,{ 2 } });
	modifiesTable.insert({ 18,{ 0 } });
	modifiesTable.insert({ 19,{ 1 } });
	modifiesTable.insert({ 20,{ 1 } });
	modifiesTable.insert({ 21,{ 1 } });
	modifiesTable.insert({ 22,{ 0,1 } });
	modifiesTable.insert({ 23,{ 1 } });
	modifiesTable.insert({ 24,{ 0 } });

	procModifyVarTable.insert({ 0,{ 0,1,2 } });
	procModifyVarTable.insert({ 1,{ 0,1,2 } });
	procModifyVarTable.insert({ 2,{ 0,1 } });
	procModifyVarTable.insert({ 3,{ 0 } });

	modifyStmts = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 };

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
	usesTable.insert({ 20,{} });
	usesTable.insert({ 21,{ 0,1,2 } });
	usesTable.insert({ 22,{ 0,1 } });
	usesTable.insert({ 23,{ 0 } });
	usesTable.insert({ 24,{ 0,1 } });

	stmtUseVarTable.insert({ 0,{ 4,5,6,7,8,9,10,12,13,14,16,18,19,21,22,23,24 } });
	stmtUseVarTable.insert({ 1,{ 4,6,8,9,10,12,13,14,15,16,19,21,22,24 } });
	stmtUseVarTable.insert({ 2,{ 4,9,11,12,13,14,17 } });
	stmtUseVarTable.insert({ 3,{ 12,13,14,15 } });

	procUseVarTable.insert({ 0,{ 0,1,2 } });
	procUseVarTable.insert({ 1,{ 0,1,2 } });
	procUseVarTable.insert({ 2,{ 0,1 } });
	procUseVarTable.insert({ 3,{ 1 } });

	useStmts = { 4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,21,22,23,24 };

	assignStmts = { 1, 2, 3, 5, 7, 8, 9, 11, 15, 17, 18, 19, 20, 21, 23, 24 };

	assignTable = { { 1, "|2|" },{ 2, "|3|" },{ 3, "|5|" },{ 5, "|-|x|1|" },{ 7, "|+|x|1|" },{ 8, "|+|z|x|" },{ 9, "|+|+|z|x|i|" },
	{ 11, "|-|i|1|" },{ 15, "|+|*|z|3|*|2|y|" },{ 17, "|-|i|1|" },{ 18, "|+|x|1|" },{ 19, "|+|x|z|" },{ 20, "|1|" },
	{ 21, "|+|+|z|x|i|" },{ 23, "|+|x|1|" },{ 24, "|+|z|x|" } };

	left_varInAssignStmt = { { 1, 0 },{ 2, 1 },{ 3, 2 },{ 5, 0 },{ 7, 1 },{ 8, 3 },
	{ 9, 1 },{ 11, 2 },{ 15, 0 },{ 17, 2 },{ 18, 0 },{ 19, 1 },
	{ 20, 1 },{ 21, 1 },{ 23, 1 },{ 24, 0 } };

	ctrlVarInWhileStmt = { { 4, 2 },{ 14, 2 } };

	whileStmts = { 4, 14 };
	whileStmtUseVar = { { 2,{ 4, 14 } } };

	ifStmtUseVar = { { 0,{ 6, 13, 22 } } };
	ifStmts = { 6, 13, 22 };

	procCalledByStmtTable.insert({ 10, 2 });
	procCalledByStmtTable.insert({ 15, 4 });
	procCalledByStmtTable.insert({ 16, 2 });
	procCalledByStmtTable.insert({ 18, 5 });

	stmtCallProcTable.insert({ 2, unordered_set<int>({ 10, 16 }) });
	stmtCallProcTable.insert({ 4, unordered_set<int>({ 15 }) });
	stmtCallProcTable.insert({ 5, unordered_set<int>({ 18 }) });

	procCallTable.insert({ 0,{ 1,2 } });
	procCallTable.insert({ 1,{ 2 } });
	procCallTable.insert({ 2,{} });

	callStmts = { 10, 12, 16 };

	nextTable = { { 1,{ 2 } },{ 2,{ 3 } },{ 3,{ 4 } },{ 4,{ 5,12 } },{ 5,{ 6 } },{ 6,{ 7,8 } },{ 7,{ -1 } },{ 8,{ -1 } },{ -1,{ 9 } },{ 9,{ 10 } },{ 10,{ 11 } },
	{ 11,{ 4 } },{ 12,{} },{ 13,{ 14,20 } },{ 14,{ 15,18 } },{ 15,{ 16 } },{ 16,{ 17 } },{ 17,{ 14 } },{ 18,{ 19 } },{ 19,{ -2 } },{ 20,{ -2 } },{ -2,{ 21 } },
	{ 21,{} },{ 22,{ 23, 24 } },{ 23,{ -3 } },{ 24,{ -3 } },{ -3,{} } };
	prevTable = { { 1,{} },{ 2,{ 1 } },{ 3,{ 2 } },{ 4,{ 3,11 } },{ 5,{ 4 } },{ 6,{ 5 } },{ 7,{ 6 } },{ 8,{ 6 } },{ 9,{ -1 } },{ -1,{ 7,8 } },{ 10,{ 9 } },
	{ 11,{ 10 } },{ 12,{ 4 } },{ 13,{} },{ 14,{ 13,17 } },{ 15,{ 14 } },{ 16,{ 15 } },{ 17,{ 16 } },{ 18,{ 14 } },{ 19,{ 18 } },{ 20,{ 13 } },
	{ -2,{ 19,20 } },{ 21,{ -2 } },{ 22,{} },{ 23,{ 22 } },{ 24,{ 22 } },{ -3,{ 23, 24 } } };
	stmtLstToProcTable = { { 0,{ 1 } },{ 1,{ 13 } },{ 2,{ 22 } } };

	stmtLst = { 1,13,22 };

	procIdToNameTable.insert({ 0,"Example" });
	procIdToNameTable.insert({ 1,"p" });
	procIdToNameTable.insert({ 2,"q" });

	assignStmtModVar = { { 0,{ 1, 5, 15, 18, 24 } },{ 1,{ 2, 7, 9, 19, 20, 21, 23 } },
	{ 2,{ 3, 11, 17 } },{ 3,{ 8 } } };

	stmtToProcTable = { { 1,0 },{ 2,0 },{ 3,0 },{ 4,0 },{ 5,0 },{ 6,0 },{ 7,0 },{ 8,0 },{ 9,0 },{ 10,0 },{ 11,0 },{ 12,0 },{ 13,1 },{ 14,1 },
	{ 15,1 },{ 16,1 },{ 17,1 },{ 18,1 },{ 19,1 },{ 20,1 },{ 21,1 },{ 22,3 },{ 23,3 },{ 24,3 } };


}

int PKBStub::getNumOfStmt() {
	return 24;
}

unordered_set<int> PKBStub::getAllStmtId() {
	return allStmts;
}

unordered_set<int> PKBStub::getUseStmtInProc(int procId) {
	unordered_set<int> stmtSet;
	auto& it = usesStmtInProcTable.find(procId);
	if (it != usesStmtInProcTable.end())
		return it->second;
	return stmtSet;
}

unordered_set<int> PKBStub::getModifyStmtInProc(int procId) {
	unordered_set<int> stmtSet;
	auto& it = modifiesStmtInProcTable.find(procId);
	if (it != modifiesStmtInProcTable.end())
		return it->second;
	return stmtSet;
}

int PKBStub::getProcIdByName(string procName) {
	auto& it = procIdTable.find(procName);
	if (it != procIdTable.end())
		return it->second;
	return -1;
}

bool PKBStub::isProcInTable(string procName) {
	auto it = procStmts.find(procName);
	if (it != procStmts.end()) {
		return true;
	}
	return false;
}

unordered_set<int> PKBStub::getAllProcId() {
	return procId;
}

string PKBStub::getProcNameById(int procId) {
	auto& it = procIdToNameTable.find(procId);
	if (it != procIdToNameTable.end())
		return it->second;
	return " ";
}

unordered_set<int> PKBStub::getAllVarId() {
	return varId;
}

string PKBStub::getVarNameById(int varId) {
	if (varId < 0 || varId >(int)varTable.size()) {
		return "";
	}
	return varTable[varId];
}

int  PKBStub::getVarIdByName(string varName) {
	auto& it = varIdTable.find(varName);
	if (it != varIdTable.end())
		return it->second;
	return -1;
}

bool PKBStub::isVarInTable(string varName) {
	for (int index = 0; index < (int)varTable.size(); index++) {
		if (varTable[index].compare(varName) == 0) {
			return true;
		}
	}
	return false;
}

unordered_set<int> PKBStub::getAllConst() {
	return constValues;
}

bool PKBStub::isConstInTable(int constValue) {
	if (constValues.find(constValue) != constValues.end()) {
		return true;
	}
	else {
		return false;
	}
}

int PKBStub::getStmtParentStmt(int stmtId) {
	auto& it = parentTable.find(stmtId);
	if (it == parentTable.end())
		return -1;
	return it->second;
}

unordered_set<int> PKBStub::getStmtParentStarStmt(int stmtId) {
	auto& it = parentStarTable.find(stmtId);
	if (it == parentStarTable.end())
		return unordered_set<int>();
	return it->second;
}

unordered_set<int> PKBStub::getStmtChildrenStmt(int a) {
	auto& it = childrenTable.find(a);
	if (it == childrenTable.end())
		return unordered_set<int>();
	return it->second;
}

unordered_set<int> PKBStub::getStmtChildrenStarStmt(int a) {
	auto& it = childrenStarTable.find(a);
	if (it == childrenStarTable.end())
		return unordered_set<int>();
	return it->second;
}

int PKBStub::getStmtFollowStmt(int a) {
	auto& it = followsTable.find(a);
	if (it == followsTable.end())
		return -1;
	return it->second;
}

int PKBStub::getStmtFollowedByStmt(int stmtId) {
	auto& it = followedByTable.find(stmtId);
	if (it == followedByTable.end())
		return -1;
	return it->second;
}

unordered_set<int> PKBStub::getStmtFollowStarStmt(int stmtId) {
	auto& it = followsStarTable.find(stmtId);
	if (it == followsStarTable.end())
		return unordered_set<int>();
	return it->second;
}

unordered_set<int> PKBStub::getStmtFollowedByStarStmt(int stmtId) {
	auto& it = followedByStarTable.find(stmtId);
	if (it == followedByStarTable.end())
		return unordered_set<int>();
	return it->second;
}

unordered_set<int> PKBStub::getStmtModifyVar(int varId) {
	unordered_set<int> stmtSet;
	auto& it = stmtModifyVarTable.find(varId);
	if (it != stmtModifyVarTable.end())
		return it->second;
	return stmtSet;
}

unordered_set<int> PKBStub::getVarModifiedInStmt(int stmtId) {
	unordered_set<int> varSet;
	auto& it = modifiesTable.find(stmtId);
	if (it != modifiesTable.end())
		return it->second;
	return varSet;
}

unordered_set<int> PKBStub::getProcModifyVar(int varId) {
	unordered_set<int> procSet;
	auto& it = procModifyVarTable.find(varId);
	if (it != procModifyVarTable.end())
		return it->second;
	return procSet;
}

unordered_set<int> PKBStub::getAllModifyStmt() {
	return modifyStmts;
}

bool PKBStub::isStmtInModifyTable(int stmtId) {
	auto it = modifyStmts.find(stmtId);
	if (it != modifyStmts.end()) {
		return true;
	}
	return false;
}

bool PKBStub::hasModifyRel(int stmtId, int varId) {
	unordered_set<int> varSet = {};
	auto& it = modifiesTable.find(stmtId);
	if (it != modifiesTable.end())
		varSet = it->second;

	auto its = varSet.find(varId);
	if (its != varSet.end()) {
		return true;
	}
	return false;
}

unordered_set<int> PKBStub::getVarUsedByStmt(int stmtId) {
	unordered_set<int> varSet;
	auto& it = usesTable.find(stmtId);
	if (it != usesTable.end())
		return it->second;
	return varSet;
}

unordered_set<int> PKBStub::getStmtUseVar(int varId) {
	unordered_set<int> stmtSet;
	auto& it = stmtUseVarTable.find(varId);
	if (it != stmtUseVarTable.end())
		return it->second;
	return stmtSet;
}

unordered_set<int> PKBStub::getProcUseVar(int varId) {
	unordered_set<int> procSet;
	auto& it = procUseVarTable.find(varId);
	if (it != procUseVarTable.end())
		return it->second;
	return procSet;
}

unordered_set<int> PKBStub::getAllUseStmt() {
	return useStmts;
}

bool PKBStub::isStmtInUseTable(int stmtId) {
	auto it = useStmts.find(stmtId);
	if (it != useStmts.end()) {
		return true;
	}
	return false;
}

bool PKBStub::checkStmtVarUseRelExist(int stmtId, int varId) {
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

unordered_set<int> PKBStub::getAllAssignStmt() {
	return assignStmts;
}

string PKBStub::getExpInAssignStmt(int assignStmtId) {
	auto it = assignTable.find(assignStmtId);
	if (it == assignTable.end())
		return "";
	else
		return it->second;
}

bool PKBStub::isStmtInAssignTable(int stmtId) {
	if (assignTable.find(stmtId) == assignTable.end()) {
		return false;
	}
	return true;
}

int PKBStub::getVarAtLeftOfAssignStmt(int assignStmtId) {
	return left_varInAssignStmt.at(assignStmtId);
}

int PKBStub::getCtrlVarInWhileStmt(int stmtId) {
	if (ctrlVarInWhileStmt.find(stmtId) == ctrlVarInWhileStmt.end()) {
		return -1;
	}
	return ctrlVarInWhileStmt.at(stmtId);
}

unordered_set<int> PKBStub::getAllWhileStmt() {
	return whileStmts;
}

unordered_set<int> PKBStub::getStmtInWhileWithCtrlVar(int varId) {
	if (whileStmtUseVar.find(varId) == whileStmtUseVar.end()) {
		return unordered_set<int>();
	}
	return whileStmtUseVar.at(varId);
}

bool PKBStub::isStmtInWhileTable(int stmtId) {
	if (whileStmts.find(stmtId) == whileStmts.end()) {
		return false;
	}
	return true;
}

unordered_set<int> PKBStub::getStmtInIfWithCtrlVar(int varId) {
	if (ifStmtUseVar.find(varId) == ifStmtUseVar.end()) {
		return unordered_set<int>();
	}
	return ifStmtUseVar.at(varId);
}

bool PKBStub::isStmtInIfTable(int stmtId) {
	if (ifStmts.find(stmtId) == ifStmts.end()) {
		return false;
	}
	return true;
}

unordered_set<int> PKBStub::getAllIfId() {
	return ifStmts;
}

bool PKBStub::isStmtInCallTable(int stmtId) {
	if (callStmts.find(stmtId) == callStmts.end()) {
		return false;
	}
	return true;
}

int PKBStub::getProcCalledByStmt(int a) {
	if (procCalledByStmtTable.find(a) == procCalledByStmtTable.end())
		return -1;
	return procCalledByStmtTable.find(a)->second;
}

unordered_set<int> PKBStub::getStmtCallProc(int a) {
	if (stmtCallProcTable.find(a) == stmtCallProcTable.end())
		return unordered_set<int>();
	return stmtCallProcTable.find(a)->second;
}

unordered_set<int> PKBStub::getProcCalledByProc(int callerProcId) {
	unordered_set<int> procSet;
	auto& it = procCallTable.find(callerProcId);
	if (it != procCallTable.end())
		return it->second;
	return procSet;
}

unordered_set<int> PKBStub::getAllCallId() {
	return callStmts;
}

unordered_set<int> PKBStub::getProcCalledByStarProc(int callerProcId) {
	unordered_set<int> procSet;
	auto& it = procCallTable.find(callerProcId);
	if (it != procCallTable.end())
		return it->second;
	return procSet;
}

unordered_set<int> PKBStub::getNextStmt(int a) {
	auto& it = nextTable.find(a);
	if (it == nextTable.end())
		return unordered_set<int>();
	return it->second;
}

unordered_set<int> PKBStub::getPreviousStmt(int a) {
	auto& it = prevTable.find(a);
	if (it == prevTable.end())
		return unordered_set<int>();
	return it->second;
}

vector<int> PKBStub::getStmtLstContainedInProc(int stmtId) {
	if (stmtLstToProcTable.find(stmtId) == stmtLstToProcTable.end()) {
		return{};
	}
	return stmtLstToProcTable.at(stmtId);
}

unordered_set<int> PKBStub::getAllStmtLst() {
	return stmtLst;
}

unordered_set<int> PKBStub::getStmtInAssignWithVar(int varId) {
	return assignStmtModVar.at(varId);
}

int PKBStub::getProcContainingStmt(int stmtId) {
	if (stmtToProcTable.find(stmtId) == stmtToProcTable.end()) {
		return -1;
	}
	return stmtToProcTable.at(stmtId);
}

