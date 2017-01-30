#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ModifiesTable {
public:
	ModifiesTable(int tsize);
	int insertStmtModify(int varNo, int stmtNo);
	int insertProcModify(int varNo, int procNo);
	vector<int> getStmtModify(int varNo);
	vector<int> getProcModify(int varNo);
	vector<int> getVarModifiedByStmt(int stmtNo);
	vector<int> getVarModifiedByProc(int procNo);
};
