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
    //Table API
    /*
	static VarTable* varTable; 
	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST (PROC p);
    */
    //set is for direct parent/relations and not *
    bool setFollowDirectRel(int stmtId, int followsId);
    bool setParentDirectRel(int parent, int child);
    bool setStmtModifyRel(int stmtId, int varId);
    bool setProcModifyRel(int procId, int varId);
    bool setStmtUseRel(int stmtId, int varId);
    bool setStmtUseRelConst(int stmtId, int constId);

    //insert is for *
    bool insertFollowRel(int stmtId, int followId);
    bool insertParentRel(int parent, int child);

    int insertVar(string varName);
    int insertProc(string procName);
    int insertConst(int value);

    bool setAssignExp(int stmtId, string expression);
    bool setWhileCtrlVar(int stmtId, int varId);//check var exist
    bool setIfCtrlVar(int stmtId, int varId);
    bool setCallProc(int stmtId, int procId);

    int getFollowDirect(int stmtId);//-1 if no follows
    int getFollowedByDirect(int stmtId);//-1 if no followedby
    int getParentDirect(int stmtId);//-1 if no parent
    vector<int> getChildren(int stmtId);
    vector<int> getChildrenStar(int stmtId);
    vector<int> getFollowStar(int stmtId);
    vector<int> getFollowedByStar(int stmtId);
    vector<int> getParentStar(int stmtId);

    //usestable
    vector<int> getVarUsedByStmt(int stmtId);
    vector<int> getStmtUsesVar(int varId);
    vector<int> getVarUsedByProc(int procId);
    vector<int> getProcUsesVar(int varId);

    vector<int> getConstUsedByStmt(int stmtId);
    vector<int> getStmtUsesConst(int constId);
    vector<int> getConstUsedByProc(int procId);
    vector<int> getProcUsesConst(int constId);

    bool setProcUseRel(int procId, int varId);
    bool setProcUseRelConst(int procId, int constId);
    //constTable
    int getConstTableSize();
    //bool checkConstExist(int constId);renamed and place in private
    int getConstValueById(int constId);

    //modifiesTable
    bool setModifyDirectRelProc(int stmtId, int varId);
    vector<int> getModifiedByStmt(int varId);
    vector<int> getStmtModify(int stmtId);
    vector<int> getModifiedByProc(int varId);
    vector<int> getProcModify(int stmtId);

    int getTotalStmtNum();

    vector<int> getAllAssignStmtId();
    vector<int> getAllWhileStmtId();
    vector<int> getAllVarId();

    string getVarName(int varId);
    int getVarId(string varName);

    /*
    //usesTable
    vector<int> getVarUsedByStmt(int stmtId);
    vector<int> getStmtUsesVar(int varId);
    vector<int> getVarUsedByProc(int procId);
    vector<int> getProcUsesVar(int varId);

    vector<int> getConstUsedByStmt(int stmtId);
    vector<int> getStmtUsesConst(int varId);
    vector<int> getConstUsedByProc(int procId);
    vector<int> getProcUsesConst(int varId);

    bool setUseDirecRelProc(int procId, int varId);
    bool setUseDirectRelConst(int stmtId, int varId);
    bool setUseDirectRelConstProc(int procId, int varId);

    //constTable
    int insertConst(int constName, int value);
    int getSize();
    int getConstName(int constId);
    int getConstIndex(int constName);
    bool checkConstExist(int constName);
    int getValueById(int constId);
    int getValueByName(int constName);


    //modifiesTable
    bool setModifyDirectRelProc(int stmtId, int varId);
    vector<int> getModifiedByStmt(int varId);
    vector<int> getStmtModify(int stmtId);
    vector<int> getModifiedByProc(int varId);
    vector<int> getProcModify(int stmtId);

    //parentTable
    vector<int> getDirectChild(int stmtId);
    */

};