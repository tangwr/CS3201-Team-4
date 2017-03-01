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
	int size;

public:
	IfTable();
	int getSize();
	void printContents();
	bool setVarToIfStmt(int stmtId, int varId);
	int getVarInIfStmt(int stmtId);
    unordered_set<int> getAllIfId();
	bool isStmtInTable(int stmtId);
};