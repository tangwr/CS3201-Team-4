#pragma once
#include "IfTable.h"

#define INVALID_INDEX -1

using namespace std;

bool IfTable::setCtrlVarUsedByStmt(int ctrlVarId, int stmtId) {
    unordered_map<int, unordered_set<int>>::iterator it = ctrlVarStmtList.find(ctrlVarId);
    unordered_set<int> ifStmtSet;
    if (it != this->ctrlVarStmtList.end()) {
        ifStmtSet = it->second;
        if (ifStmtSet.find(stmtId) != ifStmtSet.end()) {
            return false;
        }
        this->ctrlVarStmtList.erase(it);
    }
    ifStmtSet.insert(stmtId);
    this->ctrlVarStmtList.insert(make_pair(ctrlVarId, ifStmtSet));
    return true;
}

IfTable::IfTable() {
	this->size = 0;
	ifList = unordered_map<int,int>();
}

bool IfTable::setVarToIfStmt(int stmtId, int varId) {
	if (this->ifList.find(stmtId) != this->ifList.end()) {
		return false;
	}
	else {
		this->ifList.insert({ stmtId, varId });
        this->ifStmtSet.insert(stmtId);
		this->size++;
        return this->setCtrlVarUsedByStmt(varId, stmtId);
	}
}

int IfTable::getCtrlVarInIfStmt(int stmtId) {
	auto it = this->ifList.find(stmtId);
	if (it != ifList.end()) {
		return it->second;
	}
	else {
		return INVALID_INDEX;
	}
}

unordered_set<int> IfTable::getStmtWithCtrlVar(int ctrlVarId) {
    unordered_map<int, unordered_set<int>>::iterator it = this->ctrlVarStmtList.find(ctrlVarId);
    unordered_set<int> stmtsWithCtrlVar;
    if (it != this->ctrlVarStmtList.end()) {
        stmtsWithCtrlVar = it->second;
    }
    return stmtsWithCtrlVar;
}

unordered_set<int> IfTable::getAllIfId() {
    return this->ifStmtSet;
}

bool IfTable::isStmtInTable(int stmtId)
{
    for (auto stmtEntry : this->ifList) {
        if (stmtEntry.first == stmtId) {
            return true;
        }
    }
	return false;
}

int IfTable::getSize() {
	return this->size;
}

void IfTable::printContents() {

    cout << "---PRINT IF TABLE---" << endl;

    cout << "StmtId : ControlVarId" << endl;
    for (auto entry : ifList) {
        cout << entry.first << " : " << entry.second << endl;
    }

    cout << "---END PRINT IF TABLE---" << endl;
}