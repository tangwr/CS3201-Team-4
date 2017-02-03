#include "ProcTable.h"

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<string> procList;
unordered_map<string, int> procMap;
int ptsize; // number of procedures in the program

ProcTable::ProcTable(void) {
	ptsize = 0;
}

/*
Insert procedure to procTable.
Return procId if insert success. If procedure already exist, return its existing procId without duplicate insertion.
*/
int ProcTable::insertProc(string procName)
{
	unordered_map<string, int>::iterator it = procMap.find(procName);

	if (it != procMap.end())
		return it->second;
	else
	{
		int procId = ptsize;
		procList.push_back(procName);
		procMap.insert(make_pair(procName, procId));
		ptsize++;
		return procId;   
	}
}

/*
Query the size of procTable i.e. How many procedures exist in the table
Return numbers of existing procedures
*/
int ProcTable::getSize()
{
	return ptsize;
}

/*
Query the procName by procId
Return procName if procId is valid. else throw exception
*/
string ProcTable::getProcName(int procId)
{
	if (procId >= ptsize) throw "InvalidReferenceException";
	else return procList.at(procId);
}


/*
Query the procId by procName
Return varId if varName is valid, else return -1
*/
int ProcTable::getProcIndex(string procName)
{
	unordered_map<string, int>::iterator it = procMap.find(procName);

	if (it != procMap.end())
		return it->second;
	else 
		return -1;
}

bool ProcTable::checkProcExistById(int procId)
{
	if (procId < ptsize)
		return true;
	else
		return false;
}

bool ProcTable::checkProcExistByName(string procName)
{
	unordered_map<string, int>::iterator it = procMap.find(procName);

	if (it != procMap.end())
		return true;
	else
		return false;
}

void ProcTable::printContents()
{
	cout << "---PRINT PROCTABLE---" << endl;

	for (pair<string, int> it : procMap) {
		cout << "ProcId: " << it.second;
		cout << " ProcName " << it.first << endl;
	}
	cout << "---END PRINT PROCTABLE---" << endl;
}

void ProcTable::printVector(vector<int> vec)
{
	for (int t : vec) {
		cout << t << ' ';
	}
}
