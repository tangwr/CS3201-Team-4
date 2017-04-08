#pragma once

#include "PKB.h"

class PKBStubNextBipStar : public PKB {
public:
	PKBStubNextBipStar();
	unordered_set<int> getPreviousStmt(int);
	unordered_set<int> getNextStmt(int);
	unordered_set<int> getStmtParentStarStmt(int);
	int getNumOfStmt();
	unordered_set<int> getAllWhileStmt();
	unordered_set<int> getAllAssignStmt();
	unordered_set<int> getAllIfId();
	unordered_set<int> getAllCallId();
	bool isStmtInWhileTable(int);
	bool isStmtInCallTable(int);
	bool isStmtInIfTable(int);
	unordered_set<int> getAllStmtId();
	int getProcContainingStmt(int);
	int getProcCalledByStmt(int);
	unordered_set<int> getStmtCallProc(int);
	vector<int> getStmtLstContainedInProc(int);

private:
	unordered_set<int> allStmts;
	unordered_set<int> assignStmts;
	unordered_set<int> whileStmts;
	unordered_set<int> ifStmts;
	unordered_set<int> callStmts;
	unordered_map<int, unordered_set<int>> parentStarTable;
	unordered_map<int, unordered_set<int>> nextTable;
	unordered_map<int, unordered_set<int>> prevTable;
	unordered_map<int, int> myProcTable;
	unordered_map<int, int> procCalledByStmtTable;
	unordered_map<int, unordered_set<int>> stmtCallProcTable;
	unordered_map<int, vector<int>> stmtLstContainedInProc;
};