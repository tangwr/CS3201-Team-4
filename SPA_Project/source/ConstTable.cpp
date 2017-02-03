#include "ConstTable.h"

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> constList;   // constId -> constName = Value
unordered_map<int, int> constMap;    // constName -> constId

int ctsize; // number of variables in the program

ConstTable::ConstTable(void) {
	ctsize = 0;
}

int ConstTable::insertConst(int constName)
{
	unordered_map<int, int>::iterator it = constMap.find(constName);

	if (it != constMap.end())
		return it->second;
	else
	{
		int constId = ctsize;
		constList.push_back(constName);
		constMap.insert(make_pair(constName, constId));
		ctsize++;
		return constId;   // index of the variable in the vector
	}
}

int ConstTable::getSize()
{
	return ctsize;
}

int ConstTable::getConstName(int constId)
{
	if (constId >= ctsize) throw "InvalidReferenceException";
	else return constList.at(constId);
}

int ConstTable::getConstIndex(int constName)
{
	unordered_map<int, int>::iterator it = constMap.find(constName);

	if (it != constMap.end())
		return it->second;
	else
		return -1;
}

bool ConstTable::checkConstExist(int constName)
{
	unordered_map<int, int>::iterator it = constMap.find(constName);

	if (it != constMap.end())
		return true;
	else
		return false;
}

int ConstTable::getValueById(int constId)
{
	if (constId >= ctsize) throw "InvalidReferenceException";
	else return constList.at(constId);
}

/*
	Return list of constants
*/
vector<int> ConstTable::getAllConst()
{
	return constList;
}

void ConstTable::printContents()
{
	for (int it : constList)
		cout << it << endl;
}

