#include "ModifiesTable.h"

#include <string>
#include <vector>

using namespace std;

vector<vector<int>> modifiesStmtList;
vector<vector<int>> modifiesProcList;
int vsize; // number of procedures in the program

ModifiesTable::ModifiesTable(int tsize)
{
	vsize = tsize;
	modifiesProcList.resize(tsize);
	modifiesStmtList.resize(tsize);
}

int ModifiesTable::insertStmtModify(int varNo, int stmtNo)
{
	if (varNo >= vsize) throw "InvalidVarIndexException";
	for (int t : modifiesStmtList.at(varNo)) {
		if (t == stmtNo) return -1;
	}

	modifiesStmtList.at(varNo).push_back(stmtNo);
	return 1;
}

int ModifiesTable::insertProcModify(int varNo, int procNo)
{
	if (varNo >= vsize) throw "InvalidVarIndexException";
	for (int t : modifiesProcList.at(varNo)) {
		if (t == procNo) return -1;
	}

	modifiesProcList.at(varNo).push_back(procNo);
	return 1;
}

vector<int> ModifiesTable::getStmtModify(int varNo)
{
	if (varNo >= vsize) throw "InvalidVarIndexException";
	return modifiesStmtList.at(varNo);
}

vector<int> ModifiesTable::getProcModify(int varNo)
{
	if (varNo >= vsize) throw "InvalidVarIndexException";
	return modifiesProcList.at(varNo);
}

vector<int> ModifiesTable::getVarModifiedByStmt(int stmtNo)
{
	vector<int> tmp;
	for (int i = 0; i < vsize; i++) {
		vector<int> v = modifiesStmtList.at(i);
		if (std::find(v.begin(), v.end(), stmtNo) != v.end()) {
			/* v contains x */
			tmp.push_back(i);
		}
	}
	return tmp;
}

vector<int> ModifiesTable::getVarModifiedByProc(int procNo)
{
		vector<int> tmp;
	for (int i = 0; i < vsize; i++) {
		vector<int> v = modifiesProcList.at(i);
		if (std::find(v.begin(), v.end(), procNo) != v.end()) {
			/* v contains x */
			tmp.push_back(i);
		}
	}
	return tmp;
}
