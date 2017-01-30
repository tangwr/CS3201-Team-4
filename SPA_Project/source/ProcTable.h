#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ProcTable {
public:
	ProcTable(void);
	int insertProc(string procName);
	int getSize();
	string getProcName(int idx);
	int getProcIndex(string procName);
};