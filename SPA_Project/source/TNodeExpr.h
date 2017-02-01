#pragma once
#include "TNode.h"

class TNodeExpr : public TNode {
private:
    /*
    TNode* parent;
    std::vector<TNode*> children;
    bool cVar;
    std::string operatorValue;
    TNodeType nodeType;
    TNode* controlNode;
    */
protected:
    std::string operatorValue;

public:

    //TNodeExpr();
    virtual void setParent(TNode* p) = 0;
    virtual TNode* getParent();
    virtual void setChildren(std::vector<TNode*> childrenVector);
    virtual void addChild(TNode* c);
    virtual std::vector<TNode*> getChildren();
    virtual bool hasControlVar();
    virtual std::string getOperatorValue();
    virtual TNodeType getType();
};
