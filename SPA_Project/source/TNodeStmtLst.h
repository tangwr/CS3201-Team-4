#pragma once
#include "TNodeStmt.h"
#include "TNode.h"


class TNodeStmtLst : public TNode {

private:

    std::vector<TNode*> children;
    TNode* parent;
    TNodeType nodeType;
    bool cVar;

public:

    TNodeStmtLst();
    TNodeStmtLst(std::vector<TNode*> childrenVector);
    std::vector<TNode*> getChildren();
    void setChildren(std::vector<TNode*> childrenVector);
    void addChild(TNode* c);
    void setParent(TNode* p);
    TNode* getParent();
    bool hasControlVar();
    TNodeType getType();

};