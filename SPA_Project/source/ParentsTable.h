#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ParentsTable {
private:
	void printVector(vector<int> vec);
public:
	ParentsTable();
	bool setParentDirectRel(int father, int child);
	bool ParentsTable::insertParentRel(int father, int child);
	vector<int> getChildren(int stmtNo);  // direct children
	int getParent(int stmtNo);
	//vector<int> getChildrenList(int stmtNo);
	//vector<int> getParentList(int stmtNo);
	vector<int> getChildrenStar(int stmtId);
	vector<int> getParentStar(int stmtId);

	void printContents();

};