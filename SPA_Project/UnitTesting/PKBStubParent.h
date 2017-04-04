#pragma once

#include "PKB.h"

class PKBStubParent : public PKB {
public:
	PKBStubParent();

	int getStmtParentStmt(int);
	unordered_set<int> getStmtChildrenStmt(int);
	int getNumOfStmt();
	unordered_set<int> getAllWhileStmt();
	unordered_set<int> getAllAssignStmt();
	unordered_set<int> getAllIfId();
	unordered_set<int> getAllCallId();
	unordered_set<int> getAllStmtId();

private:
	unordered_set<int> allStmts;
	unordered_set<int> assignStmts;
	unordered_set<int> whileStmts;
	unordered_set<int> ifStmts;
	unordered_set<int> callStmts;
	unordered_map<int, int> parentTable;
	unordered_map<int, unordered_set<int>> childrenTable;
};