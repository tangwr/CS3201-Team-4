#pragma once

#include "DesignExtractor.h"
#include "TableOperations.h"
#include <queue>

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
			if (pkb->isStmtInCallTable(currentStmt)) {
				//cout << "here" << endl;
				int calledProcId = pkb->getProcCalledByStmt(currentStmt);

				//populate current stmt use/modify with the ones from called proc
				populateStmtUseVarFromProc(currentStmt, calledProcId);

				populateStmtUseConstFromProc(currentStmt, calledProcId);

				populateStmtModifyVarFromProc(currentStmt, calledProcId);

				//getting call* of called proc and inserting into the proc containing current stmt
				populateProcCallStar(procId, calledProcId);
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

			populateUseRelFromStmt(procId, containerStmtId, stmtLstStmt[i]);

			//get stmt modifies and set as proc/container stmt modifies

			populateModifyRelFromStmt(procId, containerStmtId, stmtLstStmt[i]);

			//get follow star insert into 1 stmt up
			if (i > 0) {
				populateFollowStarFromStmt(stmtLstStmt[i], stmtLstStmt[i - 1]);
			}

			//get children* for current stmt, set for parent* for container stmt.
			if (containerStmtId != -1) {
				//got container stmt
				populateParentStarForContainerStmt(containerStmtId, stmtLstStmt[i]);
			}
		}
	}
}

void DesignExtractor::extractNextBipRel() {
	//get all stmts
	unordered_set<int> allStmtSet = pkb->getAllStmtId();

	//for all stmt

	for (int stmt : allStmtSet) {
		if (pkb->isStmtInCallTable(stmt)) {
			//if current stmt is call
			int calledProcId = pkb->getProcCalledByStmt(stmt);
			vector<int> procFirstStmt = pkb->getStmtLstContainedInProc(calledProcId);
			for (int element : procFirstStmt) {
				pkb->setStmtNextStmtRel(stmt, element);
			}
        }
        else if (pkb->isStmtInWhileTable(stmt)) {
            //current stmt is while
            int followingStmt = pkb->getStmtFollowStmt(stmt);
            unordered_set<int> containerStmtStarSet = pkb->getStmtParentStarStmt(stmt);
            if (followingStmt == -1 && containerStmtStarSet.empty()) {
                //while is the last in proc
                int currentContainerProcId = pkb->getProcContainingStmt(stmt);
                unordered_set<int> procCallerStmtSet = pkb->getStmtCallProc(currentContainerProcId);
                for (int callerStmt : procCallerStmtSet) {
                    unordered_set<int> callerNextStmtSet = pkb->getNextStmt(callerStmt);
                    for (int callerNextStmt : callerNextStmtSet) {
                        pkb->setStmtNextBipStmtRel(stmt, callerNextStmt);
                    }
                }
                
            }
            //copy next
            copyNext(stmt);
        }
        /*
        Dont think this section is needed because both if then and else last stmt will be process as without next condition.

        */
        //else if (pkb->isStmtInIfTable(stmt)) {
        //    //current stmt is if
        //    int followingStmt = pkb->getStmtFollowStmt(stmt);
        //    unordered_set<int> containerStmtStarSet = pkb->getStmtParentStarStmt(stmt);
        //    if (followingStmt == -1 && containerStmtStarSet.empty()) {

        //    }
        //    //copy next

        
        //}
		else if (pkb->getNextStmt(stmt) == unordered_set<int>()) {
			//no next stmt
			populateNextBipEndOfProc(stmt);
			/*
			int currentContainerProcId = pkb->getProcContainingStmt(stmt);
			unordered_set<int> procCallerStmtSet = pkb->getStmtCallProc(currentContainerProcId);
			for (int callerStmt : procCallerStmtSet) {
				unordered_set<int> callerNextStmtSet = pkb->getNextStmt(callerStmt);
				for (int callerNextStmt : callerNextStmtSet) {
					pkb->setStmtNextBipStmtRel(stmt, callerNextStmt);
				}
			}
			*/
		}
		else {
            copyNext(stmt);
		}
	}
	//if current is a call
		//nextbip go to that proc stmtlst first stmt
	//else if no next
		//check if got stmt call this proc, set this stmt nextBip to the next of the call stmts.
    //else if if stmt
        //copy next
        //check if it is the end by checking last stmt in stmt list got next or not, no next set both last stmt to call proc stmt next
    //else if while stmt
        //copy next
        //check if no more stmt by using follows, if no more set while next to call proc stmt next
	//else
		//set same as next rel
}

void DesignExtractor::populateNextBipEndOfProc(int stmtId) {
	//no next stmt

	int currentContainerProcId = pkb->getProcContainingStmt(stmtId);
	queue<int> callerStmtQueue;
	unordered_set<int> procCallerStmtSet = pkb->getStmtCallProc(currentContainerProcId);

	for (int callerStmtId : procCallerStmtSet) {
		callerStmtQueue.push(callerStmtId);
	}

	while (!callerStmtQueue.empty()) {
		int currentCallerStmt = callerStmtQueue.front();
		callerStmtQueue.pop();
		unordered_set<int> callerNextStmtSet = pkb->getNextStmt(currentCallerStmt);
		if (!callerNextStmtSet.empty()) {
			for (int callerNextStmt : callerNextStmtSet) {
				pkb->setStmtNextBipStmtRel(stmtId, callerNextStmt);
			}
		}
		else {
			int callerContainerProcId = pkb->getProcContainingStmt(stmtId);
			unordered_set<int> callerProcCallerStmtSet = pkb->getStmtCallProc(callerContainerProcId);
			for (int callerProcCallerStmt : callerProcCallerStmtSet) {
				callerStmtQueue.push(callerProcCallerStmt);
			}
		}
	}
}

void DesignExtractor::copyNext(int stmtId) {
	unordered_set<int> nextStmtSet = pkb->getNextStmt(stmtId);
	for (int nextStmt : nextStmtSet) {
		pkb->setStmtNextBipStmtRel(stmtId, nextStmt);
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
    //unordered_set<int> procs = pkb->getAllProcs();
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
	//extract next bip
	extractNextBipRel();
}
