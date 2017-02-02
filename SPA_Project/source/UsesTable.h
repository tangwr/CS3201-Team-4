#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class UsesTable {
private:
	bool setStmtUsedByRel(int stmtId, int varId);
	bool setProcUsedByRel(int procId, int varId);
	bool setStmtUsedByRelConst(int stmtId, int varId);
	bool setProcUsedByRelConst(int procId, int varId);
public:
	UsesTable();
	bool setStmtUseRel(int stmtId, int varId);
	bool setProcUseRel(int procId, int varId);
	bool setStmtUseRelConst(int stmtId, int constId);
	bool setProcUseRelConst(int procId, int constId);

	vector<int> getVarUsedByStmt(int stmtId);
	vector<int> getStmtUsesVar(int varId);
	vector<int> getVarUsedByProc(int procId);
	vector<int> getProcUsesVar(int varId);

	vector<int> getConstUsedByStmt(int stmtId);
	vector<int> getStmtUsesConst(int constId);
	vector<int> getConstUsedByProc(int procId);
	vector<int> getProcUsesConst(int constId);

};