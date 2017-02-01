#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ModifiesTable {
private: 
	bool setModifiedByDirectRel(int stmtId, int varId);
	bool setModifiedByDirectRelProc(int stmtId, int varId);
public:
	ModifiesTable();
	bool setModifyDirectRel(int stmtId, int varId);
	bool setModifyDirectRelProc(int stmtId, int varId);
	//int insertStmtModify(int varNo, int stmtNo);
	//int insertProcModify(int varNo, int procNo);
	vector<int> getModifiedByStmt(int varId);
	vector<int> getStmtModify(int stmtId);
	vector<int> getModifiedByProc(int varId);
	vector<int> getProcModify(int stmtId);

};
