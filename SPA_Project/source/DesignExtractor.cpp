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


void DesignExtractor::recursiveTablePopulation(int procId, unordered_map<int, bool> *isProcInPath, unordered_map<int, bool> *isProcValidated) {
    cout << "procID : "<< procId << endl;
    if (isProcInPath->at(procId)) {        
        throw "Circular call detected";
    }
    isProcInPath->at(procId) = true;

    if (!isProcValidated->at(procId)) {
    	unordered_set<int> calledProcs = pkb->getProcCalledByProc(procId);
        
    	for (auto calledProcId : calledProcs) {
            recursiveTablePopulation(calledProcId, isProcInPath, isProcValidated);
    		isProcInPath->at(calledProcId) = false;
    	}
        populateProcRel(procId, -1);
        isProcValidated->at(procId) = true;
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
			if (pkb->isStmtInCallTable(currentStmt)) {
				int calledProcId = pkb->getProcCalledByStmt(currentStmt);

				populateStmtUseVarFromProc(currentStmt, calledProcId);

				populateStmtUseConstFromProc(currentStmt, calledProcId);

				populateStmtModifyVarFromProc(currentStmt, calledProcId);

				populateProcCallStar(procId, calledProcId);
			}
			else if (pkb->isStmtInWhileTable(currentStmt) || pkb->isStmtInIfTable(currentStmt)) {
				populateProcRel(procId, currentStmt);
			}

			stmtLstStmt.push_back(currentStmt);
			currentStmt = pkb->getStmtFollowStmt(currentStmt);
		}

		for (int i = (int)stmtLstStmt.size() - 1; i >= 0 ; i--) {
			cout << "counter : ";
			cout << i << endl;

			populateUseRelFromStmt(procId, containerStmtId, stmtLstStmt[i]);

			populateModifyRelFromStmt(procId, containerStmtId, stmtLstStmt[i]);

			if (i > 0) {
				populateFollowStarFromStmt(stmtLstStmt[i], stmtLstStmt[i - 1]);
			}

			if (containerStmtId != -1) {
				populateParentStarForContainerStmt(containerStmtId, stmtLstStmt[i]);
			}
		}
	}
}

void DesignExtractor::populateStmtUseVarFromProc(int stmtId, int calledProcId) {
	unordered_set<int> calledProcUsedVarLst = pkb->getVarUsedByProc(calledProcId);
	for (int varId : calledProcUsedVarLst) {
		pkb->insertStmtUseVarRel(stmtId, varId);
	}
}

void DesignExtractor::populateStmtUseConstFromProc(int stmtId, int calledProcId) {
	unordered_set<int> calledProcUsedConstLst = pkb->getConstUsedByProc(calledProcId);
	for (int constId : calledProcUsedConstLst) {
		pkb->insertStmtUseConstRel(stmtId, constId);
	}
}

void DesignExtractor::populateStmtModifyVarFromProc(int stmtId, int calledProcId) {
	unordered_set<int> calledProcModifiedVarLst = pkb->getVarModifiedInProc(calledProcId);
	for (int varId : calledProcModifiedVarLst) {
		pkb->insertStmtModifyVarRel(stmtId, varId);
	}
}

void DesignExtractor::populateProcCallStar(int procId, int calledProcId) {
	unordered_set<int> calledProcCallStarLst = pkb->getProcCalledByStarProc(calledProcId);
	for (int calledStarProcId : calledProcCallStarLst) {
		pkb->insertProcCallStarProcRel(procId, calledStarProcId);
	}
}

void DesignExtractor::populateUseRelFromStmt(int procId, int containerStmtId, int sourceStmtId) {
	unordered_set<int> currentStmtUsedVarLst = pkb->getVarUsedByStmt(sourceStmtId);
	unordered_set<int> currentStmtUsedConstLst = pkb->getConstUsedByStmt(sourceStmtId);

	if (containerStmtId == -1) {
		for (int varId : currentStmtUsedVarLst) {
			pkb->insertProcUseVarRel(procId, varId);
		}
		for (int constVal : currentStmtUsedConstLst) {
			pkb->insertProcUseConstRel(procId, constVal);
		}
	}
	else {
		for (int varId : currentStmtUsedVarLst) {
			pkb->insertStmtUseVarRel(containerStmtId, varId);
		}
		for (int constVal : currentStmtUsedConstLst) {
			pkb->insertStmtUseConstRel(containerStmtId, constVal);
		}
	}
}

void DesignExtractor::populateModifyRelFromStmt(int procId, int containerStmtId, int sourceStmtId) {
	unordered_set<int> currentStmtModifiedVarLst = pkb->getVarModifiedInStmt(sourceStmtId);
	for (int varId : currentStmtModifiedVarLst) {
		if (containerStmtId == -1) {
			pkb->insertProcModifyVarRel(procId, varId);
		}
		else {
			pkb->insertStmtModifyVarRel(containerStmtId, varId);
		}
	}
}

void DesignExtractor::populateFollowStarFromStmt(int sourceStmtId, int targetStmtId) {
	unordered_set<int> stmtFollowerStarLst = pkb->getStmtFollowStarStmt(sourceStmtId);
	for (int followerStarStmtId : stmtFollowerStarLst) {
		pkb->insertStmtFollowStmtRel(targetStmtId, followerStarStmtId);
	}
}

void DesignExtractor::populateParentStarForContainerStmt(int containerStmtId, int sourceStmtId) {
	unordered_set<int> currentStmtChildrenStarLst = pkb->getStmtChildrenStarStmt(sourceStmtId);
	for (int childStarStmtId : currentStmtChildrenStarLst) {
		pkb->insertStmtParentStmtRel(containerStmtId, childStarStmtId);
	}
}

void DesignExtractor::extractStarRelations() {
    unordered_set<int> procs = pkb->getAllProcId();
    unordered_map<int, bool> isProcInPath;
    unordered_map<int, bool> isProcValidated;
    for (auto procId : procs) {
        isProcInPath.insert({ procId, false });
        isProcValidated.insert({ procId, false });
    }

    for (auto procId : procs) {
        if (!isProcValidated.at(procId)) {
            recursiveTablePopulation(procId, &isProcInPath, &isProcValidated);
            isProcInPath.at(procId) = false;
        }
        cout << "end iter" << endl;
    }
}
