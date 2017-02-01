#include "TNodeWhile.h"

TNodeWhile::TNodeWhile() {
    this->parent = NULL;
    this->controlNode = NULL;
    this->stmtNumber = -1;//-1 means undefined
    this->cVar = false;
    this->children = *(new std::vector<TNode*>);
}
TNodeType TNodeWhile::getType() {
    return this->nodeType;
}
void TNodeWhile::setControlNode(TNodeVar* contNode) {
    this->controlNode = contNode;
}
void TNodeWhile::setStmtListNode(TNodeStmtLst * stmtList) {
    this->stmtListNode = stmtList;
}
