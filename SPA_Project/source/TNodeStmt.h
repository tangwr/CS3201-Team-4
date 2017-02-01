#pragma once
#include "TNode.h"
//#include "TNodeStmtLst.h"

class TNodeStmt : public TNode {
/*    
private:
    TNode* parent;
    std::vector<TNode*> children;
    int stmtNumber;
    TNode* controlNode;
    bool cVar;
*/
public:
    //TNodeStmt();
    virtual void setParent(TNode* p);
    virtual TNode* getParent();
    virtual void setChildren(std::vector<TNode*> childrenVector);
    virtual void addChild(TNode* c);
    virtual std::vector<TNode*> getChildren();
    virtual void setControlNode(TNode* cont);
    virtual void setStmtNumber(int i);
    virtual int getStmtNumber();
    virtual bool hasControlVar();
    
};