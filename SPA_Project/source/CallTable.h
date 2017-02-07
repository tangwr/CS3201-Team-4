#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <utility>
#include <unordered_map>

using namespace std;

class CallTable {
private:
	unordered_map<int, int> callList;
	int size;

public:
	CallTable();
	int getSize();
	void printContents();
	bool setStmtCallProc(int stmtId, int procId);
	int getCallProc(int stmtId);
	bool isStmtInTable(int stmtId);
};