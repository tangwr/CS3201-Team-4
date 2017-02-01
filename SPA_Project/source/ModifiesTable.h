#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ModifiesTable {
private: 
	bool ModifiesTable::setModifiedByDirectRel(int stmtId, int varId);
	bool ModifiesTable::setModifiedByDirectRelProc(int stmtId, int varId);
public:
	ModifiesTable();
	bool ModifiesTable::setModifyDirectRel(int stmtId, int varId);
	bool ModifiesTable::setModifyDirectRelProc(int stmtId, int varId);
	//int insertStmtModify(int varNo, int stmtNo);
	//int insertProcModify(int varNo, int procNo);
	vector<int> ModifiesTable::getModifiedByStmt(int varId);
	vector<int> ModifiesTable::getStmtModify(int stmtId);
	vector<int> ModifiesTable::getModifiedByProc(int varId);
	vector<int> ModifiesTable::getProcModify(int stmtId);

};
