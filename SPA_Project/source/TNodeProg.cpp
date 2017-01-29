#include "TNodeProg.h"

TNodeProg::TNodeProg() {
    this->controlNode = NULL;
    this->cVar = false;
    this->children = *(new std::vector<TNode*>);
    this->parent = NULL;
    this->name = "none";
}
TNodeProg::TNodeProg(std::string procName) {
    this->controlNode = NULL;
    this->cVar = false;
    this->children = *(new std::vector<TNode*>);
    this->parent = NULL;
    this->name = procName;
}
std::string TNodeProg::getName() {
    return this->name;
}
void TNodeProg::setName(std::string newName) {
    this->name = newName;
}
