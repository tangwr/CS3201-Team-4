#pragma once

#include "TNode.h"

class AST {

private:

    TNode rootNode;

public:

    TNode createTNode(enum nodeType);
    void setAsRoot(TNode root);
    void setParent(TNode p, TNode c);
    void setChild(TNode p, TNode c);
    TNode getRoot();
    TNode getParent(TNode c);
    TNode getChild(TNode p);

};