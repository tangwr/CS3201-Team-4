#include "WhileTable.h"

using namespace std;


WhileTable::WhileTable() {
	this->size = 0;
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
	for (auto& it : this->whileList)
		cout << it.first << ": " << it.second << endl;
}