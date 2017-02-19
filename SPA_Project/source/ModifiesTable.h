#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class ModifiesTable {
private: 
	bool setStmtModifiedByRel(int stmtId, int varId);
	bool setProcModifiedByRel(int procId, int varId);
	bool insertStmtModifiedByRel(int stmtId, int varId);
	bool insertProcModifiedByRel(int procId, int varId);
	void printVector(vector<int> vec);
    void printUnorderedSet(unordered_set<int> uSet);
	//unordered_map<int, vector<int>> modifiesStmtMap, modifiedByStmtMap;
	//unordered_map<int, vector<int>> modifiesProcMap, modifiedByProcMap;
    unordered_map<int, unordered_set<int>> modifiesStmtMap, modifiedByStmtMap;
    unordered_map<int, unordered_set<int>> modifiesProcMap, modifiedByProcMap;

public:
	ModifiesTable();
	bool setStmtModifyVarRel(int stmtId, int varId);
	bool setProcModifyVarRel(int procId, int varId);
	bool insertStmtModify(int stmtId, int varId);
	bool insertProcModify(int stmtId, int varId);
	vector<int> getStmtModifyVar(int varId);
	vector<int> getVarModifiedInStmt(int stmtId);
	vector<int> getProcModifyVar(int varId);
	vector<int> getVarModifiedInProc(int procId);
	bool checkStmtExist(int stmtId);
	bool checkStmtVarRelExist(int stmtId, int varId);
	vector<int> getAllStmt();
	void printContents();

};
