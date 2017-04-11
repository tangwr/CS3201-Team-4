#pragma once


#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class AssignTable {
public:
	AssignTable();
	bool setExpToAssignStmt(int stmtId, string exp);
	bool setVarToAssignStmt(int stmtId, int varId);
	bool setVarExpToAssignStmt(int varId, string exp, int stmtId);
	string getExpInAssignStmt(int stmtId);
	int getAssignedVarInAssignStmt(int stmtId);//-1 if does not exist
	unordered_set<int> getStmtWithCtrlVar(int varId);
	unordered_set<int> getAllStmtId();
	bool isStmtInTable(int stmtId);
	int getSize();
	void printContents();

private:
	unordered_map<int, string> assignList;//stmtId, expression
    unordered_map<int, int> variableAssignList; //stmtId, varId assigned on left of operator
    unordered_map<int, unordered_set<int>> varAssignedByStmtList;//varid to list of assign stmt
    unordered_set<int> assignStmtSet;
    bool setAssignStmtToVar(int assignStmtId, int varId);
	int size;


};