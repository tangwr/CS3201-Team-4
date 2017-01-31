#pragma once
#include "TNodeOper.h"

class TNodePlus : public TNodeOper {
private:
    TNode* parent;
    std::vector<TNode*> children;
    bool cVar;
    std::string operatorValue;

public:
    TNodePlus();
};