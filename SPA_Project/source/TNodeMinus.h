#pragma once
#include "TNodeExpr.h"

class TNodeMinus : public TNodeExpr {
private:
    TNode* parent;
    std::vector<TNode*> children;
    bool cVar;
    std::string operatorValue;

public:
    TNodeMinus();
};