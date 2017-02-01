#pragma once


#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class AssignTable {
private:
	unordered_map<int, string> assignList;
	int size;

public:
	AssignTable();
	int getSize();
	void printContents();
	bool setAssignExp(int stmtId, string exp);
	string getAssignExp(int stmtId);
};