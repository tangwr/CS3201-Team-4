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
	vector<int> getAllStmtId();//currentnly only returning while and assignment statements


	//proc table
	int insertProc(string procName);


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
	vector<int> getStmtParentStarStmt(int stmtId);//was get Parent Star
		//vector<int> getStmtParentStarStmt(int stmtId);
	vector<int> getStmtChildrenStmt(int stmtId);//was get Children
		//vector<int> getStmtChildrenStmt(int stmtId);
	vector<int> getStmtChildrenStarStmt(int stmtId);//was get Children Star
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
	vector<int> getStmtFollowStarStmt(int stmtId);
		//vector<int> getStmtFollowStarStmt(int stmtId);
	vector<int> getStmtFollowedByStarStmt(int stmtId);//was get Followed By Star
		//vector<int> getStmtFollowedByStarStmt(int stmtId);


	//Modifies table
	bool setStmtModifyVarRel(int stmtId, int varId);//was set Stmt Modify Rel
		//bool setStmtModifyVarRel(int stmtId, int varId);
	bool setProcModifyVarRel(int procId, int varId);//was set Proc Modify Rel
		//bool setProcModifyVarRel(int procId, int varId);
    bool insertStmtModifyVarRel(int stmtId, int varId);//was insert Stmt Modifies Var
		//bool insertStmtModifyVarRel(int stmtId, int varId);

	virtual vector<int> getStmtModifyVar(int varId);//was get Modified By Stmt
		//vector<int> getStmtModifyVar(int varId);
	virtual vector<int> getVarModifiedInStmt(int stmtId);//was get Stmt Modify
		//vector<int> getVarModifiedInStmt(int stmtId);
	vector<int> getProcModifyVar(int varId);//was get Modified By Proc
		//vector<int> getProcModifiyVar(int varId);
	vector<int> getVarModifiedInProc(int procId);//was get Proc Modify
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

	vector<int> getVarUsedByStmt(int stmtId);
	vector<int> getStmtUseVar(int varId);//was get Stmt Uses Var
		//vector<int> getStmtUseVar(int varId);
	vector<int> getVarUsedByProc(int procId);
	vector<int> getProcUseVar(int varId);//was get Proc Uses Var
		//vector<int> getProcUseVar(int varId);
	vector<int> getConstUsedByStmt(int stmtId);
	vector<int> getStmtUseConst(int constId);//was get Stmt Uses Const
		//vector<int> getStmtUseConst(int constId);
	vector<int> getConstUsedByProc(int procId);
	vector<int> getProcUseConst(int constId);//was get Proc Uses Const
		//vector<int> getProcUseConst(int constId);

    vector<int> getAllUseStmt();//was get All Use Stmt
		//vector<int> getAllUseStmt();

    bool isStmtInUseTable(int stmtId);// was is Stmt In Uses Table
		//bool isStmtInUseTable(int stmtId);
    bool checkStmtVarUseRelExist(int stmtId, int varId);
		//bool checkStmtVarUseRelExist(int stmtId, int varId);


	//Assign table
	bool setExpToAssignStmt(int stmtId, string expression);// was set Assign Exp
		//bool setExpToAssignStmt(int stmtId, string expression);

	virtual vector<int> getAllAssignStmt();//was get All Assign StmtId
		//vector<int> getAllAssignStmt();
	virtual string getExpInAssignStmt(int stmtId);//was get Assign Exp
		//string getExpInAssignStmt(int stmtId);

	bool isStmtInAssignTable(int stmtId);


	//While table
	bool setVarToWhileStmt(int stmtId, int varId);//check var exist//was set While Ctrl Var
		//bool setVarToWhileStmt(int stmtId, int varId);

	int getVarInWhileStmt(int stmtId);//was get While Ctrl Var
		//int getVarInWhileStmt(int stmtId);
	virtual vector<int> getAllWhileStmt();

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
};