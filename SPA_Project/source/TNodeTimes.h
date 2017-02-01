#pragma once
#include "TNodeOper.h"

class TNodeTimes : public TNodeOper {
private:
    TNode* parent;
    std::vector<TNode*> children;
    bool cVar;
    std::string operatorValue;

public:
    TNodeTimes();
};