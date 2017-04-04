#include <unordered_map>

#include "stdafx.h"
#include "PKBStubParent.h"

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

PKBStubParent::PKBStubParent() {
	allStmts = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 };
	assignStmts = { 1, 2, 3, 5, 7, 8, 9, 11, 15, 17, 18, 19, 20, 21, 23, 24 };
	whileStmts = { 4, 14 };
	ifStmts = { 6, 13, 22 };
	callStmts = { 10, 12, 16 };

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

	childrenTable.insert({ 4, unordered_set<int>({5,6,10,11}) });
	childrenTable.insert({ 6, unordered_set<int>({ 7, 8 }) });
	childrenTable.insert({ 13, unordered_set<int>({ 14,18,19,20}) });
	childrenTable.insert({ 14, unordered_set<int>({ 15, 16, 17 }) });
	childrenTable.insert({ 22, unordered_set<int>({ 23, 24 }) });
}

unordered_set<int> PKBStubParent::getAllAssignStmt() {
	return assignStmts;
}

unordered_set<int> PKBStubParent::getAllWhileStmt() {
	return whileStmts;
}

unordered_set<int> PKBStubParent::getAllIfId() {
	return ifStmts;
}

unordered_set<int> PKBStubParent::getAllCallId() {
	return callStmts;
}

int PKBStubParent::getNumOfStmt() {
	return 24;
}

int PKBStubParent::getStmtParentStmt(int a) {
	auto& it = parentTable.find(a);
	if (it == parentTable.end())
		return -1;
	return it->second;
}


unordered_set<int> PKBStubParent::getStmtChildrenStmt(int a) {
	auto& it = childrenTable.find(a);
	if (it == childrenTable.end())
		return unordered_set<int>();
	return it->second;
}

unordered_set<int> PKBStubParent::getAllStmtId() {
	return allStmts;
}