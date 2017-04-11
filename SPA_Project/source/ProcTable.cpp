#pragma once
#include "ProcTable.h"
#include <string>
#include <vector>
#include <unordered_map>

#define INVALID_INDEX -1

using namespace std;

ProcTable::ProcTable(void) {
	ptsize = 0;
}

/*
Insert procedure to procTable.
Return procId if insert success. If procedure already exist, return its existing procId without duplicate insertion.
*/
int ProcTable::insertProc(string procName)
{
	unordered_map<string, int>::iterator it = procMap.find(procName);

	if (it != procMap.end())
		return it->second;
	else
	{
		int procId = ptsize;
		procList.push_back(procName);
		procMap.insert(make_pair(procName, procId));
		ptsize++;
		return procId;   
	}
}

/*
Query the size of procTable i.e. How many procedures exist in the table
Return numbers of existing procedures
*/
int ProcTable::getSize()
{
	return ptsize;
}

/*
Query the procName by procId
Return procName if procId is valid. else return ""
*/
string ProcTable::getProcName(int procId)
{
	if (procId >= ptsize) {
		return "";
	}
	else {
		return procList.at(procId);
	}
}


/*
Query the procId by procName
Return varId if varName is valid, else return -1
*/
int ProcTable::getProcIndex(string procName)
{
	unordered_map<string, int>::iterator it = procMap.find(procName);

	if (it != procMap.end())
		return it->second;
	else 
		return INVALID_INDEX;
}

//given statment, return procedure that contains it, -1 if statement does not exist
int ProcTable::getProcContainStmt(int stmtId) {
    unordered_map<int, int>::iterator it = this->stmtContainedInProcMap.find(stmtId);
    if (it != this->stmtContainedInProcMap.end()) {
        return it->second;
    }
    else {
        return INVALID_INDEX;
    }
}

/*
Sets the relation ship that a proc contains a certain statement.
Also sets statement contained by the proc.
*/
bool ProcTable::setProcToStmtRel(int procId, int stmtId) {
    if (this->stmtContainedInProcMap.find(stmtId) != this->stmtContainedInProcMap.end()) {
        return false;
    }
    else {
        this->stmtContainedInProcMap.insert(make_pair(stmtId, procId));
    }

    unordered_map<int, unordered_set<int>>::iterator it;
    it = procContainsStmtMap.find(procId);
    unordered_set<int> stmtSet;
    if (it != procContainsStmtMap.end()) {
        stmtSet = it->second;
        if (stmtSet.find(stmtId) != stmtSet.end()) {
            return false;
        }
        procContainsStmtMap.erase(it);
    }
    stmtSet.insert(stmtId);
    procContainsStmtMap.insert(make_pair(procId, stmtSet));
    return true;
}

unordered_set<int> ProcTable::getProcStmts(int procId) {
    unordered_map<int, unordered_set<int>>::iterator it;
    unordered_set<int> resultSet;
    it = this->procContainsStmtMap.find(procId);
    if (it != this->procContainsStmtMap.end()) {
        resultSet = it->second;
    }
    return resultSet;
}

unordered_set<int> ProcTable::getAllProcId() {
    unordered_set<int> resultSet;
    for (auto element : procMap) {
        resultSet.insert(element.second);
    }
    return resultSet;
}

bool ProcTable::checkProcExistById(int procId)
{
	if (procId < ptsize)
		return true;
	else
		return false;
}

bool ProcTable::checkProcExistByName(string procName)
{
	unordered_map<string, int>::iterator it = procMap.find(procName);

	if (it != procMap.end())
		return true;
	else
		return false;
}

void ProcTable::printContents()
{
	cout << "---PRINT PROCTABLE---" << endl;

    cout << "ProcId : ProcName" << endl;
	for (pair<string, int> it : procMap) {
        cout << it.second << " : " << it.first << endl;
	}
    cout << endl;

    cout << "StmtId : Direct containing proc" << endl;
    for (pair<int, int> entry : stmtContainedInProcMap) {
        cout << entry.first << " : " << entry.second << endl;
    }
    cout << endl;

    cout << "ProcId : contained stmtId" << endl;
    for (pair<int, unordered_set<int>> entry : procContainsStmtMap) {
        cout << entry.first << " : ";
        printUnorderedSet(entry.second);
        cout << endl;
    }
	cout << "---END PRINT PROCTABLE---" << endl;
}

void ProcTable::printVector(vector<int> vec)
{
	for (int t : vec) {
		cout << t << ' ';
	}
}

void ProcTable::printUnorderedSet(unordered_set<int> uSet) {
    for (int element : uSet) {
        cout << element << ' ';
    }
}