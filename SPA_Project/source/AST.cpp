#include "AST.h"

TNode AST::createTNode(nodeType) {
    return TNode();
}

void AST::setAsRoot(TNode root) {
    this->rootNode = root;
}

void AST::setParent(TNode p, TNode c) {
    c.setParent(p);
}

void AST::setChild(TNode p, TNode c) {
    p.setChild(c)
}

TNode AST::getRoot() {
    return this->rootNode;
}

TNode AST::getParent(TNode c) {
    return c.getParent();
}

vector<TNode*> AST::getChildren(TNode p) {
    return p.getChildren();
}
