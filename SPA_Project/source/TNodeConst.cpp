#include "TNodeConst.h"

TNodeConst::TNodeConst() {
    this->parent = NULL;
    this->children = *(new std::vector<TNode*>);
    this->cVar = false;
    this->operatorValue = "none";
    this->nodeValue = "node";
}
