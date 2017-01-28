#pragma once
#include "TNodeStmt.h"

class TNodeWhile : public TNodeStmt {
private:
    TNode* controlNode;
    int stmtNumber;
    bool cVar;
    std::vector<TNode*> children;
    TNodeStmtLst* parent;

public:
    TNodeWhile();
};