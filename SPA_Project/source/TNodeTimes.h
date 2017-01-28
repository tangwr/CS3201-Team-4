#pragma once
#include "TNodeExpr.h"

class TNodeTimes : public TNodeExpr {
private:
    TNode* parent;
    std::vector<TNode*> children;
    bool cVar;
    std::string operatorValue;

public:
    TNodeTimes();
};