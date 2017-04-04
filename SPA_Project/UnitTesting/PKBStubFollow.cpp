#include <unordered_map>

#include "stdafx.h"
#include "PKBStubFollow.h"

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

PKBStubFollow::PKBStubFollow() {
	allStmts = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 };
	assignStmts = { 1, 2, 3, 5, 7, 8, 9, 11, 15, 17, 18, 19, 20, 21, 23, 24 };
	whileStmts = { 4, 14 };
	ifStmts = { 6, 13, 22 };
	callStmts = { 10, 12, 16 };

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
}

unordered_set<int> PKBStubFollow::getAllAssignStmt() {
	return assignStmts;
}

unordered_set<int> PKBStubFollow::getAllWhileStmt() {
	return whileStmts;
}

unordered_set<int> PKBStubFollow::getAllIfId() {
	return ifStmts;
}

unordered_set<int> PKBStubFollow::getAllCallId() {
	return callStmts;
}

int PKBStubFollow::getNumOfStmt() {
	return 24;
}

int PKBStubFollow::getStmtFollowedByStmt(int a) {
	auto& it = followedByTable.find(a);
	if (it == followedByTable.end())
		return -1;
	return it->second;
}


int PKBStubFollow::getStmtFollowStmt(int a) {
	auto& it = followsTable.find(a);
	if (it == followsTable.end())
		return -1;
	return it->second;
}

unordered_set<int> PKBStubFollow::getAllStmtId() {
	return allStmts;
}