#pragma once
#include "TNodeStmt.h"
#include "TNodeStmtLst.h"
#include "TNodeVar.h"

class TNodeWhile : public TNodeStmt {
private:
    TNodeVar* controlNode;
    int stmtNumber;
    bool cVar;
    //std::vector<TNode*> children;
    TNode* parent;
    TNodeStmtLst* stmtListNode;

public:
    TNodeWhile();
    TNodeType getType();
    void setControlNode(TNodeVar* controlNode);
    void setStmtListNode(TNodeStmtLst* stmtList);
};