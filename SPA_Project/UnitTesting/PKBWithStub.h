#pragma once

#include "PKB.h"

class PKBWithStub : public PKB {
public:
	PKBWithStub();

	unordered_set<int> getAllVarId();
	int getVarIdByName(string varName);

	unordered_set<int> getAllProcId();
	int getProcIdByName(string procName);

	unordered_set<int> getAllConstId();

	unordered_set<int> getAllStmtId();
	unordered_set<int> getAllAssignStmt();
	unordered_set<int> getAllWhileStmt();
	unordered_set<int> getAllIfId();

	unordered_set<int> getAllCallId();
	int getProcCalledByStmt(int callstmtId);

private:
	vector<string> varTable;
	vector<string> procTable;
	vector<int> constTable;

	unordered_set<int> assignStmts;
	unordered_set<int> whileStmts;
	unordered_set<int> ifStmts;
	unordered_set<int> callStmts;
	unordered_map<int, int> callTable;
};