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
	unordered_map<int, unordered_set<int>>::iterator it;
	it = vUsesStmtMap.find(stmtId);
    unordered_set<int> variableSet;
	if (it != vUsesStmtMap.end()) {
		variableSet = it->second;
		if (std::find(variableSet.begin(), variableSet.end(), varId) != variableSet.end()) {
			return false;
		}
		vUsesStmtMap.erase(it);
	}
	variableSet.insert(varId);
	vUsesStmtMap.insert(make_pair(stmtId, variableSet));
	setStmtUsedByRel(stmtId, varId);
	return true;
}

bool UsesTable::setStmtUsedByRel(int stmtId, int varId) {
	unordered_map<int, unordered_set<int>>::iterator it;
	it = vUsedByStmtMap.find(varId);
    unordered_set<int> statementSet;
	if (it != vUsedByStmtMap.end()) {
		statementSet = it->second;
		if (std::find(statementSet.begin(), statementSet.end(), stmtId) != statementSet.end()) {
			return false;
		}
		vUsedByStmtMap.erase(it);
	}
	statementSet.insert(stmtId);
	vUsedByStmtMap.insert(make_pair(varId, statementSet));
	return true;
}

bool UsesTable::insertStmtUseRel(int stmtId, int varId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
	it = vUsesStmtMap.find(stmtId);
    unordered_set<int> variableSet;
	if (it != vUsesStmtMap.end()) {
		variableSet = it->second;
		if (std::find(variableSet.begin(), variableSet.end(), varId) != variableSet.end()) {
			return false;
		}
		vUsesStmtMap.erase(it);
	}
	variableSet.insert(varId);
	vUsesStmtMap.insert(make_pair(stmtId, variableSet));
	insertStmtUsedByRel(stmtId, varId);
	return true;
}

bool UsesTable::insertStmtUsedByRel(int stmtId, int varId) {
	unordered_map<int, unordered_set<int>>::iterator it;
	it = vUsedByStmtMap.find(varId);
    unordered_set<int> statementSet;
	if (it != vUsedByStmtMap.end()) {
		statementSet = it->second;
		if (std::find(statementSet.begin(), statementSet.end(), stmtId) != statementSet.end()) {
			return false;
		}
		vUsedByStmtMap.erase(it);
	}
	statementSet.insert(stmtId);
	vUsedByStmtMap.insert(make_pair(varId, statementSet));
	return true;
}

bool UsesTable::setProcUseVarRel(int procId, int varId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
	it = vUsesProcMap.find(procId);
    unordered_set<int> variableSet;
	if (it != vUsesProcMap.end()) {
		variableSet = it->second;
		if (std::find(variableSet.begin(), variableSet.end(), varId) != variableSet.end()) {
			return false;
		}
		vUsesProcMap.erase(it);
	}
	variableSet.insert(varId);
	vUsesProcMap.insert(make_pair(procId, variableSet));
	setProcUsedByRel(procId, varId);
	return true;
}

bool UsesTable::setProcUsedByRel(int procId, int varId) {
	unordered_map<int, unordered_set<int>>::iterator it;
	it = vUsedByProcMap.find(varId);
    unordered_set<int> procedureSet;
	if (it != vUsedByProcMap.end()) {
		procedureSet = it->second;
		if (std::find(procedureSet.begin(), procedureSet.end(), procId) != procedureSet.end()) {
			return false;
		}
		vUsedByProcMap.erase(it);
	}
	procedureSet.insert(procId);
	vUsedByProcMap.insert(make_pair(varId, procedureSet));
	return true;
}

bool UsesTable::insertProcUseRel(int procId, int varId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
	it = vUsesProcMap.find(procId);
    unordered_set<int> variableSet;
	if (it != vUsesProcMap.end()) {
		variableSet = it->second;
		if (std::find(variableSet.begin(), variableSet.end(), varId) != variableSet.end()) {
			return false;
		}
		vUsesProcMap.erase(it);
	}
	variableSet.insert(varId);
	vUsesProcMap.insert(make_pair(procId, variableSet));
	insertProcUsedByRel(procId, varId);
	return true;
}

bool UsesTable::insertProcUsedByRel(int procId, int varId) {
	unordered_map<int, unordered_set<int>>::iterator it;
	it = vUsedByProcMap.find(varId);
    unordered_set<int> procedureSet;
	if (it != vUsedByProcMap.end()) {
		procedureSet = it->second;
		if (std::find(procedureSet.begin(), procedureSet.end(), procId) != procedureSet.end()) {
			return false;
		}
		vUsedByProcMap.erase(it);
	}
	procedureSet.insert(procId);
	vUsedByProcMap.insert(make_pair(varId, procedureSet));
	return true;
}
 
// function for constant
bool UsesTable::setStmtUseConstRel(int stmtId, int varId)//varId or constId?
{
	unordered_map<int, unordered_set<int>>::iterator it;
	it = cUsesStmtMap.find(stmtId);
    unordered_set<int> constantSet;
	if (it != cUsesStmtMap.end()) {
		constantSet = it->second;
		if (std::find(constantSet.begin(), constantSet.end(), varId) != constantSet.end()) {
			return false;
		}
		cUsesStmtMap.erase(it);
	}
	constantSet.insert(varId);
	cUsesStmtMap.insert(make_pair(stmtId, constantSet));
	setStmtUsedByRelConst(stmtId, varId);
	return true;
}

