#pragma once

#include "DesignExtractor.h"
#include "TableOperations.h"

using namespace std;


DesignExtractor::DesignExtractor(PKB* pkbSource) {
	pkb = pkbSource;
}

void DesignExtractor::extractProcModifiesUsesStar() {
    unordered_map<int, bool> isProcInPath;
    unordered_map<int, bool> isProcValidated;
    unordered_set<int> procSet = pkb->getAllProcId();
    for (int procId : procSet) {
        recursiveTablePopulation(procId, &isProcInPath, &isProcValidated);
    }
}

void DesignExtractor::extractStarRelations() {
    //unordered_set<int> procs = pkb->getAllProcs();
    unordered_set<int> procs = pkb->getAllProcId();
    unordered_map<int, bool> isProcInPath;
    unordered_map<int, bool> isProcValidated;
    for (auto procId: procs) {
    	isProcInPath.insert({procId, false});
    	isProcValidated.insert({procId, false});
    }

    for (auto procId: procs) {
    	if (!isProcValidated.at(procId)) {
			recursiveTablePopulation(procId, &isProcInPath, &isProcValidated);
    	}
        cout << "end iter" << endl;
    }
}


void DesignExtractor::recursiveTablePopulation(int procId, unordered_map<int, bool> *isProcInPath, unordered_map<int, bool> *isProcValidated) {
    cout << "procID : "<< procId << endl;
    if (isProcInPath->at(procId)) {        
        throw "Circular call detected";
    }
    isProcInPath->at(procId) = true;

    if (!isProcValidated->at(procId)) {
    	unordered_set<int> calledProcs = pkb->getProcCalledByProc(procId);
        //cout << procId << " calls proc ";
        //TableOperations::printUnorderedSet(calledProcs);
        //cout << endl;
        
    	for (auto calledProcId : calledProcs) {
            //cout << "proc " << procId << " called " << calledProcId << endl;

            recursiveTablePopulation(calledProcId, isProcInPath, isProcValidated);
    		isProcInPath->at(calledProcId) = false;
    	}
        populateProcRel(procId, -1);
        //cout << "validate proc : " << procId << endl;
        isProcValidated->at(procId) = true;
    }


}



void DesignExtractor::extractFollowsStar() {
	int statementNum = 0, numOfStatements = pkb->getNumOfStmt(), followStar = 0;
	
	for (int i = 1; i <= numOfStatements; i++) {
		statementNum = i;
		followStar = pkb->getStmtFollowStmt(statementNum);
		followStar = pkb->getStmtFollowStmt(followStar);
		while (followStar != -1) {
			
			pkb->insertStmtFollowStmtRel(statementNum, followStar);
			followStar = pkb->getStmtFollowStmt(followStar);
		}
	}
}

void DesignExtractor::extractParentStar() {
	int statementNum = 0, numOfStatements = pkb->getNumOfStmt(), parentStar = 0;
	for (int i = 1; i <= numOfStatements; i++) {
		statementNum = i;
		parentStar = pkb->getStmtParentStmt(statementNum);
		parentStar = pkb->getStmtParentStmt(parentStar);
		while (parentStar != -1) {
			pkb->insertStmtParentStmtRel(parentStar, statementNum);
			parentStar = pkb->getStmtParentStmt(parentStar);
		}
	}
}

void DesignExtractor::extractModifiesStar() {
    // get all stmt from modify table
    //vector<int> allModifyStmt = pkb->getAllModifyStmt();
    unordered_set<int> allModifyStmt = pkb->getAllModifyStmt();
    // iterate through each stmt, finding their parent *
    for (int stmtId : allModifyStmt) {

        //vector<int> currentVarIdLst = pkb->getVarModifiedInStmt(stmtId);
        //vector<int> currentStmtParentStar = pkb->getStmtParentStarStmt(stmtId);

        unordered_set<int> currentVarIdLst = pkb->getVarModifiedInStmt(stmtId);
        unordered_set<int> currentStmtParentStar = pkb->getStmtParentStarStmt(stmtId);

        for (int currentVarId : currentVarIdLst) {
            for (int parentStmtId : currentStmtParentStar) {
                //if ((pkb->isStmtInModifyTable(parentStmtId)
                //    && pkb->ckeckStmtVarModifiesRelExist(parentStmtId, currentVarId))) {
                //}

				if (!pkb->hasModifyRel(parentStmtId, currentVarId)) {
					pkb->insertStmtModifyVarRel(parentStmtId, currentVarId);
				}
            }
        }
    }
    //for each parent *, set modify relationship
}
void DesignExtractor::extractUsesStar() {
    //vector<int> allUsesStmt = pkb->getAllUseStmt();
    unordered_set<int> allUsesStmt = pkb->getAllUseStmt();

    for (int stmtId : allUsesStmt) {
        //vector<int> currentVarIdLst = pkb->getVarUsedByStmt(stmtId);
        //vector<int> currentStmtParentStar = pkb->getStmtParentStarStmt(stmtId);
        unordered_set<int> currentVarIdLst = pkb->getVarUsedByStmt(stmtId);
        unordered_set<int> currentStmtParentStar = pkb->getStmtParentStarStmt(stmtId);

        for (int currentVarId : currentVarIdLst) {
            for (int parentStmtId : currentStmtParentStar) {
                //only if parent statement in table and already uses given varId then do not insert, else insert
               // if ((pkb->isStmtInUseTable(parentStmtId)
                //    && pkb->checkStmtVarUseRelExist(parentStmtId, currentVarId))) {

//                    pkb->insertStmtUseVarRel(parentStmtId, currentVarId);

				if (!pkb->checkStmtVarUseRelExist(parentStmtId, currentVarId)) {
					pkb->insertStmtUseVarRel(parentStmtId, currentVarId);
                }
            }
        }
    }
}

