#pragma once

#include "PKB.h"

class PKBStubNextStar : public PKB {
public:
	PKBStubNextStar();

	unordered_set<int> getPreviousStmt(int);
	unordered_set<int> getNextStmt(int);
	unordered_set<int> getStmtParentStarStmt(int);
	int getNumOfStmt();
	unordered_set<int> getAllWhileStmt();
	unordered_set<int> getAllAssignStmt();
	unordered_set<int> getAllIfId();
	unordered_set<int> getAllCallId();
	bool isStmtInWhileTable(int);
	unordered_set<int> getAllStmtId();

private:
	unordered_set<int> allStmts;
	unordered_set<int> assignStmts;
	unordered_set<int> whileStmts;
	unordered_set<int> ifStmts;
	unordered_set<int> callStmts;
	unordered_map<int, unordered_set<int>> parentStarTable;
	unordered_map<int, unordered_set<int>> nextTable;
	unordered_map<int, unordered_set<int>> prevTable;
};