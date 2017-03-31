#pragma once

#include "PKB.h"

class PKBWithStub : public PKB {
public:
	PKBWithStub();

	unordered_set<int> getAllVarId();
	int getVarIdByName(string varName);
	string getVarNameById(int varId);
	bool isVarInTable(string varName);

	unordered_set<int> getAllProcId();
	int getProcIdByName(string procName);
	string getProcNameById(int procId);
	bool isProcInTable(string procName);

	unordered_set<int> getAllConst();
	bool isConstInTable(int constValue);

	unordered_set<int> getAllStmtId();
	unordered_set<int> getAllAssignStmt();
	unordered_set<int> getAllWhileStmt();
	unordered_set<int> getAllIfId();

	unordered_set<int> getAllCallId();
	int getProcCalledByStmt(int callStmtId);
	unordered_set<int> getStmtCallProc(int procId);

private:
	vector<string> varTable;
	vector<string> procTable;

	unordered_set<int> constValues;
	unordered_set<int> assignStmts;
	unordered_set<int> whileStmts;
	unordered_set<int> ifStmts;
	unordered_set<int> callStmts;
	unordered_map<int, int> callTable;
};