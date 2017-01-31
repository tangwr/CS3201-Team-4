#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "AST.h"

using namespace std;
typedef short PROC;

class TNode;

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer

class PKB {
public:
    PKB();
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
    bool addStmtLstStmtNode(TNodeStmtLst* stmtListNode, TNodeStmt* stmtNode);
    //proc
    bool setProcStmtLstNode(TNodeProc* procNode, TNodeStmtLst* stmtListNode);
    //prog
    bool addProgProcNode(TNodeProg* progNode, TNodeProc* procNode);
    //operator
    bool setOperLeftExpNode(TNodeOper* operNode, TNodeExpr* expNode);
    bool setOperRightExpNode(TNodeOper* operNode, TNodeExpr* expNode);

    //TABLE
	static VarTable* varTable; 
	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST (PROC p);
	
	void addProcedure(string name);
	void addVariable(string name);
	void addStatement(int statementNum, TNodeType type);

	void addFollows(int statementNum, list<int> followList);
	void addParents(int statementNum, list<int> parentList);
	void addUses(int statementNum, string variable);
	void addModifies(int statementNum, string Variable);

private:
    AST ast;
};
