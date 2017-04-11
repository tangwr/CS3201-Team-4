#include <unordered_map>

#include "stdafx.h"
#include "FollowStarPKBStub.h"

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

FollowStarPKBStub::FollowStarPKBStub() {
	allStmts = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 };
	assignStmts = { 1, 2, 3, 5, 7, 8, 9, 11, 15, 17, 18, 19, 20, 21, 23, 24 };
	whileStmts = { 4, 14 };
	ifStmts = { 6, 13, 22 };
	callStmts = { 10, 12, 16 };

	followsTable.insert({ 1, unordered_set<int>({2,3,4,12}) });
	followsTable.insert({ 2, unordered_set<int>({ 3,4,12 }) });
	followsTable.insert({ 3, unordered_set<int>({ 4,12 }) });
	followsTable.insert({ 4, unordered_set<int>({ 12 }) });
	followsTable.insert({ 5, unordered_set<int>({ 6,9,10,11 }) });
	followsTable.insert({ 6, unordered_set<int>({ 9,10,11 }) });
	followsTable.insert({ 9, unordered_set<int>({ 10,11 }) });
	followsTable.insert({ 10, unordered_set<int>({ 11 }) });
	followsTable.insert({ 13, unordered_set<int>({ 21 }) });
	followsTable.insert({ 14, unordered_set<int>({ 18,19 }) });
	followsTable.insert({ 15, unordered_set<int>({ 16,17 }) });
	followsTable.insert({ 16, unordered_set<int>({ 17 }) });
	followsTable.insert({ 18, unordered_set<int>({ 19 }) });


	followedByTable.insert({ 2, unordered_set<int>({ 1 }) });
	followedByTable.insert({ 3, unordered_set<int>({ 1, 2 }) });
	followedByTable.insert({ 4, unordered_set<int>({ 1,2,3 }) });
	followedByTable.insert({ 12, unordered_set<int>({ 1,2,3,4 }) });
	followedByTable.insert({ 6, unordered_set<int>({ 5 }) });
	followedByTable.insert({ 9, unordered_set<int>({ 5,6 }) });
	followedByTable.insert({ 10, unordered_set<int>({ 5,6,9 }) });
	followedByTable.insert({ 11, unordered_set<int>({ 5,6,9,10 }) });
	followedByTable.insert({ 21, unordered_set<int>({ 13 }) });
	followedByTable.insert({ 18, unordered_set<int>({ 14 }) });
	followedByTable.insert({ 16, unordered_set<int>({ 15 }) });
	followedByTable.insert({ 17, unordered_set<int>({ 15,16 }) });
	followedByTable.insert({ 19, unordered_set<int>({ 14,18 }) });

}

unordered_set<int> FollowStarPKBStub::getAllAssignStmt() {
	return assignStmts;
}

unordered_set<int> FollowStarPKBStub::getAllWhileStmt() {
	return whileStmts;
}

unordered_set<int> FollowStarPKBStub::getAllIfId() {
	return ifStmts;
}

unordered_set<int> FollowStarPKBStub::getAllCallId() {
	return callStmts;
}

int FollowStarPKBStub::getNumOfStmt() {
	return 24;
}

unordered_set<int> FollowStarPKBStub::getStmtFollowedByStarStmt(int a) {
	auto& it = followedByTable.find(a);
	if (it == followedByTable.end())
		return unordered_set<int>();
	return it->second;
}


unordered_set<int> FollowStarPKBStub::getStmtFollowStarStmt(int a) {
	auto& it = followsTable.find(a);
	if (it == followsTable.end())
		return unordered_set<int>();
	return it->second;
}

unordered_set<int> FollowStarPKBStub::getAllStmtId() {
	return allStmts;
}