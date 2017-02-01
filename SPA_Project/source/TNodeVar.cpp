#include "TNodeVar.h"

TNodeVar::TNodeVar() {
    this->parent = NULL;
    this->children = *(new std::vector<TNode*>);
    this->cVar = false;
    this->operatorValue = "none";
    this->nodeValue = "node";
}

void TNodeVar::setParent() {
}
