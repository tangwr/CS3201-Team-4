#pragma once

#include "TNode.h"

class AST {

public:

    TNode createTNode(enum nodeType);
    void setAsRoot(TNode root);
    void setParent(TNode p, TNode c);
    void setChild(TNode p, TNode c);

};