bool UsesTable::setStmtUsedByRelConst(int stmtId, int varId) {
	unordered_map<int, unordered_set<int>>::iterator it;
	it = cUsedByStmtMap.find(varId);
    unordered_set<int> statementSet;
	if (it != cUsedByStmtMap.end()) {
		statementSet = it->second;
		if (std::find(statementSet.begin(), statementSet.end(), stmtId) != statementSet.end()) {
			return false;
		}
		cUsedByStmtMap.erase(it);
	}
	statementSet.insert(stmtId);
	cUsedByStmtMap.insert(make_pair(varId, statementSet));
	return true;
}



bool UsesTable::setProcUseConstRel(int procId, int varId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
	it = cUsesProcMap.find(procId);
    unordered_set<int> constantSet;
	if (it != cUsesProcMap.end()) {
		constantSet = it->second;
		if (std::find(constantSet.begin(), constantSet.end(), varId) != constantSet.end()) {
			return false;
		}
		cUsesProcMap.erase(it);
	}
	constantSet.insert(varId);
	cUsesProcMap.insert(make_pair(procId, constantSet));
	setProcUsedByRelConst(procId, varId);
	return true;
}


bool UsesTable::setProcUsedByRelConst(int procId, int varId) {
	unordered_map<int, unordered_set<int>>::iterator it;
	it = cUsedByProcMap.find(varId);
    unordered_set<int> procedureSet;
	if (it != cUsedByProcMap.end()) {
		procedureSet = it->second;
		if (std::find(procedureSet.begin(), procedureSet.end(), procId) != procedureSet.end()) {
			return false;
		}
		cUsedByProcMap.erase(it);
	}
	procedureSet.insert(procId);
	cUsedByProcMap.insert(make_pair(varId, procedureSet));
	return true;
}


vector<int> UsesTable::getVarUsedByStmt(int stmtId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
	it = vUsesStmtMap.find(stmtId);
	if (it != vUsesStmtMap.end()) {
		//return it->second;
        return vector<int>(it->second.begin(), it->second.end());
	}
	return vector<int>();
}

vector<int> UsesTable::getStmtUseVar(int varId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
	it = vUsedByStmtMap.find(varId);
	if (it != vUsedByStmtMap.end()) {
		//return it->second;
        return vector<int>(it->second.begin(), it->second.end());
	}
	return vector<int>();
}

vector<int> UsesTable::getVarUsedByProc(int procId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
	it = vUsesProcMap.find(procId);
	if (it != vUsesProcMap.end()) {
		//return it->second;
        return vector<int>(it->second.begin(), it->second.end());
	}
	return vector<int>();
}

vector<int> UsesTable::getProcUseVar(int varId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
	it = vUsedByProcMap.find(varId);
	if (it != vUsedByProcMap.end()) {
		//return it->second;
        return vector<int>(it->second.begin(), it->second.end());
	}
	return vector<int>();
}

vector<int> UsesTable::getConstUsedByStmt(int stmtId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
	it = cUsesStmtMap.find(stmtId);
	if (it != cUsesStmtMap.end()) {
		//return it->second;
        return vector<int>(it->second.begin(), it->second.end());
	}
	return vector<int>();
}

vector<int> UsesTable::getStmtUseConst(int varId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
	it = cUsedByStmtMap.find(varId);
	if (it != cUsedByStmtMap.end()) {
		//return it->second;
        return vector<int>(it->second.begin(), it->second.end());
	}
	return vector<int>();
}

vector<int> UsesTable::getConstUsedByProc(int procId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
	it = cUsesProcMap.find(procId);
	if (it != cUsesProcMap.end()) {
		//return it->second;
        return vector<int>(it->second.begin(), it->second.end());
	}
	return vector<int>();
}

vector<int> UsesTable::getProcUseConst(int varId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
	it = cUsedByProcMap.find(varId);
	if (it != cUsedByProcMap.end()) {
		//return it->second;
        return vector<int>(it->second.begin(), it->second.end());
	}
	return vector<int>();
}

void UsesTable::printContents()
{
	cout << "---PRINT USESTABLE---" << endl;
	for (pair<int, unordered_set<int>> it : vUsesStmtMap) {
		cout << "StmtId: " << it.first;
		cout << " Uses VarId ";
        printUnorderedSet(it.second);
		cout << endl;
	}
	for (pair<int, unordered_set<int>> it : cUsesStmtMap) {
		cout << "StmtId: " << it.first;
		cout << " Uses ConstId ";
        printUnorderedSet(it.second);
		cout << endl;
	}
	for (pair<int, unordered_set<int>> it : vUsesProcMap) {
		cout << "ProcId: " << it.first;
		cout << " Uses VarId ";
        printUnorderedSet(it.second);
		cout << endl;
	}
	for (pair<int, unordered_set<int>> it : cUsesProcMap) {
		cout << "ProcId: " << it.first;
		cout << " Uses ConstId ";
        printUnorderedSet(it.second);
		cout << endl;
	}

	cout << "---END PRINT USESTABLE---" << endl;
}

void UsesTable::printUnorderedSet(unordered_set<int> uSet) {
    for (int element : uSet) {
        cout << element << ' ';
    }
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

