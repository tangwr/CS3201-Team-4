#pragma once

#include "PKB.h"

class PKBStub : public PKB {
public:
	PKBStub();

	int getVarIdByName(string varName);
	unordered_set<int> getAllAssignStmt();
	unordered_set<int> getAllWhileStmt();
	unordered_set<int> getAllIfStmt();
	unordered_set<int> getStmtModifyVar(int varId);
	unordered_set<int> getVarModifiedInStmt(int stmtId);
	string getExpInAssignStmt(int assignStmtId);

private:
	unordered_map<int, string> assignTable;
	vector<unordered_set<int>> modifyTable;
	unordered_set<int> modifyStmts;
	unordered_set<int> ifStmts;
	unordered_set<int> whileStmts;
	unordered_set<int> assignStmts;
	vector<string> varTable;
};