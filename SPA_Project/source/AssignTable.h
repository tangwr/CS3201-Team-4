#pragma once


#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class AssignTable {
private:
	unordered_map<int, string> assignList;//stmtId, expression
	int size;

public:
	AssignTable();
	int getSize();
	void printContents();
	bool setExpToAssignStmt(int stmtId, string exp);
	string getExpInAssignStmt(int stmtId);
    vector<int> getAllStmtId();
	bool isStmtInTable(int stmtId);
};