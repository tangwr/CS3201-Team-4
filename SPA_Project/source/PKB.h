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
#include "StmtLstTable.h"
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
    StmtLstTable stmtLstTable;

	bool isValidVarId(int VarId);
	bool isValidVar(string varName);
	bool isValidConst(int constId);
public:

	PKB();
    virtual void printAllTables();
	//Table API
	//set is for direct parent/relations and not *
	//insert is for *

    virtual int getNumOfStmt();//was get total stmt num
		//int getNumOfStmt();
    virtual unordered_set<int> getAllStmtId();//currentnly only returning while, assign, if & while statements

    //multi-table api
    virtual unordered_set<int> getUseStmtInProc(int procId);
    virtual unordered_set<int> getModifyStmtInProc(int procId);

	//proc table
    virtual int insertProc(string procName);

    virtual bool setProcToStmtRel(int procId, int stmtId);

    virtual int getProcIdByName(string procName);
    virtual int getProcNameById(int procId);//not implemented yet

    virtual bool isProcInTable(string procName);
    
    virtual int getProcContainingStmt(int stmtId);
    virtual unordered_set<int> getStmtInProc(int procId);
    virtual unordered_set<int> getAllProcId();


	//variable table
    virtual int insertVar(string varName);

	virtual unordered_set<int> getAllVarId();
	virtual string getVarNameById(int varId);//was get var name
		//string getVarNameById(int varId);
	virtual int getVarIdByName(string varName);// was get VarId
		//int getVarIdByName(string varName);
    virtual bool isVarInTable(string varName);


	//const table
    virtual int insertConst(int value);

	virtual unordered_set<int> getAllConstId();
    virtual unordered_set<int> getAllConst();
    virtual int getNumOfConst();//was get Const Table Size
		//int getNumOfConst();
    virtual int getConstValueById(int constId);


	//Parent table
    virtual bool setStmtParentStmtRel(int parentStmtId, int childStmtId);//was set Parent Direct Rel
		//bool setStmtParentStmtRel(int parentStmtId, int childStmtId);
    virtual bool insertStmtParentStmtRel(int parentStmtId, int childStmtId);//was insert Parent Rel
		//bool insertStmtParentStmtRel(int parentStmtId, int childStmtId);
    virtual bool hasParentRel();

    virtual int getStmtParentStmt(int stmtId);//-1 if no parent, was get Parent Direct
		//int getStmtParentStmt(int stmtId);
    virtual unordered_set<int> getStmtParentStarStmt(int stmtId);//was get Parent Star
		//vector<int> getStmtParentStarStmt(int stmtId);
    virtual unordered_set<int> getStmtChildrenStmt(int stmtId);//was get Children
		//vector<int> getStmtChildrenStmt(int stmtId);
    virtual unordered_set<int> getStmtChildrenStarStmt(int stmtId);//was get Children Star
		//vector<int> getStmtChildrenStarStmt(int stmtId);


	//Follow table
    virtual bool setStmtFollowStmtRel(int stmtId, int followStmtId);//was set Follow Direct Rel
		//bool setStmtFollowStmtRel(int stmtId, int followStmtId);
    virtual bool insertStmtFollowStmtRel(int followeeId, int followerId);// was insert Follow Rel
		//bool insertStmtFollowStmtRel(int stmtId, int followStmtId);
    virtual bool hasFollowRel();

    virtual int getStmtFollowStmt(int stmtId);//-1 if no follows, was get Follow Direct
		//int getStmtFollowStmt(int stmtId);
    virtual int getStmtFollowedByStmt(int stmtId);//-1 if no followedby, was get Followed By Direct
		//int getStmtFollowedByStmt(int stmtId);
    virtual unordered_set<int> getStmtFollowStarStmt(int stmtId);
		//vector<int> getStmtFollowStarStmt(int stmtId);
    virtual unordered_set<int> getStmtFollowedByStarStmt(int stmtId);//was get Followed By Star
		//vector<int> getStmtFollowedByStarStmt(int stmtId);


	//Modifies table
    virtual bool setStmtModifyVarRel(int stmtId, int varId);//was set Stmt Modify Rel
		//bool setStmtModifyVarRel(int stmtId, int varId);
    virtual bool setProcModifyVarRel(int procId, int varId);//was set Proc Modify Rel
		//bool setProcModifyVarRel(int procId, int varId);
    virtual bool insertStmtModifyVarRel(int stmtId, int varId);//was insert Stmt Modifies Var
		//bool insertStmtModifyVarRel(int stmtId, int varId);
    virtual bool insertProcModifyVarRel(int procId, int varId);

	virtual unordered_set<int> getStmtModifyVar(int varId);//was get Modified By Stmt
		//vector<int> getStmtModifyVar(int varId);
	virtual unordered_set<int> getVarModifiedInStmt(int stmtId);//was get Stmt Modify
		//vector<int> getVarModifiedInStmt(int stmtId);
    virtual unordered_set<int> getProcModifyVar(int varId);//was get Modified By Proc
		//vector<int> getProcModifiyVar(int varId);
    virtual unordered_set<int> getVarModifiedInProc(int procId);//was get Proc Modify
		//vector<int> getVarModifiedInProc(int procId);

    virtual unordered_set<int> getAllModifyStmt();//was get All Modifies Stmt
		//vector<int> getAllModifyStmt();
    virtual bool isStmtInModifyTable(int stmtId);//was is Stmt In Modifies Table
		//bool isStmtInModifyTable(int stmtId);
    virtual bool hasModifyRel(int stmtId, int varId);//was check Stmt Var Modifies Rel Exist
		//bool hasModifyRel(int stmtId, int varId);

	//Uses table
    virtual bool setStmtUseVarRel(int stmtId, int varId);//was set Stmt Use Rel
		//bool setStmtUseVarRel(int stmtId, int varId);
	virtual bool setStmtUseConstRel(int stmtId, int constId);//was set Stmt Use Rel Const
		//bool setStmtUseConstRel(int stmtId, int constId);
    virtual bool setProcUseVarRel(int procId, int varId);//was set Proc Use Rel
		//bool setProcUseVarRel(int procId, int varId);
    virtual bool setProcUseConstRel(int procId, int constId);//was set Proc Use Rel Const
		//bool setProcUseConstRel(int procId, int constId);
    virtual bool insertStmtUseVarRel(int stmtId, int varId);//was insert Stmt Uses Var
		//bool insertStmtUseVarRel(int stmtId, int varId);
    virtual bool insertStmtUseConstRel(int stmtId, int constId);
    virtual bool insertProcUseVarRel(int procId, int varId);
    virtual bool insertProcUseConstRel(int procId, int constId);

    virtual unordered_set<int> getVarUsedByStmt(int stmtId);
    virtual unordered_set<int> getStmtUseVar(int varId);//was get Stmt Uses Var
		//vector<int> getStmtUseVar(int varId);
    virtual unordered_set<int> getVarUsedByProc(int procId);
    virtual unordered_set<int> getProcUseVar(int varId);//was get Proc Uses Var
		//vector<int> getProcUseVar(int varId);
    virtual unordered_set<int> getConstUsedByStmt(int stmtId);
    virtual unordered_set<int> getStmtUseConst(int constId);//was get Stmt Uses Const
		//vector<int> getStmtUseConst(int constId);
    virtual unordered_set<int> getConstUsedByProc(int procId);
    virtual unordered_set<int> getProcUseConst(int constId);//was get Proc Uses Const
		//vector<int> getProcUseConst(int constId);

    virtual unordered_set<int> getAllUseStmt();//was get All Use Stmt
		//vector<int> getAllUseStmt();

    virtual bool isStmtInUseTable(int stmtId);// was is Stmt In Uses Table
		//bool isStmtInUseTable(int stmtId);
    virtual bool checkStmtVarUseRelExist(int stmtId, int varId);
		//bool checkStmtVarUseRelExist(int stmtId, int varId);


	//Assign table
    virtual bool setExpToAssignStmt(int stmtId, string expression);// was set Assign Exp
		//bool setExpToAssignStmt(int stmtId, string expression);

	virtual unordered_set<int> getAllAssignStmt();//was get All Assign StmtId
		//vector<int> getAllAssignStmt();
	virtual string getExpInAssignStmt(int stmtId);//was get Assign Exp
		//string getExpInAssignStmt(int stmtId);

	virtual bool isStmtInAssignTable(int stmtId);
    virtual bool setVarAtLeftOfAssignStmt(int assignStmtId, int varId);
    virtual int getVarAtLeftOfAssignStmt(int assignStmtId);


	//While table
    virtual bool setVarToWhileStmt(int stmtId, int varId);//check var exist//was set While Ctrl Var
		//bool setVarToWhileStmt(int stmtId, int varId);

	virtual int getCtrlVarInWhileStmt(int stmtId);//was get While Ctrl Var
		//int getCtrlVarInWhileStmt(int stmtId);
	virtual unordered_set<int> getAllWhileStmt();
    virtual unordered_set<int> getStmtInWhileWithCtrlVar(int varId);

	virtual bool isStmtInWhileTable(int stmtId);


	//if table
    virtual bool setVarToIfStmt(int stmtId, int varId);//was set If Ctrl Var
		//bool setVarToIfStmt(int stmtId, int varId);
	virtual int getCtrlVarInIfStmt(int stmtId);//was get If Ctrl Var
		//int getCtrlVarInIfStmt(int stmtId);
	virtual bool isStmtInIfTable(int stmtId);
    virtual unordered_set<int> getAllIfId();


	//call table
    virtual bool setStmtCallProcRel(int stmtId, int procId);//was set Call Proc
		//bool setStmtCallProcRel(int stmtId, int procId);
    virtual bool setProcCallProcRel(int callerProcId, int calledProcId);
    virtual bool insertProcCallStarProcRel(int callerProcId, int calledStarProcId);
    virtual bool isStmtInCalltable(int stmtId);
    virtual int getProcCalledByStmt(int callStmtId);
    virtual unordered_set<int> getProcCalledByProc(int callerProcId);
    virtual unordered_set<int> getAllCallId();
    //unordered_set<int> getStmtCallProc(int calledProcId);
    virtual unordered_set<int> getProcCalledByStarProc(int callerProcId);

    //next table
    virtual bool setStmtNextStmtRel(int currentStmtId, int nextStmtid);

    virtual unordered_set<int> getNextStmt(int currentStmtId);
    virtual unordered_set<int> getPreviousStmt(int currentStmtId);

    //stmtLst table
    virtual bool setProcStmtLstContainsStmtRel(int procId, int stmtId);
    virtual bool setContainerStmtStmtLstContainsStmtRel(int containerStmtId, int stmtId);

    virtual vector<int> getStmtLstContainedInProc(int procId);
    virtual vector<int> getStmtlstContainedInContainerStmt(int containerStmtId);
    virtual unordered_set<int> getAllStmtLst();


    //to be implemented
	virtual unordered_set<int> getStmtInAssignWithVar(int varId);
	
	
	virtual unordered_set<int> getStmtInIfWithCtrlVar(int varId);
};