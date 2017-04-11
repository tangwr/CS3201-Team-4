#include <unordered_map>

#include "stdafx.h"
#include "PatternPKBStub.h"

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

PatternPKBStub::PatternPKBStub() {
	varTable = { "x", "z", "i", "y" };

	assignStmts = { 1, 2, 3, 5, 7, 8, 9, 11, 15, 17, 18, 19, 20, 21, 23, 24 };
	left_varInAssignStmt = { { 1, 0 }, { 2, 1 }, { 3, 2 }, { 5, 0 },  { 7, 1 }, { 8, 3 },  
								{ 9, 1 }, { 11, 2 }, { 15, 0 }, { 17, 2 }, { 18, 0 }, { 19, 1 },
								{ 20, 1 }, { 21, 1 }, { 23, 1 }, { 24, 0 } };
	assignStmtModVar = { {0, {1, 5, 15, 18, 24} },{ 1, { 2, 7, 9, 19, 20, 21, 23 } },
						{ 2, { 3, 11, 17 } },{ 3, { 8 } } };
	assignTable = { { 1, "|2|" },{ 2, "|3|" },{ 3, "|5|" },{ 5, "|-|x|1|" },{ 7, "|+|x|1|" },{ 8, "|+|z|x|" },{ 9, "|+|+|z|x|i|" },
					{ 11, "|-|i|1|" },{ 15, "|+|*|z|3|*|2|y|" },{ 17, "|-|i|1|" },{ 18, "|+|x|1|" },{ 19, "|+|x|z|" },{ 20, "|1|" },
					{ 21, "|+|+|z|x|i|" },{ 23, "|+|x|1|" },{ 24, "|+|z|x|" } };

	whileStmts = { 4, 14 };
	whileStmtUseVar = { { 2, { 4, 14 } } };
	ctrlVarInWhileStmt = { { 4, 2 },{ 14, 2 } };

	ifStmts = { 6, 13, 22 };
	ifStmtUseVar = { { 0,{ 6, 13, 22 } } };
	ctrlVarInIfStmt = { { 6, 0 },{ 13, 0 },{ 22, 0 } };
}

unordered_set<int> PatternPKBStub::getAllVarId() {
	unordered_set<int> vars;
	for (int varId = 0; varId < varTable.size(); varId++) {
		vars.insert(varId);
	}
	return vars;
}

int PatternPKBStub::getVarIdByName(string varName) {
	for (int i = 0; i < (int)varTable.size(); i++) {
		if (varTable[i].compare(varName) == 0) {
			return i;
		}
	}
	return -1;
}

unordered_set<int> PatternPKBStub::getAllAssignStmt() {
	return assignStmts;
}

unordered_set<int> PatternPKBStub::getStmtInAssignWithVar(int varId) {
	return assignStmtModVar.at(varId);
}

string PatternPKBStub::getExpInAssignStmt(int assignStmtId) {
	auto it = assignTable.find(assignStmtId);
	if (it == assignTable.end())
		return "";
	else
		return it->second;
}

int PatternPKBStub::getVarAtLeftOfAssignStmt(int assignStmtId) {
	return left_varInAssignStmt.at(assignStmtId);
}

bool PatternPKBStub::isStmtInAssignTable(int stmtId) {
	if (assignTable.find(stmtId) == assignTable.end()) {
		return false;
	}
	return true;
}

unordered_set<int> PatternPKBStub::getStmtInWhileWithCtrlVar(int varId) {
	if (whileStmtUseVar.find(varId) == whileStmtUseVar.end()) {
		return unordered_set<int>();
	}
	return whileStmtUseVar.at(varId);
}

int PatternPKBStub::getCtrlVarInWhileStmt(int stmtId) {
	if (ctrlVarInWhileStmt.find(stmtId) == ctrlVarInWhileStmt.end()) {
		return -1;
	}
	return ctrlVarInWhileStmt.at(stmtId);
}

bool PatternPKBStub::isStmtInWhileTable(int stmtId) {
	if (whileStmts.find(stmtId) == whileStmts.end()) {
		return false;
	}
	return true;
}

unordered_set<int> PatternPKBStub::getStmtInIfWithCtrlVar(int varId) {
	if (ifStmtUseVar.find(varId) == ifStmtUseVar.end()) {
		return unordered_set<int>();
	}
	return ifStmtUseVar.at(varId);
}

int PatternPKBStub::getCtrlVarInIfStmt(int stmtId) {
	if (ctrlVarInIfStmt.find(stmtId) == ctrlVarInIfStmt.end()) {
		return -1;
	}
	return ctrlVarInIfStmt.at(stmtId);
}

bool PatternPKBStub::isStmtInIfTable(int stmtId) {
	if (ifStmts.find(stmtId) == ifStmts.end()) {
		return false;
	}
	return true;
}