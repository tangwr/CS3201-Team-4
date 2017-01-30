#include "AST.h"

AST::AST() {
    this->rootNode = NULL;
}

TNode* AST::createTNode(nodeType type) {
    return TNode::createTNode(type);
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

    }
    //return &TNode();
    */
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
