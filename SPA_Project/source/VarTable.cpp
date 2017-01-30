#include "VarTable.h"

#include <string>
#include <vector>

using namespace std;

vector<string> varList;
int vsize; // number of variables in the program

VarTable::VarTable(void) {
	vsize = 0;
}

int VarTable::insertVar(string varName)
{
	for (int idx = 0; idx < vsize; idx++) {
		if (varName.compare(varList.at(idx)) == 0)
			return idx;
	}

	varList.push_back(varName);
	vsize++;
	return vsize - 1;   // index of the variable in the vector
}

int VarTable::getSize()
{
	return vsize;
}

string VarTable::getVarName(int idx)
{
	if (idx >= vsize) throw "InvalidReferenceException";
	else return varList.at(idx);
}

int VarTable::getVarIndex(string varName)
{
	for (int idx = 0; idx < vsize; idx++) {
		if (varName.compare(varList.at(idx)) == 0)
			return idx;
	}
	return -1;
}

