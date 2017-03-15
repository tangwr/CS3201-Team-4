#pragma once


#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class AssignTable {
private:
	unordered_map<int, string> assignList;//stmtId, expression
    unordered_map<int, int> variableAssignList; //stmtId, varId assigned on left of operator
	int size;

public:
	AssignTable();
	int getSize();
	void printContents();
	bool setExpToAssignStmt(int stmtId, string exp);
    bool setVarToAssignStmt(int stmtId, int varId);
    bool setVarExpToAssignStmt(int varId, string exp, int stmtId);
	string getExpInAssignStmt(int stmtId);
    int getAssignedVarInAssignStmt(int stmtId);//-1 if does not exist
    unordered_set<int> getAllStmtId();
	bool isStmtInTable(int stmtId);
};