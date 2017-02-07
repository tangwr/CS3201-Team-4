#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
//#include "TNode.h"


//constructor
PKB::PKB() {

}


//general functions
void PKB::printAllTables() {
	followsTable.printContents();
	modifiesTable.printContents();
	parentTable.printContents();
	procTable.printContents();
	usesTable.printContents();
	//variableTable.printContents(); waiting for implementation
	constTable.printContents();
	whileTable.printContents();
	ifTable.printContents();
	callTable.printContents();
	assignTable.printContents();
}

bool PKB::isValidVarId(int varId) {
	return this->variableTable.checkVarExistById(varId);
}
bool PKB::isValidVar(string varName) {
	return this->variableTable.checkVarExistByName(varName);
}
bool PKB::isValidConst(int constId) {
	return this->constTable.checkConstExist(constId);
}

int PKB::getNumOfStmt() {
	return this->whileTable.getSize() + this->assignTable.getSize();
}
vector<int> PKB::getAllStmtId() {//currently only returning while and assignment statements
	vector<int> combinedLst;

	vector<int> whileStmtId = this->getAllWhileStmt();
	vector<int> assignStmtId = this->getAllAssignStmt();
	std::sort(whileStmtId.begin(), whileStmtId.end());
	std::sort(assignStmtId.begin(), assignStmtId.end());

	set_union(whileStmtId.begin(), whileStmtId.end(), assignStmtId.begin(), assignStmtId.end(), back_inserter(combinedLst));
	return combinedLst;
}


//proc table
int PKB::insertProc(string procName) {
	return this->procTable.insertProc(procName);
}


//variable table
int PKB::insertVar(string varName) {
	return this->variableTable.insertVar(varName);
}

vector<int> PKB::getAllVarId() {
	return this->variableTable.getAllVarId();
}
string PKB::getVarNameById(int varId) {
	return this->variableTable.getVarNameById(varId);
}
int PKB::getVarIdByName(string varName) {
	return this->variableTable.getVarIndex(varName);
}


//const table
int PKB::insertConst(int value) {
	return this->constTable.insertConst(value);//constname?
}
int PKB::getNumOfConst() {
	return this->constTable.getSize();
}

int PKB::getConstValueById(int constId) {
	return this->constTable.getValueById(constId);
}
vector<int> PKB::getAllConstId() {
    return this->constTable.getAllConstId();
}



//parent table
bool PKB::setStmtParentStmtRel(int parent, int child) {
	return this->parentTable.setStmtParentStmtRel(parent, child);//check param order
}
bool PKB::insertStmtParentStmtRel(int parent, int child) {
	return this->parentTable.insertStmtParentStmtRel(parent, child);
}
bool PKB::hasParentRel() {
    return this->parentTable.hasParentRel();//yet to implement
}


int PKB::getStmtParentStmt(int stmtId) {
	return this->parentTable.getParent(stmtId);
}
vector<int> PKB::getStmtParentStarStmt(int stmtId) {
	return this->parentTable.getStmtParentStarStmt(stmtId);
}
vector<int> PKB::getStmtChildrenStmt(int stmtId) {
	return this->parentTable.getStmtChildrenStmt(stmtId);
}
vector<int> PKB::getStmtChildrenStarStmt(int stmtId) {
	return this->parentTable.getStmtChildrenStarStmt(stmtId);
}


//follow table
bool PKB::setStmtFollowStmtRel(int stmtId, int followsId) {
	return this->followsTable.setStmtFollowStmtRel(stmtId, followsId);//check order
}
bool PKB::insertStmtFollowStmtRel(int stmtId, int followNum) {
	return this->followsTable.insertStmtFollowStmtRel(stmtId, followNum);//check param order
}
bool PKB::hasFollowRel() {
    return this->followsTable.hasFollowRel();//yet to implement
}


int PKB::getStmtFollowStmt(int stmtId) {
	return this->followsTable.getDirectFollow(stmtId);
}
int PKB::getStmtFollowedByStmt(int stmtId) {
	return this->followsTable.getDirectFollowedBy(stmtId);
}
vector<int> PKB::getStmtFollowStarStmt(int stmtId) {
	return this->followsTable.getStmtFollowStarStmt(stmtId);
}
vector<int> PKB::getStmtFollowedByStarStmt(int stmtId) {
	return this->followsTable.getStmtFollowedByStarStmt(stmtId);
}


//modifies table
bool PKB::setStmtModifyVarRel(int stmtId, int varId) {
	if (!this->isValidVarId(varId)) {
		return false;
	}
	return this->modifiesTable.setStmtModifyVarRel(stmtId, varId);
}
bool PKB::setProcModifyVarRel(int procId, int varId) {
	if (!this->isValidVarId(varId)) {
		return false;
	}
	return this->modifiesTable.setProcModifyVarRel(procId, varId);
}
bool PKB::setStmtModifyProcRel(int stmtId, int varId) {
	if (!this->isValidVarId(varId)) {
		return false;
	}
	return this->modifiesTable.setProcModifyVarRel(stmtId, varId);//original call set Proc Modify Rel check correctness
}
bool PKB::insertStmtModifyVarRel(int stmtId, int varId) {
    return this->modifiesTable.insertStmtModify(stmtId, varId);//yet implemented by table
}


