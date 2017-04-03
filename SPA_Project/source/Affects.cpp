#include "Affects.h"

const int contStmtId = 0;
const int contNextStmtId = 1;
const int varToStmtTable = 2;

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
	setBooleanToTable(&affectResultTable);

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
		}
		else {
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
		}
		else {
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

		/*
		if (affectorStmts.size() <= affectedStmts.size()) {
			for (auto stmtMap : affectorStmts) {
				if (!stmtMap.second) {
					fowardDfs(pkb, affectResultTable, procId, stmtMap.first, &affectorStmts, &unordered_map<int, int>(), &affectedStmts);
					if (hasFoundAllResult) {
						return;
					}
				}
			}
		} else {
			for (auto stmtMapIter = affectedStmts.rbegin(); stmtMapIter != affectedStmts.rend(); ++stmtMapIter) {
				if (!(*stmtMapIter).second) {
					reverseDfs(pkb, affectResultTable, (*stmtMapIter).first, &affectorStmts, &unordered_map<int, unordered_set<int>>(), &affectedStmts);
					if (hasFoundAllResult) {
						return;
					}
				}
			}
		}
		*/
	}
}

void Affects::fowardDfs(PKB* pkb, ResultTable* affectResultTable, int procId, int startStmt, map<int, bool>* affectorStmts, map<int, bool>* affectedStmts) {
	unordered_map<int, int> stmtVisitedCount;
	unordered_map<int, unordered_set<int>> modifiedVarToStmt;
	
	stack <tuple<int, int, unordered_map<int, unordered_set<int>>>> ifTableStack;
	stack <tuple<int, int, unordered_map<int, unordered_set<int>>>> whileTableStack;
	
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

		Type stmtType = getStmtType(pkb, curStmt);
		int numOfPrevStmt = pkb->getPreviousStmt(curStmt).size();
		if (numOfPrevStmt > 2 || (numOfPrevStmt > 1 && (stmtType != WHILE || curStmt == *(pkb->getStmtLstContainedInProc(procId).begin())))) {
			//std::cout << curStmt;
			if (stmtVisitedCount.find(curStmt) == stmtVisitedCount.end()) {
				stmtVisitedCount.insert({ curStmt,1 });
			}
			else {
				stmtVisitedCount.at(curStmt)++;
			}

			if (!ifTableStack.empty()) {
				if (get<contNextStmtId>(ifTableStack.top()) == -1 || stmtVisitedCount.at(curStmt) < numOfPrevStmt) {
					get<contNextStmtId>(ifTableStack.top()) = curStmt;
					unordered_map<int, unordered_set<int>> copyModifiedVarToStmt = modifiedVarToStmt;
					modifiedVarToStmt = get<varToStmtTable>(ifTableStack.top());
					mergeTable(&copyModifiedVarToStmt, &get<varToStmtTable>(ifTableStack.top()));
					continue;
				}
				else {
					while (!ifTableStack.empty() && get<contNextStmtId>(ifTableStack.top()) != -1) {
						mergeTable(&get<varToStmtTable>(ifTableStack.top()), &modifiedVarToStmt);
					ifTableStack.pop();
					}
				}
			}

			stmtVisitedCount.erase(curStmt);
			if (stmtType == WHILE && curStmt != *(pkb->getStmtLstContainedInProc(procId).begin())) {
				stmtVisitedCount.insert({ curStmt,1 });
			}
			else {
				stmtVisitedCount.insert({ curStmt,0 });
			}
		}

		//std::cout << curStmt;
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
			if (nextStmts.size() > 0) {
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
			if (nextStmts.size() > 0) {
				dfsStack.push(*nextStmts.begin());
			}
			break;
		}

		case WHILE: {
			unordered_set<int> nextStmts = pkb->getNextStmt(curStmt);
			int stmtWithinWhile = curStmt + 1;
			int stmtAfterWhile = -1;
			for (auto nextStmtId : nextStmts) {
				if (nextStmtId != stmtWithinWhile) {
					stmtAfterWhile = nextStmtId;
				}
			}

			if (whileTableStack.empty() || get<contStmtId>(whileTableStack.top()) != curStmt) {
				whileTableStack.push({ curStmt, stmtAfterWhile, modifiedVarToStmt });
				dfsStack.push(stmtWithinWhile);
			}
			else {
				bool hasNewEntryInTable = mergeTable(&modifiedVarToStmt, &get<varToStmtTable>(whileTableStack.top()));
				if (hasNewEntryInTable) {
					dfsStack.push(stmtWithinWhile);
				}
				else {
					modifiedVarToStmt = get<varToStmtTable>(whileTableStack.top());
					whileTableStack.pop();
					if (stmtAfterWhile != -1) {
						dfsStack.push(stmtAfterWhile);
					}
				}
			}
			break;
		}

		case IF: {
			ifTableStack.push({ curStmt, -1, modifiedVarToStmt });
			unordered_set<int> nextStmts = pkb->getNextStmt(curStmt);
			for (auto nextStmtId : nextStmts) {
				dfsStack.push(nextStmtId);
			}
		}
		}
	}
}

