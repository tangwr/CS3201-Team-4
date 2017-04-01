#pragma once

#include "PKB.h"

class PKBAffectsStub : public PKB {
public:
	PKBAffectsStub();

	unordered_set<int> getAllAssignStmt();
	int getVarAtLeftOfAssignStmt(int stmtId);

	bool isStmtInAssignTable(int stmtId);
	bool isStmtInWhileTable(int stmtId);
	bool isStmtInIfTable(int stmtId);
	bool isStmtInCallTable(int stmtId);

	int getProcContainingStmt(int stmtId);
	unordered_set<int> getVarModifiedInStmt(int stmtId);
	unordered_set<int> getVarUsedByStmt(int stmtId);

	unordered_set<int> getNextStmt(int stmtId);
	unordered_set<int> getPreviousStmt(int stmtId);

private:
	unordered_set<int> assignStmts;
	unordered_set<int> whileStmts;
	unordered_set<int> ifStmts;
	unordered_set<int> callStmts;

	unordered_map<int, int> assignStmtToVarTable;
	unordered_map<int, int> stmtToProcTable;
	unordered_map<int, unordered_set<int>> modStmtToVarTable;
	unordered_map<int, unordered_set<int>> useStmtToVarTable;

	unordered_map<int, unordered_set<int>> nextTable;
	unordered_map<int, unordered_set<int>> prevTable;
};
