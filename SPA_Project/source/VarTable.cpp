#include "VarTable.h"

#include <string>
#include <vector>
#include <unordered_map>

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
		vtsize++;
		return varId;   // index of the variable in the vector
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
	Return varName if varId is valid. else throw exception
*/
string VarTable::getVarNameById(int varId)
{
	if (varId >= vtsize) throw "InvalidReferenceException";
	else return varList.at(varId);
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
		return -1;
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
returns a vector<int> of all varId
*/
vector<int> VarTable::getAllVarId() {
    vector<int> allVarIdList;
    for (auto varEntry : varMap) {
        allVarIdList.push_back(varEntry.second);
    }
    return allVarIdList;
}

void VarTable::printContents()
{
	cout << "---PRINT VARTABLE---" << endl;

    cout << "VarId : VarName" << endl;
	for (pair<string, int> it : varMap) {
        cout << it.second << " : " << it.first << endl;
		//cout << "VarId: " << it.second;
		//cout << " VarName " << it.first << endl;
	}
	cout << "---END PRINT VARTABLE---" << endl;
}
