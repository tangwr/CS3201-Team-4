#include "TNodeAssign.h"

TNodeAssign::TNodeAssign() {
    this->parent = NULL;
    this->controlNode = NULL;
    this->stmtNumber = -1;
    this->cVar = false;
    this->children = *(new std::vector<TNode*>);
}