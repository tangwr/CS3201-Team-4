#include "IfTable.h"

using namespace std;


IfTable::IfTable() {
	this->size = 0;
}

bool IfTable::setIfCtrlVar(int stmtId, int varId) {
	if (this->ifList.find(stmtId) == this->ifList.end()) {
		return false;
	}
	else {
		this->ifList.insert({ stmtId, varId });
		this->size++;
		return true;
	}
}

int IfTable::getIfCtrlVar(int stmtId) {
	auto it = this->ifList.find(stmtId);
	if (it != ifList.end()) {
		return it->second;
	}
	else {
		return -1;
	}
}

int IfTable::getSize() {
	return this->size;
}

void IfTable::printContents() {
	for (auto& it : this->ifList)
		cout << it.first << ": " << it.second << endl;
}