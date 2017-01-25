#pragma once
class TNode
{
private:
    TNode* parent;
    TNode* child;
public:
    void TNode::setParent(TNode p);
    void TNode::setChild(TNode c);
    TNode TNode::getChild();
    TNode TNode::getParent();
};