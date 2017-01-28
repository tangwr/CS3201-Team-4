#include "TNodeif.h"

TNodeIf::TNodeIf() {
    this->parent = NULL;
    this->controlNode = NULL;
    this->stmtNumber = -1;//-1 means undefined
    this->cVar = false;
    this->children = *(new std::vector<TNode*>);
}