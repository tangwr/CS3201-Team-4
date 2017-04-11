#pragma once

#include "PKB.h"

class FollowPKBStub : public PKB {
public:
	FollowPKBStub();

	int getStmtFollowStmt(int);
	int getStmtFollowedByStmt(int);
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
	unordered_map<int, int> followsTable;
	unordered_map<int, int> followedByTable;
};