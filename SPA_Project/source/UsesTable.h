#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class UsesTable {
private:
	bool setUsedByDirectRel(int stmtId, int varId);
	bool setUsedByDirectRelProc(int procId, int varId);
	bool setUsedByDirectRelConst(int stmtId, int varId);
	bool setUsedByDirectRelConstProc(int procId, int varId);
public:
	UsesTable(int tsize);
	bool setUseDirectRel(int stmtId, int varId);
	bool setUseDirectRelProc(int procId, int varId);
	bool setUseDirectRelConst(int stmtId, int varId);
	bool setUseDirectRelConstProc(int procId, int varId);

	vector<int> getVarUsedByStmt(int stmtId);
	vector<int> getStmtUsesVar(int varId);
	vector<int> getVarUsedByProc(int procId);
	vector<int> getProcUsesVar(int varId);

	vector<int> getConstUsedByStmt(int stmtId);
	vector<int> getStmtUsesConst(int varId);
	vector<int> getConstUsedByProc(int procId);
	vector<int> getProcUsesConst(int varId);

};