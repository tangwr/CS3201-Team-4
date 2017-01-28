#include "TNodeStmtLst.h"

TNodeStmtLst::TNodeStmtLst() {
    this->children = *(new std::vector<TNodeStmt*>);
    this->parent = NULL;
}

TNodeStmtLst::TNodeStmtLst(std::vector<TNodeStmt*> childrenVector) {
    this->children = childrenVector;
    this->parent = NULL;
}

std::vector<TNodeStmt*> TNodeStmtLst::getChildren() {
    return this->children;
}

void TNodeStmtLst::setChildren(std::vector<TNodeStmt*> childrenVector) {
    this->children = childrenVector;
}

void TNodeStmtLst::addChild(TNodeStmt c) {
    this->children.push_back(&c);
}

void TNodeStmtLst::setParent(TNode p) {
    this->parent = &p;
}

TNode* TNodeStmtLst::getParent() {
    return this->parent;
}