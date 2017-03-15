#pragma once

#include "PKB.h"

class PKBStub : public PKB {
public:
	PKBStub();

	unordered_set<int> getAllVarId();
	int getVarIdByName(string varName);

	unordered_set<int> getAllAssignStmt();
	unordered_set<int> getStmtInAssignWithVar(int varId);
	string getExpInAssignStmt(int assignStmtId);
	int getVarAtLeftOfAssignStmt(int assignStmtId);
	bool isStmtInAssignTable(int stmtId);

	unordered_set<int> getAllWhileStmt();
	unordered_set<int> getStmtInWhileWithCtrlVar(int varId);
	int getCtrlVarInWhileStmt(int stmtId);
	bool isStmtInWhileTable(int stmtId);

	unordered_set<int> getAllIfStmt();
	unordered_set<int> getStmtInIfWithCtrlVar(int varId);
	int getCtrlVarInIfStmt(int stmtId);
	bool isStmtInIfTable(int stmtId);

private:
	unordered_set<int> assignStmts;
	unordered_map<int, string> assignTable;
	unordered_map<int, unordered_set<int>> assignStmtModVar;
	unordered_map<int, int> left_varInAssignStmt;

	unordered_set<int> whileStmts;
	unordered_map<int, unordered_set<int>> whileStmtUseVar;
	unordered_map<int, int> ctrlVarInWhileStmt;

	unordered_set<int> ifStmts;
	unordered_map<int, unordered_set<int>> ifStmtUseVar;
	unordered_map<int, int> ctrlVarInIfStmt;

	vector<unordered_set<int>> modifyTable;
	unordered_set<int> modifyStmts;

	vector<string> varTable;
};