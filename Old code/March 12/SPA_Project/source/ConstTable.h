#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class ConstTable {
private:

	vector<int> constList;   // constId -> constName = Value
	unordered_map<int, int> constMap;    // constName -> constId

	int ctsize; // number of variables in the program

public:
	ConstTable(void);
	int insertConst( int value);
	int getSize();
	int getConstName(int constId);
	int getConstIndex(int constName);
	bool checkConstExist(int constName);
	int getValueById(int constId);
	void printContents();
	vector<int> getAllConst();
    vector<int> getAllConstId();
};