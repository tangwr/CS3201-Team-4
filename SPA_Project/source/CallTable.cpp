#include "CallTable.h"

using namespace std;


CallTable::CallTable() {
	this->size = 0;
}

bool CallTable::setCallProc(int stmtId, int procId) {
	if (this->callList.find(stmtId) == this->callList.end()) {
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

int CallTable::getSize() {
	return this->size;
}

void CallTable::printContents() {
	for (auto& it : this->callList)
		cout << it.first << ": " << it.second << endl;
}