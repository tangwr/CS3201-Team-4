#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <utility>
#include <unordered_map>

using namespace std;

class IfTable {
private:

	unordered_map<int, int> ifList;
	int size;

public:
	IfTable();
	int getSize();
	void printContents();
	bool setIfCtrlVar(int stmtId, int varId);
	int getIfCtrlVar(int stmtId);
};