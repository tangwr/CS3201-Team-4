#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <utility>
#include <unordered_map>
#include <unordered_set>


using namespace std;

class WhileTable {
private:

	unordered_map<int, int> whileList;//stmtId, controlVarId
    unordered_map<int, unordered_set<int>> ctrlVarList; //control var to list of stmtId
	int size;
    bool setStmtToCtrlVar(int varId, int stmtId);

public:
	WhileTable();
	int getSize();
	void printContents();
	bool setVarToWhileStmt(int stmtId, int varId);
	int getCtrlVarInWhileStmt(int stmtId);
    unordered_set<int> getStmtWithCtrlVar(int varId);
    unordered_set<int> getAllStmtId();
	bool isStmtInTable(int stmtId);
};