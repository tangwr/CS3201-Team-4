#include "TNodeMinus.h"

TNodeMinus::TNodeMinus() {
    this->operatorValue = "-";
    this->parent = NULL;
    this->children = *(new std::vector<TNode*>);
    this->cVar = false;
}