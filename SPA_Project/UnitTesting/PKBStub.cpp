#include <unordered_map>

#include "stdafx.h"
#include "PKBStub.h"

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
	varTable = { "x", "z", "i", "y" };
	assignStmts = { 1, 2, 3, 5, 7, 8, 9, 11, 15, 17, 18, 19, 20, 21, 23, 24 };
	whileStmts = { 4, 14 };
	ifStmts = { 6, 13, 22 };
	modifyStmts = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };

	//modifyTable.push_back({ 1, 4, 5, 10, 12, 13, 14, 15, 16, 18, 22, 24 });
	//modifyTable.push_back({ 2, 4, 6, 7, 9, 10, 12, 13, 14, 16, 19, 20, 21, 22, 23});
	//modifyTable.push_back({ 3, 4, 11, 12, 13, 14, 17 });
	//modifyTable.push_back({ 4, 6, 8 });
	
	modifyTable.push_back({});
	modifyTable.push_back({ 0 });
	modifyTable.push_back({ 1 });
	modifyTable.push_back({ 2 });
	modifyTable.push_back({ 0, 1, 2, 3 });
	modifyTable.push_back({ 0 });
	modifyTable.push_back({ 1, 3 });
	modifyTable.push_back({ 1 });
	modifyTable.push_back({ 3 });
	modifyTable.push_back({ 1 });
	modifyTable.push_back({ 0, 1 });
	modifyTable.push_back({ 2 });
	modifyTable.push_back({ 0, 1, 2 });
	modifyTable.push_back({ 0, 1, 2 });
	modifyTable.push_back({ 0, 1, 2 });
	modifyTable.push_back({ 0 });
	modifyTable.push_back({ 0, 1 });
	modifyTable.push_back({ 2 });
	modifyTable.push_back({ 0 });
	modifyTable.push_back({ 1 });
	modifyTable.push_back({ 1 });
	modifyTable.push_back({ 1 });
	modifyTable.push_back({ 0, 1 });
	modifyTable.push_back({ 1 });
	modifyTable.push_back({ 0 });
	
	assignTable.insert({ 1, "2|" });
	assignTable.insert({ 2, "3|" });
	assignTable.insert({ 3, "5|" });
	assignTable.insert({ 5, "-|x|1|" });
	assignTable.insert({ 7, "+|x|1|" });
	assignTable.insert({ 8, "+|z|x|" });
	assignTable.insert({ 9, "+|+|z|x|i|" });
	assignTable.insert({ 11, "-|i|1|" });
	assignTable.insert({ 15, "+|*|z|3|*|2|y|"});
	assignTable.insert({ 17, "-|i|1|" });
	assignTable.insert({ 18, "+|x|1|" });
	assignTable.insert({ 19, "+|x|z|" });
	assignTable.insert({ 20, "1|" });
	assignTable.insert({ 21, "+|+|z|x|i|" });
	assignTable.insert({ 23, "+|x|1|" });
	assignTable.insert({ 24, "+|z|x|" });
}

int PKBStub::getVarIdByName(string varName) {
	for (int i = 0; i < (int)varTable.size(); i++) {
		if (varTable[i].compare(varName) == 0) {
			return i;
		}
	}
	return -1;
}

unordered_set<int> PKBStub::getAllAssignStmt() {
	return assignStmts;
}

unordered_set<int> PKBStub::getAllWhileStmt() {
	return whileStmts;
}

unordered_set<int> PKBStub::getAllIfStmt() {
	return ifStmts;
}

unordered_set<int> PKBStub::getStmtModifyVar(int varId) {
	return modifyStmts;
}

unordered_set<int> PKBStub::getVarModifiedInStmt(int stmtId) {
	return modifyTable[stmtId];
}

string PKBStub::getExpInAssignStmt(int assignStmtId) {
	auto it = assignTable.find(assignStmtId);
	if (it == assignTable.end())
		return "";
	else
		return it->second;
}