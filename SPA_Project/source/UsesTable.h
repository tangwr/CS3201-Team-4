#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class UsesTable {
private:
	bool setStmtUsedByRel(int stmtId, int varId);
	bool setProcUsedByRel(int procId, int varId);
	bool setStmtUsedByRelConst(int stmtId, int varId);
	bool setProcUsedByRelConst(int procId, int varId);
	bool insertStmtUsedByRel(int stmtId, int varId);
	bool insertProcUsedByRel(int procId, int varId);
	void printVector(vector<int> vec);
    void printUnorderedSet(unordered_set<int> uSet);

	//unordered_map<int, vector<int>> vUsesStmtMap;
	//unordered_map<int, vector<int>> vUsesProcMap;
	//unordered_map<int, vector<int>> vUsedByStmtMap;
	//unordered_map<int, vector<int>> vUsedByProcMap;

	//unordered_map<int, vector<int>> cUsesStmtMap;
	//unordered_map<int, vector<int>> cUsesProcMap;
	//unordered_map<int, vector<int>> cUsedByStmtMap;
	//unordered_map<int, vector<int>> cUsedByProcMap;

    unordered_map<int, unordered_set<int>> vUsesStmtMap;
    unordered_map<int, unordered_set<int>> vUsesProcMap;
    unordered_map<int, unordered_set<int>> vUsedByStmtMap;
    unordered_map<int, unordered_set<int>> vUsedByProcMap;

    unordered_map<int, unordered_set<int>> cUsesStmtMap;
    unordered_map<int, unordered_set<int>> cUsesProcMap;
    unordered_map<int, unordered_set<int>> cUsedByStmtMap;
    unordered_map<int, unordered_set<int>> cUsedByProcMap;

public:
	UsesTable();
	bool setStmtUseVarRel(int stmtId, int varId);
	bool setProcUseVarRel(int procId, int varId);
	bool setStmtUseConstRel(int stmtId, int constId);
	bool setProcUseConstRel(int procId, int constId);
	bool insertStmtUseRel(int stmtId, int varId);
	bool insertProcUseRel(int procId, int varId);

	vector<int> getVarUsedByStmt(int stmtId);
	vector<int> getStmtUseVar(int varId);
	vector<int> getVarUsedByProc(int procId);
	vector<int> getProcUseVar(int varId);

	vector<int> getConstUsedByStmt(int stmtId);
	vector<int> getStmtUseConst(int constId);
	vector<int> getConstUsedByProc(int procId);
	vector<int> getProcUseConst(int constId);
	vector<int> getAllStmt();
	bool checkStmtExist(int stmtId);
	bool checkStmtVarRelExist(int stmtId, int varId);
	void printContents();

};