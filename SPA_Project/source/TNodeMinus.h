#pragma once
#include "TNodeOper.h"

class TNodeMinus : public TNodeOper {
private:
    TNode* parent;
    std::vector<TNode*> children;
    bool cVar;
    std::string operatorValue;

public:
    TNodeMinus();
};