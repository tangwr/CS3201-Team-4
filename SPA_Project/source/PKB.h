
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

//class TNode;

//class VarTable;  // no need to #include "VarTable.h" as all I need is pointer

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

	int getTotalStmtNum();
		//int getNumOfStmt();
	vector<int> getAllStmtId();//currentnly only returning while and assignment statements


	//proc table
	int insertProc(string procName);


	//variable table
	int insertVar(string varName);

	vector<int> getAllVarId();
	string getVarName(int varId);
		//string getVarNameById(int varId);
	int getVarId(string varName);
		//int getVarIdByName(string varName);


	//const table
	int insertConst(int value);

	vector<int> getAllConstId();
	int getConstTableSize();
		//int getNumOfConst();
	int getConstValueById(int constId);


	//Parent table
	bool setParentDirectRel(int parent, int child);
		//bool setStmtParentStmtRel(int parentStmtId, int childStmtId);
	bool insertParentRel(int parent, int child);
		//bool insertStmtParentStmtRel(int parentStmtId, int childStmtId);
    bool hasParentRel();

	int getParentDirect(int stmtId);//-1 if no parent
		//int getStmtParentStmt(int stmtId);
	vector<int> getParentStar(int stmtId);
		//vector<int> getStmtParentStarStmt(int stmtId);
	vector<int> getChildren(int stmtId);
		//vector<int> getStmtChildrenStmt(int stmtId);
	vector<int> getChildrenStar(int stmtId);
		//vector<int> getStmtChildrenStarStmt(int stmtId);


	//Follow table
	bool setFollowDirectRel(int stmtId, int followStmtId);
		//bool setStmtFollowStmtRel(int stmtId, int followStmtId);
	bool insertFollowRel(int stmtId, int followStmtId);
		//bool insertStmtFollowStmtRel(int stmtId, int followStmtId);
    bool hasFollowRel();

	int getFollowDirect(int stmtId);//-1 if no follows
		//int getStmtFollowStmt(int stmtId);
	int getFollowedByDirect(int stmtId);//-1 if no followedby
		//int getStmtFollowedByStmt(int stmtId);
	vector<int> getFollowStar(int stmtId);
		//vector<int> getStmtFollowStarStmt(int stmtId);
	vector<int> getFollowedByStar(int stmtId);
		//vector<int> getStmtFollowedByStarStmt(int stmtId);


	//Modifies table
	bool setStmtModifyRel(int stmtId, int varId);
		//bool setStmtModifyVarRel(int stmtId, int varId);
	bool setProcModifyRel(int procId, int varId);
		//bool setProcModifyVarRel(int procId, int varId);
	bool setModifyDirectRelProc(int procId, int varId);
		//bool setStmtModifyProcRel(int procId, int varId);
    bool insertStmtModifiesVar(int stmtId, int varId);
		//bool insertStmtModifyVarRel(int stmtId, int varId);

	vector<int> getModifiedByStmt(int varId);
		//vector<int> getStmtModifyVar(int varId);
	vector<int> getStmtModify(int stmtId);
		//vector<int> getVarModifiedInStmt(int stmtId);
	vector<int> getModifiedByProc(int varId);
		//vector<int> getProcModifiyVar(int varId);
	vector<int> getProcModify(int stmtId);
		//vector<int> getVarModifiedInProc(int procId);

    vector<int> getAllModifiesStmt();
		//vector<int> getAllModifyStmt();
    bool isStmtInModifiesTable(int stmtId);
		//bool isStmtInModifyTable(int stmtId);
    bool checkStmtVarModifiesRelExist(int stmtId, int varId);
		//bool hasModifyRel(int stmtId, int varId);

	//Uses table
	bool setStmtUseRel(int stmtId, int varId);
		//bool setStmtUseStmtRel(int stmtId, int varId);
	bool setStmtUseRelConst(int stmtId, int constId);
		//bool setStmtUseConstRel(int stmtId, int constId);
	bool setProcUseRel(int procId, int varId);
		//bool setProcUseVarRel(int procId, int varId);
	bool setProcUseRelConst(int procId, int constId);
		//bool setProcUseConstRel(int procId, int constId);
    bool insertStmtUsesVar(int stmtId, int varId);
		//bool insertStmtUseVarRel(int stmtId, int varId);

	vector<int> getVarUsedByStmt(int stmtId);
	vector<int> getStmtUsesVar(int varId);
		//vector<int> getStmtUseVar(int varId);
	vector<int> getVarUsedByProc(int procId);
	vector<int> getProcUsesVar(int varId);
		//vector<int> getProcUseVar(int varId);
	vector<int> getConstUsedByStmt(int stmtId);
	vector<int> getStmtUsesConst(int constId);
		//vector<int> getStmtUseConst(int constId);
	vector<int> getConstUsedByProc(int procId);
	vector<int> getProcUsesConst(int constId);
		//vector<int> getProcUsesConst(int constId);

    vector<int> getAllUsesStmt();
		//vector<int> getAllUseStmt();

    bool isStmtInUsesTable(int stmtId);
		//bool isStmtInUseTable(int stmtId);
    bool checkStmtVarUseRelExist(int stmtId, int varId);
		//bool checkStmtVarUseRelExist(int stmtId, int varId);


	//Assign table
	bool setAssignExp(int stmtId, string expression);
		//bool setExpToAssignStmt(int stmtId, string expression);

	vector<int> getAllAssignStmtId();
		//vector<int> getAllAssignStmt();
	string getAssignExp(int stmtId);
		//string getExpInAssignStmt(int stmtId);

	bool isStmtInAssignTable(int stmtId);


	//While table
	bool setWhileCtrlVar(int stmtId, int varId);//check var exist
		//bool setVarToWhileStmt(int stmtId, int varId);

	int getWhileCtrlVar(int stmtId);
		//int getVarInWhileStmt(int stmtId);
	vector<int> getAllWhileStmtId();

	bool isStmtInWhileTable(int stmtId);


	//if table
	bool setIfCtrlVar(int stmtId, int varId);
		//bool setVarToIfStmt(int stmtId, int varId);
	int getIfCtrlVar(int stmtId);
		//int getVarInIfStmt(int stmtId);
	bool isStmtInIfTable(int stmtId);


	//call table
	bool setCallProc(int stmtId, int procId);
		//bool setStmtCallProc(int stmtId, int procId);
};