#include "UsesTable.h"

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

UsesTable::UsesTable()
{
}

bool UsesTable::setStmtUseVarRel(int stmtId, int varId)
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
	setStmtUsedByRel(stmtId, varId);
	return true;
}

bool UsesTable::setStmtUsedByRel(int stmtId, int varId) {
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

bool UsesTable::insertStmtUseRel(int stmtId, int varId)
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
	insertStmtUsedByRel(stmtId, varId);
	return true;
}

bool UsesTable::insertStmtUsedByRel(int stmtId, int varId) {
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

bool UsesTable::setProcUseVarRel(int procId, int varId)
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
	setProcUsedByRel(procId, varId);
	return true;
}

bool UsesTable::setProcUsedByRel(int procId, int varId) {
	unordered_map<int, vector<int>>::iterator it;
	it = vUsedByProcMap.find(varId);
	vector<int> list;
	if (it != vUsedByProcMap.end()) {
		list = it->second;
		if (std::find(list.begin(), list.end(), procId) != list.end()) {
			return false;
		}
		vUsedByProcMap.erase(it);
	}
	list.push_back(procId);
	vUsedByProcMap.insert(make_pair(varId, list));
	return true;
}

bool UsesTable::insertProcUseRel(int procId, int varId)
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
	insertProcUsedByRel(procId, varId);
	return true;
}

bool UsesTable::insertProcUsedByRel(int procId, int varId) {
	unordered_map<int, vector<int>>::iterator it;
	it = vUsedByProcMap.find(varId);
	vector<int> list;
	if (it != vUsedByProcMap.end()) {
		list = it->second;
		if (std::find(list.begin(), list.end(), procId) != list.end()) {
			return false;
		}
		vUsedByProcMap.erase(it);
	}
	list.push_back(procId);
	vUsedByProcMap.insert(make_pair(varId, list));
	return true;
}
 
// function for constant
bool UsesTable::setStmtUseConstRel(int stmtId, int varId)
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
	setStmtUsedByRelConst(stmtId, varId);
	return true;
}

bool UsesTable::setStmtUsedByRelConst(int stmtId, int varId) {
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



bool UsesTable::setProcUseConstRel(int procId, int varId)
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
	setProcUsedByRelConst(procId, varId);
	return true;
}


bool UsesTable::setProcUsedByRelConst(int procId, int varId) {
	unordered_map<int, vector<int>>::iterator it;
	it = cUsedByProcMap.find(varId);
	vector<int> list;
	if (it != cUsedByProcMap.end()) {
		list = it->second;
		if (std::find(list.begin(), list.end(), procId) != list.end()) {
			return false;
		}
		cUsedByProcMap.erase(it);
	}
	list.push_back(procId);
	cUsedByProcMap.insert(make_pair(varId, list));
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

vector<int> UsesTable::getStmtUseVar(int varId)
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

vector<int> UsesTable::getProcUseVar(int varId)
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

vector<int> UsesTable::getStmtUseConst(int varId)
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

vector<int> UsesTable::getProcUseConst(int varId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = cUsedByProcMap.find(varId);
	if (it != cUsedByProcMap.end()) {
		return it->second;
	}
	return vector<int>();
}

void UsesTable::printContents()
{
	cout << "---PRINT USESTABLE---" << endl;
	for (pair<int, vector<int>> it : vUsesStmtMap) {
		cout << "StmtId: " << it.first;
		cout << " Uses VarId ";
		printVector(it.second);
		cout << endl;
	}
	for (pair<int, vector<int>> it : cUsesStmtMap) {
		cout << "StmtId: " << it.first;
		cout << " Uses ConstId ";
		printVector(it.second);
		cout << endl;
	}
	for (pair<int, vector<int>> it : vUsesProcMap) {
		cout << "ProcId: " << it.first;
		cout << " Uses VarId ";
		printVector(it.second);
		cout << endl;
	}
	for (pair<int, vector<int>> it : cUsesProcMap) {
		cout << "ProcId: " << it.first;
		cout << " Uses ConstId ";
		printVector(it.second);
		cout << endl;
	}

	cout << "---END PRINT USESTABLE---" << endl;
}

void UsesTable::printVector(vector<int> vec)
{
	for (int t : vec) {
		cout << t << ' ';
	}
}

vector<int> UsesTable::getAllStmt() {
	vector<int> allUsesStmtLst;
	for (auto entry : vUsesStmtMap) {
		allUsesStmtLst.push_back(entry.first);
	}
	return allUsesStmtLst;
}
bool UsesTable::checkStmtExist(int stmtId) {
	for (auto entry : this->vUsesStmtMap) {
		if (entry.first == stmtId) {
			return true;
		}
	}
	return false;
}
bool UsesTable::checkStmtVarRelExist(int stmtId, int varId) {
	vector<int> stmtVarIdLst = this->getVarUsedByStmt(stmtId);
	for (int varEntry : stmtVarIdLst) {
		if (varEntry == varId) {
			return true;
		}
	}
	return false;
}

