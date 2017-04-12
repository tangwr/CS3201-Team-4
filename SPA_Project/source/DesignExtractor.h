#pragma once

#include "PKB.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <vector>


using namespace std;

class DesignExtractor {
public:
	DesignExtractor(PKB *pkbSource);
	void extractStarRelations();

private:
	PKB *pkb;
    void extractProcModifiesUsesStar();
    void recursiveTablePopulation(int procId, unordered_map<int, bool> *isProcInPath, unordered_map<int, bool> *isProcValidated);
    void populateProcRel(int procId, int containerStmtId);
	void populateStmtUseVarFromProc(int stmtId, int calledProcId);
	void populateStmtUseConstFromProc(int stmtId, int calledProcId);
	void populateStmtModifyVarFromProc(int stmtId, int calledProcId);
	void populateProcCallStar(int procId, int calledProcId);
	void populateUseRelFromStmt(int procId, int containerStmtId, int sourceStmtId);
	void populateModifyRelFromStmt(int procId, int containerStmtId, int sourceStmtId);
	void populateFollowStarFromStmt(int sourceStmtId, int targetStmtId);
	void populateParentStarForContainerStmt(int containerStmtId, int sourceStmtId);
};
