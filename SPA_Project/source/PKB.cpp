#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"

PKB::PKB() {

}

bool PKB::isValidVarId(int varId) {
    return this->variableTable.checkVarExistById(varId);
}
bool PKB::isValidVar(string varName) {
    return this->variableTable.checkVarExistByName(varName);
}
/*
TNode* PKB::createNode(TNodeType nodeType) {//return TNode object
    TNode* newNode = ast.createTNode(nodeType);
    return newNode;
}
void PKB::setAsRoot(TNode* root) {
    ast.setAsRoot(root);
}
void PKB::setName(TNode* node, string name) {
    ast.setName(node, name);
}

void PKB::setValue(TNode* node, int value) {//stmt number or constant
    ast.setValue(node, value);
}


bool PKB::setParent(TNode* parent, TNode* child) {
    ast.setParent(parent, child);
    return true;
}

bool PKB::setChild(TNode* parent, TNode* child) {
parent->addChild(child);
return true;
}


//while
bool PKB::setWhileVarNode(TNodeWhile* whileNode, TNodeVar* varNode) {
    //whileNode->setControlNode(varNode);
    ast.setWhileVarNode(whileNode, varNode);
    return true;
}
bool PKB::setWhileStmtLstNode(TNodeWhile* whileNode, TNodeStmtLst* stmtLstNode) {
    ast.setWhileStmtLstNode(whileNode, stmtLstNode);
    //whileNode->setStmtListNode(stmtLstNode);
    return true;
}
//if
bool PKB::setIfVarNode(TNodeIf* ifNode, TNodeVar* varNode) {
    ast.setIfVarNode(ifNode, varNode);
    return true;
}
bool PKB::setIfThenStmtLstNode(TNodeIf* ifNode, TNodeStmtLst* thenStmtLstNode) {
    ast.setIfThenStmtLstNode(ifNode, thenStmtLstNode);
    return true;
}
bool PKB::setIfElseStmtLstNode(TNodeIf* ifNode, TNodeStmtLst* elseStmtLstNode) {
    ast.setIfElseStmtLstNode(ifNode, elseStmtLstNode);
    return true;
}
//call
//assign
bool PKB::setAssignVarNode(TNodeAssign* assignNode, TNodeVar* varNode) {
    ast.setAssignVarNode(assignNode, varNode);
    return true;
}
bool PKB::setAssignExpString(TNodeAssign* assignNode, string expressionString) {
    ast.setAssignExpString(assignNode, expressionString);
    return true;
}
bool PKB::setAssignExpNode(TNodeAssign* assignNode, TNodeExpr* expNode) {
    ast.setAssignExpNode(assignNode, expNode);
    return true;
}
//var
bool PKB::setVarNodeValue(TNodeVar* varNode, int value) {
    ast.setVarNodeValue(varNode, value);
    return true;
}
//const
bool PKB::setConstNodeValue(TNodeConst* constNode, int value) {
    ast.setConstNodeValue(constNode, value);
    return true;
}
//stmtList
bool PKB::addStmtLstStmtNode(TNodeStmtLst* stmtLstNode, TNodeStmt* stmtNode) {
    ast.addStmtLstStmtNode(stmtLstNode, stmtNode);
    return true;
}
//proc
bool PKB::setProcStmtLstNode(TNodeProc* procNode, TNodeStmtLst* stmtLstNode) {
    ast.setProcStmtLstNode(procNode, stmtLstNode);
    return true;
}
//prog
bool PKB::addProgProcNode(TNodeProg* progNode, TNodeProc* procNode) {
    ast.addProgProcNode(progNode, procNode);
    return true;
}
//operator
bool PKB::setOperLeftExpNode(TNodeOper* operNode, TNodeExpr* expNode) {
    ast.setOperLeftExpNode(operNode, expNode);
    return true;
}
bool PKB::setOperRightExpNode(TNodeOper* operNode, TNodeExpr* expNode) {
    ast.setOperRightExpNode(operNode, expNode);
    return true;
}
*/


int PKB::setProcToAST(PROC p, TNode* r) {
	return NULL;//ast on hold
}

TNode* PKB::getRootAST (PROC p){
	return NULL;//ast on hold
}

bool PKB::setFollowDirectRel(int stmtId, int followsId) {
    return this->followsTable.setFollowDirectRel(followsId, stmtId);//check param order
}
bool PKB::setParentDirectRel(int parent, int child) {
    return this->parentTable.setParentDirectRel(parent, child);//check param order
}
bool PKB::setModifyRel(int stmtId, int varId) {
    if (!this->isValidVarId(varId)) {
        return false;
    }
    return this->modifiesTable.setModifyDirectRel(stmtId, varId);
}
bool PKB::setUseVarRel(int stmtId, int varId) {
    if (!this->isValidVarId(varId)) {
        return false;
    }
    return this->usesTable.setUseDirectRel(stmtId, varId);
}
bool PKB::setUseConstRel(int stmtId, int constId) {
    return this->usesTable.setUseDirectRelConst(stmtId, constId);
}
/*
bool PKB::setFollowedByDirectRel(int stmtId, int followedByIndex) {

}
bool PKB::setModifiedByDirectRel(int stmtId, int varId) {

}
bool PKB::setUsedByDirectRel(int stmtId, int varId) {

}
*/

bool PKB::insertFollowRel(int stmtId, int followNum) {
    return this->followsTable.insertFollowRel(stmtId, followNum);//check param order
}
bool PKB::insertParentRel(int parent, int child) {
    return this->parentTable.insertParentRel(parent, child);
}
int PKB::insertConst(int value) {
    return this->constTable.insertConst(value);//constname?
}



int PKB::insertVar(string varName) {
    return this->variableTable.insertVar(varName);
}
int PKB::insertProc(string procName) {
    return this->procTable.insertProc(procName);
}

bool PKB::setAssignExp(int stmtId, string expression) {
    return this->assignTable.setAssignExp(stmtId, expression);
}
bool PKB::setWhileCtrlVar(int stmtId, int varId) {
    if (!this->isValidVarId(varId)) {
        return false;
    }
    return this->whileTable.setWhileCtrlVar(stmtId, varId);
}
bool PKB::setIfCtrlVar(int stmtId, int varId) {
    if (!this->isValidVarId(varId)) {
        return false;
    }
    return this->ifTable.setIfCtrlVar(stmtId, varId);
}
bool PKB::setCallProc(int stmtId, int varId) {
    if (!this->isValidVarId(varId)) {
        return false;
    }
    return this->callTable.setCallProc(stmtId, varId);
}

int PKB::getFollowDirect(int stmtId) {
    return this->followsTable.getDirectFollow(stmtId);
}
int PKB::getFollowedByDirect(int stmtId) {
    return this->followsTable.getDirectFollowedBy(stmtId);
}
int PKB::getParentDirect(int stmtId) {
    return this->parentTable.getParent(stmtId);
}
vector<int> PKB::getChildren(int stmtId) {
    return this->parentTable.getChildrenStar(stmtId);
}
vector<int> PKB::getFollowStar(int stmtId) {
    return this->followsTable.getFollowStar(stmtId);
}
vector<int> PKB::getFollowedByStar(int stmtId) {
    return this->followsTable.getFollowedByStar(stmtId);
}
vector<int> PKB::getParentStar(int stmtId) {
    return this->parentTable.getParentStar(stmtId);
}


