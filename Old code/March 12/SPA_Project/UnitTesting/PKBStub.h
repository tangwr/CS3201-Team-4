#pragma once

#include "PKB.h"

class PKBStub : public PKB {
public:
	PKBStub();

	int getVarIdByName(string varName);
	//vector<int> getAllAssignStmt();
	//vector<int> getAllWhileStmt();
	vector<int> getAllIfStmt();
	//vector<int> getStmtModifyVar(int varId);
	//vector<int> getVarModifiedInStmt(int stmtId);
	string getExpInAssignStmt(int assignStmtId);

private:
	unordered_map<int, string> assignTable;
	vector<vector<int>> modifyTable;
	vector<int> modifyStmts;
	vector<int> ifStmts;
	vector<int> whileStmts;
	vector<int> assignStmts;
	vector<string> varTable;
};