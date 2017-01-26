#pragma once
#include <vector>
class TNode
{
private:
    TNode* parent;
    std::vector<TNode*> children;
    TNode* controlNode;
    bool cVar;
public:
    TNode();
    void TNode::setParent(TNode p);
    void TNode::setChild(TNode c);
    std::vector<TNode*> TNode::getChildren();
    TNode* TNode::getParent();
    bool hasControlVar();
};