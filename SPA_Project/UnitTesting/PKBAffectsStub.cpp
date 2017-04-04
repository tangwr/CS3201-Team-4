#include <unordered_map>

#include "stdafx.h"
#include "PKBAffectsStub.h"

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

PKBAffectsStub::PKBAffectsStub() {
	assignStmts = { 1, 2, 3, 5, 7, 8, 9, 11, 15, 17, 18, 19, 20, 21, 23, 24 };
	whileStmts = { 4, 14 };
	ifStmts = { 6, 13, 22 };
	callStmts = { 10, 12, 16 };

	assignStmtToVarTable = { { 1, 0 },{ 2, 1 },{ 3, 2 },{ 5, 0 },{ 7, 1 },{ 8, 3 },{ 9, 1 },{ 11, 2 },{ 15, 0 },{ 17, 2 },{ 18, 0 },{ 19, 1 },{ 20, 1 },{ 23, 1 },{ 24, 0 } };
	modStmtToVarTable = { { 1,{ 0 } },{ 2,{ 1 } },{ 3,{ 2 } },{ 4,{ 0, 1, 2, 3 } },{ 5,{ 0 } },{ 6,{ 1, 3 } },{ 7,{ 1 } },{ 8,{ 3 } },{ 9,{ 1 } },
						{ 10,{ 0, 1 } },{ 11,{ 2 } },{ 12,{ 0, 1, 2 } },{ 13,{ 0, 1, 2 } },{ 14,{ 0, 1, 2 } },{ 15,{ 0 } },{ 16,{ 0, 1 } },{ 17,{ 2 } },
						{ 18,{ 0 } },{ 19,{ 1 } },{ 20,{ 1 } },{ 21,{ 1 } },{ 22,{ 0, 1 } },{ 23,{ 1 } },{ 24,{ 0 } } };
	useStmtToVarTable = { { 4,{ 0, 1, 2 } },{ 5,{ 0 } },{ 6,{ 0, 1 } },{ 7,{ 0 } },{ 8,{ 0, 1 } },{ 9,{ 0, 1, 2 } },{ 10,{ 0, 1 } },{ 11,{ 2 } },
						{ 12,{ 0, 1, 2, 3 } },{ 13,{ 0, 1, 2, 3 } },{ 14,{ 0, 1, 2, 3 } },{ 15,{ 1, 3 } },{ 16,{ 0, 1 } },{ 17,{ 2 } },{ 18,{ 0 } },
						{ 19,{ 0, 1 } },{ 21,{ 0, 1, 2 } },{ 22,{ 0, 1 } },{ 23,{ 0 } },{ 24,{ 0, 1 } } };
	stmtToProcTable = { { 1,0 },{ 2,0 },{ 3,0 },{ 4,0 },{ 5,0 },{ 6,0 },{ 7,0 },{ 8,0 },{ 9,0 },{ 10,0 },{ 11,0 },{ 12,0 },{ 13,1 },{ 14,1 },
						{ 15,1 },{ 16,1 },{ 17,1 },{ 18,1 },{ 19,1 },{ 20,1 },{ 21,1 },{ 22,3 },{ 23,3 },{ 24,3 } };
	stmtLstToProcTable = { { 0,{ 1 } },{ 1,{ 13 } },{ 2,{ 22 } } };

	nextTable = { { 1,{ 2 } },{ 2,{ 3 } },{ 3,{ 4 } },{ 4,{ 5,12 } },{ 5,{ 6 } },{ 6,{ 7,8 } },{ 7,{ 9 } },{ 8,{ 9 } },{ 9,{ 10 } },{ 10,{ 11 } },
				{ 11,{ 4 } },{ 12,{} },{ 13,{ 14,20 } },{ 14,{ 15,18 } },{ 15,{ 16 } },{ 16,{ 17 } },{ 17,{ 14 } },{ 18,{ 19 } },{ 19,{ 21 } },{ 20,{ 21 } },
				{ 21,{} },{ 22,{ 23, 24 } },{ 23,{} },{ 24,{} } };
	prevTable = { { 1,{} },{ 2,{ 1 } },{ 3,{ 2 } },{ 4,{ 3,11 } },{ 5,{ 4 } },{ 6,{ 5 } },{ 7,{ 6 } },{ 8,{ 6 } },{ 9,{ 7,8 } },{ 10,{ 9 } },
				{ 11,{ 10 } },{ 12,{ 4 } },{ 13,{} },{ 14,{ 13,17 } },{ 15,{ 14 } },{ 16,{ 15 } },{ 17,{ 16 } },{ 18,{ 14 } },{ 19,{ 18 } },{ 20,{ 13 } },
				{ 21,{ 19,20 } },{ 22,{} },{ 23,{ 22 } },{ 24,{ 22 } } };
}

unordered_set<int> PKBAffectsStub::getAllAssignStmt() {
	return assignStmts;
}

int PKBAffectsStub::getVarAtLeftOfAssignStmt(int stmtId) {
	if (assignStmtToVarTable.find(stmtId) == assignStmtToVarTable.end()) {
		return -1;
	}
	return assignStmtToVarTable.at(stmtId);
}

bool PKBAffectsStub::isStmtInAssignTable(int stmtId) {
	if (assignStmts.find(stmtId) == assignStmts.end()) {
		return false;
	}
	return true;
}

bool PKBAffectsStub::isStmtInWhileTable(int stmtId) {
	if (whileStmts.find(stmtId) == whileStmts.end()) {
		return false;
	}
	return true;
}

bool PKBAffectsStub::isStmtInIfTable(int stmtId) {
	if (ifStmts.find(stmtId) == ifStmts.end()) {
		return false;
	}
	return true;
}

bool PKBAffectsStub::isStmtInCallTable(int stmtId) {
	if (callStmts.find(stmtId) == callStmts.end()) {
		return false;
	}
	return true;
}

int PKBAffectsStub::getProcContainingStmt(int stmtId) {
	if (stmtToProcTable.find(stmtId) == stmtToProcTable.end()) {
		return -1;
	}
	return stmtToProcTable.at(stmtId);
}

vector<int> PKBAffectsStub::getStmtLstContainedInProc(int stmtId) {
	if (stmtLstToProcTable.find(stmtId) == stmtLstToProcTable.end()) {
		return {};
	}
	return stmtLstToProcTable.at(stmtId);
}

unordered_set<int> PKBAffectsStub::getVarModifiedInStmt(int stmtId) {
	if (modStmtToVarTable.find(stmtId) == modStmtToVarTable.end()) {
		return {};
	}
	return modStmtToVarTable.at(stmtId);
}


unordered_set<int> PKBAffectsStub::getVarUsedByStmt(int stmtId) {
	if (useStmtToVarTable.find(stmtId) == useStmtToVarTable.end()) {
		return{};
	}
	return useStmtToVarTable.at(stmtId);
}

unordered_set<int> PKBAffectsStub::getNextStmt(int stmtId) {
	if (nextTable.find(stmtId) == nextTable.end()) {
		return{};
	}
	return nextTable.at(stmtId);
}

unordered_set<int> PKBAffectsStub::getPreviousStmt(int stmtId) {
	if (prevTable.find(stmtId) == prevTable.end()) {
		return{};
	}
	return prevTable.at(stmtId);
}