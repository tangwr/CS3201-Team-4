#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"



PKB::PKB() {

}



void PKB::printAllTables() {
	followsTable.printContents();
	modifiesTable.printContents();
	parentTable.printContents();
	procTable.printContents();
	usesTable.printContents();
	variableTable.printContents();
	constTable.printContents();
	whileTable.printContents();
	ifTable.printContents();
	callTable.printContents();
	assignTable.printContents();
    nextTable.printContents();
    stmtLstTable.printContents();
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
	return this->whileTable.getSize() + this->assignTable.getSize() + this->ifTable.getSize() + this->callTable.getSize();
}


unordered_set<int> PKB::getUseStmtInProc(int procId) {
    unordered_set<int> resultSet;
    unordered_set<int> procStmtSet = this->procTable.getProcStmts(procId);
    for (int stmt : procStmtSet) {
        if (this->isStmtInUseTable(stmt)) {
            resultSet.insert(stmt);
        }
    }
    return resultSet;
}

unordered_set<int> PKB::getModifyStmtInProc(int procId) {
    unordered_set<int> resultSet;
    unordered_set<int> procStmtSet = this->procTable.getProcStmts(procId);
    for (int element : procStmtSet) {
        if (this->isStmtInModifyTable(element)) {
            resultSet.insert(element);
        }
    }
    return resultSet;
}

unordered_set<int> PKB::getAllStmtId() {
	return combinedStmtTable.getAllStmtId();
}



int PKB::insertProc(string procName) {
	return this->procTable.insertProc(procName);
}
bool PKB::setProcToStmtRel(int procId, int stmtId) {
    return this->procTable.setProcToStmtRel(procId, stmtId);
}
int PKB::getProcIdByName(string procName) {
    return this->procTable.getProcIndex(procName);
}
string PKB::getProcNameById(int procId) {
    return this->procTable.getProcName(procId);
}
bool PKB::isProcInTable(string procName) {
    return this->procTable.checkProcExistByName(procName);
}
bool PKB::isValidProcId(int procId) {
	return this->procTable.checkProcExistById(procId);
}

int PKB::getProcContainingStmt(int stmtId) {
    return this->procTable.getProcContainStmt(stmtId);
}

unordered_set<int> PKB::getStmtInProc(int procId) {
    return this->procTable.getProcStmts(procId);
}

unordered_set<int> PKB::getAllProcId() {
    return this->procTable.getAllProcId();
}


int PKB::insertVar(string varName) {
	return this->variableTable.insertVar(varName);
}

unordered_set<int> PKB::getAllVarId() {
    return this->variableTable.getAllVarId();
}
string PKB::getVarNameById(int varId) {
	return this->variableTable.getVarNameById(varId);
}
int PKB::getVarIdByName(string varName) {
	return this->variableTable.getVarIndex(varName);
}
bool PKB::isVarInTable(string varName) {
    return this->variableTable.checkVarExistByName(varName);
}


bool PKB::insertConst(int value) {
	return this->constTable.insertConst(value);
}
int PKB::getNumOfConst() {
	return this->constTable.getSize();
}
bool PKB::isConstInTable(int constValue) {
    return this->constTable.checkConstExist(constValue);
}
unordered_set<int> PKB::getAllConst() {
    return this->constTable.getAllConst();
}



bool PKB::setStmtParentStmtRel(int parentStmtId, int childStmtId) {
	return this->parentTable.setStmtParentStmtRel(parentStmtId, childStmtId);
}
bool PKB::insertStmtParentStmtRel(int parentStmtId, int childStmtId) {
	return this->parentTable.insertStmtParentStmtRel(parentStmtId, childStmtId);
}
bool PKB::hasParentRel() {
    return this->parentTable.hasParentRel();
}


int PKB::getStmtParentStmt(int stmtId) {
	return this->parentTable.getParent(stmtId);
}
unordered_set<int> PKB::getStmtParentStarStmt(int stmtId) {
	return this->parentTable.getStmtParentStarStmt(stmtId);
}
unordered_set<int> PKB::getStmtChildrenStmt(int stmtId) {
	return this->parentTable.getStmtChildrenStmt(stmtId);
}
unordered_set<int> PKB::getStmtChildrenStarStmt(int stmtId) {
	return this->parentTable.getStmtChildrenStarStmt(stmtId);
}



bool PKB::setStmtFollowStmtRel(int stmtId, int followsId) {
	return this->followsTable.setStmtFollowStmtRel(stmtId, followsId);
}
bool PKB::insertStmtFollowStmtRel(int followeeId, int followerId) {
	return this->followsTable.insertStmtFollowStmtRel(followeeId, followerId);
}
bool PKB::hasFollowRel() {
    return this->followsTable.hasFollowRel();
}


