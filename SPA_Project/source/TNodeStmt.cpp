#include "TNodeStmt.h"

TNodeStmt::TNodeStmt() {
    this->parent = NULL;
    this->controlNode = NULL;
    this->stmtNumber = -1;
    this->cVar = false;
}
void TNodeStmt::setParent(TNodeStmtLst p) {
    this->parent = &p;
}
TNodeStmtLst* TNodeStmt::getParent() {
    return this->parent;
}
void TNodeStmt::setChildren(std::vector<TNode*> childrenVector) {
    this->children = childrenVector;
}
void TNodeStmt::addChild(TNode c) {
    this->children.push_back(&c);
}
void TNodeStmt::setControlNode(TNode cont) {
    this->controlNode = &cont;
    this->cVar = true;
    this->children.push_back(&cont);
}
std::vector<TNode*> TNodeStmt::getChildren() {
    return this->children;
}
bool TNodeStmt::hasControlVar() {
    return this->cVar;
}