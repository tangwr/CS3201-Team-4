#pragma once

#include "PKB.h"

class PKBStubFollowStar : public PKB {
public:
	PKBStubFollowStar();

	unordered_set<int> getStmtFollowStarStmt(int);
	unordered_set<int> getStmtFollowedByStarStmt(int);
	int getNumOfStmt();
	unordered_set<int> getAllWhileStmt();
	unordered_set<int> getAllAssignStmt();
	unordered_set<int> getAllIfId();
	unordered_set<int> getAllCallId();



private:
	unordered_set<int> assignStmts;
	unordered_set<int> whileStmts;
	unordered_set<int> ifStmts;
	unordered_set<int> callStmts;
	unordered_map<int, unordered_set<int>> followsTable;
	unordered_map<int, unordered_set<int>> followedByTable;
};