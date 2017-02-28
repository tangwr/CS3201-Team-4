#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "FollowsTable.h"
#include "ModifiesTable.h"
#include "ParentsTable.h"
#include "ProcTable.h"
#include "UsesTable.h"
#include "VarTable.h"
#include "WhileTable.h"
#include "IfTable.h"
#include "CallTable.h"
#include "ConstTable.h"
#include "AssignTable.h"
#include "NextTable.h"
#include <algorithm>
#include <iterator>

using namespace std;
typedef short PROC;

class PKB {
private:
	FollowsTable followsTable;
	ModifiesTable modifiesTable;
	ParentsTable parentTable;
	ProcTable procTable;
	UsesTable usesTable;
	VarTable variableTable;
	ConstTable constTable;
	WhileTable whileTable;
	IfTable ifTable;
	CallTable callTable;
	AssignTable assignTable;
    NextTable nextTable;

	bool isValidVarId(int VarId);
	bool isValidVar(string varName);
	bool isValidConst(int constId);
public:

	PKB();
	void printAllTables();
	//Table API
	//set is for direct parent/relations and not *
	//insert is for *

	int getNumOfStmt();//was get total stmt num
		//int getNumOfStmt();
	unordered_set<int> getAllStmtId();//currentnly only returning while and assignment statements


	//proc table
	int insertProc(string procName);

    bool setProcToStmtRel(int procId, int stmtId);

    int getProcIdByName(string procName);


	//variable table
	int insertVar(string varName);

	vector<int> getAllVarId();
	string getVarNameById(int varId);//was get var name
		//string getVarNameById(int varId);
	int getVarIdByName(string varName);// was get VarId
		//int getVarIdByName(string varName);


	//const table
	int insertConst(int value);

	vector<int> getAllConstId();
	int getNumOfConst();//was get Const Table Size
		//int getNumOfConst();
	int getConstValueById(int constId);


	//Parent table
	bool setStmtParentStmtRel(int parentStmtId, int childStmtId);//was set Parent Direct Rel
		//bool setStmtParentStmtRel(int parentStmtId, int childStmtId);
	bool insertStmtParentStmtRel(int parentStmtId, int childStmtId);//was insert Parent Rel
		//bool insertStmtParentStmtRel(int parentStmtId, int childStmtId);
    bool hasParentRel();

	int getStmtParentStmt(int stmtId);//-1 if no parent, was get Parent Direct
		//int getStmtParentStmt(int stmtId);
    unordered_set<int> getStmtParentStarStmt(int stmtId);//was get Parent Star
		//vector<int> getStmtParentStarStmt(int stmtId);
    unordered_set<int> getStmtChildrenStmt(int stmtId);//was get Children
		//vector<int> getStmtChildrenStmt(int stmtId);
    unordered_set<int> getStmtChildrenStarStmt(int stmtId);//was get Children Star
		//vector<int> getStmtChildrenStarStmt(int stmtId);


	//Follow table
	bool setStmtFollowStmtRel(int stmtId, int followStmtId);//was set Follow Direct Rel
		//bool setStmtFollowStmtRel(int stmtId, int followStmtId);
	bool insertStmtFollowStmtRel(int stmtId, int followStmtId);// was insert Follow Rel
		//bool insertStmtFollowStmtRel(int stmtId, int followStmtId);
    bool hasFollowRel();

	int getStmtFollowStmt(int stmtId);//-1 if no follows, was get Follow Direct
		//int getStmtFollowStmt(int stmtId);
	int getStmtFollowedByStmt(int stmtId);//-1 if no followedby, was get Followed By Direct
		//int getStmtFollowedByStmt(int stmtId);
    unordered_set<int> getStmtFollowStarStmt(int stmtId);
		//vector<int> getStmtFollowStarStmt(int stmtId);
    unordered_set<int> getStmtFollowedByStarStmt(int stmtId);//was get Followed By Star
		//vector<int> getStmtFollowedByStarStmt(int stmtId);


	//Modifies table
	bool setStmtModifyVarRel(int stmtId, int varId);//was set Stmt Modify Rel
		//bool setStmtModifyVarRel(int stmtId, int varId);
	bool setProcModifyVarRel(int procId, int varId);//was set Proc Modify Rel
		//bool setProcModifyVarRel(int procId, int varId);
    bool insertStmtModifyVarRel(int stmtId, int varId);//was insert Stmt Modifies Var
		//bool insertStmtModifyVarRel(int stmtId, int varId);

