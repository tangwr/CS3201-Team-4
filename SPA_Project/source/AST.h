#pragma once

#include <vector>
#include "TNode.h"
#include "TNodeType.h"
#include "TNodeStmtLst.h"
#include "TNodeStmt.h"
#include "TNodeProc.h"
#include "TNodeProg.h"
#include "TNodeExpr.h"
#include "TNodeOper.h"
#include "TNodeRef.h"
#include "TNodeAssign.h"
#include "TNodeCall.h"
#include "TNodeConst.h"
#include "TNodeIf.h"
#include "TNodeMinus.h"
#include "TNodePlus.h"
#include "TNodeTimes.h"
#include "TNodeVar.h"
#include "TNodeWhile.h"

using namespace std;

class AST {

private:

    TNode* rootNode;

public:

    AST();
    TNode* createTNode(TNodeType nodeType);
    void setAsRoot(TNode* root);
    void setParentChildRelation(TNode* p, TNode* c);
    void setParent(TNode* p, TNode* c);
    void setChild(TNode* p, TNode* c);
    TNode* getRoot();
    TNode* getParent(TNode* c);
    //std::vector<TNode*> getChildren(TNode* p);
    bool setName(TNode* node, string name);
    bool setValue(TNode* node, int value);
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
    bool setProcStmtLstNode(TNodeProc* procNode, TNodeStmtLst* stmtLstNode);
    //prog
    bool addProgProcNode(TNodeProg* progNode, TNodeProc* procNode);
    //opertor
    bool setOperLeftExpNode(TNodeOper* operNode, TNodeExpr* expNode);
    bool setOperRightExpNode(TNodeOper* operNode, TNodeExpr* expNode);



};