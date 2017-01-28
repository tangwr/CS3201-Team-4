#pragma once
#include "TNodeStmt.h"

class TNodeIf : public TNodeStmt {

private:
    int stmtNumber;
    //cVar and controlNode in this case refers to the conditional variable
    bool cVar;
    TNode* controlNode;
    std::vector<TNode*> children;
    TNodeStmtLst* parent;

public:
    TNodeIf();
};