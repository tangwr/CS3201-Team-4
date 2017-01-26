#include "TNode.h"
void TNode::setParent(TNode p) {
    this->parent = &p;
}
void TNode::setChild(TNode c) {
    this->children.push_back(&c);
}
std::vector<TNode*> TNode::getChildren() {
    return this->children;
}
TNode TNode::getParent() {
    return *this->parent;
}
bool TNode::hasControlVar() {
    return this->cVar;
}