	virtual unordered_set<int> getStmtModifyVar(int varId);//was get Modified By Stmt
		//vector<int> getStmtModifyVar(int varId);
	virtual unordered_set<int> getVarModifiedInStmt(int stmtId);//was get Stmt Modify
		//vector<int> getVarModifiedInStmt(int stmtId);
    unordered_set<int> getProcModifyVar(int varId);//was get Modified By Proc
		//vector<int> getProcModifiyVar(int varId);
    unordered_set<int> getVarModifiedInProc(int procId);//was get Proc Modify
		//vector<int> getVarModifiedInProc(int procId);

    vector<int> getAllModifyStmt();//was get All Modifies Stmt
		//vector<int> getAllModifyStmt();
    bool isStmtInModifyTable(int stmtId);//was is Stmt In Modifies Table
		//bool isStmtInModifyTable(int stmtId);
    bool hasModifyRel(int stmtId, int varId);//was check Stmt Var Modifies Rel Exist
		//bool hasModifyRel(int stmtId, int varId);

	//Uses table
	bool setStmtUseVarRel(int stmtId, int varId);//was set Stmt Use Rel
		//bool setStmtUseVarRel(int stmtId, int varId);
	bool setStmtUseConstRel(int stmtId, int constId);//was set Stmt Use Rel Const
		//bool setStmtUseConstRel(int stmtId, int constId);
	bool setProcUseVarRel(int procId, int varId);//was set Proc Use Rel
		//bool setProcUseVarRel(int procId, int varId);
	bool setProcUseConstRel(int procId, int constId);//was set Proc Use Rel Const
		//bool setProcUseConstRel(int procId, int constId);
    bool insertStmtUseVarRel(int stmtId, int varId);//was insert Stmt Uses Var
		//bool insertStmtUseVarRel(int stmtId, int varId);

    unordered_set<int> getVarUsedByStmt(int stmtId);
    unordered_set<int> getStmtUseVar(int varId);//was get Stmt Uses Var
		//vector<int> getStmtUseVar(int varId);
    unordered_set<int> getVarUsedByProc(int procId);
    unordered_set<int> getProcUseVar(int varId);//was get Proc Uses Var
		//vector<int> getProcUseVar(int varId);
    unordered_set<int> getConstUsedByStmt(int stmtId);
    unordered_set<int> getStmtUseConst(int constId);//was get Stmt Uses Const
		//vector<int> getStmtUseConst(int constId);
    unordered_set<int> getConstUsedByProc(int procId);
    unordered_set<int> getProcUseConst(int constId);//was get Proc Uses Const
		//vector<int> getProcUseConst(int constId);

    unordered_set<int> getAllUseStmt();//was get All Use Stmt
		//vector<int> getAllUseStmt();

    bool isStmtInUseTable(int stmtId);// was is Stmt In Uses Table
		//bool isStmtInUseTable(int stmtId);
    bool checkStmtVarUseRelExist(int stmtId, int varId);
		//bool checkStmtVarUseRelExist(int stmtId, int varId);


	//Assign table
	bool setExpToAssignStmt(int stmtId, string expression);// was set Assign Exp
		//bool setExpToAssignStmt(int stmtId, string expression);

	virtual unordered_set<int> getAllAssignStmt();//was get All Assign StmtId
		//vector<int> getAllAssignStmt();
	virtual string getExpInAssignStmt(int stmtId);//was get Assign Exp
		//string getExpInAssignStmt(int stmtId);

	bool isStmtInAssignTable(int stmtId);


	//While table
	bool setVarToWhileStmt(int stmtId, int varId);//check var exist//was set While Ctrl Var
		//bool setVarToWhileStmt(int stmtId, int varId);

	int getVarInWhileStmt(int stmtId);//was get While Ctrl Var
		//int getVarInWhileStmt(int stmtId);
	virtual unordered_set<int> getAllWhileStmt();

	bool isStmtInWhileTable(int stmtId);


	//if table
	bool setVarToIfStmt(int stmtId, int varId);//was set If Ctrl Var
		//bool setVarToIfStmt(int stmtId, int varId);
	int getVarInIfStmt(int stmtId);//was get If Ctrl Var
		//int getVarInIfStmt(int stmtId);
	bool isStmtInIfTable(int stmtId);


	//call table
	bool setStmtCallProc(int stmtId, int procId);//was set Call Proc
		//bool setStmtCallProc(int stmtId, int procId);

    //next table
};