void Affects::reverseDfs(PKB* pkb, ResultTable* affectResultTable, int curStmt,
					map<int, bool>* affectorStmts, unordered_map<int, unordered_set<int>>* usedVarToStmt, map<int, bool>* affectedStmts) {
	if (hasFoundAllResult) {
		return;
	}
	if (affectedStmts->find(curStmt) != affectedStmts->end()) {
		affectedStmts->at(curStmt) = true;
	}

	Type stmtType = getStmtType(pkb, curStmt);
	switch (stmtType) {
	case ASSIGN: {
		int modifiedVarId = pkb->getVarAtLeftOfAssignStmt(curStmt);
		if (usedVarToStmt->find(modifiedVarId) != usedVarToStmt->end()) {
			unordered_set<int> usedStmts = usedVarToStmt->at(modifiedVarId);
			for (auto affectedStmt : usedStmts) {
				if (isStmtValidResult(curStmt, affectorStmts, affectedStmt, affectedStmts)) {
					setResultTupleToTable(affectResultTable, curStmt, affectedStmt);
				}
			}
			usedVarToStmt->erase(modifiedVarId);
		}

		unordered_set<int> usedVars = pkb->getVarUsedByStmt(curStmt);
		for (auto usedVarId : usedVars) {
			if (usedVarToStmt->find(usedVarId) == usedVarToStmt->end()) {
				usedVarToStmt->insert({ usedVarId, unordered_set<int>() });
			}
			usedVarToStmt->at(usedVarId).insert(curStmt);
		}

		if (pkb->getPreviousStmt(curStmt).size() != 0) {
			unordered_set<int> prevStmts = pkb->getPreviousStmt(curStmt);
			for (auto prevStmtIter = ++prevStmts.begin(); prevStmtIter != prevStmts.end(); ++prevStmtIter) {
				unordered_map<int, unordered_set<int>> copyUsedVarToStmt = *usedVarToStmt;
				reverseDfs(pkb, affectResultTable, *prevStmtIter, affectorStmts, &copyUsedVarToStmt, affectedStmts);
			}
			reverseDfs(pkb, affectResultTable, *prevStmts.begin(), affectorStmts, usedVarToStmt, affectedStmts);
		}
		break;
	}
	case CALL: {
		unordered_set<int> modifiedVars = pkb->getVarModifiedInStmt(curStmt);
		for (auto modifiedVarId : modifiedVars) {
			if (usedVarToStmt->find(modifiedVarId) != usedVarToStmt->end()) {
				usedVarToStmt->erase(modifiedVarId);
			}
		}

		if (pkb->getPreviousStmt(curStmt).size() != 0) {
			unordered_set<int> prevStmts = pkb->getPreviousStmt(curStmt);
			for (auto prevStmtIter = ++prevStmts.begin(); prevStmtIter != prevStmts.end(); ++prevStmtIter) {
				unordered_map<int, unordered_set<int>> copyUsedVarToStmt = *usedVarToStmt;
				reverseDfs(pkb, affectResultTable, *prevStmtIter, affectorStmts, &copyUsedVarToStmt, affectedStmts);
			}
			reverseDfs(pkb, affectResultTable, *prevStmts.begin(), affectorStmts, usedVarToStmt, affectedStmts);
		}
		break;
	}

	case WHILE: {
		// still thinking...
		break;
	}
	case IF:
		if (contTableMap.find(curStmt) == contTableMap.end()) {
			contTableMap.insert({ curStmt, unordered_map<int, unordered_set<int>>() });
			contTableStack.at(curStmt).insert(*usedVarToStmt);
			return;
		} else {
			mergeTable(&contTableMap.at(curStmt), usedVarToStmt);
			contTableMap.erase(curStmt);
		}

		if (pkb->getPreviousStmt(curStmt).size() != 0) {
			unordered_set<int> prevStmts = pkb->getPreviousStmt(curStmt);
			for (auto prevStmtIter = ++prevStmts.begin(); prevStmtIter != prevStmts.end(); ++prevStmtIter) {
				unordered_map<int, unordered_set<int>> copyUsedVarToStmt = *usedVarToStmt;
				reverseDfs(pkb, affectResultTable, *prevStmtIter, affectorStmts, &copyUsedVarToStmt, affectedStmts);
			}
			reverseDfs(pkb, affectResultTable, *prevStmts.begin(), affectorStmts, usedVarToStmt, affectedStmts);
		}
		break;
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
			for (auto stmtId: tableEntry.second) {
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
	}
}

bool Affects::isStmtValidResult(int affectorStmtId, map<int, bool>* validAffectorResults, int affectedStmtId, map<int, bool>* validAffectedResults) {
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

void Affects::setBooleanToTable(ResultTable* affectResultTable) {
	if (affectResultTable->getSynCount() > 0) {
		if (affectResultTable->getTupleSize() > 0) {
			affectResultTable->setBoolean(true);
		} else {
			affectResultTable->setBoolean(false);
		}
	}
}

Parameter Affects::getLeftChild() {
	return leftChild;
}

Parameter Affects::getRightChild() {
	return rightChild;
}

vector<Parameter> Affects::getSynList() {
	return synList;
}

ClauseType Affects::getClauseType() {
	return PATTERN;
}