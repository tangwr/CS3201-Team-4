#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class VarTable {
public:
	VarTable(void);
	int insertVar(string varName);
	int getSize();
	string getVarName(int idx);
	int getVarIndex(string varName);
};