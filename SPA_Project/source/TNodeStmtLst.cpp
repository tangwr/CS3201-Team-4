#include "TNodeStmtLst.h"

TNodeStmtLst::TNodeStmtLst() {
    this->children = *(new std::vector<TNode*>);
    this->parent = NULL;
    this->cVar = false;
    this->nodeType = TNodeType::lstNode;
}

TNodeStmtLst::TNodeStmtLst(std::vector<TNode*> childrenVector) {
    this->children = childrenVector;
    this->parent = NULL;
}

std::vector<TNode*> TNodeStmtLst::getChildren() {
    return this->children;
}

void TNodeStmtLst::setChildren(std::vector<TNode*> childrenVector) {
    this->children = childrenVector;
}

void TNodeStmtLst::addChild(TNode* c) {
    this->children.push_back(c);
}

void TNodeStmtLst::setParent(TNode* p) {
    this->parent = p;
}

TNode* TNodeStmtLst::getParent() {
    return this->parent;
}
bool TNodeStmtLst::hasControlVar() {
    return this->cVar;
}
TNodeType TNodeStmtLst::getType() {
    return this->nodeType;
}