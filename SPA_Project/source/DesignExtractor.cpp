#pragma once

#include "DesignExtractor.h"
#include "TableOperations.h"

using namespace std;
/*
Unused Code:
unordered_map<int, int> parentsMap, followsMap, followedByMap;
unordered_map<int, vector<int>> childrensMap;
stack<int> statementStack;

int assignedStatementNum;


void processAssign(Tnode currentNode);
void processWhile(Tnode currentNode);
void processProcedure(Tnode currentNode);
void processVariable(Tnode currentNode);
void processArithmetic(Tnode currentNode);
void processStatementList(Tnode* currentNode);
void processChildren(Tnode parent);
*/

DesignExtractor::DesignExtractor(PKB* pkbSource) {
	pkb = pkbSource;
}
/*
void DesignExtractor::extractStarRelations() {
	//extractFollowsStar();
	//extractParentStar();
	//extractModifiesStar();
	//extractUsesStar();
 //   extractProcModifiesUsesStar();
    
}
*/

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
    		unordered_set<int> calledProcs = pkb->getProcCalledByProc(procId);
    		for (auto calledProcId : calledProcs) {
                recursiveTablePopulation(calledProcId, &isProcInPath, &isProcValidated);
                isProcInPath.at(calledProcId) = false;
    		}
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
    vector<int> stmtLstStmt;
    vector<int> tempStmtLst;
    if (containerStmtId != -1) {
        tempStmtLst = pkb->getStmtlstContainedInContainerStmt(containerStmtId);
    }
    else {
        tempStmtLst = pkb->getStmtLstContainedInProc(procId);
    }
    int currentStmt = tempStmtLst[0];
    while (pkb->getStmtFollowStmt(currentStmt) != -1) {
        //still got follows
        if (pkb->isStmtInCalltable(currentStmt)) {
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
        stmtLstStmt.push_back(currentStmt);//figure out 0 duplicate
        currentStmt = pkb->getStmtFollowStmt(currentStmt);
        //stmtLstStmt.push_back(currentStmt);
    }

    //start off by the last one while loop didnt call
    if (pkb->isStmtInCalltable(currentStmt)) {
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
    stmtLstStmt.push_back(currentStmt);//figure out 0 duplicate
    currentStmt = pkb->getStmtFollowStmt(currentStmt);
    //end

    for (int i = 1; i <= (int) stmtLstStmt.size(); i++) {
        cout << "counter : ";
        cout << i << endl;
        int reverseStmtId = stmtLstStmt[(int) stmtLstStmt.size() - i];
        //check for index out of bound
        //get stmt uses and set as proc/container stmt uses
        unordered_set<int> currentStmtUsedVarLst = pkb->getVarUsedByStmt(reverseStmtId);
        for (int varId : currentStmtUsedVarLst) {
            if (containerStmtId == -1) {
                pkb->insertProcUseVarRel(procId, varId);
                //use inset
            }
            else {
                pkb->insertStmtUseVarRel(containerStmtId, varId);
            }
        }

        unordered_set<int> currentStmtUsedConstLst = pkb->getConstUsedByStmt(reverseStmtId);
        for (int constId : currentStmtUsedConstLst) {
            if (containerStmtId == -1) {
                pkb->insertProcUseConstRel(procId, constId);
            }
            else {
                pkb->insertStmtUseConstRel(containerStmtId, constId);
            }
        }
        //get stmt modifies and set as proc/container stmt modifies

        unordered_set<int> currentStmtModifiedVarLst = pkb->getVarModifiedInStmt(reverseStmtId);
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
        if (((int)stmtLstStmt.size() - i) > 0) {
            unordered_set<int> stmtFollowerStarLst = pkb->getStmtFollowStarStmt(reverseStmtId);
            for (int followerStarStmtId : stmtFollowerStarLst) {
                int stmtAtPreviousIndex = stmtLstStmt[(int) stmtLstStmt.size() - (i + 1)];
                pkb->insertStmtFollowStmtRel(stmtAtPreviousIndex, followerStarStmtId);
            }
        }

        //get children* for current stmt, set for parent* for container stmt.
        if (containerStmtId != -1) {
            //got container stmt
            unordered_set<int> currentStmtChildrenStarLst = pkb->getStmtChildrenStarStmt(reverseStmtId);
            for (int childStarStmtId : currentStmtChildrenStarLst) {
                pkb->insertStmtParentStmtRel(containerStmtId, childStarStmtId);
            }
        }

    }
}

/*
void DesignExtractor::recursiveTablePopulation(int procId, unordered_map<int, bool> *isProcInPath,
    unordered_map<int, bool> *isProcValidated) {
    //???NEED CHECK IF GIVEN PROC IS VALIDATED ALREADY???

    //if got circular call
    if (isProcInPath->at(procId)) {
        //throw ERROR_MESSAGE;
        throw "Circular call detected";
    }
    //set visited
    isProcInPath->at(procId) = true;

    //get list of proc this proc calls
    unordered_set<int> calledProcLst = pkb->getProcCalledByProc(procId);

    if (calledProcLst.empty()) {
        //if leaf
        unordered_set<int> currentProcStmtLst = pkb->getStmtInProc(procId);
        for (int stmtId : currentProcStmtLst) {
            //get stmt uses and set as proc uses
            unordered_set<int> currentStmtUsedVarLst = pkb->getVarUsedByStmt(stmtId);
            for (int varId : currentStmtUsedVarLst) {
                pkb->insertProcUseVarRel(procId, varId);
                //use inset
            }

            unordered_set<int> currentStmtUsedConstLst = pkb->getConstUsedByStmt(stmtId);
            for (int constVal : currentStmtUsedConstLst) {
                pkb->insertProcUseConstRel(procId, constVal);
            }
            //get stmt modifies and set as proc modifies

            unordered_set<int> currentStmtModifiedVarLst = pkb->getVarModifiedInStmt(stmtId);
            for (int varId : currentStmtModifiedVarLst) {
                //pkb->setProcModifyVarRel(procId, varId);
                pkb->insertProcModifyVarRel(procId, varId);
            }
        }
        //isProcValidated->at(procId) = true; maybe set after all
    }
    else {
        //unordered_set<int> callStmtContainedInCurrentProcSet;// to keep track of all call statements in proc
        for (int calledProcId : calledProcLst) {
            if (isProcValidated->at(calledProcId) == false) {
                //not validated
                //figure out how to throw
                recursiveTablePopulation(calledProcId, isProcInPath, isProcValidated);
            }
            unordered_set<int> callerStmtLst = pkb->getStmtCallProc(calledProcId);//pkb implement
            unordered_set<int> currentProcStmtLst = pkb->getStmtInProc(procId);
            unordered_set<int> callerStmtInCurrentProcLst;

            //

            for (int callerStmtId : callerStmtLst) {
                if (currentProcStmtLst.find(callerStmtId) != currentProcStmtLst.end()) {
                    callerStmtInCurrentProcLst.insert(callerStmtId);
                    //insert into current proc call stmt set
                    //callStmtContainedInCurrentProcSet.insert(callerStmtId);
                }
            }
            //populate modifies and uses for call stmts in current proc
            //uses
            unordered_set<int> varUsedByCalledProcSet = pkb->getVarUsedByProc(calledProcId);
            for (int currentProcCallerStmtId : callerStmtInCurrentProcLst) {
                for (int usedVarId : varUsedByCalledProcSet) {
                    pkb->insertStmtUseVarRel(currentProcCallerStmtId, usedVarId);
                }
            }

            unordered_set<int> constUsedByCalledProcSet = pkb->getConstUsedByProc(calledProcId);
            for (int currentProcCallerStmtId : callerStmtInCurrentProcLst) {
                for (int usedConstId : constUsedByCalledProcSet) {
                    //pkb->insertStmtModifyVarRel(currentProcCallerStmtId, usedConstId);
                    pkb->insertStmtUseConstRel(currentProcCallerStmtId, usedConstId);
                }
            }

            //modifies
            unordered_set<int> varModifiedByCalledProcSet = pkb->getVarModifiedInProc(calledProcId);
            for (int currentProcCallerStmtId : callerStmtInCurrentProcLst) {
                for (int modifiedVarId : varModifiedByCalledProcSet) {
                    pkb->insertStmtModifyVarRel(currentProcCallerStmtId, modifiedVarId);
                }
            }

            //populate call* for current proc
            //get the procs that calledProcId calls
            unordered_set<int> calledProcCallStarSet = pkb->getProcCalledByStarProc(calledProcId);//pkb implement
            for (int calledStarProcId : calledProcCallStarSet) {
                pkb->insertProcCallStarProcRel(procId, calledStarProcId);//pkb implement
            }
        }

        //loop through all contained stmts, add their uses/modifies to current proc
        unordered_set<int> currentProcStmtLst = pkb->getStmtInProc(procId);
        for (int stmtId : currentProcStmtLst) {
            //get stmt uses and set as proc uses
            unordered_set<int> currentStmtUsedVarLst = pkb->getVarUsedByStmt(stmtId);
            for (int varId : currentStmtUsedVarLst) {
                pkb->insertProcUseVarRel(procId, varId);
                //use inset
            }

            unordered_set<int> currentStmtUsedConstLst = pkb->getConstUsedByStmt(stmtId);
            for (int constVal : currentStmtUsedConstLst) {
                pkb->insertProcUseConstRel(procId, constVal);
            }
            //get stmt modifies and set as proc modifies

            unordered_set<int> currentStmtModifiedVarLst = pkb->getVarModifiedInStmt(stmtId);
            for (int varId : currentStmtModifiedVarLst) {
                //pkb->setProcModifyVarRel(procId, varId);
                pkb->insertProcModifyVarRel(procId, varId);
            }
        }

    }
    //unset visited
    isProcInPath->at(procId) = false;
    isProcValidated->at(procId) = true;

}
*/
/*
Unused code:

//performs depth first search and extract information from AST
void initialiseTables(TNode* currentNode) {
	switch (getType(currentNode)) {
	case Procedure:
		processProcedure((TNodeProc*)currentNode);
		break;
	case Variable:
		processVariable((TNodeVar*)currentNode);
		break;
	case while:
		processWhile((TNodeWhile*)currentNode);
		break;
	case assign:
		processAssign((TNodeAssign*)currentNode);
		break;
	case statementList:
		processStatementList((TNodeStmtLst*)currentNode);
		break;
	case minus:
	case plus:
	case times:
		processArithmetic((TNodeExpr*)currentNode);
		break;

	}
}

void processStatementList(TNodeStmtLst* currentNode) {
	vector<int> childrenStatements = getStmtLstChildren();
	int numberOfStatements = childrenStatements.size();
	for (int i = 0; i < numberOfStatements; i++) {
		followsMap.insert(childrenStatements[i], childrenStatements[i + 1]);
		followedByMap.insert(childrenStatements[i + 1], childrenStatements[i]);
	}
}

void processChildren(TNode parent) {
	for (int i = 0; i < parent.childList.size; i++) {
		initialiseTables(parent.childList.get(i));
	}
}

void processArithmetic(TNodeExpr* currentNode) {
	vector<TNode*> childList = getExprChildren();
	int numChildren = childList.size();
	for (int i = 0; i < numChildren; i++) {
		TNode* child = childList[i];
		if(getType(child) == variable)
			addUses(assignedStateNum, child.name);
	}
	processChildren(currentNode);
}

void processVariable(TNodeVar* currentNode) {
	addVariable(getName(currentNode));
	processChildren(currentNode);
}

void processProcedure(TNodeProc* currentNode) {
	addProcedure(getName(currentNode));
	processChildren(currentNode);
}

void processWhile(TNodeWhile* currentNode) {
	int statementNum = getStatementNum(currentNode);
	if (!statementStack.empty()) {
		parentsMap.insert(statementNum, statementStack.top());
		auto iterator = childrensMap.find(statementStack.top());
		if (iterator != childrensMap.end()) {
			vector<int> childrenList = iterator->second;
			childrenList.push_back(statementNum);
		}
		else {
			childrensMap.insert(statementStack.top(), statementNum);
		}
	}
	statementStack.push(statementNum);
	addStatement(statementNum, while);
	addUses(statementNum, getCtrlVar(currentNode));
	processChildren(currentNode);
	statementStack.pop();
}

void processAssign(TNodeAssign* currentNode) {
	int statementNum = getStatementNum(currentNode);
	if (!statementStack.empty()) {
		parentsMap.insert(statementNum, statementStack.top());
		childrensMap.insert(statementStack.top(), statementNum);
	}
	addStatement(statementNum, getType(currentNode));
	addModifies(statementNum, getModifiedVar(currentNode));
	assignedStatementNum = statementNum;
	processChildren(currentNode);
}


void extractFollowsStar() {
	int statementNum = 0, numOfStatements = getNumOfStatements();
	for (int i = 0; i< numOfStatements; i++) {
		statementNum = i;
		vector<int> listOfFollows;
		unordered_map<int, int>::const_iterator iterator = followsMap.find(statementNum);
		while (iterator != followsMap.end()) {
			listOfFollows.push_back(iterator->second);
			iterator++;
		}
		addFollows(statementNum, listOfFollows);
	}
}

void extractParentStar() {
	int statementNum = 0, numOfStatements = getNumOfStatements();
	for (int i = 0; i< numOfStatements; i++) {
		statementNum = i;
		vector<int> listOfParents;
		unordered_map<int, int>::const_iterator iterator = parentsMap.find(statementNum);
		while (iterator != parentsMap.end()) {
			listOfParents.push_back(iterator->second);
			iterator++;
		}
		addParents(statementNum, listOfParents);
	}
}

void extractFollowedByStar() {
	
	int statementNum = 0, numOfStatements = getNumOfStatements();
	for (int i = 0; i< numOfStatements; i++) {
		statementNum = i;
		vector<int> listOfFollowedBy;
		unordered_map<int, int>::const_iterator iterator = followedByMap.find(statementNum);
		while (iterator != followsMap.end()) {
			listOfFollowedBy.push_back(iterator->second);
			iterator++;
		}
		addFollowedBy(statementNum, listOfFollowedBy);
	}
}

void extractChildrenStar() {
	int statementNum = 0, numOfStatements = getNumOfStatements();
	for (int i = 0; i< numOfStatements; i++) {
		statementNum = i;
		vector<int> listOfDirectChildren, listOfChildrenStar;
		unordered_map<int, vector<int>>::const_iterator iterator = childrensMap.find(statementNum);
		if (iterator != childrensMap.end()) {
			listOfDirectChildren = iterator->second;
			for (int j = 0; j < listOfDirectChildren.size(); j++) {
				auto it = childrensMap.find(listOfDirectChildren[j]);
				while (it != childrensMap.end()) {
					listOfChildrenStar.push_back(it)
				}
			}

		}
	}
}
*/
