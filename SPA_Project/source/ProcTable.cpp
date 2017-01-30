#include "ProcTable.h"

#include <string>
#include <vector>

using namespace std;

vector<string> procList;
int vsize; // number of procedures in the program

ProcTable::ProcTable(void) {
	vsize = 0;
}

int ProcTable::insertProc(string procName)
{
	for (int idx = 0; idx < vsize; idx++) {
		if (procName.compare(procList.at(idx)) == 0)
			return idx;
	}

	procList.push_back(procName);
	vsize++;
	return vsize - 1;   // index of the procedure in the vector
}

int ProcTable::getSize()
{
	return vsize;
}

string ProcTable::getProcName(int idx)
{
	if (idx >= vsize) throw "InvalidReferenceException";
	else return procList.at(idx);
}

int ProcTable::getProcIndex(string procName)
{
	for (int idx = 0; idx < vsize; idx++) {
		if (procName.compare(procList.at(idx)) == 0)
			return idx;
	}
	return -1;
}

