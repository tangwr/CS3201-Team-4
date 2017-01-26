#pragma once
#include <vector>
class TNode
{
private:
    TNode* parent;
    std::vector<TNode*> children;
    TNode* controlVar;
    bool cVar;
public:
    void TNode::setParent(TNode p);
    void TNode::setChild(TNode c);
    std::vector<TNode*> TNode::getChildren();
    TNode TNode::getParent();
    bool hasControlVar();
};