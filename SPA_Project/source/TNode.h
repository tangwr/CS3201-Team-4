#pragma once

#include <vector>
#include "TNodeType.h"

class TNode
{
private:
    //TNode* parent;
    //std::vector<TNode*> children;
    //contol variable refers to if x, x is the control var
    //TNode* controlNode;
    //bool cVar; 
    //std::string nodetype;
    //TNodeType nodetype;
protected:
    TNodeType nodeType;
    TNode* parent;
    std::vector<TNode*> children;
    bool cVar;
    TNode* controlNode;

public:
    //TNode();
    virtual void setParent(TNode* p);
    virtual TNode* getParent();
    virtual void addChild(TNode* c);
    virtual void setChildren(std::vector<TNode*> childrenVector);
    virtual std::vector<TNode*> getChildren();
    virtual bool hasControlVar();
    virtual TNodeType getType() = 0;
};