int PKB::getStmtFollowStmt(int stmtId) {
	return this->followsTable.getDirectFollow(stmtId);
}
int PKB::getStmtFollowedByStmt(int stmtId) {
	return this->followsTable.getDirectFollowedBy(stmtId);
}
unordered_set<int> PKB::getStmtFollowStarStmt(int stmtId) {
	return this->followsTable.getStmtFollowStarStmt(stmtId);
}
unordered_set<int> PKB::getStmtFollowedByStarStmt(int stmtId) {
	return this->followsTable.getStmtFollowedByStarStmt(stmtId);
}



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
bool PKB::insertStmtModifyVarRel(int stmtId, int varId) {
    return this->modifiesTable.insertStmtModifyVarRel(stmtId, varId);
}

bool PKB::insertProcModifyVarRel(int procId, int varId) {
    return this->modifiesTable.insertProcModifyVarRel(procId, varId);
}


unordered_set<int> PKB::getStmtModifyVar(int varId) {
	return this->modifiesTable.getStmtModifyVar(varId);
}
unordered_set<int> PKB::getVarModifiedInStmt(int stmtId) {
	return this->modifiesTable.getVarModifiedInStmt(stmtId);
}
unordered_set<int> PKB::getProcModifyVar(int varId) {
	return this->modifiesTable.getProcModifyVar(varId);
}
unordered_set<int> PKB::getVarModifiedInProc(int procId) {
	return this->modifiesTable.getVarModifiedInProc(procId);
}
unordered_set<int> PKB::getAllModifyStmt() {
    return this->modifiesTable.getAllStmt();
}
bool PKB::isStmtInModifyTable(int stmtId) {
    return this->modifiesTable.checkStmtExist(stmtId);
}
bool PKB::hasModifyRel(int stmtId, int varId) {
    return this->modifiesTable.checkStmtVarRelExist(stmtId, varId);
}




bool PKB::setStmtUseVarRel(int stmtId, int varId) {
	if (!this->isValidVarId(varId)) {
		return false;
	}
	return this->usesTable.setStmtUseVarRel(stmtId, varId);
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
    return this->usesTable.insertStmtUseVarRel(stmtId, varId);
}

bool PKB::insertStmtUseConstRel(int stmtId, int constId) {
    return this->usesTable.insertStmtUseConstRel(stmtId, constId);
}

bool PKB::insertProcUseVarRel(int procId, int varId) {
    return this->usesTable.insertProcUseVarRel(procId, varId);
}

bool PKB::insertProcUseConstRel(int procId, int constId) {
    return this->usesTable.insertStmtUseConstRel(procId, constId);
}



unordered_set<int> PKB::getVarUsedByStmt(int stmtId) {
	return this->usesTable.getVarUsedByStmt(stmtId);
}
unordered_set<int> PKB::getStmtUseVar(int varId) {
	return this->usesTable.getStmtUseVar(varId);
}
unordered_set<int> PKB::getVarUsedByProc(int procId) {
	return this->usesTable.getVarUsedByProc(procId);
}
unordered_set<int> PKB::getProcUseVar(int varId) {
	return this->usesTable.getProcUseVar(varId);
}
unordered_set<int> PKB::getConstUsedByStmt(int stmtId) {
	return this->usesTable.getConstUsedByStmt(stmtId);
}
unordered_set<int> PKB::getStmtUseConst(int constId) {
	return this->usesTable.getStmtUseConst(constId);
}
unordered_set<int> PKB::getConstUsedByProc(int procId) {
	return this->usesTable.getConstUsedByProc(procId);
}
unordered_set<int> PKB::getProcUseConst(int constId) {
	return this->usesTable.getProcUseConst(constId);
}
unordered_set<int> PKB::getAllUseStmt() {
    return this->usesTable.getAllStmtId();
}
bool PKB::isStmtInUseTable(int stmtId) {
    return this->usesTable.checkStmtExist(stmtId);
}
bool PKB::checkStmtVarUseRelExist(int stmtId, int varId) {
    return this->usesTable.checkStmtVarRelExist(stmtId, varId);
}




bool PKB::setExpToAssignStmt(int stmtId, string expression) {
	this->combinedStmtTable.insertStmt(stmtId);
	return this->assignTable.setExpToAssignStmt(stmtId, expression);
}

unordered_set<int> PKB::getAllAssignStmt() {
	return this->assignTable.getAllStmtId();
}
string PKB::getExpInAssignStmt(int stmtId) {
	return this->assignTable.getExpInAssignStmt(stmtId);
}

bool PKB::isStmtInAssignTable(int stmtId) {
	return this->assignTable.isStmtInTable(stmtId);
}

bool PKB::setVarAtLeftOfAssignStmt(int assignStmtId, int varId) {
    return this->assignTable.setVarToAssignStmt(assignStmtId, varId);
}

int PKB::getVarAtLeftOfAssignStmt(int assignStmtId) {
    return this->assignTable.getAssignedVarInAssignStmt(assignStmtId);
}

