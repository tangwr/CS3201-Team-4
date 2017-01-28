#pragma once
#include "TNode.h"
#include "TNodeStmtLst.h"
class TNodeStmt : public TNode {

private:
    TNodeStmtLst* parent;
    std::vector<TNode*> children;
    int stmtNumber;
    TNode* controlNode;
    bool cVar;

public:
    TNodeStmt();
    void setParent(TNodeStmtLst p);
    TNodeStmtLst* getParent();
    void setChildren(std::vector<TNode*> childrenVector);
    void addChild(TNode c);
    void setControlNode(TNode cont);
    std::vector<TNode*> getChildren();
    bool hasControlVar();
};