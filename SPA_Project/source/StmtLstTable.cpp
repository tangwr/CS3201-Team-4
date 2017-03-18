#include "StmtLstTable.h"

StmtLstTable::StmtLstTable() {

}

bool StmtLstTable::setProcStmtLstContainsStmtRel(int procId, int stmtId) {

    unordered_map<int, vector<int>>::iterator it;
    vector<int> stmtLstList;
    it = procToStmtLstMap.find(procId);

    if (it != procToStmtLstMap.end()) {
        stmtLstList = it->second;
        if (std::find(stmtLstList.begin(), stmtLstList.end(), stmtId) != stmtLstList.end()) {
            return false;
        }
        procToStmtLstMap.erase(it);
    }

    stmtLstList.push_back(stmtId);
    procToStmtLstMap.insert(make_pair(procId, stmtLstList));

    return true;
}

bool StmtLstTable::setContainerStmtStmtLstContainsStmtRel(int containerStmtId, int stmtId) {

    unordered_map<int, vector<int>>::iterator it;
    vector<int> stmtLstList;
    it = containerStmtToStmtLstMap.find(containerStmtId);

    if (it != containerStmtToStmtLstMap.end()) {
        stmtLstList = it->second;
        if (std::find(stmtLstList.begin(), stmtLstList.end(), stmtId) != stmtLstList.end()) {
            return false;
        }
        containerStmtToStmtLstMap.erase(it);
    }

    stmtLstList.push_back(stmtId);
    containerStmtToStmtLstMap.insert(make_pair(containerStmtId, stmtLstList));

    return true;
}

vector<int> StmtLstTable::getStmtLstContainedInProc(int procId) {
    
    unordered_map<int, vector<int>>::iterator it;
    vector<int> resultList;
    it = this->procToStmtLstMap.find(procId);

    if (it != this->procToStmtLstMap.end()) {
        resultList = it->second;
    }
    return resultList;

}

vector<int> StmtLstTable::getStmtlstContainedInContainerStmt(int containerStmtid) {

    unordered_map<int, vector<int>>::iterator it;
    vector<int> resultList;
    it = this->containerStmtToStmtLstMap.find(containerStmtid);

    if (it != this->containerStmtToStmtLstMap.end()) {
        resultList = it->second;
    }
    return resultList;

}

unordered_set<int> StmtLstTable::getAllStmtLst() {

    unordered_set<int> resultSet;
    //check need only 1 or both table
    for (pair<int, vector<int>> entry : procToStmtLstMap) {
        for (int element : entry.second) {
            resultSet.insert(element);
        }
    }

    
    for (pair<int, vector<int>> entry : containerStmtToStmtLstMap) {
        for (int element : entry.second) {
            resultSet.insert(element);
        }
    }

    return resultSet;
}

void StmtLstTable::printContents() {
    cout << "---PRINT STMTLST TABLE---" << endl;

    cout << "ProcId : First stmtId in StmtLst" << endl;
    for (pair<int, vector<int>> it : procToStmtLstMap) {
        cout << it.first << " : ";
        //cout << "StmtId: " << it.first;
        //cout << " Modifies VarId: ";
        //printVector(it.second);
        TableOperations::printTableVector(it.second);
        cout << endl;
    }
    cout << endl;

    cout << "Container StmtId : First stmtId in StmtLst" << endl;
    for (pair<int, vector<int>> it : containerStmtToStmtLstMap) {
        cout << it.first << " : ";
        //cout << "ProcId: " << it.first;
        //cout << " Modifies VarId: ";
        //printVector(it.second);
        TableOperations::printTableVector(it.second);
        cout << endl;
    }
    cout << endl;

    cout << "---END PRINT STMTLST TABLE---" << endl;
}