vector<int> PKB::getStmtModifyVar(int varId) {
	return this->modifiesTable.getStmtModifyVar(varId);
}
vector<int> PKB::getVarModifiedInStmt(int stmtId) {
	return this->modifiesTable.getVarModifiedInStmt(stmtId);
}
vector<int> PKB::getProcModifyVar(int varId) {//get procs which modifies the given var
	return this->modifiesTable.getProcModifyVar(varId);
}
vector<int> PKB::getVarModifiedInProc(int stmtId) {
	return this->modifiesTable.getVarModifiedInProc(stmtId);
}
vector<int> PKB::getAllModifyStmt() {
    return this->modifiesTable.getAllStmt();
}
bool PKB::isStmtInModifyTable(int stmtId) {
    return this->modifiesTable.checkStmtExist(stmtId);
}
bool PKB::hasModifyRel(int stmtId, int varId) {
    return this->modifiesTable.checkStmtVarRelExist(stmtId, varId);
}



//uses table
bool PKB::setStmtUseStmtRel(int stmtId, int varId) {
	if (!this->isValidVarId(varId)) {
		return false;
	}
	return this->usesTable.setStmtUseStmtRel(stmtId, varId);
}
bool PKB::setStmtUseConstRel(int stmtId, int constId) {
	if (!this->isValidConst(constId)) {
		return false;
	}
	return this->usesTable.setStmtUseConstRel(stmtId, constId);
}
bool PKB::setProcUseVarRel(int procId, int varId) {
	if (!this->isValidVarId(varId)) {
		return false;
	}
	return this->usesTable.setProcUseVarRel(procId, varId);
}
bool PKB::setProcUseConstRel(int procId, int constId) {
	if (!this->isValidConst(constId)) {
		return false;
	}
	return this->usesTable.setProcUseConstRel(procId, constId);
}
bool PKB::insertStmtUseVarRel(int stmtId, int varId) {
    return this->usesTable.insertStmtUseRel(stmtId, varId);
}



vector<int> PKB::getVarUsedByStmt(int stmtId) {
	return this->usesTable.getVarUsedByStmt(stmtId);
}
vector<int> PKB::getStmtUseVar(int varId) {
	return this->usesTable.getStmtUseVar(varId);
}
vector<int> PKB::getVarUsedByProc(int procId) {
	return this->usesTable.getVarUsedByProc(procId);
}
vector<int> PKB::getProcUseVar(int varId) {
	return this->usesTable.getProcUseVar(varId);
}
vector<int> PKB::getConstUsedByStmt(int stmtId) {
	return this->usesTable.getConstUsedByStmt(stmtId);
}
vector<int> PKB::getStmtUseConst(int constId) {
	return this->usesTable.getStmtUseConst(constId);
}
vector<int> PKB::getConstUsedByProc(int procId) {
	return this->usesTable.getConstUsedByProc(procId);
}
vector<int> PKB::getProcUseConst(int constId) {
	return this->usesTable.getProcUseConst(constId);
}
vector<int> PKB::getAllUseStmt() {
    return this->usesTable.getAllStmt();
}
bool PKB::isStmtInUseTable(int stmtId) {
    return this->usesTable.checkStmtExist(stmtId);
}
bool PKB::checkStmtVarUseRelExist(int stmtId, int varId) {
    return this->usesTable.checkStmtVarRelExist(stmtId, varId);
}



//assign table
bool PKB::setExpToAssignStmt(int stmtId, string expression) {
	return this->assignTable.setExpToAssignStmt(stmtId, expression);
}

vector<int> PKB::getAllAssignStmt() {
	return this->assignTable.getAllStmtId();
}
string PKB::getExpInAssignStmt(int stmtId) {
	return this->assignTable.getExpInAssignStmt(stmtId);
}

bool PKB::isStmtInAssignTable(int stmtId) {
	return this->assignTable.isStmtInTable(stmtId);
}


//while table
bool PKB::setVarToWhileStmt(int stmtId, int varId) {
	if (!this->isValidVarId(varId)) {
		return false;
	}
	return this->whileTable.setVarToWhileStmt(stmtId, varId);
}

vector<int> PKB::getAllWhileStmt() {
	return this->whileTable.getAllStmtId();
}
int PKB::getVarInWhileStmt(int stmtId) {
	return this->whileTable.getVarInWhileStmt(stmtId);
}

bool PKB::isStmtInWhileTable(int stmtId) {
	return this->whileTable.isStmtInTable(stmtId);
}


//if table
bool PKB::setVarToIfStmt(int stmtId, int varId) {
	if (!this->isValidVarId(varId)) {
		return false;
	}
	return this->ifTable.setVarToIfStmt(stmtId, varId);
}

int PKB::getVarInIfStmt(int stmtId) {
	return this->ifTable.getVarInIfStmt(stmtId);
}

bool PKB::isStmtInIfTable(int stmtId) {
	return this->ifTable.isStmtInTable(stmtId);
}


//call table
bool PKB::setStmtCallProc(int stmtId, int varId) {
	if (!this->isValidVarId(varId)) {
		return false;
	}
	return this->callTable.setStmtCallProc(stmtId, varId);
}


/*
bool PKB::setFollowedByDirectRel(int stmtId, int followedByIndex) {

}
bool PKB::setModifiedByDirectRel(int stmtId, int varId) {

}
bool PKB::setUsedByDirectRel(int stmtId, int varId) {

}
*/


//deprecated AST API
/*
int PKB::setProcToAST(PROC p, TNode* r) {
return NULL;//ast on hold
}

TNode* PKB::getRootAST (PROC p){
return NULL;//ast on hold
}
*/
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