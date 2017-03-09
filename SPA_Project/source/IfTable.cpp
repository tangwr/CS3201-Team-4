#include "IfTable.h"

using namespace std;


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
		this->size++;
		return true;
	}
}

int IfTable::getCtrlVarInIfStmt(int stmtId) {
	auto it = this->ifList.find(stmtId);
	if (it != ifList.end()) {
		return it->second;
	}
	else {
		return -1;
	}
}

unordered_set<int> IfTable::getAllIfId() {
    unordered_set<int> resultSet;
    for (auto entry : ifList) {
        resultSet.insert(entry.first);
    }
    return resultSet;
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
    /*
	cout << "If Table" << endl;
	cout << "====================" << endl;

	for (auto& it : this->ifList)
		cout << it.first << ": " << it.second << endl;

	cout << "====================" << endl;
    */
}