#pragma once
#include "TNode.h"

class TNodeProg : public TNode {
private:
    std::string name;
    TNode* parent;
    std::vector<TNode*> children;
    //contol variable refers to if x, x is the control var
    TNode* controlNode;
    bool cVar;

public:
    TNodeProg();
    TNodeProg(std::string);
    std::string getName();
    void setName(std::string newName);
};