void DesignExtractor::populateProcRel(int procId, int containerStmtId) {
    vector<int> tempStmtLst;
    if (containerStmtId != -1) {
        tempStmtLst = pkb->getStmtlstContainedInContainerStmt(containerStmtId);
    }
    else {
        tempStmtLst = pkb->getStmtLstContainedInProc(procId);
    }

	for (auto stmtLst : tempStmtLst) {
		vector<int> stmtLstStmt;

		int currentStmt = stmtLst;
		while (currentStmt != -1) {
			//still got follows
			if (pkb->isStmtInCalltable(currentStmt)) {
				cout << "here" << endl;
				int calledProcId = pkb->getProcCalledByStmt(currentStmt);

				//populate current stmt use/modify with the ones from called proc
				unordered_set<int> calledProcUsedVarLst = pkb->getVarUsedByProc(calledProcId);
				for (int varId : calledProcUsedVarLst) {
					pkb->insertStmtUseVarRel(currentStmt, varId);
				}

				unordered_set<int> calledProcUsedConstLst = pkb->getConstUsedByProc(calledProcId);
				for (int constId : calledProcUsedConstLst) {
					pkb->insertStmtUseConstRel(currentStmt, constId);
				}

				unordered_set<int> calledProcModifiedVarLst = pkb->getVarModifiedInProc(calledProcId);
				for (int varId : calledProcModifiedVarLst) {
					//pkb->setProcModifyVarRel(procId, varId);
					pkb->insertStmtModifyVarRel(currentStmt, varId);
				}
				//getting call* of called proc and inserting into the proc containing current stmt
				unordered_set<int> calledProcCallStarLst = pkb->getProcCalledByStarProc(calledProcId);
				for (int calledStarProcId : calledProcCallStarLst) {
					pkb->insertProcCallStarProcRel(procId, calledStarProcId);
				}
			}
			else if (pkb->isStmtInWhileTable(currentStmt) || pkb->isStmtInIfTable(currentStmt)) {
				populateProcRel(procId, currentStmt);
			}

			stmtLstStmt.push_back(currentStmt);//figure out 0 duplicate
			currentStmt = pkb->getStmtFollowStmt(currentStmt);
			//stmtLstStmt.push_back(currentStmt);
		}

		for (int i = (int)stmtLstStmt.size() - 1; i >= 0 ; i--) {
			cout << "counter : ";
			cout << i << endl;

			//check for index out of bound
			//get stmt uses and set as proc/container stmt uses
			unordered_set<int> currentStmtUsedVarLst = pkb->getVarUsedByStmt(stmtLstStmt[i]);
			for (int varId : currentStmtUsedVarLst) {
				if (containerStmtId == -1) {
					pkb->insertProcUseVarRel(procId, varId);
					//use inset
				}
				else {
					pkb->insertStmtUseVarRel(containerStmtId, varId);
				}
			}

			unordered_set<int> currentStmtUsedConstLst = pkb->getConstUsedByStmt(stmtLstStmt[i]);
			for (int constId : currentStmtUsedConstLst) {
				if (containerStmtId == -1) {
					pkb->insertProcUseConstRel(procId, constId);
				}
				else {
					pkb->insertStmtUseConstRel(containerStmtId, constId);
				}
			}
			//get stmt modifies and set as proc/container stmt modifies

			unordered_set<int> currentStmtModifiedVarLst = pkb->getVarModifiedInStmt(stmtLstStmt[i]);
			for (int varId : currentStmtModifiedVarLst) {
				//pkb->setProcModifyVarRel(procId, varId);
				if (containerStmtId == -1) {
					//no container stmt
					pkb->insertProcModifyVarRel(procId, varId);
				}
				else {
					pkb->insertStmtModifyVarRel(containerStmtId, varId);
				}
			}

			//get follow star insert into 1 stmt up
			if (i > 0) {
				unordered_set<int> stmtFollowerStarLst = pkb->getStmtFollowStarStmt(stmtLstStmt[i]);
				int stmtAtPreviousIndex = stmtLstStmt[i - 1];
				for (int followerStarStmtId : stmtFollowerStarLst) {
					pkb->insertStmtFollowStmtRel(stmtAtPreviousIndex, followerStarStmtId);
				}
			}

			//get children* for current stmt, set for parent* for container stmt.
			if (containerStmtId != -1) {
				//got container stmt
				unordered_set<int> currentStmtChildrenStarLst = pkb->getStmtChildrenStarStmt(stmtLstStmt[i]);
				for (int childStarStmtId : currentStmtChildrenStarLst) {
					pkb->insertStmtParentStmtRel(containerStmtId, childStarStmtId);
				}
			}
		}
	}
}
