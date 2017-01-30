#pragma once
#include "TNodeStmt.h"

class TNodeCall : public TNodeStmt {
private:
    TNode* controlNode;
    int stmtNumber;
    bool cVar;
    //although there is a list of children, there should only be one element
    std::vector<TNode*> children;
    TNode* parent;

public:
    TNodeCall();
};