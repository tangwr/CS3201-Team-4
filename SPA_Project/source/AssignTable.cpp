#include "AssignTable.h"

using namespace std;

AssignTable::AssignTable() {
	size = 0;
}

//returns a vector<int> of all assign statement Id
unordered_set<int> AssignTable::getAllStmtId() {
    unordered_set<int> allAssignStmtSet;
    for (auto assignEntry : this->assignList) {
        allAssignStmtSet.insert(assignEntry.first);
    }
    return allAssignStmtSet;
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

bool AssignTable::setExpToAssignStmt(int stmtId, string exp) {
	if (this->assignList.find(stmtId) != this->assignList.end()) {
		return false;
	}
	else {
		this->assignList.insert({ stmtId, exp });
		this->size++;
		return true;
	}
}

string AssignTable::getExpInAssignStmt(int stmtId) {
	auto it = this->assignList.find(stmtId);
	if (it != assignList.end()) {
		return it->second;
	}
	else {
		return "";
	}
}

int AssignTable::getSize() {
	return this->size;
}

void AssignTable::printContents() {
	cout << "Assign Table" << endl;
	cout << "====================" << endl;

	for (auto& it : this->assignList)
		cout << it.first << ": " << it.second << endl;

	cout << "====================" << endl;
}
