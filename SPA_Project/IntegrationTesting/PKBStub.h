#pragma once

#include "PKB.h"

class PKBStub : public PKB {
private:
	unordered_set<int> allStmts;
	unordered_map<int, unordered_set<int>> usesStmtInProcTable;
	unordered_map<int, unordered_set<int>> modifiesStmtInProcTable;
	unordered_map<string, int> procIdTable;
	unordered_set<string> procStmts;
	unordered_set<int> procId;
	unordered_set<int> modifyStmts;
	unordered_set<int> varId;
	vector<string> varTable;
	unordered_map<string, int> varIdTable;
	unordered_set<int> constValues;
	unordered_map<int, int> parentTable;
	unordered_map<int, unordered_set<int>> parentStarTable;
	unordered_map<int, unordered_set<int>> childrenTable;
	unordered_map<int, unordered_set<int>> childrenStarTable;
	unordered_map<int, int> followsTable;
	unordered_map<int, int> followedByTable;
	unordered_map<int, unordered_set<int>> followsStarTable;
	unordered_map<int, unordered_set<int>> followedByStarTable;
	unordered_map<int, unordered_set<int>> stmtModifyVarTable;
	unordered_map<int, unordered_set<int>> modifiesTable;
	unordered_map<int, unordered_set<int>> procModifyVarTable;
	unordered_map<int, unordered_set<int>> usesTable;
	unordered_map<int, unordered_set<int>> stmtUseVarTable;
	unordered_map<int, unordered_set<int>> procUseVarTable;
	unordered_set<int> useStmts;
	unordered_set<int> assignStmts;
	unordered_map<int, string> assignTable;
	unordered_map<int, int> left_varInAssignStmt;
	unordered_map<int, int> ctrlVarInWhileStmt;
	unordered_set<int> whileStmts;
	unordered_map<int, unordered_set<int>> whileStmtUseVar;
	bool isStmtInWhileTable(int stmtId);
	unordered_map<int, unordered_set<int>> ifStmtUseVar;
	unordered_set<int> ifStmts;
	unordered_set<int> callStmts;
	unordered_map<int, int> procCalledByStmtTable;
	unordered_map<int, unordered_set<int>> stmtCallProcTable;
	unordered_map<int, unordered_set<int>> procCallTable;
	unordered_map<int, unordered_set<int>> nextTable;
	unordered_map<int, unordered_set<int>> prevTable;
	unordered_map<int, vector<int>> stmtLstToProcTable;
	unordered_set<int> stmtLst;
	unordered_map<int, string> procIdToNameTable;
	unordered_map<int, unordered_set<int>> assignStmtModVar;
	unordered_map<int, int> stmtToProcTable;
public:
	PKBStub();
	int getNumOfStmt();
	unordered_set<int> getAllStmtId();

	//multi-table api
	unordered_set<int> getUseStmtInProc(int procId);
	unordered_set<int> getModifyStmtInProc(int procId);

	//proc table
	int getProcIdByName(string procName);
	bool isProcInTable(string procName);
	unordered_set<int> getAllProcId();
	string getProcNameById(int procId);
	int getProcContainingStmt(int stmtId);

	//variable table
	unordered_set<int> getAllVarId();
	string getVarNameById(int varId);
	int getVarIdByName(string varName);
	bool isVarInTable(string varName);


	//const table
	unordered_set<int> getAllConst();
	bool isConstInTable(int constValue);

	//Parent table
	int getStmtParentStmt(int stmtId);
	unordered_set<int> getStmtParentStarStmt(int stmtId);
	unordered_set<int> getStmtChildrenStmt(int stmtId);
	unordered_set<int> getStmtChildrenStarStmt(int stmtId);

	//Follow table
	int getStmtFollowStmt(int stmtId);
	int getStmtFollowedByStmt(int stmtId);
	unordered_set<int> getStmtFollowStarStmt(int stmtId);
	unordered_set<int> getStmtFollowedByStarStmt(int stmtId);

	//Modifies table
	unordered_set<int> getStmtModifyVar(int varId);
	unordered_set<int> getVarModifiedInStmt(int stmtId);
	unordered_set<int> getProcModifyVar(int varId);
	unordered_set<int> getAllModifyStmt();
	bool isStmtInModifyTable(int stmtId);
	bool hasModifyRel(int stmtId, int varId);

	//Uses table
	unordered_set<int> getVarUsedByStmt(int stmtId);
	unordered_set<int> getStmtUseVar(int varId);
	unordered_set<int> getProcUseVar(int varId);
	unordered_set<int> getAllUseStmt();
	bool isStmtInUseTable(int stmtId);
	bool checkStmtVarUseRelExist(int stmtId, int varId);

	//Assign table
	unordered_set<int> getAllAssignStmt();
	string getExpInAssignStmt(int assignStmtId);
	bool isStmtInAssignTable(int stmtId);
	int getVarAtLeftOfAssignStmt(int assignStmtId);
	unordered_set<int> getStmtInAssignWithVar(int varId);

	//While table
	int getCtrlVarInWhileStmt(int stmtId);
	unordered_set<int> getAllWhileStmt();
	unordered_set<int> getStmtInWhileWithCtrlVar(int varId);

	//if table
	unordered_set<int> getStmtInIfWithCtrlVar(int varId);
	bool isStmtInIfTable(int stmtId);
	unordered_set<int> getAllIfId();

	//call table
	bool isStmtInCallTable(int stmtId);
	int getProcCalledByStmt(int callStmtId);
	unordered_set<int> getStmtCallProc(int procId);
	unordered_set<int> getProcCalledByProc(int callerProcId);
	unordered_set<int> getAllCallId();
	unordered_set<int> getProcCalledByStarProc(int callerProcId);

	//next table
	unordered_set<int> getNextStmt(int currentStmtId);
	unordered_set<int> getPreviousStmt(int currentStmtId);

	//stmtLst table
	vector<int> getStmtLstContainedInProc(int procId);
	unordered_set<int> getAllStmtLst();

};