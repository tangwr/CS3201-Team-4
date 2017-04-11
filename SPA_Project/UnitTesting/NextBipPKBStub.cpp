#include <unordered_map>

#include "stdafx.h"
#include "NextBipPKBStub.h"

/*
procedure o {
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
}

procedure q {
if x then {					//12
	z = x + 1; }			//13
else {
	x = z + x; } }			//14

procedure first{
call second;			//15
call q;					//16
a = b;					//17
}

procedure second{
call third;				//18
}

procedure third{
c = d;					//19
}
*/

NextBipPKBStub::NextBipPKBStub() {
	allStmts = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };
	assignStmts = { 1, 2, 3, 5, 7, 8, 9, 11, 13, 14, 17, 19 };
	whileStmts = { 4 };
	ifStmts = { 6, 12 };
	callStmts = { 10, 15, 16, 18 };

	stmtLstContainedInProc.insert({ 1, vector<int>({ 1 }) });
	stmtLstContainedInProc.insert({ 2, vector<int>({ 12 }) });
	stmtLstContainedInProc.insert({ 3, vector<int>({ 15 }) });
	stmtLstContainedInProc.insert({ 4, vector<int>({ 18 }) });
	stmtLstContainedInProc.insert({ 5, vector<int>({ 19 }) });

	stmtCallProcTable.insert({ 2, unordered_set<int>({ 10, 16 }) });
	stmtCallProcTable.insert({ 4, unordered_set<int>({ 15 }) });
	stmtCallProcTable.insert({ 5, unordered_set<int>({ 18 }) });

	procCalledByStmtTable.insert({ 10, 2 });
	procCalledByStmtTable.insert({ 15, 4 });
	procCalledByStmtTable.insert({ 16, 2 });
	procCalledByStmtTable.insert({ 18, 5 });

	myProcTable.insert({ 1, 1 });
	myProcTable.insert({ 2, 1 });
	myProcTable.insert({ 3, 1 });
	myProcTable.insert({ 4, 1 });
	myProcTable.insert({ 5, 1 });
	myProcTable.insert({ 6, 1 });
	myProcTable.insert({ 7, 1 });
	myProcTable.insert({ 8, 1 });
	myProcTable.insert({ 9, 1 });
	myProcTable.insert({ 10, 1 });
	myProcTable.insert({ 11, 1 });

	myProcTable.insert({ 12, 2 });
	myProcTable.insert({ 13, 2 });
	myProcTable.insert({ 14, 2 });

	myProcTable.insert({ 15, 3 });
	myProcTable.insert({ 16, 3 });
	myProcTable.insert({ 17, 3 });

	myProcTable.insert({ 18, 4 });
	myProcTable.insert({ 19, 5 });

	nextTable.insert({ 1, unordered_set<int>({ 2 }) });
	nextTable.insert({ 2, unordered_set<int>({ 3 }) });
	nextTable.insert({ 3, unordered_set<int>({ 4 }) });
	nextTable.insert({ 4, unordered_set<int>({ 5 }) });
	nextTable.insert({ 5, unordered_set<int>({ 6 }) });
	nextTable.insert({ 6, unordered_set<int>({ 7 , 8 }) });
	nextTable.insert({ 7, unordered_set<int>({ 9 }) });
	nextTable.insert({ 8, unordered_set<int>({ 9 }) });
	nextTable.insert({ 9, unordered_set<int>({ 10 }) });
	nextTable.insert({ 10, unordered_set<int>({ 11 }) });
	nextTable.insert({ 11, unordered_set<int>({ 4 }) });

	nextTable.insert({ 12, unordered_set<int>({ 13 , 14 }) });
	nextTable.insert({ 13, unordered_set<int>({ -1 }) });
	nextTable.insert({ 14, unordered_set<int>({ -1 }) });
	nextTable.insert({ 15, unordered_set<int>({ 16 }) });
	nextTable.insert({ 16, unordered_set<int>({ 17 }) });

	prevTable.insert({ 2, unordered_set<int>({ 1 }) });
	prevTable.insert({ 3, unordered_set<int>({ 2 }) });
	prevTable.insert({ 4, unordered_set<int>({ 3, 11 }) });
	prevTable.insert({ 5, unordered_set<int>({ 4 }) });
	prevTable.insert({ 6, unordered_set<int>({ 5 }) });
	prevTable.insert({ 7, unordered_set<int>({ 6 }) });
	prevTable.insert({ 8, unordered_set<int>({ 6 }) });
	prevTable.insert({ 9, unordered_set<int>({ 7 , 8 }) });
	prevTable.insert({ 10, unordered_set<int>({ 9 }) });
	prevTable.insert({ 11, unordered_set<int>({ 10 }) });

	prevTable.insert({ -1, unordered_set<int>({ 13, 14 }) });
	prevTable.insert({ 13, unordered_set<int>({ 12 }) });
	prevTable.insert({ 14, unordered_set<int>({ 12 }) });
	prevTable.insert({ 16, unordered_set<int>({ 15 }) });
	prevTable.insert({ 17, unordered_set<int>({ 16 }) });

	parentStarTable.insert({ 5, unordered_set<int>({ 4 }) });
	parentStarTable.insert({ 6, unordered_set<int>({ 4 }) });
	parentStarTable.insert({ 7, unordered_set<int>({ 4, 6 }) });
	parentStarTable.insert({ 8, unordered_set<int>({ 4, 6 }) });
	parentStarTable.insert({ 9, unordered_set<int>({ 4 }) });
	parentStarTable.insert({ 10, unordered_set<int>({ 4 }) });
	parentStarTable.insert({ 11, unordered_set<int>({ 4 }) });

	parentStarTable.insert({ 13, unordered_set<int>({ 12 }) });
	parentStarTable.insert({ 14, unordered_set<int>({ 12 }) });
}

