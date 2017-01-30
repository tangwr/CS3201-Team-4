#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ParentsTable {
public:
	ParentsTable();
	int insertParent(int stmtNo1, int stmtNo2);
	int getChildren(int stmtNo);
	int getParent(int stmtNo);
	vector<int> getChildrenList(int stmtNo);
	vector<int> getParentList(int stmtNo);
};