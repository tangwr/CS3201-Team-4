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

int PKB::setProcToAST(PROC p, TNode* r) {
	return NULL;
}

TNode* PKB::getRootAST (PROC p){
	return NULL;
}

TNode PKB::createNode(TNodeType nodeType) {//return TNode object
    TNode* newNode = ast.createTNode(nodeType);
    return *newNode;
}
void PKB::setAsRoot(TNode root) {
    ast.setAsRoot(root);
}
void PKB::setName(TNode node, string name) {

}
void PKB::setValue(TNode node, int value) {//stmt number or constant

}

void addProcedure(String name){

}
void addVariable(String name){

}
void addStatement(int statementNum, TnodeType type){
	
}

void addFollows(int statementNum, list<int> followList){
	
}
void addParents(int statementNum, list<int> parentList){
	
}
void addUses(int statementNum, String variable){
	
}
void addModifies(int statementNum, String Variable){
	
}
