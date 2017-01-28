#pragma once
#include <vector>

enum nodeType {
    assignNode,
    callNode,
    constNode,
    exprNode,
    ifNode,
    minusNode,
    plusNode,
    procNode,
    progNode,
    refNode,
    stmtNode,
    stmtLstNode,
    timesNode,
    varNode,
    whileNode
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
    void setParent(TNode p);
    TNode* getParent();
    void setChild(TNode c);
    std::vector<TNode*> getChildren();
    bool hasControlVar();
};