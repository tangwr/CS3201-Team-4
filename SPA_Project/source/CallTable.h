#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <utility>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class CallTable {
private:
	unordered_map<int, int> stmtCallProcList;//stmtId, procId
    unordered_map<int, unordered_set<int>> procCallProcList;//procId, procId
	int size;//check if need another size

public:
	CallTable();
	int getSize();
	void printContents();
	bool setStmtCallProc(int stmtId, int procId);
    bool setProcCallProc(int callerProcId, int calledProcId);
	int getCallProc(int stmtId);
    unordered_set<int> getProcCallProc(int callerProcId);
	bool isStmtInTable(int stmtId);
};