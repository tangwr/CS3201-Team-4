#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <utility>
#include <unordered_map>


using namespace std;

class WhileTable {
private:

	unordered_map<int, int> whileList;//stmtId, controlVarId
	int size;

public:
	WhileTable();
	int getSize();
	void printContents();
	bool setWhileCtrlVar(int stmtId, int varId);
	int getWhileCtrlVar(int stmtId);
    vector<int> getAllStmtId();
};