#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include "TableOperations.h"

using namespace std;

class CallTable {

public:
	CallTable();
	bool setStmtCallProcRel(int stmtId, int procId);
	bool setProcCallProcRel(int callerProcId, int calledProcId);
	bool insertProcCallStarProcRel(int callerProcId, int calledProcId);
	int getProcCalledByStmt(int stmtId);
	unordered_set<int> getCallerStmtCallProc(int procId);
	unordered_set<int> getCallerProcCallProc(int calledProcId);
	unordered_set<int> getProcCalledByProc(int callerProcId);
	unordered_set<int> getProcCalledByStarProc(int callerProcId);
	unordered_set<int> getAllCallId();
	bool isStmtInTable(int stmtId);
	int getSize();
	void printContents();

private:
	unordered_map<int, int> stmtCallProcList;//stmtId, procId
    unordered_map<int, unordered_set<int>> procCalledByStmtList;//procId, callerstmtId
    unordered_map<int, unordered_set<int>> procCallProcList;//procId, calledprocId
    unordered_map<int, unordered_set<int>> procCallStarProcList;//procId, calledStarProcId
    unordered_map<int, unordered_set<int>> procCallerProcList;//procId, callerProcId
    unordered_set<int> callStmtSet;
    int size;//check if need another size
    bool setProcCalledByStmt(int procId, int callerStmtId);
    bool setProcCalledByProc(int procId, int callerProcId);


};