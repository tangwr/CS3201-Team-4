#pragma once
#include "TNodeExpr.h"

class TNodeRef : public TNodeExpr {
private:
    TNode* parent;
    std::vector<TNode*> children;
    bool cVar;
    std::string operatorValue;
    std::string nodeValue;

public:
    std::string getNodeValue();//constructor with nodevalue make
    void setNodeValue(std::string nValue);
};