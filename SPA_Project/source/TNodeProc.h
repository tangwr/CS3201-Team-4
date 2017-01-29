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

public:
    TNodeProc();
    TNodeProc(std::string);
    std::string getName();
    void setName(std::string newName);
};