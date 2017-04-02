#include <unordered_map>

#include "stdafx.h"
#include "PKBStubNextStar.h"

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

PKBStubNextStar::PKBStubNextStar() {
	assignStmts = { 1, 2, 3, 5, 7, 8, 9, 11, 15, 17, 18, 19, 20, 21, 23, 24 };
	whileStmts = { 4, 14 };
	ifStmts = { 6, 13, 22 };
	callStmts = { 10, 12, 16 };

	nextTable.insert({ 1, unordered_set<int>({ 2 }) });
	nextTable.insert({ 2, unordered_set<int>({ 3 }) });
	nextTable.insert({ 3, unordered_set<int>({ 4 }) });
	nextTable.insert({ 4, unordered_set<int>({ 5 , 12 }) });
	nextTable.insert({ 5, unordered_set<int>({ 6 }) });
	nextTable.insert({ 6, unordered_set<int>({ 7 , 8 }) });
	nextTable.insert({ 7, unordered_set<int>({ 9 }) });
	nextTable.insert({ 8, unordered_set<int>({ 9 }) });
	nextTable.insert({ 9, unordered_set<int>({ 10 }) });
	nextTable.insert({ 10, unordered_set<int>({ 11 }) });
	nextTable.insert({ 11, unordered_set<int>({ 4 }) });

	nextTable.insert({ 13, unordered_set<int>({ 14 , 20 }) });
	nextTable.insert({ 14, unordered_set<int>({ 15 , 18 }) });
	nextTable.insert({ 15, unordered_set<int>({ 16 }) });
	nextTable.insert({ 16, unordered_set<int>({ 17 }) });
	nextTable.insert({ 17, unordered_set<int>({ 14 }) });
	nextTable.insert({ 18, unordered_set<int>({ 19 }) });
	nextTable.insert({ 20, unordered_set<int>({ 21 }) });

	nextTable.insert({ 22, unordered_set<int>({ 23,24 }) });

	prevTable.insert({ 2, unordered_set<int>({ 1 }) });
	prevTable.insert({ 3, unordered_set<int>({ 2 }) });
	prevTable.insert({ 4, unordered_set<int>({ 3 , 11 }) });
	prevTable.insert({ 5, unordered_set<int>({ 4 }) });
	prevTable.insert({ 6, unordered_set<int>({ 5 }) });
	prevTable.insert({ 7, unordered_set<int>({ 6 }) });
	prevTable.insert({ 8, unordered_set<int>({ 6 }) });
	prevTable.insert({ 9, unordered_set<int>({ 7 , 8 }) });
	prevTable.insert({ 10, unordered_set<int>({ 9 }) });
	prevTable.insert({ 11, unordered_set<int>({ 10 }) });
	prevTable.insert({ 12, unordered_set<int>({ 4 }) });

	prevTable.insert({ 14, unordered_set<int>({ 13 , 17 }) });
	prevTable.insert({ 15, unordered_set<int>({ 14 }) });
	prevTable.insert({ 16, unordered_set<int>({ 15 }) });
	prevTable.insert({ 17, unordered_set<int>({ 16 }) });
	prevTable.insert({ 18, unordered_set<int>({ 14 }) });
	prevTable.insert({ 19, unordered_set<int>({ 18 }) });
	prevTable.insert({ 20, unordered_set<int>({ 13 }) });
	prevTable.insert({ 21, unordered_set<int>({ 20 }) });
	prevTable.insert({ 23, unordered_set<int>({ 22 }) });
	prevTable.insert({ 24, unordered_set<int>({ 22 }) });

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
}

unordered_set<int> PKBStubNextStar::getAllAssignStmt() {
	return assignStmts;
}

unordered_set<int> PKBStubNextStar::getAllWhileStmt() {
	return whileStmts;
}

unordered_set<int> PKBStubNextStar::getAllIfId() {
	return ifStmts;
}

unordered_set<int> PKBStubNextStar::getAllCallId() {
	return callStmts;
}

int PKBStubNextStar::getNumOfStmt() {
	return 24;
}

unordered_set<int> PKBStubNextStar::getPreviousStmt(int a) {
	auto& it = prevTable.find(a);
	if (it == prevTable.end())
		return unordered_set<int>();
	return it->second;
}


unordered_set<int> PKBStubNextStar::getNextStmt(int a) {
	auto& it = nextTable.find(a);
	if (it == nextTable.end())
		return unordered_set<int>();
	return it->second;
}

unordered_set<int> PKBStubNextStar::getStmtParentStarStmt(int a) {
	auto& it = parentStarTable.find(a);
	if (it == parentStarTable.end())
		return unordered_set<int>();
	return it->second;
}

bool PKBStubNextStar::isStmtInWhileTable(int a) {
	return whileStmts.find(a) != whileStmts.end();
}