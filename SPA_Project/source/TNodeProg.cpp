#include "TNodeProg.h"

TNodeProg::TNodeProg() {
    this->controlNode = NULL;
    this->cVar = false;
    this->children = *(new std::vector<TNode*>);
    this->parent = NULL;
    this->name = "none";
    this->nodeType = TNodeType::procNode;
}
TNodeProg::TNodeProg(std::string procName) {
    this->controlNode = NULL;
    this->cVar = false;
    this->children = *(new std::vector<TNode*>);
    this->parent = NULL;
    this->name = procName;
    this->nodeType = TNodeType::procNode;
}
std::string TNodeProg::getName() {
    return this->name;
}
void TNodeProg::setName(std::string newName) {
    this->name = newName;
}
void TNodeProg::setParent(TNode* p) {
    this->parent = p;
}
TNode* TNodeProg::getParent() {
    return this->parent;
}
void TNodeProg::addChild(TNode* c) {
    this->children.push_back(c);
}
void TNodeProg::setChildren(std::vector<TNode*> childrenVector) {
    this->children = childrenVector;
}
std::vector<TNode*> TNodeProg::getChildren() {
    return this->children;
}
bool TNodeProg::hasControlVar() {
    return this->cVar;
}
TNodeType TNodeProg::getType() {
    return this->nodeType;
}