#include "WhileTable.h"

using namespace std;


WhileTable::WhileTable() {
	this->size = 0;
}

//returns a vector<int> of all while statements
vector<int> WhileTable::getAllStmtId() {
    vector<int> allWhileStmtList;
    for (auto whileEntry : this->whileList) {
        allWhileStmtList.push_back(whileEntry.first);
    }
    return allWhileStmtList;
}

bool WhileTable::isStmtInTable(int stmtId)
{
	return false;
}

bool WhileTable::setWhileCtrlVar(int stmtId, int varId) {
	if (this->whileList.find(stmtId) != this->whileList.end()) {
		return false;
	}
	else {
		this->whileList.insert({ stmtId, varId });
		this->size++;
		return true;
	}
}

int WhileTable::getWhileCtrlVar(int stmtId) {
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
	cout << "While Table" << endl;
	cout << "====================" << endl;

	for (auto& it : this->whileList)
		cout << it.first << ": " << it.second << endl;

	cout << "====================" << endl;
}