unordered_set<int> NextBipPKBStub::getAllAssignStmt() {
	return assignStmts;
}

unordered_set<int> NextBipPKBStub::getAllWhileStmt() {
	return whileStmts;
}

unordered_set<int> NextBipPKBStub::getAllIfId() {
	return ifStmts;
}

unordered_set<int> NextBipPKBStub::getAllCallId() {
	return callStmts;
}

int NextBipPKBStub::getNumOfStmt() {
	return 24;
}

unordered_set<int> NextBipPKBStub::getPreviousStmt(int a) {
	auto& it = prevTable.find(a);
	if (it == prevTable.end())
		return unordered_set<int>();
	return it->second;
}


unordered_set<int> NextBipPKBStub::getNextStmt(int a) {
	auto& it = nextTable.find(a);
	if (it == nextTable.end())
		return unordered_set<int>();
	return it->second;
}

unordered_set<int> NextBipPKBStub::getStmtParentStarStmt(int a) {
	auto& it = parentStarTable.find(a);
	if (it == parentStarTable.end())
		return unordered_set<int>();
	return it->second;
}

bool NextBipPKBStub::isStmtInWhileTable(int a) {
	return whileStmts.find(a) != whileStmts.end();
}

bool NextBipPKBStub::isStmtInCallTable(int a) {
	return callStmts.find(a) != callStmts.end();
}

bool NextBipPKBStub::isStmtInIfTable(int a) {
	return ifStmts.find(a) != ifStmts.end();
}

unordered_set<int> NextBipPKBStub::getAllStmtId() {
	return allStmts;
}

int NextBipPKBStub::getProcContainingStmt(int a) {
	if (myProcTable.find(a) == myProcTable.end())
		return -1;
	return myProcTable.find(a)->second;
}

int NextBipPKBStub::getProcCalledByStmt(int a) {
	if (procCalledByStmtTable.find(a) == procCalledByStmtTable.end())
		return -1;
	return procCalledByStmtTable.find(a)->second;
}


unordered_set<int> NextBipPKBStub::getStmtCallProc(int a) {
	if (stmtCallProcTable.find(a) == stmtCallProcTable.end())
		return unordered_set<int>();
	return stmtCallProcTable.find(a)->second;
}


vector<int> NextBipPKBStub::getStmtLstContainedInProc(int a) {
	if (stmtLstContainedInProc.find(a) == stmtLstContainedInProc.end())
		return vector<int>();
	return stmtLstContainedInProc.find(a)->second;
}
