#include "UsesTable.h"

#include <string>
#include <vector>

using namespace std;

vector<vector<int>> usesStmtList;
vector<vector<int>> usesProcList;
int vsize; // number of procedures in the program

UsesTable::UsesTable(int tsize)
{
	vsize = tsize;
	usesProcList.resize(tsize);
	usesStmtList.resize(tsize);
}

int UsesTable::insertStmtUse(int varNo, int stmtNo)
{
	if (varNo >= vsize) throw "InvalidVarIndexException";
	for (int t : usesStmtList.at(varNo)) {
		if (t == stmtNo) return -1;
	}

	usesStmtList.at(varNo).push_back (stmtNo);
	return 1;
}

int UsesTable::insertProcUse(int varNo, int procNo)
{
	if (varNo >= vsize) throw "InvalidVarIndexException";
	for (int t : usesProcList.at(varNo)) {
		if (t == procNo) return -1;
	}

	usesProcList.at(varNo).push_back(procNo);
	return 1;
}

vector<int> UsesTable::getStmtUse(int varNo)
{
	if (varNo >= vsize) throw "InvalidVarIndexException";
	return usesStmtList.at(varNo);
}

vector<int> UsesTable::getProcUse(int varNo)
{
	if (varNo >= vsize) throw "InvalidVarIndexException";
	return usesProcList.at(varNo);
}

vector<int> UsesTable::getVarUsedByStmt(int stmtNo)
{
	vector<int> tmp;
	for (int i = 0; i < vsize; i++) {
		vector<int> v = usesStmtList.at(i);
		if (std::find(v.begin(), v.end(), stmtNo) != v.end()) {
			/* v contains x */
			tmp.push_back(i);
		}
	}
	return tmp;
}

vector<int> UsesTable::getVarUsedByProc(int procNo)
{
	vector<int> tmp;
	for (int i = 0; i < vsize; i++) {
		vector<int> v = usesProcList.at(i);
		if (std::find(v.begin(), v.end(), procNo) != v.end()) {
			/* v contains x */
			tmp.push_back(i);
		}
	}
	return tmp;
}
