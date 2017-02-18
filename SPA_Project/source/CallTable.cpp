#include "CallTable.h"

using namespace std;


CallTable::CallTable() {
	this->size = 0;
}

bool CallTable::setStmtCallProc(int stmtId, int procId) {
	if (this->callList.find(stmtId) != this->callList.end()) {
		return false;
	}
	else {
		this->callList.insert({stmtId, procId});
		this->size++;
		return true;
	}
}

int CallTable::getCallProc(int stmtId) {
	auto it = this->callList.find(stmtId);
	if (it != callList.end()) {
		return it->second;
	}
	else {
		return -1;
	}
}

bool CallTable::isStmtInTable(int stmtId)
{
	return false;
}

int CallTable::getSize() {
	return this->size;
}

void CallTable::printContents() {
	cout << "Call Table" << endl;
	cout << "====================" << endl;

	for (auto& it : this->callList)
		cout << it.first << ": " << it.second << endl;

	cout << "====================" << endl;
}