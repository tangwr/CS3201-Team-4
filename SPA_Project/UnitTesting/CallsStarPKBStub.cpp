#include <unordered_map>

#include "stdafx.h"
#include "CallsStarPKBStub.h"

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

CallsStarPKBStub::CallsStarPKBStub() {
	procId = { 0,1,2 };
	procStmts = { "Example","p","q" };

	procIdTable.insert({ "Example", 0 });
	procIdTable.insert({ "p", 1 });
	procIdTable.insert({ "q", 2 });

	procCallTable.insert({ 0,{ 1,2 } });
	procCallTable.insert({ 1,{ 2 } });
	procCallTable.insert({ 2,{} });
}

unordered_set<int> CallsStarPKBStub::getAllProcId() {
	return procId;
}

bool CallsStarPKBStub::isProcInTable(string procName) {
	auto it = procStmts.find(procName);
	if (it != procStmts.end()) {
		return true;
	}
	return false;
}

int CallsStarPKBStub::getProcIdByName(string procName) {
	auto& it = procIdTable.find(procName);
	if (it != procIdTable.end())
		return it->second;
	return -1;
}

unordered_set<int> CallsStarPKBStub::getProcCalledByStarProc(int callerProcId) {
	unordered_set<int> procSet;
	auto& it = procCallTable.find(callerProcId);
	if (it != procCallTable.end())
		return it->second;
	return procSet;
}