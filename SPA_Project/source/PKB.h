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
#include "CombinedStmtTable.h"
#include <algorithm>
#include <iterator>

using namespace std;
typedef short PROC;

class PKB {
public:

	PKB();
    virtual void printAllTables();

	/*
	Retrieves the total number of statement

	return		number of statements as an integer
	*/
    virtual int getNumOfStmt();

	/*
	Retrieves all the statement indices

	return		an unordered_set of all statement indices
	*/
    virtual unordered_set<int> getAllStmtId();

    //multi-table api
	/*
	Retrieves all the statemnts that have uses relations in a given procedure

	param int procId	procedure index to retrieve statements from
	return				an unordered_set of all the statemnts that have uses relations in a given procedure
	*/
    virtual unordered_set<int> getUseStmtInProc(int procId);

	/*
	Retrieves all the statemnts that have modifies relations in a given procedure

	param int procId	procedure index to retrieve statements from
	return				an unordered_set of all the statemnts that have modifies relations in a given procedure
	*/
    virtual unordered_set<int> getModifyStmtInProc(int procId);


	//proc table
	/*
	Stores a procedure in the proc table

	param string procName		procedure name
	return						the procedure's given index as an integer
	*/
    virtual int insertProc(string procName);
	
	/*
	Stores relationship that a given procedure contains a given statement

	param int procId			procedure index
	param int stmtId			statement index
	return						true if successful, false otherwise
	*/
    virtual bool setProcToStmtRel(int procId, int stmtId);

	/*
	Given a procedure name, retrieves its corresponding index

	param string procName		procedure name
	return						index of the given procedure as an integer
	*/
    virtual int getProcIdByName(string procName);

	/*
	Given a procedure index, retrieves its corresponding name

	param int procId			procedure index
	return						procedure name as a string, an empty string if the procedure index in invalid
	*/
    virtual string getProcNameById(int procId);

	/*
	Given a procedure, check if it exists in the table

	param string procName
	return						true if the given procedure exists in the table, false if it does not
	*/
    virtual bool isProcInTable(string procName);

	/*
	Given a procedure index, check if it exists in the table

	param int procId			procedure index
	return						true if the given procedure index exists in the table, false if it does not
	*/
	virtual bool isValidProcId(int procId);
    
	/*
	Given a statement index, retrieves the produre that contains it

	param int stmtId			statement index
	return						procedure index of the procedure which contains the given statement
	*/
    virtual int getProcContainingStmt(int stmtId);

	/*
	Given a procedure index, retrieves all the statement that it contains

	param int procId			procedure index
	return						all the statement indices of statement that the given procedure contains as an unordered_set
	*/
    virtual unordered_set<int> getStmtInProc(int procId);

	/*
	Retrieves all procedure indices

	return						an unordered_set which contains all the procedure indices in the SIMPLE source
	*/
    virtual unordered_set<int> getAllProcId();


	//variable table
	/*
	Stores a variable in the var table

	param string varName		variable name
	return						a unique assigned index for the variable
	*/
    virtual int insertVar(string varName);
	
	/*
	Retrieves all variable indices

	return						an unordered_set containing all the variable indices in the var table
	*/
	virtual unordered_set<int> getAllVarId();

	/*
	Given a variable index, retrieves the name of the variable

	param int varId				variable index
	return						the name of the corresponding variable as a string
	*/
	virtual string getVarNameById(int varId);

	/*
	Given a variable name, retrieves the index of the variable

	param string varName		variable name
	return						the index of the corresponding variable as an integer
	*/
	virtual int getVarIdByName(string varName);

	/*
	Checks if a variable is in var table

	param string varName		variable name
	return						true if the given variable exists, false otherwise
	*/
    virtual bool isVarInTable(string varName);


	//const table
	/*
	Stores a constant into the const table

	param int value				constant value
	return						true if successful, false otherwise
	*/
    virtual bool insertConst(int value);

	//virtual unordered_set<int> getAllConstId();
    virtual unordered_set<int> getAllConst();
    virtual int getNumOfConst();//was get Const Table Size
    //virtual int getConstValueById(int constId);
    //virtual int getConstIdByValue(int constValue);
    virtual bool isConstInTable(int constValue);


	//Parent table
    virtual bool setStmtParentStmtRel(int parentStmtId, int childStmtId);//was set Parent Direct Rel
    virtual bool insertStmtParentStmtRel(int parentStmtId, int childStmtId);//was insert Parent Rel
    virtual bool hasParentRel();

    virtual int getStmtParentStmt(int stmtId);//-1 if no parent, was get Parent Direct
    virtual unordered_set<int> getStmtParentStarStmt(int stmtId);//was get Parent Star
    virtual unordered_set<int> getStmtChildrenStmt(int stmtId);//was get Children
    virtual unordered_set<int> getStmtChildrenStarStmt(int stmtId);//was get Children Star


	//Follow table
    virtual bool setStmtFollowStmtRel(int stmtId, int followStmtId);//was set Follow Direct Rel
    virtual bool insertStmtFollowStmtRel(int followeeId, int followerId);// was insert Follow Rel
    virtual bool hasFollowRel();

