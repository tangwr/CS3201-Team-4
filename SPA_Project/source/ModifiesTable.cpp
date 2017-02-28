#include "ModifiesTable.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

ModifiesTable::ModifiesTable()
{
}

bool ModifiesTable::setStmtModifyVarRel(int stmtId, int varId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
	it = modifiesStmtMap.find(stmtId);
	unordered_set<int> tempSet;
	if (it != modifiesStmtMap.end()) {
//		list = it->second;
//		if (std::find(list.begin(), list.end(), varId) != list.end()) {
			return false;
		}
//		modifiesStmtMap.erase(it);
//	}
	tempSet.insert(varId);
	modifiesStmtMap.insert(make_pair(stmtId, tempSet));
	setStmtModifiedByRel(stmtId, varId);
	return true;
}

bool ModifiesTable::setStmtModifiedByRel(int stmtId, int varId) {
	unordered_map<int, unordered_set<int>>::iterator it;
	it = modifiedByStmtMap.find(varId);
	unordered_set<int> tempSet;
	if (it != modifiedByStmtMap.end()) {
		tempSet = it->second;
        //can be improved, use set native find
		if (std::find(tempSet.begin(), tempSet.end(), stmtId) != tempSet.end()) {
			return false;
		}
		modifiedByStmtMap.erase(it);
	}
	tempSet.insert(stmtId);
	modifiedByStmtMap.insert(make_pair(varId, tempSet));
	return true;
}

bool ModifiesTable::insertStmtModify(int stmtId, int varId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
	it = modifiesStmtMap.find(stmtId);
	unordered_set<int> tempSet;
	if (it != modifiesStmtMap.end()) {
		tempSet = it->second;
		if (std::find(tempSet.begin(), tempSet.end(), varId) != tempSet.end()) {
			return false;
		}
		modifiesStmtMap.erase(it);
	}
	tempSet.insert(varId);
	modifiesStmtMap.insert(make_pair(stmtId, tempSet));
	insertStmtModifiedByRel(stmtId, varId);
}


bool ModifiesTable::insertStmtModifiedByRel(int stmtId, int varId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
	it = modifiedByStmtMap.find(varId);
	unordered_set<int> tempSet;
	if (it != modifiedByStmtMap.end()) {
		tempSet = it->second;
		if (std::find(tempSet.begin(), tempSet.end(), stmtId) != tempSet.end()) {
			return false;
		}
		modifiedByStmtMap.erase(it);
	}
	tempSet.insert(stmtId);
	modifiedByStmtMap.insert(make_pair(varId, tempSet));
	return true;
}

bool ModifiesTable::setProcModifyVarRel(int procId, int varId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
	it = modifiesProcMap.find(procId);
    unordered_set<int> tempSet;
	if (it != modifiesProcMap.end()) {
//		list = it->second;
//		if (std::find(list.begin(), list.end(), procId) != list.end()) {
			return false;
		}
//		modifiesStmtMap.erase(it);
//	}
	tempSet.insert(varId);
	modifiesProcMap.insert(make_pair(procId, tempSet));
	setProcModifiedByRel(procId, varId);
	return true;
}

bool ModifiesTable::setProcModifiedByRel(int procId, int varId) {
	unordered_map<int, unordered_set<int>>::iterator it;
	it = modifiedByProcMap.find(varId);
    unordered_set<int> tempSet;
	if (it != modifiedByProcMap.end()) {
		tempSet = it->second;
		if (std::find(tempSet.begin(), tempSet.end(), procId) != tempSet.end()) {
			return false;
		}
		modifiedByProcMap.erase(it);
	}
	tempSet.insert(procId);
	modifiedByProcMap.insert(make_pair(varId, tempSet));
	return true;
}

bool ModifiesTable::insertProcModify(int procId, int varId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
	it = modifiesProcMap.find(procId);
    unordered_set<int> tempSet;
	if (it != modifiesProcMap.end()) {
		tempSet = it->second;
		if (std::find(tempSet.begin(), tempSet.end(), varId) != tempSet.end()) {
			return false;
		}
		modifiesProcMap.erase(it);
	}
	tempSet.insert(varId);
	modifiesProcMap.insert(make_pair(procId, tempSet));
	insertProcModifiedByRel(procId, varId);
}


