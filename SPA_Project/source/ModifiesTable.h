#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class ModifiesTable {

public:
	ModifiesTable();
	bool setStmtModifyVarRel(int stmtId, int varId);
	bool setProcModifyVarRel(int procId, int varId);
	bool insertStmtModifyVarRel(int stmtId, int varId);
	bool insertProcModifyVarRel(int stmtId, int varId);
	unordered_set<int> getStmtModifyVar(int varId);
	unordered_set<int> getVarModifiedInStmt(int stmtId);
	unordered_set<int> getProcModifyVar(int varId);
	unordered_set<int> getVarModifiedInProc(int procId);
	bool checkStmtExist(int stmtId);
	bool checkStmtVarRelExist(int stmtId, int varId);
	unordered_set<int> getAllStmt();
	void printContents();

private: 
	bool setStmtModifiedByRel(int stmtId, int varId);
	bool setProcModifiedByRel(int procId, int varId);
	bool insertStmtModifiedByRel(int stmtId, int varId);
	bool insertProcModifiedByRel(int procId, int varId);
	void printVector(vector<int> vec);
    void printUnorderedSet(unordered_set<int> uSet);
    unordered_map<int, unordered_set<int>> modifiesStmtMap, modifiedByStmtMap;
    unordered_map<int, unordered_set<int>> modifiesProcMap, modifiedByProcMap;

};
