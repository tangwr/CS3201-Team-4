#include "AST.h"

AST::AST() {
    this->rootNode = NULL;
}
TNode* AST::createTNode(nodeType type) {
    switch (type) {

        case assignNode: {
            return &TNodeAssign();
        }

        case callNode: {
            return &TNodeCall();
        }

        case constNode: {
            return &TNodeConst();
        }

        case exprNode: {
            return &TNodeExpr();
        }

        case ifNode: {
            return &TNodeIf();
        }

        case minusNode: {
            return &TNodeMinus();
        }

        case plusNode: {
            return &TNodePlus();
        }

        case procNode: {
            return &TNodeProc();
        }

        case progNode: {
            return &TNodeProg();
        }

        case refNode: {
            return &TNodeRef();
        }

        case stmtNode: {
            return &TNodeStmt();
        }

        case stmtLstNode: {
            return &TNodeStmtLst();
        }

        case timesNode: {
            return &TNodeTimes();
        }

        case varNode: {
            return &TNodeVar();
        }

        case whileNode: {
            return &TNodeWhile();
        }

    }
    //return &TNode();
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
