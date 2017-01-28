#pragma once
#include "TNode.h"
#include "TNodeStmt.h"

class TNodeStmtLst : public TNode {

private:

    std::vector<TNodeStmt*> children;
    TNode* parent;
public:

    TNodeStmtLst::TNodeStmtLst();
    TNodeStmtLst::TNodeStmtLst(std::vector<TNodeStmt*> childrenVector);
    std::vector<TNodeStmt*> TNodeStmtLst::getChildren();
    void TNodeStmtLst::setChildren(std::vector<TNodeStmt*> childrenVector);
    void TNodeStmtLst::addChild(TNodeStmt c);
    void TNodeStmtLst::setParent(TNode p);
    TNode* TNodeStmtLst::getParent();

};