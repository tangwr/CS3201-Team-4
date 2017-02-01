#pragma once
#include "TNode.h"

class TNodeProc : public TNode {
private:
    std::string name;
    TNode* parent;
    std::vector<TNode*> children;
    //contol variable refers to if x, x is the control var
    TNode* controlNode;
    bool cVar;
    TNodeType nodeType;
     
public:
    TNodeProc();
    TNodeProc(std::string);
    std::string getName();
    void setName(std::string newName);
    void setParent(TNode* p);
    TNode* getParent();
    void addChild(TNode* c);
    void setChildren(std::vector<TNode*> childrenVector);
    std::vector<TNode*> getChildren();
    bool hasControlVar();
    TNodeType getType();

};