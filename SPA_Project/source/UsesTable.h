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
	UsesTable();
	bool setUseDirectRel(int stmtId, int varId);
	bool setUseDirectRelProc(int procId, int varId);
	bool setUseDirectRelConst(int stmtId, int constId);
	bool setUseDirectRelConstProc(int procId, int constId);

	vector<int> getVarUsedByStmt(int stmtId);
	vector<int> getStmtUsesVar(int varId);
	vector<int> getVarUsedByProc(int procId);
	vector<int> getProcUsesVar(int varId);

	vector<int> getConstUsedByStmt(int stmtId);
	vector<int> getStmtUsesConst(int constId);
	vector<int> getConstUsedByProc(int procId);
	vector<int> getProcUsesConst(int constId);

};