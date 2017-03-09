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
	int size;

public:
	WhileTable();
	int getSize();
	void printContents();
	bool setVarToWhileStmt(int stmtId, int varId);
	int getCtrlVarInWhileStmt(int stmtId);
    unordered_set<int> getAllStmtId();
	bool isStmtInTable(int stmtId);
};