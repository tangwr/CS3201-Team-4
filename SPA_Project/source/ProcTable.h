#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ProcTable {
private:
	void printVector(vector<int> vec);
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