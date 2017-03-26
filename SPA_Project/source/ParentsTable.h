#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class ParentsTable {
private:
	void printVector(vector<int> vec);
    void printUnorderedSet(unordered_set<int> uSet);
	unordered_map<int, int> parentsMap;   // <child, parent> direct
	//unordered_map<int, vector<int>> childsMap;  // <parent, child>  direct
	//unordered_map<int, vector<int>> parentListMap; // <child parent*>
	//unordered_map<int, vector<int>> childListMap; // <parent, child*>
    unordered_map<int, unordered_set<int>> childsMap;  // <parent, child>  direct
    unordered_map<int, unordered_set<int>> parentListMap; // <child parent*>
    unordered_map<int, unordered_set<int>> childListMap; // <parent, child*>

public:
	ParentsTable();
	bool setStmtParentStmtRel(int father, int child);
	bool insertStmtParentStmtRel(int father, int child);
    unordered_set<int> getStmtChildrenStmt(int stmtNo);  // direct children
	int getParent(int stmtNo);
	//vector<int> getChildrenList(int stmtNo);
	//vector<int> getParentList(int stmtNo);
    unordered_set<int> getStmtChildrenStarStmt(int stmtId);
    unordered_set<int> getStmtParentStarStmt(int stmtId);
	bool hasParentRel();
	void printContents();

};