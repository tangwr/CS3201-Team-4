#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class ProcTable {
private:
	void printVector(vector<int> vec);
	vector<string> procList;
	unordered_map<string, int> procMap;
	int ptsize; // number of procedures in the program

public:
	ProcTable(void);
	int insertProc(string procName);
	int getSize();
	string getProcName(int idx);
	int getProcIndex(string procName);
	bool checkProcExistByName(string procName);
	void printContents();
	bool checkProcExistById(int ProcId);
};