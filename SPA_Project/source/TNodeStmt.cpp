#include "TNodeStmt.h"

TNodeStmt::TNodeStmt() {
    this->parent = NULL;
    this->controlNode = NULL;
    this->stmtNumber = -1;//-1 means undefined
    this->cVar = false;
    this->children = *(new std::vector<TNode*>);
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
std::vector<TNode*> TNodeStmt::getChildren() {
    return this->children;
}
void TNodeStmt::setControlNode(TNode cont) {
    this->controlNode = &cont;
    this->cVar = true;
    this->children.push_back(&cont);
}
void TNodeStmt::setStmtNumber(int i) {
    this->stmtNumber = i;
}
int TNodeStmt::getStmtNumber() {
    return this->stmtNumber;
}
bool TNodeStmt::hasControlVar() {
    return this->cVar;
}