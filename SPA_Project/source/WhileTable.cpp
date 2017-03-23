#include "WhileTable.h"

using namespace std;

bool WhileTable::setStmtToCtrlVar(int varId, int stmtId) {
    unordered_map<int, unordered_set<int>>::iterator it = this->ctrlVarList.find(varId);
    unordered_set<int> stmtSet;
    if (it != this->ctrlVarList.end()) {
        stmtSet = it->second;
        if (stmtSet.find(stmtId) != stmtSet.end()) {
            return false;
        }
        this->ctrlVarList.erase(it);
    }
    stmtSet.insert(stmtId);
    this->ctrlVarList.insert(make_pair(varId, stmtSet));
    return true;
}

WhileTable::WhileTable() {
	this->size = 0;
}

bool WhileTable::setVarToWhileStmt(int stmtId, int varId) {
	if (this->whileList.find(stmtId) != this->whileList.end()) {
		return false;
	}
	else {
		this->whileList.insert({ stmtId, varId });
        this->whileStmtSet.insert(stmtId);
		this->size++;
		//return true;
        return setStmtToCtrlVar(varId, stmtId);
	}
}

int WhileTable::getCtrlVarInWhileStmt(int stmtId) {
	auto it = this->whileList.find(stmtId);
	if (it != whileList.end()) {
		return it->second;
	}
	else {
		return -1;
	}
}

unordered_set<int> WhileTable::getStmtWithCtrlVar(int varId) {
    unordered_map<int, unordered_set<int>>::iterator it = this->ctrlVarList.find(varId);
    //unordered_set<int> stmtSet = unordered_set<int>();
    if (it != this->ctrlVarList.end()) {
        return it->second;
    }
    else {
        return unordered_set<int>();
    }
}

//returns a vector<int> of all while statements
unordered_set<int> WhileTable::getAllStmtId() {
    return this->whileStmtSet;
    /*
    unordered_set<int> allWhileStmtList;
    for (auto whileEntry : this->whileList) {
        allWhileStmtList.insert(whileEntry.first);
    }
    return allWhileStmtList;
    */
}

bool WhileTable::isStmtInTable(int stmtId)
{
    for (auto stmtEntry : this->whileList) {
        if (stmtEntry.first == stmtId) {
            return true;
        }
    }
    return false;
}

int WhileTable::getSize() {
	return this->size;
}

void WhileTable::printContents() {
    cout << "---PRINT WHILE TABLE---" << endl;

    cout << "StmtId : ControlVarId" << endl;
    for (auto entry : whileList) {
        cout << entry.first << " : " << entry.second << endl;
    }

    cout << "---END PRINT WHILE TABLE---" << endl;
}