#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class VarTable {
private:
	vector<string> varList;   // varId -> varName
	unordered_map<string, int> varMap;    // varName -> varId
	int vtsize; // number of variables in the program

public:
	VarTable(void);
	int insertVar(string varName);
	int getSize();
	string getVarName(int varId);
	int getVarIndex(string varName);
	bool checkVarExistByName(string varName);
	void printContents();
	bool checkVarExistById(int varId);
    vector<int> getAllVarId();
};