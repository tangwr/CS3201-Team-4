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
    vector<int> getAllStmtId();//currentnly only returning while and assignment statements


    //proc table
    int insertProc(string procName);


    //variable table
    int insertVar(string varName);

    vector<int> getAllVarId();
    string getVarName(int varId);
    int getVarId(string varName);


    //const table
    int insertConst(int value);

    int getConstTableSize();
    int getConstValueById(int constId);


    //Parent table
    bool setParentDirectRel(int parent, int child);
    bool insertParentRel(int parent, int child);

    int getParentDirect(int stmtId);//-1 if no parent
    vector<int> getParentStar(int stmtId);
    vector<int> getChildren(int stmtId);
    vector<int> getChildrenStar(int stmtId);


    //Follow table
    bool setFollowDirectRel(int stmtId, int followsId);
    bool insertFollowRel(int stmtId, int followId);

    int getFollowDirect(int stmtId);//-1 if no follows
    int getFollowedByDirect(int stmtId);//-1 if no followedby
    vector<int> getFollowStar(int stmtId);
    vector<int> getFollowedByStar(int stmtId);


    //Modifies table
    bool setStmtModifyRel(int stmtId, int varId);
    bool setProcModifyRel(int procId, int varId);
    bool setModifyDirectRelProc(int stmtId, int varId);

    vector<int> getModifiedByStmt(int varId);
    vector<int> getStmtModify(int stmtId);
    vector<int> getModifiedByProc(int varId);
    vector<int> getProcModify(int stmtId);


    //Uses table
    bool setStmtUseRel(int stmtId, int varId);
    bool setStmtUseRelConst(int stmtId, int constId);
    bool setProcUseRel(int procId, int varId);
    bool setProcUseRelConst(int procId, int constId);

    vector<int> getVarUsedByStmt(int stmtId);
    vector<int> getStmtUsesVar(int varId);
    vector<int> getVarUsedByProc(int procId);
    vector<int> getProcUsesVar(int varId);
    vector<int> getConstUsedByStmt(int stmtId);
    vector<int> getStmtUsesConst(int constId);
    vector<int> getConstUsedByProc(int procId);
    vector<int> getProcUsesConst(int constId);


    //Assign table
    bool setAssignExp(int stmtId, string expression);

    vector<int> getAllAssignStmtId();
    string getAssignExp(int stmtId);

    bool isStmtInAssignTable(int stmtId);


    //While table
    bool setWhileCtrlVar(int stmtId, int varId);//check var exist

    int getWhileCtrlVar(int stmtId);
    vector<int> getAllWhileStmtId();

    bool isStmtInWhileTable(int stmtId);


    //if table
    bool setIfCtrlVar(int stmtId, int varId);

    int getIfCtrlVar(int stmtId);

    bool isStmtInIfTable(int stmtId);


    //call table
    bool setCallProc(int stmtId, int procId);




    //deprecated AST API
    /*
    static int setProcToAST(PROC p, TNode* r);
    static TNode* getRootAST (PROC p);
    */
    /*
    //AST API
    TNode* createNode(TNodeType nodeType);//returns created object
    void setAsRoot(TNode* root);
    void setName(TNode* node, string name);
    void setValue(TNode* node, int value);//stmt number or constant
    bool setParent(TNode* child, TNode* parent);
    //bool setChild(TNode* parent, TNode* child);

    //while
    bool setWhileVarNode(TNodeWhile* whileNode, TNodeVar* varNode);
    bool setWhileStmtLstNode(TNodeWhile* whileNode, TNodeStmtLst* stmtLstNode);
    //if
    bool setIfVarNode(TNodeIf* ifNode, TNodeVar* varNode);
    bool setIfThenStmtLstNode(TNodeIf* ifNode, TNodeStmtLst* thenStmtLstNode);
    bool setIfElseStmtLstNode(TNodeIf* ifNode, TNodeStmtLst* elseStmtLstNode);
    //call
    //assign
    bool setAssignVarNode(TNodeAssign* assignNode, TNodeVar* varNode);
    bool setAssignExpString(TNodeAssign* assignNode, string expressionString);
    bool setAssignExpNode(TNodeAssign* assignNode, TNodeExpr* expNode);
    //var
    bool setVarNodeValue(TNodeVar* varNode, int value);
    //const
    bool setConstNodeValue(TNodeConst* constNode, int value);
    //stmtList
    bool addStmtLstStmtNode(TNodeStmtLst* stmtLstNode, TNodeStmt* stmtNode);
    //proc
    bool setProcStmtLstNode(TNodeProc* procNode, TNodeStmtLst* stmtListNode);
    //prog
    bool addProgProcNode(TNodeProg* progNode, TNodeProc* procNode);
    //operator
    bool setOperLeftExpNode(TNodeOper* operNode, TNodeExpr* expNode);
    bool setOperRightExpNode(TNodeOper* operNode, TNodeExpr* expNode);
    */
	int getProcCount();
	int getVarCount();
};