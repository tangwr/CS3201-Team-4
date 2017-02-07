#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class ParentsTable {
private:
	void printVector(vector<int> vec);
	unordered_map<int, int> parentsMap;   // <child, parent> direct
	unordered_map<int, vector<int>> childsMap;  // <parent, child>  direct
	unordered_map<int, vector<int>> parentListMap; // <child parent*>
	unordered_map<int, vector<int>> childListMap; // <parent, child*>

public:
	ParentsTable();
	bool setStmtParentStmtRel(int father, int child);
	bool ParentsTable::insertStmtParentStmtRel(int father, int child);
	vector<int> getStmtChildrenStmt(int stmtNo);  // direct children
	int getParent(int stmtNo);
	//vector<int> getChildrenList(int stmtNo);
	//vector<int> getParentList(int stmtNo);
	vector<int> getStmtChildrenStarStmt(int stmtId);
	vector<int> getStmtParentStarStmt(int stmtId);
	bool hasParentRel();
	void printContents();

};