#include "UsesTable.h"

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;


unordered_map<int, vector<int>> vUsesStmtMap;
unordered_map<int, vector<int>> vUsesProcMap;
unordered_map<int, vector<int>> vUsedByStmtMap;
unordered_map<int, vector<int>> vUsedByProcMap;

unordered_map<int, vector<int>> cUsesStmtMap;
unordered_map<int, vector<int>> cUsesProcMap;
unordered_map<int, vector<int>> cUsedByStmtMap;
unordered_map<int, vector<int>> cUsedByProcMap;

UsesTable::UsesTable()
{
}

bool UsesTable::setUseDirectRel(int stmtId, int varId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = vUsesStmtMap.find(stmtId);
	vector<int> list;
	if (it != vUsesStmtMap.end()) {
		list = it->second;
		if (std::find(list.begin(), list.end(), varId) != list.end()) {
			return false;
		}
		vUsesStmtMap.erase(it);
	}
	list.push_back(varId);
	vUsesStmtMap.insert(make_pair(stmtId, list));
	setUsedByDirectRel(stmtId, varId);
	return true;
}

bool UsesTable::setUsedByDirectRel(int stmtId, int varId) {
	unordered_map<int, vector<int>>::iterator it;
	it = vUsedByStmtMap.find(varId);
	vector<int> list;
	if (it != vUsedByStmtMap.end()) {
		list = it->second;
		if (std::find(list.begin(), list.end(), stmtId) != list.end()) {
			return false;
		}
		vUsedByStmtMap.erase(it);
	}
	list.push_back(stmtId);
	vUsedByStmtMap.insert(make_pair(varId, list));
	return true;
}



bool UsesTable::setUseDirectRelProc(int procId, int varId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = vUsesProcMap.find(procId);
	vector<int> list;
	if (it != vUsesProcMap.end()) {
		list = it->second;
		if (std::find(list.begin(), list.end(), varId) != list.end()) {
			return false;
		}
		vUsesProcMap.erase(it);
	}
	list.push_back(varId);
	vUsesProcMap.insert(make_pair(procId, list));
	setUsedByDirectRelProc(procId, varId);
	return true;
}

bool UsesTable::setUsedByDirectRelProc(int procId, int varId) {
	unordered_map<int, vector<int>>::iterator it;
	it = vUsedByStmtMap.find(varId);
	vector<int> list;
	if (it != vUsedByStmtMap.end()) {
		list = it->second;
		if (std::find(list.begin(), list.end(), procId) != list.end()) {
			return false;
		}
		vUsedByStmtMap.erase(it);
	}
	list.push_back(procId);
	vUsedByStmtMap.insert(make_pair(varId, list));
	return true;
}
 
// function for constant
bool UsesTable::setUseDirectRelConst(int stmtId, int varId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = cUsesStmtMap.find(stmtId);
	vector<int> list;
	if (it != cUsesStmtMap.end()) {
		list = it->second;
		if (std::find(list.begin(), list.end(), varId) != list.end()) {
			return false;
		}
		cUsesStmtMap.erase(it);
	}
	list.push_back(varId);
	cUsesStmtMap.insert(make_pair(stmtId, list));
	setUsedByDirectRelConst(stmtId, varId);
	return true;
}

bool UsesTable::setUsedByDirectRelConst(int stmtId, int varId) {
	unordered_map<int, vector<int>>::iterator it;
	it = cUsedByStmtMap.find(varId);
	vector<int> list;
	if (it != cUsedByStmtMap.end()) {
		list = it->second;
		if (std::find(list.begin(), list.end(), stmtId) != list.end()) {
			return false;
		}
		cUsedByStmtMap.erase(it);
	}
	list.push_back(stmtId);
	cUsedByStmtMap.insert(make_pair(varId, list));
	return true;
}



bool UsesTable::setUseDirectRelConstProc(int procId, int varId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = cUsesProcMap.find(procId);
	vector<int> list;
	if (it != cUsesProcMap.end()) {
		list = it->second;
		if (std::find(list.begin(), list.end(), varId) != list.end()) {
			return false;
		}
		cUsesProcMap.erase(it);
	}
	list.push_back(varId);
	cUsesProcMap.insert(make_pair(procId, list));
	setUsedByDirectRelConstProc(procId, varId);
	return true;
}


bool UsesTable::setUsedByDirectRelConstProc(int procId, int varId) {
	unordered_map<int, vector<int>>::iterator it;
	it = cUsedByStmtMap.find(varId);
	vector<int> list;
	if (it != cUsedByStmtMap.end()) {
		list = it->second;
		if (std::find(list.begin(), list.end(), procId) != list.end()) {
			return false;
		}
		cUsedByStmtMap.erase(it);
	}
	list.push_back(procId);
	cUsedByStmtMap.insert(make_pair(varId, list));
	return true;
}


vector<int> UsesTable::getVarUsedByStmt(int stmtId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = vUsesStmtMap.find(stmtId);
	if (it != vUsesStmtMap.end()) {
		return it->second;
	}
	return vector<int>();
}

vector<int> UsesTable::getStmtUsesVar(int varId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = vUsedByStmtMap.find(varId);
	if (it != vUsedByStmtMap.end()) {
		return it->second;
	}
	return vector<int>();
}

vector<int> UsesTable::getVarUsedByProc(int procId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = vUsesProcMap.find(procId);
	if (it != vUsesProcMap.end()) {
		return it->second;
	}
	return vector<int>();
}

vector<int> UsesTable::getProcUsesVar(int varId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = vUsedByProcMap.find(varId);
	if (it != vUsedByProcMap.end()) {
		return it->second;
	}
	return vector<int>();
}

vector<int> UsesTable::getConstUsedByStmt(int stmtId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = cUsesStmtMap.find(stmtId);
	if (it != cUsesStmtMap.end()) {
		return it->second;
	}
	return vector<int>();
}

vector<int> UsesTable::getStmtUsesConst(int varId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = cUsedByStmtMap.find(varId);
	if (it != cUsedByStmtMap.end()) {
		return it->second;
	}
	return vector<int>();
}

vector<int> UsesTable::getConstUsedByProc(int procId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = cUsesProcMap.find(procId);
	if (it != cUsesProcMap.end()) {
		return it->second;
	}
	return vector<int>();
}

vector<int> UsesTable::getProcUsesConst(int varId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = cUsedByProcMap.find(varId);
	if (it != cUsedByProcMap.end()) {
		return it->second;
	}
	return vector<int>();
}

