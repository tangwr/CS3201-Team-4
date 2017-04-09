#include "AffectsBip.h"

const int contStmtId = 0;
const int numOfPathDone = 1;
const int varToStmtTable = 2;

const int NOT_FOUND = 0;

AffectsBip::AffectsBip(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;

	if (leftChild.isSynonym()) {
		synList.push_back(leftChild);
	}
	if (rightChild.isSynonym() && !rightChild.isSame(leftChild)) {
		synList.push_back(rightChild);
	}

	hasFoundAllResult = false;
}

ResultTable AffectsBip::evaluate(PKB* pkb, ResultTable intResultTable) {
	ResultTable affectResultTable;
	affectResultTable.setBoolean(false);

	setSynToTable(&affectResultTable);
	setResultToTable(pkb, &intResultTable, &affectResultTable);
	setBooleanToTable(&affectResultTable);

	return affectResultTable;
}

void AffectsBip::setSynToTable(ResultTable* affectResultTable) {
	affectResultTable->setSynList(synList);
}

void AffectsBip::setResultToTable(PKB* pkb, ResultTable* intResultTable, ResultTable* affectResultTable) {
	unordered_set<int> affectorValidStmts = getValidStmts(pkb, intResultTable, leftChild);
	unordered_set<int> affectedValidStmts = getValidStmts(pkb, intResultTable, rightChild);
	dfsToSetResultTable(pkb, intResultTable, affectResultTable, affectorValidStmts, affectedValidStmts);
	affectResultTable->removeDuplicateTuple();
}

unordered_set<int> AffectsBip::getValidStmts(PKB* pkb, ResultTable* intResultTable, Parameter child) {
	switch (child.getParaType()) {
	case INTEGER: {
		int stmtId = stoi(child.getParaName());
		if (pkb->isStmtInAssignTable(stmtId)) {
			return{ stmtId };
		}
		else {
			return{};
		}
	}
	case ANYTHING:
		return pkb->getAllAssignStmt();
	case ASSIGN:
		/* falls through */
	case STMT:
		/* falls through */
	case PROG_LINE:
		if (intResultTable->isSynInTable(child)) {
			return intResultTable->getSynValue(child);
		}
		else {
			return  pkb->getAllAssignStmt();
		}
	}
}

void AffectsBip::dfsToSetResultTable(PKB* pkb, ResultTable* intResultTable, ResultTable* affectResultTable,
	unordered_set<int> validAffectorStmts, unordered_set<int> validAffectedStmts) {
	if (validAffectorStmts.empty() || validAffectedStmts.empty()) {
		return;
	}

	unordered_set<int> procs = pkb->getAllProcId();
	for (auto procId : procs) {
		int startStmtId = *pkb->getStmtLstContainedInProc(procId).begin();
		fowardDfs(pkb, affectResultTable, procId, startStmtId, &validAffectorStmts, &validAffectedStmts);
		if (hasFoundAllResult) {
			return;
		}
	}
}

void AffectsBip::fowardDfs(PKB* pkb, ResultTable* affectResultTable, int procId, int startStmt, 
							unordered_set<int>* validAffectorStmts, unordered_set<int>* validAffectedStmts) {
	unordered_map<int, unordered_set<int>> modifiedVarToStmt;

	stack<tuple<int, int, unordered_map<int, unordered_set<int>>>> ifTableStack;
	stack<tuple<int, int, unordered_map<int, unordered_set<int>>>> whileTableStack;

	stack<int> dfsStack;
	dfsStack.push(startStmt);

	while (!dfsStack.empty()) {
		int curStmt = dfsStack.top();
		dfsStack.pop();

		if (hasFoundAllResult) {
			return;
		}

		if (curStmt < NOT_FOUND) {
			if (!ifTableStack.empty()) {
				if (get<numOfPathDone>(ifTableStack.top()) == 0) {
					get<numOfPathDone>(ifTableStack.top())++;
					unordered_map<int, unordered_set<int>> copyModifiedVarToStmt = modifiedVarToStmt;
					modifiedVarToStmt = get<varToStmtTable>(ifTableStack.top());
					get<varToStmtTable>(ifTableStack.top()) = copyModifiedVarToStmt;
					continue;
				} else {
					mergeTable(&get<varToStmtTable>(ifTableStack.top()), &modifiedVarToStmt);
					ifTableStack.pop();
				}
			}

			unordered_set<int> nextStmts = pkb->getNextStmt(curStmt);
			if (nextStmts.size() == 1) {
				dfsStack.push(*nextStmts.begin());
			}
			continue;
		}

		//cout << curStmt;
		Type stmtType = getStmtType(pkb, curStmt);
		switch (stmtType) {
		case ASSIGN: {
			unordered_set<int> usedVars = pkb->getVarUsedByStmt(curStmt);
			for (auto usedVarId : usedVars) {
				if (modifiedVarToStmt.find(usedVarId) != modifiedVarToStmt.end()) {
					unordered_set<int> modifiedStmts = modifiedVarToStmt.at(usedVarId);
					for (auto affectorStmt : modifiedStmts) {
						if (isStmtValidResult(affectorStmt, validAffectorStmts, curStmt, validAffectedStmts)) {
							setResultTupleToTable(affectResultTable, affectorStmt, curStmt);
						}
					}
				}
			}

			int modifiedVarId = pkb->getVarAtLeftOfAssignStmt(curStmt);
			if (modifiedVarToStmt.find(modifiedVarId) != modifiedVarToStmt.end()) {
				modifiedVarToStmt.erase(modifiedVarId);
			}
			modifiedVarToStmt.insert({ modifiedVarId, unordered_set<int>() });
			modifiedVarToStmt.at(modifiedVarId).insert(curStmt);

			unordered_set<int> nextStmts = pkb->getNextStmt(curStmt);
			if (nextStmts.size() == 1) {
				dfsStack.push(*nextStmts.begin());
			}
			break;
		}

		case CALL: {
			unordered_set<int> nextStmts = pkb->getNextStmt(curStmt);
			if (nextStmts.size() == 1) {
				dfsStack.push(*nextStmts.begin());
			}

			int calledProcId = pkb->getProcCalledByStmt(curStmt);
			vector<int> procStmtLst = pkb->getStmtLstContainedInProc(calledProcId);
			if (procStmtLst.size() == 1) {
				dfsStack.push(*procStmtLst.begin());
			} else {
				//error
			}
			break;
		}

		case WHILE: {
			unordered_set<int> nextStmts = pkb->getNextStmt(curStmt);
			int stmtWithinWhile = curStmt + 1;
			int stmtAfterWhile = 0;
			for (auto nextStmtId : nextStmts) {
				if (nextStmtId != stmtWithinWhile) {
					stmtAfterWhile = nextStmtId;
				}
			}

			if (whileTableStack.empty() || get<contStmtId>(whileTableStack.top()) != curStmt) {
				whileTableStack.push({ curStmt, 0, modifiedVarToStmt });
				dfsStack.push(stmtWithinWhile);
			} else {
				bool hasNewEntryInTable = mergeTable(&modifiedVarToStmt, &get<varToStmtTable>(whileTableStack.top()));
				if (hasNewEntryInTable) {
					dfsStack.push(stmtWithinWhile);
				} else {
					modifiedVarToStmt = get<varToStmtTable>(whileTableStack.top());
					whileTableStack.pop();
					if (stmtAfterWhile != 0) {
						dfsStack.push(stmtAfterWhile);
					}
				}
			}
			break;
		}

		case IF: {
			ifTableStack.push({ curStmt, 0, modifiedVarToStmt });
			unordered_set<int> nextStmts = pkb->getNextStmt(curStmt);
			for (auto nextStmtId : nextStmts) {
				dfsStack.push(nextStmtId);
			}
		}
		}
	}
}

