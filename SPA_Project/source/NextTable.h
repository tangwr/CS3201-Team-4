#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "TableOperations.h"

using namespace std;

class NextTable {

public:
	NextTable();
	int getSize();
	bool setStmtNextStmtRel(int currentStmtId, int nextStmtId);
	unordered_set<int> getNextStmt(int stmtId);
	unordered_set<int> getPreviousStmt(int stmtId);
	void printContents();

private:
    unordered_map<int, unordered_set<int>> nextMap; 
    unordered_map<int, unordered_set<int>> previousMap;
    int size;



};