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
/*
bool PKB::setChild(TNode* parent, TNode* child) {
    parent->addChild(child);
    return true;
}
*/

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


int PKB::setProcToAST(PROC p, TNode* r) {
	return NULL;
}

TNode* PKB::getRootAST (PROC p){
	return NULL;
}



void addProcedure(string name){

}
void addVariable(string name){

}
void addStatement(int statementNum, TNodeType type){
	
}

void addFollows(int statementNum, list<int> followList){
	
}
void addParents(int statementNum, list<int> parentList){
	
}
void addUses(int statementNum, string variable){
	
}
void addModifies(int statementNum, string Variable){
	
}
