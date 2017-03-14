#include "CallTable.h"

using namespace std;


CallTable::CallTable() {
	this->size = 0;
}

bool CallTable::setStmtCallProcRel(int stmtId, int procId) {
	if (this->stmtCallProcList.find(stmtId) != this->stmtCallProcList.end()) {
		return false;
	}
	else {
		this->stmtCallProcList.insert({stmtId, procId});
		this->size++;
		return true;
	}
}

bool CallTable::setProcCallProcRel(int callerProcId, int calledProcId) {

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

bool CallTable::insertProcCallStarProcRel(int callerProcId, int calledStarProcId) {
    unordered_map<int, unordered_set<int>>::iterator it;
    it = procCallStarProcList.find(callerProcId);
    unordered_set<int> procSet;//procSet should be empty
    if (it != procCallStarProcList.end()) {
        procSet = it->second;
        if (procSet.find(calledStarProcId) != procSet.end()) {
            return false;
        }
        procCallStarProcList.erase(it);
    }
    procSet.insert(calledStarProcId);
    procCallStarProcList.insert(make_pair(callerProcId, procSet));
    return true;

}


int CallTable::getProcCalledByStmt(int stmtId) {
	auto it = this->stmtCallProcList.find(stmtId);
	if (it != stmtCallProcList.end()) {
		return it->second;
	}
	else {
		return -1;
	}
}

unordered_set<int> CallTable::getProcCalledByProc(int callerProcId) {
    auto it = this->procCallProcList.find(callerProcId);
    if (it != procCallProcList.end()) {
        return it->second;
    }
    else {
        unordered_set<int> emptySet;
        return emptySet;
    }
}

unordered_set<int> CallTable::getProcCalledByStarProc(int callerProcId) {
    unordered_map<int, unordered_set<int>>::iterator it = this->procCallStarProcList.find(callerProcId);
    if (it != procCallStarProcList.end()) {
        return it->second;
    }
    else {
        unordered_set<int> emptySet;
        return emptySet;
    }
}


unordered_set<int> CallTable::getAllCallId() {
    unordered_set<int> resultSet;
    for (auto entry : stmtCallProcList) {
        resultSet.insert(entry.first);
    }
    return resultSet;
}

bool CallTable::isStmtInTable(int stmtId) {
	if (stmtCallProcList.find(stmtId) == stmtCallProcList.end()) {
		return false;
	}
	return true;
}

int CallTable::getSize() {
	return this->size;
}

void CallTable::printUnorderedSet(unordered_set<int> uSet) {
    for (int element : uSet) {
        cout << element << ' ';
    }
}

void CallTable::printContents() {

    cout << "---PRINT CALL TABLE---" << endl;

    cout << "StmtId : ProcId" << endl;
    for (auto entry : stmtCallProcList) {
        cout << entry.first << " : " << entry.second << endl;
    }
    cout << endl;

    cout << "Caller ProcId : Called ProcId" << endl;
    for (auto entry : procCallProcList) {
        cout << entry.first << " : ";
        printUnorderedSet(entry.second);
        cout << endl;
    }
    cout << endl;

    cout << "---END PRINT CALL TABLE---" << endl;
    /*
	cout << "Call Table" << endl;
	cout << "====================" << endl;

	for (auto& it : this->stmtCallProcList)
		cout << it.first << ": " << it.second << endl;

	cout << "====================" << endl;
    */
}