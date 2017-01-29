#include "TNodeProc.h"

TNodeProc::TNodeProc() {
    this->controlNode = NULL;
    this->cVar = false;
    this->children = *(new std::vector<TNode*>);
    this->parent = NULL;
    this->name = "none";
}
TNodeProc::TNodeProc(std::string procName) {
    this->controlNode = NULL;
    this->cVar = false;
    this->children = *(new std::vector<TNode*>);
    this->parent = NULL;
    this->name = procName;
}
std::string TNodeProc::getName() {
    return this->name;
}
void TNodeProc::setName(std::string newName) {
    this->name = newName;
}