#include "TNodeExpr.h"

TNodeExpr::TNodeExpr() {
    this->cVar = false;
    this->children = *(new std::vector<TNode*>);
    this->parent = NULL;
    this->operatorValue = "none";
}
void TNodeExpr::setParent(TNode p) {
    this->parent = &p;
}
TNode* TNodeExpr::getParent() {
    return this->parent;
}
void TNodeExpr::setChildren(std::vector<TNode*> childrenVector) {
    this->children = childrenVector;
}
void TNodeExpr::addChild(TNode c) {
    this->children.push_back(&c);
}
std::vector<TNode*> TNodeExpr::getChildren() {
    return this->children;
}
bool TNodeExpr::hasControlVar() {
    return this->cVar;
}
std::string TNodeExpr::getOperatorValue() {
    return this->operatorValue;
}