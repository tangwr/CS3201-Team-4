#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class UsesTable {
public:
	UsesTable(int tsize);
	int insertStmtUse(int varNo, int stmtNo);
	int insertProcUse(int varNo, int procNo);
	vector<int> getStmtUse(int varNo);
	vector<int> getProcUse(int varNo);
	vector<int> getVarUsedByStmt(int stmtNo);
	vector<int> getVarUsedByProc(int procNo);
};