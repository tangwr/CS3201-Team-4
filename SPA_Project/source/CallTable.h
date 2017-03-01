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
    unordered_map<int, unordered_set<int>> procCallProcList;//procId, calledprocId
	int size;//check if need another size

public:
	CallTable();
	int getSize();
	void printContents();
	bool setStmtCallProcRel(int stmtId, int procId);
    bool setProcCallProcRel(int callerProcId, int calledProcId);
	int getProcCalledByStmt(int stmtId);
    unordered_set<int> getProcCalledByProc(int callerProcId);
    unordered_set<int> getAllCallId();
	bool isStmtInTable(int stmtId);
};