bool AffectsBip::mergeTable(unordered_map<int, unordered_set<int>>* merger, unordered_map<int, unordered_set<int>>* merged) {
	bool hasNewEntry = false;
	unordered_map<int, unordered_set<int>> copyOfMerger = *merger;
	for (auto tableEntry : copyOfMerger) {
		if (merged->find(tableEntry.first) == merged->end()) {
			merged->insert({ tableEntry.first,tableEntry.second });
			hasNewEntry = true;
		}
		else {
			for (auto stmtId : tableEntry.second) {
				if (merged->at(tableEntry.first).find(stmtId) == merged->at(tableEntry.first).end()) {
					merged->at(tableEntry.first).insert(stmtId);
					hasNewEntry = true;
				}
				else {
					merger->at(tableEntry.first).erase(stmtId);
				}
			}
			if (merger->at(tableEntry.first).empty()) {
				merger->erase(tableEntry.first);
			}
		}
	}
	return hasNewEntry;
}

Type AffectsBip::getStmtType(PKB* pkb, int stmtId) {
	if (pkb->isStmtInAssignTable(stmtId)) {
		return ASSIGN;
	}
	else if (pkb->isStmtInWhileTable(stmtId)) {
		return WHILE;
	}
	else if (pkb->isStmtInIfTable(stmtId)) {
		return IF;
	}
	else if (pkb->isStmtInCallTable(stmtId)) {
		return CALL;
	}
}

bool AffectsBip::isStmtValidResult(int affectorStmtId, unordered_set<int>* validAffectorResults, int affectedStmtId, unordered_set<int>* validAffectedResults) {
	if (validAffectorResults->find(affectorStmtId) != validAffectorResults->end()
		&& validAffectedResults->find(affectedStmtId) != validAffectedResults->end()) {
		if (!leftChild.isSynonym() && !rightChild.isSynonym()) {
			validAffectorResults->clear();
			validAffectedResults->clear();
			hasFoundAllResult = true;
		}
		return true;
	}
	else {
		return false;
	}
}

void AffectsBip::setResultTupleToTable(ResultTable* affectResultTable, int affectorStmtId, int affectedStmtId) {
	switch (affectResultTable->getSynCount()) {
	case 0:
		affectResultTable->setBoolean(true);
		break;
	case 1:
		if (leftChild.isSynonym() && rightChild.isSynonym()) {
			if (affectorStmtId == affectedStmtId) {
				affectResultTable->insertTuple({ affectorStmtId });
			}
		}
		else if (leftChild.isSynonym()) {
			affectResultTable->insertTuple({ affectorStmtId });
		}
		else {
			affectResultTable->insertTuple({ affectedStmtId });
		}
		break;
	case 2:
		affectResultTable->insertTuple({ affectorStmtId, affectedStmtId });
		break;
	}
}

void AffectsBip::setBooleanToTable(ResultTable* affectResultTable) {
	if (affectResultTable->getSynCount() > 0) {
		if (affectResultTable->getTupleSize() > 0) {
			affectResultTable->setBoolean(true);
		}
		else {
			affectResultTable->setBoolean(false);
		}
	}
}

Parameter AffectsBip::getLeftChild() {
	return leftChild;
}

Parameter AffectsBip::getRightChild() {
	return rightChild;
}

vector<Parameter> AffectsBip::getSynList() {
	return synList;
}

ClauseType AffectsBip::getClauseType() {
	return AFFECTSBIP;
}
