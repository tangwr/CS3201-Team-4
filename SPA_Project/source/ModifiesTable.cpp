#include "ModifiesTable.h"

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<int, vector<int>> modifiesStmtMap, modifiedByStmtMap;
unordered_map<int, vector<int>> modifiesProcMap, modifiedByProcMap;

ModifiesTable::ModifiesTable(int tsize)
{
}

bool ModifiesTable::setModifyDirectRel(int stmtId, int varId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = modifiesStmtMap.find(stmtId);
	vector<int> list;
	if (it != modifiesStmtMap.end()) {
		list = it->second;
		if (std::find(list.begin(), list.end(), varId) != list.end()) {
			return false;
		}
		modifiesStmtMap.erase(it);
	}
	list.push_back(varId);
	modifiesStmtMap.insert(make_pair(stmtId, list));
	setModifiedByDirectRel(stmtId, varId);
	return true;
}

bool ModifiesTable::setModifiedByDirectRel(int stmtId, int varId) {
	unordered_map<int, vector<int>>::iterator it;
	it = modifiedByStmtMap.find(varId);
	vector<int> list;
	if (it != modifiedByStmtMap.end()) {
		list = it->second;
		if (std::find(list.begin(), list.end(), stmtId) != list.end()) {
			return false;
		}
		modifiedByStmtMap.erase(it);
	}
	list.push_back(stmtId);
	modifiedByStmtMap.insert(make_pair(varId, list));
	return true;
}

bool ModifiesTable::setModifyDirectRelProc(int procId, int varId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = modifiesStmtMap.find(procId);
	vector<int> list;
	if (it != modifiesStmtMap.end()) {
		list = it->second;
		if (std::find(list.begin(), list.end(), procId) != list.end()) {
			return false;
		}
		modifiesStmtMap.erase(it);
	}
	list.push_back(varId);
	modifiesStmtMap.insert(make_pair(procId, list));
	setModifiedByDirectRelProc(procId, varId);
	return true;
}

bool ModifiesTable::setModifiedByDirectRelProc(int procId, int varId) {
	unordered_map<int, vector<int>>::iterator it;
	it = modifiedByStmtMap.find(varId);
	vector<int> list;
	if (it != modifiedByStmtMap.end()) {
		list = it->second;
		if (std::find(list.begin(), list.end(), procId) != list.end()) {
			return false;
		}
		modifiedByStmtMap.erase(it);
	}
	list.push_back(procId);
	modifiedByStmtMap.insert(make_pair(varId, list));
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
vector<int> ModifiesTable::getModifiedByStmt(int varId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = modifiedByStmtMap.find(varId);
	if (it != modifiedByStmtMap.end()) {
		return it->second;
	}
	return vector<int>();
}


/*
	return list of variables that is modified in a given stmt
*/
vector<int> ModifiesTable::getStmtModify(int stmtId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = modifiesStmtMap.find(stmtId);
	if (it != modifiesStmtMap.end()) {
		return it->second;
	}
	return vector<int>();
}

/*
	return list of procs that modifies given variable
*/
vector<int> ModifiesTable::getModifiedByProc(int varId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = modifiedByProcMap.find(varId);
	if (it != modifiedByProcMap.end()) {
		return it->second;
	}
	return vector<int>();
}

/*
return list of variables that is modified in a given proc
*/
vector<int> ModifiesTable::getProcModify(int procId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = modifiesProcMap.find(procId);
	if (it != modifiesProcMap.end()) {
		return it->second;
	}
	return vector<int>();
}
