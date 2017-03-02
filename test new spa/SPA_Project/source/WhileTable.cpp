#include "WhileTable.h"

using namespace std;


WhileTable::WhileTable() {
	this->size = 0;
}

//returns a vector<int> of all while statements
unordered_set<int> WhileTable::getAllStmtId() {
    unordered_set<int> allWhileStmtList;
    for (auto whileEntry : this->whileList) {
        allWhileStmtList.insert(whileEntry.first);
    }
    return allWhileStmtList;
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

bool WhileTable::setVarToWhileStmt(int stmtId, int varId) {
	if (this->whileList.find(stmtId) != this->whileList.end()) {
		return false;
	}
	else {
		this->whileList.insert({ stmtId, varId });
		this->size++;
		return true;
	}
}

int WhileTable::getVarInWhileStmt(int stmtId) {
	auto it = this->whileList.find(stmtId);
	if (it != whileList.end()) {
		return it->second;
	}
	else {
		return -1;
	}
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

    /*
	cout << "While Table" << endl;
	cout << "====================" << endl;

	for (auto& it : this->whileList)
		cout << it.first << ": " << it.second << endl;

	cout << "====================" << endl;
    */
}