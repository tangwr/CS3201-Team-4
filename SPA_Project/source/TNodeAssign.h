#pragma once
#include "TNodeStmt.h"

class TNodeAssign : public TNodeStmt {
private:
    TNode* controlNode;
    int stmtNumber;
    bool cVar;
    std::vector<TNode*> children;
    TNode* parent;

public:
    TNodeAssign();
    /*
    void setParent(TNodeStmtLst p);
    TNodeStmtLst* getParent();
    void setChildren(std::vector<TNode*> childrenVector);
    void addChild(TNode c);
    std::vector<TNode*> getChildren();
    void setControlNode(TNode cont);
    void setStmtNumber(int i);
    int getStmtNumber();
    bool hasControlVar();
    */
};