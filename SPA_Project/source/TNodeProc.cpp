#include "TNodeProc.h"

TNodeProc::TNodeProc() {
    this->controlNode = NULL;
    this->cVar = false;
    this->children = *(new std::vector<TNode*>);
    this->parent = NULL;
    this->name = "none";
    this->nodeType = TNodeType::procNode;
}
TNodeProc::TNodeProc(std::string procName) {
    this->controlNode = NULL;
    this->cVar = false;
    this->children = *(new std::vector<TNode*>);
    this->parent = NULL;
    this->name = procName;
    this->nodeType = TNodeType::procNode;
}
std::string TNodeProc::getName() {
    return this->name;
}
void TNodeProc::setName(std::string newName) {
    this->name = newName;
}

void TNodeProc::setParent(TNode* p) {
    this->parent = p;
}
TNode* TNodeProc::getParent() {
    return this->parent;
}
void TNodeProc::addChild(TNode* c) {
    this->children.push_back(c);
}
void TNodeProc::setChildren(std::vector<TNode*> childrenVector) {
    this->children = childrenVector;
}
std::vector<TNode*> TNodeProc::getChildren() {
    return this->children;
}
bool TNodeProc::hasControlVar() {
    return this->cVar;
}
TNodeType TNodeProc::getType() {
    return this->nodeType;
}