bool ModifiesTable::insertProcModifiedByRel(int procId, int varId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
	it = modifiedByProcMap.find(varId);
    unordered_set<int> tempSet;
	if (it != modifiedByProcMap.end()) {
		tempSet = it->second;
		if (std::find(tempSet.begin(), tempSet.end(), procId) != tempSet.end()) {
			return false;
		}
		modifiedByProcMap.erase(it);
	}
	tempSet.insert(procId);
	modifiedByProcMap.insert(make_pair(varId, tempSet));
	return true;
}


/*
int ModifiesTable::insertProcModify(int varNo, int procNo)
{
	if (varNo >= vsize) throw "InvalidVarIndexException";
	for (int t : modifiesProcList.at(varNo)) {
		if (t == procNo) return -1;
	}

	modifiesProcList.at(varNo).push_back(procNo);
	return 1;
}
*/


/*
	return list of stmt that modify the given variable
*/
unordered_set<int> ModifiesTable::getStmtModifyVar(int varId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
    unordered_set<int> resultSet;
	it = modifiedByStmtMap.find(varId);
	if (it != modifiedByStmtMap.end()) {
		resultSet = it->second;
	}
    return resultSet;
}


/*
	return list of variables that is modified in a given stmt
*/
unordered_set<int> ModifiesTable::getVarModifiedInStmt(int stmtId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
    unordered_set<int> resultSet;
	it = modifiesStmtMap.find(stmtId);
	if (it != modifiesStmtMap.end()) {
		resultSet = it->second;
	}
    return resultSet;
}

/*
	return list of procs that modifies given variable
*/
unordered_set<int> ModifiesTable::getProcModifyVar(int varId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
    unordered_set<int> resultSet;
	it = modifiedByProcMap.find(varId);
	if (it != modifiedByProcMap.end()) {
		resultSet = it->second;
	}
    return resultSet;
}

/*
return list of variables that is modified in a given proc
*/
unordered_set<int> ModifiesTable::getVarModifiedInProc(int procId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
    unordered_set<int> resultSet;
	it = modifiesProcMap.find(procId);
	if (it != modifiesProcMap.end()) {
		resultSet = it->second;
	}
    return resultSet;
}


void ModifiesTable::printContents()
{
	cout << "---PRINT MODIFIESTABLE---" << endl;
	for (pair<int, unordered_set<int>> it : modifiesStmtMap) {
		cout << "StmtId: " << it.first;
		cout << " Modifies VarId ";
		//printVector(it.second);
        printUnorderedSet(it.second);
		cout << endl;
	}
	for (pair<int, unordered_set<int>> it : modifiesProcMap) {
		cout << "ProcId: " << it.first;
		cout << " Modifies VarId ";
		//printVector(it.second);
        printUnorderedSet(it.second);
		cout << endl;
	}

	cout << "---END PRINT MODIFIESTABLE---" << endl;
}

void ModifiesTable::printUnorderedSet(unordered_set<int> uSet) {
    for (int element : uSet) {
        cout << element << ' ';
    }
}

void ModifiesTable::printVector(vector<int> vec)
{
	for (int t : vec) {
		cout << t << ' ';
	}
}

//improve efficiency
bool ModifiesTable::checkStmtExist(int stmtId) {
	for (auto stmtEntry : this->modifiesStmtMap) {
		if (stmtEntry.first == stmtId) {
			return true;
		}
	}
	return false;
}

bool ModifiesTable::checkStmtVarRelExist(int stmtId, int varId) {
	unordered_set<int> stmtVarLst = this->getVarModifiedInStmt(stmtId);
    if (stmtVarLst.find(varId) != stmtVarLst.end()) {
        return true;
    }
    else {
        return false;
    }
}

/*
return list of all statements(stmtId) in this table
*/
vector<int> ModifiesTable::getAllStmt() {
	vector<int> stmtVector;
	for (auto stmtEntry : modifiesStmtMap) {
		stmtVector.push_back(stmtEntry.first);
	}
	return stmtVector;
}