#pragma once
#include "TNode.h"

class TNodeExpr : public TNode {
private:
    TNode* parent;
    std::vector<TNode*> children;
    bool cVar;
    std::string operatorValue;

public:
    TNodeExpr();
    void setParent(TNode p);
    TNode* getParent();
    void setChildren(std::vector<TNode*> childrenVector);
    void addChild(TNode c);
    std::vector<TNode*> getChildren();
    bool hasControlVar();
    std::string getOperatorValue();
};
