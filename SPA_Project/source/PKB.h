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

	/*
	Retrieves all constants

	return						an unordered_set of all constant values
	*/
    virtual unordered_set<int> getAllConst();

	/*
	Retrieves total number of constants in const table

	return						total number of constants as an integer
	*/
	virtual int getNumOfConst();
	
	/*
	Checks if a given constant exists in const table

	param int constValue		constant value
	return						true if constant is in table, false otherwise
	*/
    virtual bool isConstInTable(int constValue);


	//Parent table
	/*
	Stores the direct parent child relation between two statements

	param int parentStmtId		statement index of the parent
	param int childStmtId		statement index of the child
	return						true if successful, false otherwise
	*/
    virtual bool setStmtParentStmtRel(int parentStmtId, int childStmtId);
	
	/*
	Stores the transitive parent child relation between two statements

	param int parentStmtId		statement index of the parent
	param int childStmtId		statement index of the child
	return						true if successful, false otherwise
	*/
    virtual bool insertStmtParentStmtRel(int parentStmtId, int childStmtId);

	/*
	Checks if there exist any parent child relationship in parent table

	return						true if ther exist at least one parent child relation, false otherwise
	*/
    virtual bool hasParentRel();

	/*
	Given a statement index, retrieves the index of its direct parent

	param int stmtId			statement index
	return						index of direct parent statement as an integer, returns -1 if it does not have any parent
	*/
    virtual int getStmtParentStmt(int stmtId);

	/*
	Given a statement index, retrieves the indices of its parents by transitive parent relation

	param int stmtId			statement index
	return						an unordered_set containing all of its parents by transitive parent relation
	*/
    virtual unordered_set<int> getStmtParentStarStmt(int stmtId);

	/*
	Given a statement index, retrieves all its direct children
	
	param int stmtId			statement index
	return						an unordered_set containing all of its direct children
	*/
    virtual unordered_set<int> getStmtChildrenStmt(int stmtId);

	/*
	Given a statement index, retrieves all of its children by transitive relation

	param int stmtId			statement index
	return						an unordered_set containing all of its children, by transitive relation
	*/
    virtual unordered_set<int> getStmtChildrenStarStmt(int stmtId);


	//Follow table
	/*
	Stores follow relation between two given statement

	param int stmtId			statement index
	param int followStmtId		follower statement index
	return						true if sucessful, false otherwise, if statment already has a follower, fails
	*/
    virtual bool setStmtFollowStmtRel(int stmtId, int followStmtId);

	/*
	Inserts transitive follow relation between two given statement

	param int followeeId		statement index of statement being followed
	param int followStmtId		follower statement index
	return						true if sucessful, false otherwise
	*/
    virtual bool insertStmtFollowStmtRel(int followeeId, int followerId);

	/*
	Checks if follows table has any follow relation

	returns						true if no follows relation, false otherwise
	*/
    virtual bool hasFollowRel();

	/*
	Given a statement, retrieves its follower statment

	param int stmtId			statement index
	return						index of follower statement, -1 if no follower
	*/
    virtual int getStmtFollowStmt(int stmtId);

	/*
	Given a statement, retrieves the statement that it is following

	param int stmtId			statement index
	return						the index of the statement that it follows as an integer, -1 if not following any statement
	*/
    virtual int getStmtFollowedByStmt(int stmtId);

	/*
	Given a statement, retrieves follower statements by transitive relation

	param int stmtId			statement index
	return						an unordered_set of follower statement indices
	*/
    virtual unordered_set<int> getStmtFollowStarStmt(int stmtId);

	/*
	Given a statement, retrieves statements that it is following by transitive relation

	param int stmtId			statement index
	return						an unordered_set of statements that it follows, by transitive relation
	*/
    virtual unordered_set<int> getStmtFollowedByStarStmt(int stmtId);


	//Modifies table

	/*
	Stores the modify relation between a statement and the variable that it modifies

	param int stmtId			statement index
	param int varId				variable index
	return						true if successful, false if otherwise, if statement already has an entry, fails
	*/
    virtual bool setStmtModifyVarRel(int stmtId, int varId);

	/*
	Stores the modify relation between a procedure and the variable that it modifies

	param int procId			procedure index
	param int varId				variable index
	return						true if successful, false if otherwise, if statement already has an entry, fails
	*/
    virtual bool setProcModifyVarRel(int procId, int varId);

	/*
	Stores the modifies relation between a statement and variable

	param int stmtId			statement index
	param int varId				variable index
	return						true if successful, false if otherwise
	*/
    virtual bool insertStmtModifyVarRel(int stmtId, int varId);

	/*
	Stores the modifies relation between a procedure and variable

	param int stmtId			statement index
	param int procId			procedure index
	return						true if successful, false if otherwise
	*/
    virtual bool insertProcModifyVarRel(int procId, int varId);

	/*
	Given a variable index, retrieves the statements that modifies it

	param int varId				variable index
	return						unordered_set of statements that modifies the given variable
	*/
	virtual unordered_set<int> getStmtModifyVar(int varId);

	/*
	Given a statement index, retrieves the variables that it modifies

	param int stmtId			statement index
	return						unordered_set of variable indices that it modifies
	*/
	virtual unordered_set<int> getVarModifiedInStmt(int stmtId);

	/*
	Given a variable index, retrieves the procedures modifies it

	param int varId				variable index
	return						an unordered_set of procedure indices that modifies it
	*/
    virtual unordered_set<int> getProcModifyVar(int varId);

	/*
	Given a procedure index, retrieves the variable that it modifies

	param int procId			procedure index
	return						an unordered_set of variable indices that it modifies
	*/
    virtual unordered_set<int> getVarModifiedInProc(int procId);

	/*
	Retrieves all modifies statements

	return						an unordered_set of modify statement indices in the modifies table
	*/
    virtual unordered_set<int> getAllModifyStmt();

	/*
	Checks if a statement is in modifies table

	return						
	*/
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