unordered_set<int> PKB::getStmtInAssignWithVar(int varId) {
    return this->assignTable.getStmtWithCtrlVar(varId);
}



bool PKB::setVarToWhileStmt(int stmtId, int varId) {
	if (!this->isValidVarId(varId)) {
		return false;
	}
	this->combinedStmtTable.insertStmt(stmtId);
	return this->whileTable.setVarToWhileStmt(stmtId, varId);
}

unordered_set<int> PKB::getAllWhileStmt() {
	return this->whileTable.getAllStmtId();
}
int PKB::getCtrlVarInWhileStmt(int stmtId) {
	return this->whileTable.getCtrlVarInWhileStmt(stmtId);
}

bool PKB::isStmtInWhileTable(int stmtId) {
	return this->whileTable.isStmtInTable(stmtId);
}



bool PKB::setVarToIfStmt(int stmtId, int varId) {
	if (!this->isValidVarId(varId)) {
		return false;
	}
	this->combinedStmtTable.insertStmt(stmtId);
	return this->ifTable.setVarToIfStmt(stmtId, varId);
}

int PKB::getCtrlVarInIfStmt(int stmtId) {
	return this->ifTable.getCtrlVarInIfStmt(stmtId);
}

unordered_set<int> PKB::getStmtInIfWithCtrlVar(int varId) {
    return this->ifTable.getStmtWithCtrlVar(varId);
}

bool PKB::isStmtInIfTable(int stmtId) {
	return this->ifTable.isStmtInTable(stmtId);
}

unordered_set<int> PKB::getAllIfId() {
    return this->ifTable.getAllIfId();
}



bool PKB::setStmtCallProcRel(int stmtId, int procId) {
	if (!this->isValidProcId(procId)) {
		return false;
	}
	this->combinedStmtTable.insertStmt(stmtId);
	return this->callTable.setStmtCallProcRel(stmtId, procId);
}
bool PKB::setProcCallProcRel(int callerProcId, int calledProcId) {
	if (!this->isValidProcId(callerProcId) || !this->isValidProcId(calledProcId)) {
		return false;
	}
    return this->callTable.setProcCallProcRel(callerProcId, calledProcId);
}

bool PKB::insertProcCallStarProcRel(int callerProcId, int calledStarProcId) {
    return this->callTable.insertProcCallStarProcRel(callerProcId, calledStarProcId);
}

bool PKB::isStmtInCallTable(int stmtId) {
    return this->callTable.isStmtInTable(stmtId);
}

int PKB::getProcCalledByStmt(int callStmtId) {
    return this->callTable.getProcCalledByStmt(callStmtId);
}

unordered_set<int> PKB::getStmtCallProc(int procId) {
    return this->callTable.getCallerStmtCallProc(procId);
}

unordered_set<int> PKB::getProcCallProc(int calledProcId) {
    return this->callTable.getCallerProcCallProc(calledProcId);
}

unordered_set<int> PKB::getProcCalledByProc(int callerProcId) {
    return this->callTable.getProcCalledByProc(callerProcId);
}

unordered_set<int> PKB::getAllCallId() {
    return this->callTable.getAllCallId();
}

unordered_set<int> PKB::getProcCalledByStarProc(int callerProcId) {
    return this->callTable.getProcCalledByStarProc(callerProcId);
}


bool PKB::setStmtNextStmtRel(int currentStmtId, int nextStmtId) {
    return this->nextTable.setStmtNextStmtRel(currentStmtId, nextStmtId);
}

unordered_set<int> PKB::getNextStmt(int currentStmtId) {
    return this->nextTable.getNextStmt(currentStmtId);
}

unordered_set<int> PKB::getPreviousStmt(int currentStmtId) {
    return this->nextTable.getPreviousStmt(currentStmtId);
}


bool PKB::setProcStmtLstContainsStmtRel(int procId, int stmtId) {
    return this->stmtLstTable.setProcStmtLstContainsStmtRel(procId, stmtId);
}

bool PKB::setContainerStmtStmtLstContainsStmtRel(int containerStmtId, int stmtId) {
    return this->stmtLstTable.setContainerStmtStmtLstContainsStmtRel(containerStmtId, stmtId);
}

vector<int> PKB::getStmtLstContainedInProc(int procId) {
    return this->stmtLstTable.getStmtLstContainedInProc(procId);
}

vector<int> PKB::getStmtlstContainedInContainerStmt(int containerStmtId) {
    return this->stmtLstTable.getStmtlstContainedInContainerStmt(containerStmtId);
}

unordered_set<int> PKB::getAllStmtLst() {
    return this->stmtLstTable.getAllStmtLst();
}


unordered_set<int> PKB::getStmtInWhileWithCtrlVar(int varId) {
    return this->whileTable.getStmtWithCtrlVar(varId);
}

