#pragma once
#include "TNodeRef.h"

class TNodeVar : public TNodeRef {
private:
    TNode* parent;
    std::vector<TNode*> children;
    bool cVar;
    std::string operatorValue;
    std::string nodeValue;

public:
    TNodeVar();
    void setParent();
};