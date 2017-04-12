#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>;

using namespace std;

class ConstTable {
public:
	ConstTable(void);
	int getSize();
	bool insertConst(int value);
	bool checkConstExist(int constValue);
	void printContents();
	unordered_set<int> getAllConst();

private:

    unordered_set<int> constSet;

	int ctsize;
};