#include "TNode.h"

TNode::TNode() {
    this->parent = NULL;
    this->controlNode = NULL;
    this->cVar = false;
    this->children = {};
}
void TNode::setParent(TNode p) {
    this->parent = &p;
}
void TNode::addChild(TNode c) {
    this->children.push_back(&c);
}
void TNode::setChildren(std::vector<TNode*> childrenVector) {
    this->children = childrenVector;
}
std::vector<TNode*> TNode::getChildren() {
    return this->children;
}
TNode* TNode::getParent() {
    return this->parent;
}
bool TNode::hasControlVar() {
    return this->cVar;
}