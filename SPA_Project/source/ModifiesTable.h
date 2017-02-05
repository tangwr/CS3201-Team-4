#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class ModifiesTable {
private: 
	bool setStmtModifiedByRel(int stmtId, int varId);
	bool setProcModifiedByRel(int procId, int varId);
	void printVector(vector<int> vec);
	unordered_map<int, vector<int>> modifiesStmtMap, modifiedByStmtMap; //stmt list of var, var - list of stmt
	unordered_map<int, vector<int>> modifiesProcMap, modifiedByProcMap;

public:
	ModifiesTable();
	bool setStmtModifyRel(int stmtId, int varId);
	bool setProcModifyRel(int procId, int varId);
    bool checkStmtExist(int stmtId);
    bool checkStmtVarRelExist(int stmt, int varId);
	//bool insertStmtModify(int stmtId, int varId);
	//bool insertProcModify(int procId, int varId);
	vector<int> getModifiedByStmt(int varId);
	vector<int> getStmtModify(int stmtId);
	vector<int> getModifiedByProc(int varId);
	vector<int> getProcModify(int procId);

    vector<int> getAllStmt();

	void printContents();

};
