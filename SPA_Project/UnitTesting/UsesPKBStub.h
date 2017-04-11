#pragma once

#include "PKB.h"

class UsesPKBStub : public PKB {
public:
	UsesPKBStub();
	
	unordered_set<int> getAllStmtId();
	unordered_set<int> getAllAssignStmt();
	unordered_set<int> getAllWhileStmt();
	unordered_set<int> getAllIfId();
	unordered_set<int> getAllProcId();
	unordered_set<int> getAllCallId();
	unordered_set<int> getAllVarId();
	unordered_set<int> getAllUseStmt();

	bool checkStmtVarUseRelExist(int stmtId, int varId);
	bool isProcInTable(string paramName);
	bool isStmtInUseTable(int stmtId);

	int getVarIdByName(string varName);
	int getProcIdByName(string procName);


	unordered_set<int> getUseStmtInProc(int procId);
	unordered_set<int> getStmtUseVar(int varId);
	unordered_set<int> getProcUseVar(int varId);

	unordered_set<int> getVarUsedByStmt(int stmtId);
	

private:

	unordered_set<int> allStmts;
	unordered_set<int> assignStmts;
	unordered_set<int> whileStmts;
	unordered_set<int> ifStmts;
	unordered_set<int> callStmts;
	unordered_set<int> procId;
	unordered_set<int> varId;
	unordered_set<int> useStmts;
	unordered_set<string> procStmts;

	unordered_map<string, int> varIdTable;
	unordered_map<string, int> procIdTable;
	unordered_map<int, unordered_set<int>> usesTable;
	unordered_map<int, unordered_set<int>> usesStmtInProcTable;
	unordered_map<int, unordered_set<int>> stmtUseVarTable;
	unordered_map<int, unordered_set<int>> procUseVarTable;
};