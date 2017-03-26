#pragma once

#include "PKB.h"

class PKBStubModifies : public PKB {
public:
	PKBStubModifies();

	unordered_set<int> getAllStmtId();
	unordered_set<int> getAllAssignStmt();
	unordered_set<int> getAllWhileStmt();
	unordered_set<int> getAllIfId();
	unordered_set<int> getAllProcId();
	unordered_set<int> getAllCallId();
	unordered_set<int> getAllVarId();
	unordered_set<int> getAllModifyStmt();

	bool hasModifyRel(int stmtId, int varId);
	bool isProcInTable(string paramName);
	bool isStmtInModifyTable(int stmtId);

	int getVarIdByName(string varName);
	int getProcIdByName(string procName);


	unordered_set<int> getModifyStmtInProc(int procId);
	unordered_set<int> getStmtModifyVar(int varId);
	unordered_set<int> getProcModifyVar(int varId);
	unordered_set<int> getVarModifiedInStmt(int stmtId);
	

private:

	unordered_set<int> allStmts;
	unordered_set<int> assignStmts;
	unordered_set<int> whileStmts;
	unordered_set<int> ifStmts;
	unordered_set<int> callStmts;
	unordered_set<int> procId;
	unordered_set<int> varId;
	unordered_set<int> modifyStmts;
	unordered_set<string> procStmts;

	unordered_map<string,int> varIdTable;
	unordered_map<string, int> procIdTable;
	unordered_map<int, unordered_set<int>> modifiesTable;
	unordered_map<int, unordered_set<int>> modifiesStmtInProcTable;
	unordered_map<int, unordered_set<int>> stmtModifyVarTable;
	unordered_map<int, unordered_set<int>> procModifyVarTable;
};