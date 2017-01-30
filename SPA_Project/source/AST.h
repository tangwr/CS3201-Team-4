#pragma once

#include "TNode.h"
#include "TNodeAssign.h"
#include "TNodeCall.h"
#include "TNodeConst.h"
#include "TNodeExpr.h"
#include "TNodeIf.h"
#include "TNodeMinus.h"
#include "TNodePlus.h"
#include "TNodeProc.h"
#include "TNodeProg.h"
#include "TNodeRef.h"
#include "TNodeStmt.h"
#include "TNodeStmtLst.h"
#include "TNodeTimes.h"
#include "TNodeVar.h"
#include "TNodeWhile.h"

#include <vector>


class AST {

private:

    TNode* rootNode;

public:

    AST();
    TNode* createTNode(nodeType node);
    void setAsRoot(TNode root);
    void setParent(TNode p, TNode c);
    void setChild(TNode p, TNode c);
    TNode* getRoot();
    TNode* getParent(TNode c);
    std::vector<TNode*> getChildren(TNode p);

};