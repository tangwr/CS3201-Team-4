#include <unordered_map>

#include "stdafx.h"
#include "PKBStubModifies.h"

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

PKBStubModifies::PKBStubModifies() {
	allStmts = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 };
	assignStmts = { 1, 2, 3, 5, 7, 8, 9, 11, 15, 17, 18, 19, 20, 21, 23, 24 };
	whileStmts = { 4, 14 };
	ifStmts = { 6, 13, 22 };
	callStmts = { 10, 12, 16 };
	procId = { 0,1,2 };
	varId = { 0,1,2,3 };

	modifyStmts = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 };
	procStmts = { "Example","p","q" };

	modifiesTable.insert({ 1,{ 0 } });
	modifiesTable.insert({ 2,{ 1 } });
	modifiesTable.insert({ 3,{ 2 } });
	modifiesTable.insert({ 4,{ 0,1,2,3} });
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

	varIdTable.insert({ "x",0 });
	varIdTable.insert({ "z",1 });
	varIdTable.insert({ "i",2 });
	varIdTable.insert({ "y",3 });

	procIdTable.insert({ "Example", 0 });
	procIdTable.insert({ "p", 1 });
	procIdTable.insert({ "q", 2 });

	modifiesStmtInProcTable.insert({ 0,{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 } });
	modifiesStmtInProcTable.insert({ 1,{ 13,14,15,16,17,18,19,20,21,22,23,24 } });
	modifiesStmtInProcTable.insert({ 2,{ 22,23,24 } });

	stmtModifyVarTable.insert({ 0,{1,4,5,10,12,13,14,15,16,18,22,24} });
	stmtModifyVarTable.insert({ 1,{ 2,4,6,7,9,10,12,13,14,16,19,20,21,22,23} });
	stmtModifyVarTable.insert({ 2,{ 3,4,11,12,13,14,17 } });
	stmtModifyVarTable.insert({ 3,{ 4,6,8} });

	procModifyVarTable.insert({ 0,{0,1,2} });
	procModifyVarTable.insert({ 1,{0,1,2} });
	procModifyVarTable.insert({ 2,{0,1} });
	procModifyVarTable.insert({ 3,{0} });

}

unordered_set<int> PKBStubModifies::getAllStmtId() {
	return allStmts;
}

unordered_set<int> PKBStubModifies::getAllAssignStmt() {
	return assignStmts;
}

unordered_set<int> PKBStubModifies::getAllWhileStmt() {
	return whileStmts;
}

unordered_set<int> PKBStubModifies::getAllIfId() {
	return ifStmts;
}

unordered_set<int> PKBStubModifies::getAllCallId() {
	return callStmts;
}

unordered_set<int> PKBStubModifies::getAllProcId() {
	return procId;
}

unordered_set<int> PKBStubModifies::getAllVarId() {
	return varId;
}

unordered_set<int> PKBStubModifies::getAllModifyStmt() {
	return modifyStmts;
}

bool PKBStubModifies::hasModifyRel(int stmtId, int varId) {
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
bool PKBStubModifies::isProcInTable(string procName) {
	auto it = procStmts.find(procName);
	if (it != procStmts.end()) {
		return true;
	}
	return false;
}
bool PKBStubModifies::isStmtInModifyTable(int stmtId) {
	auto it = modifyStmts.find(stmtId);
	if (it != modifyStmts.end()) {
		return true;
	}
	return false;
}

int PKBStubModifies::getVarIdByName(string varName) {
	auto& it = varIdTable.find(varName);
	if (it != varIdTable.end())
		return it->second;
	return -1;
}

int PKBStubModifies::getProcIdByName(string procName) {
	auto& it = procIdTable.find(procName);
	if (it != procIdTable.end())
		return it->second;
	return -1;
}

unordered_set<int> PKBStubModifies::getModifyStmtInProc(int procId) {
	unordered_set<int> stmtSet;
	auto& it = modifiesStmtInProcTable.find(procId);
	if (it != modifiesStmtInProcTable.end())
		return it->second;
	return stmtSet;
}

unordered_set<int> PKBStubModifies::getStmtModifyVar(int varId) {
	unordered_set<int> stmtSet;
	auto& it = stmtModifyVarTable.find(varId);
	if (it != stmtModifyVarTable.end())
		return it->second;
	return stmtSet;
}

unordered_set<int> PKBStubModifies::getProcModifyVar(int varId) {
	unordered_set<int> procSet;
	auto& it = procModifyVarTable.find(varId);
	if (it != procModifyVarTable.end())
		return it->second;
	return procSet;
}

unordered_set<int>PKBStubModifies::getVarModifiedInStmt(int stmtId) {
	unordered_set<int> varSet;
	auto& it = modifiesTable.find(stmtId);
	if (it != modifiesTable.end())
		return it->second;
	return varSet;
}