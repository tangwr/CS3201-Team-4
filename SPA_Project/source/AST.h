#pragma once

#include "TNode.h"
#include <vector>

class AST {

private:

    TNode* rootNode;

public:

    AST();
    TNode* createTNode(enum nodeType);
    void setAsRoot(TNode root);
    void setParent(TNode p, TNode c);
    void setChild(TNode p, TNode c);
    TNode* getRoot();
    TNode* getParent(TNode c);
    std::vector<TNode*> getChildren(TNode p);

};