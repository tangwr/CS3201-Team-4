#pragma once

#include "PKB.h"

class ParentStarPKBStub : public PKB {
public:
	ParentStarPKBStub();

	unordered_set<int> getStmtParentStarStmt(int);
	unordered_set<int> getStmtChildrenStarStmt(int);
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
	unordered_map<int, unordered_set<int>> parentTable;
	unordered_map<int, unordered_set<int>> childrenTable;
};