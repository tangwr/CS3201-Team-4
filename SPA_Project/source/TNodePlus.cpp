#include "TNodePlus.h"

TNodePlus::TNodePlus() {
    this->operatorValue = "+";
    this->parent = NULL;
    this->children = *(new std::vector<TNode*>);
    this->cVar = false;
}