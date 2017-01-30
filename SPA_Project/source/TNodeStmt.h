#pragma once
#include "TNode.h"
//#include "TNodeStmtLst.h"

class TNodeStmt : public TNode {
    
private:
    TNode* parent;
    std::vector<TNode*> children;
    int stmtNumber;
    TNode* controlNode;
    bool cVar;

public:
    TNodeStmt();
    void setParent(TNode p);
    TNode* getParent();
    void setChildren(std::vector<TNode*> childrenVector);
    void addChild(TNode c);
    std::vector<TNode*> getChildren();
    void setControlNode(TNode cont);
    void setStmtNumber(int i);
    int getStmtNumber();
    bool hasControlVar();
    
};