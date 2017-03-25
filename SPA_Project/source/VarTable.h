#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class VarTable {
private:
	vector<string> varList;   // varId -> varName
	unordered_map<string, int> varMap;    // varName -> varId
    unordered_set<int> varIdSet;
	int vtsize; // number of variables in the program

public:
	VarTable();
	int insertVar(string varName);
	int getSize();
	string getVarNameById(int varId);
	int getVarIndex(string varName);
    unordered_set<int> getAllVarId();
	bool checkVarExistByName(string varName);
	bool checkVarExistById(int varId);
    void printContents();
};