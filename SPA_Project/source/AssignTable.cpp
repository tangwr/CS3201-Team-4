#pragma once
#include "AssignTable.h"

#define EMPTY_STRING ""
#define INVALID_INDEX -1

using namespace std;

bool AssignTable::setAssignStmtToVar(int assignStmtId, int varId) {
    unordered_map<int, unordered_set<int>>::iterator it = varAssignedByStmtList.find(varId);
    unordered_set<int> assignStmtSet;
    if (it != this->varAssignedByStmtList.end()) {
        assignStmtSet = it->second;
        if (assignStmtSet.find(assignStmtId) != assignStmtSet.end()) {
            return false;
        }
        varAssignedByStmtList.erase(it);
    }
    assignStmtSet.insert(assignStmtId);
    varAssignedByStmtList.insert(make_pair(varId, assignStmtSet));
    return true;
}

AssignTable::AssignTable() {
	size = 0;
}



bool AssignTable::setExpToAssignStmt(int stmtId, string exp) {
	if (this->assignList.find(stmtId) != this->assignList.end()) {
		return false;
	}
	else {
		this->assignList.insert({ stmtId, exp });
        this->assignStmtSet.insert(stmtId);
		this->size++;
		return true;
	}
}

bool AssignTable::setVarToAssignStmt(int stmtId, int varId) {
    if (this->variableAssignList.find(stmtId) != this->variableAssignList.end()) {
        return false;
    }
    else {
        this->variableAssignList.insert({ stmtId, varId });
        //return true;
        return this->setAssignStmtToVar(stmtId, varId);
    }
}

bool AssignTable::setVarExpToAssignStmt(int varId, string exp, int stmtId) {
    bool isSuccessful = this->setVarToAssignStmt(stmtId, varId);
    if (!isSuccessful) {
        isSuccessful = false;
    }
    else {
        isSuccessful = this->setExpToAssignStmt(stmtId, exp);
    }
    return isSuccessful;
}

string AssignTable::getExpInAssignStmt(int stmtId) {
	auto it = this->assignList.find(stmtId);
	if (it != assignList.end()) {
		return it->second;
	}
	else {
		return EMPTY_STRING;
	}
}

int AssignTable::getAssignedVarInAssignStmt(int stmtId) {
    unordered_map<int, int>::iterator it = this->variableAssignList.find(stmtId);
    if (it != this->variableAssignList.end()) {
        return it->second;
    }
    else {
        return INVALID_INDEX;
    }
}

unordered_set<int> AssignTable::getStmtWithCtrlVar(int varId) {
    unordered_map<int, unordered_set<int>>::iterator it = this->varAssignedByStmtList.find(varId);
    unordered_set<int> assignStmtSet;
    if (it != this->varAssignedByStmtList.end()) {
        assignStmtSet = it->second;
    }
    return assignStmtSet;
}

//returns a vector<int> of all assign statement Id
unordered_set<int> AssignTable::getAllStmtId() {
    return this->assignStmtSet;
}

bool AssignTable::isStmtInTable(int stmtId)
{
    for (auto stmtEntry : this->assignList) {
        if (stmtEntry.first == stmtId) {
            return true;
        }
    }
    return false;
}

int AssignTable::getSize() {
	return this->size;
}

void AssignTable::printContents() {

    cout << "---PRINT ASSIGN TABLE---" << endl;

    cout << "StmtId : Expression" << endl;
    for (auto entry : assignList) {
        cout << entry.first << " : " << entry.second << endl;
    }
    cout << endl;

    cout << "StmtId : variable assigned on left" << endl;
    for (auto entry : variableAssignList) {
        cout << entry.first << " : " << entry.second << endl;
    }
    cout << endl;

    cout << "---END PRINT ASSIGN TABLE---" << endl;

}
