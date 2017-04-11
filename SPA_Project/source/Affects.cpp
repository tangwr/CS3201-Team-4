#pragma once

#include "Affects.h"

#define contStmtId 0
#define numOfPathDone 1
#define varToStmtTable 2

#define NOT_FOUND 0
#define NONE 0
#define INITIAL_NUM_OF_PATH_DONE 0
#define VALID_NUM_OF_NEXT_STMT 1
#define INCREMENT 1

Affects::Affects(Parameter lc, Parameter rc) {
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

ResultTable Affects::evaluate(PKB* pkb, ResultTable intResultTable) {
	ResultTable affectResultTable;
	affectResultTable.setBoolean(false);

	setSynToTable(&affectResultTable);
	setResultToTable(pkb, &intResultTable, &affectResultTable);

	return affectResultTable;
}

void Affects::setSynToTable(ResultTable* affectResultTable) {
	affectResultTable->setSynList(synList);
}

void Affects::setResultToTable(PKB* pkb, ResultTable* intResultTable, ResultTable* affectResultTable) {
	unordered_set<int> affectorValidStmts = getValidStmts(pkb, intResultTable, leftChild);
	unordered_set<int> affectedValidStmts = getValidStmts(pkb, intResultTable, rightChild);
	dfsToSetResultTable(pkb, intResultTable, affectResultTable, affectorValidStmts, affectedValidStmts);
	affectResultTable->removeDuplicateTuple();
}

unordered_set<int> Affects::getValidStmts(PKB* pkb, ResultTable* intResultTable, Parameter child) {
	switch (child.getParaType()) {
	case INTEGER: {
		int stmtId = stoi(child.getParaName());
		if (pkb->isStmtInAssignTable(stmtId)) {
			return { stmtId };
		} else {
			return {};
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
		} else {
			return  pkb->getAllAssignStmt();
		}
	}
}

void Affects::dfsToSetResultTable(PKB* pkb, ResultTable* intResultTable, ResultTable* affectResultTable,
									unordered_set<int> validAffectorStmts, unordered_set<int> validAffectedStmts) {
	if (validAffectorStmts.empty() || validAffectedStmts.empty()) {
		return;
	}
	
	unordered_map<int, map<int, bool>> affector;
	unordered_map<int, map<int, bool>> affected;

	for (auto affectorStmtId : validAffectorStmts) {
		int procId = pkb->getProcContainingStmt(affectorStmtId);
		if (affector.find(procId) == affector.end()) {
			affector.insert({ procId, map<int, bool>() });
		}
		affector.at(procId).insert({ affectorStmtId, false });
	}

	for (auto affectedStmtId : validAffectedStmts) {
		int procId = pkb->getProcContainingStmt(affectedStmtId);
		if (affected.find(procId) == affected.end()) {
			affected.insert({ procId, map<int, bool>() });
		}
		affected.at(procId).insert({ affectedStmtId, false });
	}

	for (auto proc : affector) {
		int procId = proc.first;
		if (affected.find(procId) == affected.end()) {
			continue;
		}
		
		map<int, bool> affectorStmts = proc.second;
		map<int, bool> affectedStmts = affected.at(procId);

		for (auto stmtMap : affectorStmts) {
			if (!stmtMap.second) {
				fowardDfs(pkb, affectResultTable, procId, stmtMap.first, &affectorStmts, &affectedStmts);
				if (hasFoundAllResult) {
					return;
				}
			}
		}
	}
}

void Affects::fowardDfs(PKB* pkb, ResultTable* affectResultTable, int procId, int startStmt, map<int, bool>* affectorStmts, map<int, bool>* affectedStmts) {
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
		if (affectorStmts->find(curStmt) != affectorStmts->end()) {
			affectorStmts->at(curStmt) = true;
		}

		if (curStmt < NOT_FOUND) {
			if (!ifTableStack.empty()) {
				if (get<numOfPathDone>(ifTableStack.top()) == NONE) {
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
			if (nextStmts.size() == VALID_NUM_OF_NEXT_STMT) {
				dfsStack.push(*nextStmts.begin());
			}
			continue;
		}

		Type stmtType = getStmtType(pkb, curStmt);
		switch (stmtType) {
		case ASSIGN: {
			unordered_set<int> usedVars = pkb->getVarUsedByStmt(curStmt);
			for (auto usedVarId : usedVars) {
				if (modifiedVarToStmt.find(usedVarId) != modifiedVarToStmt.end()) {
					unordered_set<int> modifiedStmts = modifiedVarToStmt.at(usedVarId);
					for (auto affectorStmt : modifiedStmts) {
						if (isStmtValidResult(affectorStmt, affectorStmts, curStmt, affectedStmts)) {
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
			if (nextStmts.size() == VALID_NUM_OF_NEXT_STMT) {
				dfsStack.push(*nextStmts.begin());
			}
			break;
		}

		case CALL: {
			unordered_set<int> modifiedVars = pkb->getVarModifiedInStmt(curStmt);
			for (auto modifiedVarId : modifiedVars) {
				if (modifiedVarToStmt.find(modifiedVarId) != modifiedVarToStmt.end()) {
					modifiedVarToStmt.erase(modifiedVarId);
				}
			}

			unordered_set<int> nextStmts = pkb->getNextStmt(curStmt);
			if (nextStmts.size() == VALID_NUM_OF_NEXT_STMT) {
				dfsStack.push(*nextStmts.begin());
			}
			break;
		}

		case WHILE: {
			unordered_set<int> nextStmts = pkb->getNextStmt(curStmt);
			int stmtWithinWhile = curStmt + INCREMENT;
			int stmtAfterWhile = NOT_FOUND;
			for (auto nextStmtId : nextStmts) {
				if (nextStmtId != stmtWithinWhile) {
					stmtAfterWhile = nextStmtId;
				}
			}

			if (whileTableStack.empty() || get<contStmtId>(whileTableStack.top()) != curStmt) {
				whileTableStack.push({ curStmt, INITIAL_NUM_OF_PATH_DONE, modifiedVarToStmt });
				dfsStack.push(stmtWithinWhile);
			} else {
				bool hasNewEntryInTable = mergeTable(&modifiedVarToStmt, &get<varToStmtTable>(whileTableStack.top()));
				if (hasNewEntryInTable) {
					dfsStack.push(stmtWithinWhile);
				} else {
					modifiedVarToStmt = get<varToStmtTable>(whileTableStack.top());
					whileTableStack.pop();
					if (stmtAfterWhile != NOT_FOUND) {
						dfsStack.push(stmtAfterWhile);
					}
				}
			}
			break;
		}

		case IF: {
			ifTableStack.push({ curStmt, INITIAL_NUM_OF_PATH_DONE, modifiedVarToStmt });
			unordered_set<int> nextStmts = pkb->getNextStmt(curStmt);
			for (auto nextStmtId : nextStmts) {
				dfsStack.push(nextStmtId);
			}
		}
		}
	}
}

bool Affects::mergeTable(unordered_map<int, unordered_set<int>>* merger, unordered_map<int, unordered_set<int>>* merged) {
	bool hasNewEntry = false;
	unordered_map<int, unordered_set<int>> copyOfMerger = *merger;
	for (auto tableEntry: copyOfMerger) {
		if (merged->find(tableEntry.first) == merged->end()) {
			merged->insert({ tableEntry.first,tableEntry.second });
			hasNewEntry = true;
		} else {
			for (auto stmtId : tableEntry.second) {
				if (merged->at(tableEntry.first).find(stmtId) == merged->at(tableEntry.first).end()) {
					merged->at(tableEntry.first).insert(stmtId);
					hasNewEntry = true;
				} else {
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

Type Affects::getStmtType(PKB* pkb, int stmtId) {
	if (pkb->isStmtInAssignTable(stmtId)) {
		return ASSIGN;
	} else if (pkb->isStmtInWhileTable(stmtId)) {
		return WHILE;
	} else if (pkb->isStmtInIfTable(stmtId)) {
		return IF;
	} else if (pkb->isStmtInCallTable(stmtId)) {
		return CALL;
	} else {
		return INVALID;
	}
}

bool Affects::isStmtValidResult(int affectorStmtId, map<int, bool>* validAffectorResults, int affectedStmtId, map<int, bool>* validAffectedResults) {
	if (validAffectorResults->find(affectorStmtId) != validAffectorResults->end()
		&& validAffectedResults->find(affectedStmtId) != validAffectedResults->end()) {
		if (!leftChild.isSynonym() && !rightChild.isSynonym()) {
			hasFoundAllResult = true;
		}
		return true;
	} else {
		return false;
	}
}

void Affects::setResultTupleToTable(ResultTable* affectResultTable, int affectorStmtId, int affectedStmtId) {
	switch (affectResultTable->getSynCount()) {
	case 0:
		affectResultTable->setBoolean(true);
		break;
	case 1:
		if (leftChild.isSynonym() && rightChild.isSynonym()) {
			if (affectorStmtId == affectedStmtId) {
				affectResultTable->insertTuple({ affectorStmtId });
			}
		} else if (leftChild.isSynonym()) {
			affectResultTable->insertTuple({ affectorStmtId });
		} else {
			affectResultTable->insertTuple({ affectedStmtId });
		}
		break;
	case 2:
		affectResultTable->insertTuple({ affectorStmtId, affectedStmtId });
		break;
	}
}

vector<Parameter> Affects::getSynList() {
	return synList;
}

ClauseType Affects::getClauseType() {
	return AFFECTS;
}
