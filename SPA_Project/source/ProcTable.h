#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class ProcTable {
private:
	void printVector(vector<int> vec);
	vector<string> procList;
	unordered_map<string, int> procMap;
    unordered_map<int, int> stmtContainedInProcMap;
    unordered_map<int, unordered_set<int>> procContainsStmtMap;
	int ptsize; // number of procedures in the program

public:
	ProcTable(void);
	int insertProc(string procName);
	int getSize();
	string getProcName(int idx);
	int getProcIndex(string procName);
    bool setProcToStmtRel(int procId, int stmtId);
	bool checkProcExistByName(string procName);
	void printContents();
	bool checkProcExistById(int ProcId);
};