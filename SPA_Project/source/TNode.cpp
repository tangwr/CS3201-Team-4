#include "TNode.h"
void TNode::setParent(TNode p) {
    this->parent = &p;
}
void TNode::setChild(TNode c) {
    this->child = &c;
}
TNode TNode::getChild() {
    return *this->child;
}
TNode TNode::getParent() {
    return *this->parent;
}