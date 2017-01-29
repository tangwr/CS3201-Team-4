#include "AST.h"

AST::AST() {
    this->rootNode = NULL;
}
TNode* AST::createTNode(nodeType type) {
    return &TNode();
}

void AST::setAsRoot(TNode root) {
    this->rootNode = &root;
}

void AST::setParent(TNode p, TNode c) {
    c.setParent(p);
}

void AST::setChild(TNode p, TNode c) {
    p.addChild(c);
}

TNode* AST::getRoot() {
    return this->rootNode;
}

TNode* AST::getParent(TNode c) {
    return c.getParent();
}

std::vector<TNode*> AST::getChildren(TNode p) {
    return p.getChildren();
}
