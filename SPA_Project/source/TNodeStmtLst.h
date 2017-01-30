#pragma once
#include "TNodeStmt.h"
#include "TNode.h"


class TNodeStmtLst : public TNode {

private:

    std::vector<TNodeStmt*> children;
    TNode* parent;
public:

    TNodeStmtLst();
    TNodeStmtLst(std::vector<TNodeStmt*> childrenVector);
    std::vector<TNodeStmt*> getChildren();
    void setChildren(std::vector<TNodeStmt*> childrenVector);
    void addChild(TNodeStmt c);
    void setParent(TNode p);
    TNode* getParent();

};