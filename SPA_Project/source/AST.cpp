#include "AST.h"

AST::AST() {
    this->rootNode = NULL;
}

TNode* AST::createTNode(TNodeType nodeType) {

    switch (nodeType) {

        case assignNode: {
            return new TNodeAssign();
        }

        case callNode: {
            return new TNodeCall();
        }

        case constNode: {
            return new TNodeConst();
        }
/*
        case exprNode: {
            return new TNodeExpr();
        }
*/
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
/*
        case refNode: {
            return new TNodeRef();
        }

        case stmtNode: {
            return new TNodeStmt();
        }

        case stmtLstNode: {
            return new TNodeStmtLst();
        }
*/
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
}

void AST::setAsRoot(TNode* root) {
    this->rootNode = root;
}

void AST::setParentChildRelation(TNode* p, TNode* c) {
    p->addChild(c);
    c->setParent(p);
}

void AST::setParent(TNode* p, TNode* c) {
    c->setParent(p);
}

void AST::setChild(TNode* p, TNode* c) {
    p->addChild(c);
}

TNode* AST::getRoot() {
    return this->rootNode;
}

TNode* AST::getParent(TNode* c) {
    return c->getParent();
}
/*
std::vector<TNode*> AST::getChildren(TNode* p) {
    return p.getChildren();
}
*/
bool setName(TNode* node, string name);
bool setValue(TNode* node, int value);
//while
bool setWhileVarNode(TNodeWhile* whileNode, TNodeVar* varNode);
bool setWhileStmtLstNode(TNodeWhile* whileNode, TNodeStmtLst* stmtLstNode);
//if
bool setIfVarNode(TNodeIf* ifNode, TNodeVar* varNode);
bool setIfThenStmtLstNode(TNodeIf* ifNode, TNodeStmtLst* thenStmtLstNode);
bool setIfElseStmtLstNode(TNodeIf* ifNode, TNodeStmtLst* elseStmtLstNode);
//call
//assign
bool setAssignVarNode(TNodeAssign* assignNode, TNodeVar* varNode);
bool setAssignExpString(TNodeAssign* assignNode, string expressionString);
bool setAssignExpNode(TNodeAssign* assignNode, TNodeExpr* expNode);
//var
bool setVarNodeValue(TNodeVar* varNode, int value);
//const
bool setConstNodeValue(TNodeConst* constNode, int value);
//stmtList
bool addStmtLstStmtNode(TNodeStmtLst* stmtLstNode, TNodeStmt* stmtNode);
//proc
bool setProcStmtLstNode(TNodeProc* procNode, TNodeStmtLst* stmtLstNode);
//prog
bool addProgProcNode(TNodeProg* progNode, TNodeProc* procNode);
//opertor
bool setOperLeftExpNode(TNodeOper* operNode, TNodeExpr* expNode);
bool setOperRightExpNode(TNodeOper* operNode, TNodeExpr* expNode);