    virtual int getStmtFollowStmt(int stmtId);//-1 if no follows, was get Follow Direct
    virtual int getStmtFollowedByStmt(int stmtId);//-1 if no followedby, was get Followed By Direct
    virtual unordered_set<int> getStmtFollowStarStmt(int stmtId);
    virtual unordered_set<int> getStmtFollowedByStarStmt(int stmtId);//was get Followed By Star


	//Modifies table
    virtual bool setStmtModifyVarRel(int stmtId, int varId);//was set Stmt Modify Rel
    virtual bool setProcModifyVarRel(int procId, int varId);//was set Proc Modify Rel
    virtual bool insertStmtModifyVarRel(int stmtId, int varId);//was insert Stmt Modifies Var
    virtual bool insertProcModifyVarRel(int procId, int varId);

	virtual unordered_set<int> getStmtModifyVar(int varId);//was get Modified By Stmt
	virtual unordered_set<int> getVarModifiedInStmt(int stmtId);//was get Stmt Modify
    virtual unordered_set<int> getProcModifyVar(int varId);//was get Modified By Proc
    virtual unordered_set<int> getVarModifiedInProc(int procId);//was get Proc Modify

    virtual unordered_set<int> getAllModifyStmt();//was get All Modifies Stmt
    virtual bool isStmtInModifyTable(int stmtId);//was is Stmt In Modifies Table
    virtual bool hasModifyRel(int stmtId, int varId);//was check Stmt Var Modifies Rel Exist

	//Uses table
    virtual bool setStmtUseVarRel(int stmtId, int varId);//was set Stmt Use Rel 
	virtual bool setStmtUseConstRel(int stmtId, int constId);//was set Stmt Use Rel Const
    virtual bool setProcUseVarRel(int procId, int varId);//was set Proc Use Rel
    virtual bool setProcUseConstRel(int procId, int constId);//was set Proc Use Rel Const
    virtual bool insertStmtUseVarRel(int stmtId, int varId);//was insert Stmt Uses Var
    virtual bool insertStmtUseConstRel(int stmtId, int constId);
    virtual bool insertProcUseVarRel(int procId, int varId);
    virtual bool insertProcUseConstRel(int procId, int constId);

    virtual unordered_set<int> getVarUsedByStmt(int stmtId);
    virtual unordered_set<int> getStmtUseVar(int varId);//was get Stmt Uses Var
    virtual unordered_set<int> getVarUsedByProc(int procId);
    virtual unordered_set<int> getProcUseVar(int varId);//was get Proc Uses Var
    virtual unordered_set<int> getConstUsedByStmt(int stmtId);
    virtual unordered_set<int> getStmtUseConst(int constId);//was get Stmt Uses Const
    virtual unordered_set<int> getConstUsedByProc(int procId);
    virtual unordered_set<int> getProcUseConst(int constId);//was get Proc Uses Const
    virtual unordered_set<int> getAllUseStmt();//was get All Use Stmt
    
    virtual bool isStmtInUseTable(int stmtId);// was is Stmt In Uses Table
    virtual bool checkStmtVarUseRelExist(int stmtId, int varId);


	//Assign table
    virtual bool setExpToAssignStmt(int stmtId, string expression);// was set Assign Exp
	virtual unordered_set<int> getAllAssignStmt();//was get All Assign StmtId
	virtual string getExpInAssignStmt(int stmtId);//was get Assign Exp
	virtual bool isStmtInAssignTable(int stmtId);
    virtual bool setVarAtLeftOfAssignStmt(int assignStmtId, int varId);
    virtual int getVarAtLeftOfAssignStmt(int assignStmtId);
    virtual unordered_set<int> getStmtInAssignWithVar(int varId);


	//While table
    virtual bool setVarToWhileStmt(int stmtId, int varId);//check var exist//was set While Ctrl Var
	virtual int getCtrlVarInWhileStmt(int stmtId);//was get While Ctrl Var
	virtual unordered_set<int> getAllWhileStmt();
    virtual unordered_set<int> getStmtInWhileWithCtrlVar(int varId);

	virtual bool isStmtInWhileTable(int stmtId);


	//if table
    virtual bool setVarToIfStmt(int stmtId, int varId);//was set If Ctrl Var
	virtual int getCtrlVarInIfStmt(int stmtId);//was get If Ctrl Var
    virtual unordered_set<int> getStmtInIfWithCtrlVar(int varId);
	virtual bool isStmtInIfTable(int stmtId);
    virtual unordered_set<int> getAllIfId();


	//call table
    virtual bool setStmtCallProcRel(int stmtId, int procId);//was set Call proc
    virtual bool setProcCallProcRel(int callerProcId, int calledProcId);
    virtual bool insertProcCallStarProcRel(int callerProcId, int calledStarProcId);
    virtual bool isStmtInCallTable(int stmtId);
    virtual int getProcCalledByStmt(int callStmtId);
    virtual unordered_set<int> getStmtCallProc(int procId);
    virtual unordered_set<int> getProcCallProc(int calledProcId);
    virtual unordered_set<int> getProcCalledByProc(int callerProcId);
    virtual unordered_set<int> getAllCallId();
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
	CombinedStmtTable combinedStmtTable;

	bool isValidVarId(int VarId);
	bool isValidVar(string varName);
	bool isValidConst(int constId);
};