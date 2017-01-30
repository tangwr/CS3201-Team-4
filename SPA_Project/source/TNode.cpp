#include "TNode.h"

TNode* TNode::createTNode(nodeType type) {//static method
    /*
    switch (type) {

    case assignNode: {
        return new TNodeAssign();
    }

    case callNode: {
        return new TNodeCall();
    }

    case constNode: {
        return new TNodeConst();
    }

    case exprNode: {
        return new TNodeExpr();
    }

    case ifNode: {
        return new TNodeIf();
    }

    case minusNode: {
        return new TNodeMinus();
    }

    case plusNode: {
        return new TNodePlus();
    }

    case procNode: {
        return new TNodeProc();
    }

    case progNode: {
        return new TNodeProg();
    }

    case refNode: {
        return new TNodeRef();
    }

    case stmtNode: {
        return new TNodeStmt();
    }

    case stmtLstNode: {
        return new TNodeStmtLst();
    }

    case timesNode: {
        return new TNodeTimes();
    }

    case varNode: {
        return new TNodeVar();
    }

    case whileNode: {
        return new TNodeWhile();
    }
    }*/
    return NULL;
}

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