#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class UsesTable {

public:
	UsesTable();
	bool setStmtUseVarRel(int stmtId, int varId);
	bool setProcUseVarRel(int procId, int varId);
	bool setStmtUseConstRel(int stmtId, int constId);
	bool setProcUseConstRel(int procId, int constId);
	bool insertStmtUseVarRel(int stmtId, int varId);
	bool insertProcUseVarRel(int procId, int varId);
	bool insertStmtUseConstRel(int stmtId, int constId);
	bool insertProcUseConstRel(int procId, int constId);


	unordered_set<int> getVarUsedByStmt(int stmtId);
	unordered_set<int> getStmtUseVar(int varId);
	unordered_set<int> getVarUsedByProc(int procId);
	unordered_set<int> getProcUseVar(int varId);

	unordered_set<int> getConstUsedByStmt(int stmtId);
	unordered_set<int> getStmtUseConst(int constId);
	unordered_set<int> getConstUsedByProc(int procId);
	unordered_set<int> getProcUseConst(int constId);
	unordered_set<int> getAllStmtId();
	bool checkStmtExist(int stmtId);
	bool checkStmtVarRelExist(int stmtId, int varId);
	void printContents();

private:
	bool setStmtUsedByRel(int stmtId, int varId);
	bool setProcUsedByRel(int procId, int varId);
	bool setStmtUsedByRelConst(int stmtId, int constId);
	bool setProcUsedByRelConst(int procId, int constId);
	bool insertStmtUsedByRel(int stmtId, int varId);
	bool insertProcUsedByRel(int procId, int varId);
    bool insertStmtUsedByRelConst(int stmtId, int constId);
    bool insertProcUsedByRelConst(int procId, int constId);
	void printVector(vector<int> vec);
    void printUnorderedSet(unordered_set<int> uSet);

    unordered_map<int, unordered_set<int>> vUsesStmtMap;
    unordered_map<int, unordered_set<int>> vUsesProcMap;
    unordered_map<int, unordered_set<int>> vUsedByStmtMap;
    unordered_map<int, unordered_set<int>> vUsedByProcMap;

    unordered_map<int, unordered_set<int>> cUsesStmtMap;
    unordered_map<int, unordered_set<int>> cUsesProcMap;
    unordered_map<int, unordered_set<int>> cUsedByStmtMap;
    unordered_map<int, unordered_set<int>> cUsedByProcMap;



};