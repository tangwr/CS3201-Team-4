#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <utility>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class IfTable {
private:

	unordered_map<int, int> ifList;//stmtId to ctrlVarId
    unordered_map<int, unordered_set<int>> ctrlVarStmtList;
	int size;
    bool setCtrlVarUsedByStmt(int ctrlVarId, int stmtId);

public:
	IfTable();
	int getSize();
	void printContents();
	bool setVarToIfStmt(int stmtId, int varId);
	int getCtrlVarInIfStmt(int stmtId);
    unordered_set<int> getStmtWithCtrlVar(int ctrlVarId);
    unordered_set<int> getAllIfId();
	bool isStmtInTable(int stmtId);
};