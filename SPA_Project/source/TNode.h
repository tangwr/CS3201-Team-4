#pragma once
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
    void setParent(TNode p);
    TNode* getParent();
    void addChild(TNode c);
    void setChildren(std::vector<TNode*> childrenVector);
    std::vector<TNode*> getChildren();
    bool hasControlVar();
};