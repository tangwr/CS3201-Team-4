#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "TableOperations.h"
#include "VectorSetOperation.h"

using namespace std;

class StmtLstTable {
private:
    unordered_map<int, vector<int>> procToStmtLstMap;//proc id, list of first stmt in stmtLst in proc
    unordered_map<int, vector<int>> containerStmtToStmtLstMap;//container stmtid, list of first stmt in stmtlst in container stmt


public:
    //[action][target][table/relation][key][rel]
    StmtLstTable();

    bool setProcStmtLstContainsStmtRel(int procId, int stmtId);
    bool setContainerStmtStmtLstContainsStmtRel(int containerStmtId, int stmtId);

    vector<int> getStmtLstContainedInProc(int procId);
    vector<int> getStmtlstContainedInContainerStmt(int containerStmtId);
    unordered_set<int> getAllStmtLst();

    void printContents();

};