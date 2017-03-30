#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "TableOperations.h"

using namespace std;

class NextBipTable {
private:
	unordered_map<int, unordered_set<int>> nextBipMap;
	unordered_map<int, unordered_set<int>> previousBipMap;
	int size;

public:
	NextBipTable();
	int getSize();
	bool setStmtNextBipStmtRel(int currentStmtId, int nextBipStmtId);
	unordered_set<int> getNextBipStmt(int stmtId);
	unordered_set<int> getPreviousBipStmt(int stmtId);
	void printContents();

};