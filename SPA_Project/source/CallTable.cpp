#include "CallTable.h"

using namespace std;


CallTable::CallTable() {
	this->size = 0;
}

bool CallTable::setStmtCallProc(int stmtId, int procId) {
	if (this->stmtCallProcList.find(stmtId) != this->stmtCallProcList.end()) {
		return false;
	}
	else {
		this->stmtCallProcList.insert({stmtId, procId});
		this->size++;
		return true;
	}
}

bool CallTable::setProcCallProc(int callerProcId, int calledProcId) {

    unordered_map<int, unordered_set<int>>::iterator it;
    it = procCallProcList.find(callerProcId);
    unordered_set<int> procSet;//procSet should be empty
    if (it != procCallProcList.end()) {
        procSet = it->second;
        if (procSet.find(calledProcId) != procSet.end()) {
            return false;
        }
        procCallProcList.erase(it);
    }
    procSet.insert(calledProcId);
    procCallProcList.insert(make_pair(callerProcId, procSet));
    return true;
}

int CallTable::getCallProc(int stmtId) {
	auto it = this->stmtCallProcList.find(stmtId);
	if (it != stmtCallProcList.end()) {
		return it->second;
	}
	else {
		return -1;
	}
}

unordered_set<int> CallTable::getProcCallProc(int callerProcId) {
    auto it = this->procCallProcList.find(callerProcId);
    if (it != procCallProcList.end()) {
        return it->second;
    }
    else {
        unordered_set<int> emptySet;
        return emptySet;
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

	for (auto& it : this->stmtCallProcList)
		cout << it.first << ": " << it.second << endl;

	cout << "====================" << endl;
}