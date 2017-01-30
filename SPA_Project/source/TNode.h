#pragma once

#include "TNodeAssign.h"
#include "TNodeCall.h"
#include "TNodeConst.h"
#include "TNodeExpr.h"
#include "TNodeIf.h"
#include "TNodeMinus.h"
#include "TNodePlus.h"
#include "TNodeProc.h"
#include "TNodeProg.h"
#include "TNodeRef.h"
#include "TNodeStmt.h"
#include "TNodeStmtLst.h"
#include "TNodeTimes.h"
#include "TNodeVar.h"
#include "TNodeWhile.h"

#include <vector>

enum nodeType {
    assignNode = 0,
    callNode = 1,
    constNode = 2,
    exprNode = 3,
    ifNode = 4,
    minusNode = 5,
    plusNode = 6,
    procNode = 7,
    progNode = 8,
    refNode = 9,
    stmtNode = 10,
    stmtLstNode = 11,
    timesNode = 12,
    varNode = 13,
    whileNode = 14
};

class TNode
{
private:
    TNode* parent;
    std::vector<TNode*> children;
    //contol variable refers to if x, x is the control var
    TNode* controlNode;
    bool cVar;
public:
    TNode();
    static TNode* createTNode(nodeType type);
    void setParent(TNode p);
    TNode* getParent();
    void addChild(TNode c);
    void setChildren(std::vector<TNode*> childrenVector);
    std::vector<TNode*> getChildren();
    bool hasControlVar();
};