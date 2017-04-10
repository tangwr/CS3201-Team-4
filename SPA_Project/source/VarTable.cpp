#pragma once
#include "VarTable.h"
#include <string>
#include <vector>
#include <unordered_map>

#define EMPTY_STRING ""
#define INVALID_INDEX -1

using namespace std;

VarTable::VarTable(void) {
	vtsize = 0;
}


/*
	Insert Variable to varTable. 
	Return varId if insert success. If varName already exist, return its existing VarId without duplicate insertion.
*/
int VarTable::insertVar(string varName)
{
	unordered_map<string, int>::iterator it = varMap.find(varName);

	if (it != varMap.end())
		return it->second;
	else
	{
		int varId = vtsize;
		varList.push_back(varName);
		varMap.insert(make_pair(varName, varId));
        varIdSet.insert(varId);
		vtsize++;
		return varId;
	}
}

/*
	Query the size of varTable i.e. How many variables exist in the table
	Return numbers of existing variables
*/
int VarTable::getSize()
{
	return vtsize;
}

/*
	Query the varName by varId
	Return varName if varId is valid. else return ""
*/
string VarTable::getVarNameById(int varId)
{
	if (varId >= vtsize) {
		return EMPTY_STRING;
	}
	else {
		return varList.at(varId);
	}
}

/*
	Query the varId by varName
	Return varId if varName is valid, else return -1
*/
int VarTable::getVarIndex(string varName)
{
	unordered_map<string, int>::iterator it = varMap.find(varName);

	if (it != varMap.end())
		return it->second;
	else 
		return INVALID_INDEX;
}

bool VarTable::checkVarExistByName(string varName)
{
    unordered_map<string, int>::iterator it = varMap.find(varName);

    if (it != varMap.end())
        return true;
    else
        return false;
}

bool VarTable::checkVarExistById(int varId)
{
	if (varId < vtsize)
		return true;
	else
		return false;
}


/*
returns a unordered_set<int> of all varId
*/
unordered_set<int> VarTable::getAllVarId() {
    return this->varIdSet;
}

void VarTable::printContents()
{
	cout << "---PRINT VARTABLE---" << endl;

    cout << "VarId : VarName" << endl;
	for (pair<string, int> it : varMap) {
        cout << it.second << " : " << it.first << endl;
	}
	cout << "---END PRINT VARTABLE---" << endl;
}
