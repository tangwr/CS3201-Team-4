#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "TableOperations.h"

using namespace std;

class ParentsTable {

public:
	ParentsTable();
	bool setStmtParentStmtRel(int father, int child);
	bool insertStmtParentStmtRel(int father, int child);
	unordered_set<int> getStmtChildrenStmt(int stmtNo);  // direct children
	int getParent(int stmtNo);
	unordered_set<int> getStmtChildrenStarStmt(int stmtId);
	unordered_set<int> getStmtParentStarStmt(int stmtId);
	bool hasParentRel();
	void printContents();

private:
	unordered_map<int, int> parentsMap;   // <child, parent> direct
    unordered_map<int, unordered_set<int>> childsMap;  // <parent, child>  direct
    unordered_map<int, unordered_set<int>> parentListMap; // <child parent*>
    unordered_map<int, unordered_set<int>> childListMap; // <parent, child*>



};