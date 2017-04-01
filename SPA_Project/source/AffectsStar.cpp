#include "AffectsStar.h"

AffectsStar::AffectsStar(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;

	if (leftChild.isSynonym()) {
		synList.push_back(leftChild);
	}
	if (rightChild.isSynonym()) {
		synList.push_back(rightChild);
	}

	hasFoundAllResult = false;
}

ResultTable AffectsStar::evaluate(PKB* pkb, ResultTable intResultTable) {
	ResultTable affectResultTable;
	affectResultTable.setBoolean(false);

	setSynToTable(&affectResultTable);
	setResultToTable(pkb, &intResultTable, &affectResultTable);
	setBooleanToTable(&affectResultTable);

	return affectResultTable;
}

void AffectsStar::setSynToTable(ResultTable* affectResultTable) {
	if (leftChild.isSynonym() && leftChild.isSame(rightChild)) {
		affectResultTable->setSynList({ leftChild });
	}
	else {
		affectResultTable->setSynList(synList);
	}
}

void AffectsStar::setResultToTable(PKB* pkb, ResultTable* intResultTable, ResultTable* affectResultTable) {
	unordered_set<int> affectorValidStmts = getValidStmts(pkb, intResultTable, leftChild);
	unordered_set<int> affectedValidStmts = getValidStmts(pkb, intResultTable, rightChild);
	dfsToSetResultTable(pkb, intResultTable, affectResultTable, affectorValidStmts, affectedValidStmts);
	affectResultTable->removeDuplicateTuple();
}

unordered_set<int> AffectsStar::getValidStmts(PKB* pkb, ResultTable* intResultTable, Parameter child) {
	switch (child.getParaType()) {
	case INTEGER: {
		int stmtId = stoi(child.getParaName());
		if (pkb->isStmtInAssignTable(stmtId)) {
			return {stmtId};
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
		}
		else {
			return  pkb->getAllAssignStmt();
		}
	}
}

void AffectsStar::dfsToSetResultTable(PKB* pkb, ResultTable* intResultTable, ResultTable* affectResultTable,
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
				fowardDfs(pkb, affectResultTable, stmtMap.first, &affectorStmts, &unordered_map<int, unordered_set<int>>(), &affectedStmts);
				if (hasFoundAllResult) {
					return;
				}
			}
		}

		/*
		if (affectorStmts.size() <= affectedStmts.size()) {
			for (auto stmtMap : affectorStmts) {
				if (!stmtMap.second) {
					fowardDfs(pkb, affectResultTable, stmtMap.first, &affectorStmts, &unordered_map<int, int>(), &affectedStmts);
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

		if (hasFoundAllResult) {
			return;
		}
	}
}

void AffectsStar::fowardDfs(PKB* pkb, ResultTable* affectResultTable, int curStmt,
					map<int, bool>* affectorStmts, unordered_map<int, unordered_set<int>>* modifiedVarToStmt, map<int, bool>* affectedStmts) {
	if (hasFoundAllResult) {
		return;
	}
	if (affectedStmts->find(curStmt) != affectedStmts->end()) {
		affectorStmts->at(curStmt) = true;
	}

	Type stmtType = getStmtType(pkb, curStmt);
	bool isTableChanged = true;
	switch (stmtType) {
	case ASSIGN: {
		int modifiedVarId = pkb->getVarAtLeftOfAssignStmt(curStmt);
		if (modifiedVarToStmt->find(modifiedVarId) == modifiedVarToStmt->end()) {
			modifiedVarToStmt->insert({ modifiedVarId, unordered_set<int>() });
		}

		bool isModVarUsed = false;
		unordered_set<int> usedVars = pkb->getVarUsedByStmt(curStmt);
		for (auto usedVarId : usedVars) {
			if (modifiedVarToStmt->find(usedVarId) != modifiedVarToStmt->end()) {
				unordered_set<int> modifiedStmts = modifiedVarToStmt->at(usedVarId);
				for (auto affectorStmt : modifiedStmts) {
					if (isStmtValidResult(affectorStmt, affectorStmts, curStmt, affectedStmts)) {
						setResultTupleToTable(affectResultTable, affectorStmt, curStmt);
					}
					modifiedVarToStmt->at(modifiedVarId).insert(affectorStmt);
				}
			}

			if (modifiedVarId == usedVarId) {
				isModVarUsed = true;
			}
		}

		if (modifiedVarToStmt->find(modifiedVarId) == modifiedVarToStmt->end() || !isModVarUsed) {
			modifiedVarToStmt->insert({ modifiedVarId, unordered_set<int>() });
		}
		modifiedVarToStmt->at(modifiedVarId).insert(curStmt);
		
		for (auto usedVarId : usedVars) {

			if (modifiedVarToStmt->find(usedVarId) != modifiedVarToStmt->end()) {
				unordered_set<int> modifiedStmts = modifiedVarToStmt->at(usedVarId);
				for (auto affectorStmt : modifiedStmts) {
					modifiedVarToStmt->at(modifiedVarId).insert(affectorStmt);
				}
			}
		}
		break;
	}

	case CALL: {
		unordered_set<int> modifiedVars = pkb->getVarModifiedInStmt(curStmt);
		for (auto modifiedVarId : modifiedVars) {
			if (modifiedVarToStmt->find(modifiedVarId) != modifiedVarToStmt->end()) {
				modifiedVarToStmt->erase(modifiedVarId);
			}
		}
		break;
	}

	case WHILE:
		if (whileTableStack.find(curStmt) == whileTableStack.end()) {
			whileTableStack.insert({ curStmt, unordered_set<unordered_map<int, unordered_set<int>>, Hasher>() });
		}

		if (whileTableStack.at(curStmt).empty() || whileTableStack.at(curStmt).find(*modifiedVarToStmt) == whileTableStack.at(curStmt).end()) {
			whileTableStack.at(curStmt).insert(*modifiedVarToStmt);
		}
		else {
			isTableChanged = false;
		}
		break;
	}

	if (pkb->getNextStmt(curStmt).size() != 0 && isTableChanged) {
		unordered_set<int> nextStmts = pkb->getNextStmt(curStmt);
		for (auto nextStmtIter = ++nextStmts.begin(); nextStmtIter != nextStmts.end(); ++nextStmtIter) {
			unordered_map<int, unordered_set<int>> copyModifiedVarToStmt = *modifiedVarToStmt;
			fowardDfs(pkb, affectResultTable, *nextStmtIter, affectorStmts, &copyModifiedVarToStmt, affectedStmts);
		}
		fowardDfs(pkb, affectResultTable, *nextStmts.begin(), affectorStmts, modifiedVarToStmt, affectedStmts);
	}
}

void AffectsStar::reverseDfs(PKB* pkb, ResultTable* affectResultTable, int curStmt,
							map<int, bool>* affectorStmts, unordered_map<int, unordered_set<int>>* usedVarToStmt, map<int, bool>* affectedStmts) {
	if (hasFoundAllResult) {
		return;
	}
	if (affectedStmts->find(curStmt) != affectedStmts->end()) {
		affectedStmts->at(curStmt) = true;
	}

	Type stmtType = getStmtType(pkb, curStmt);
	bool isTableChanged = true;
	switch (stmtType) {
	case ASSIGN: {
		bool isModVarUsed = false;
		int modifiedVarId = pkb->getVarAtLeftOfAssignStmt(curStmt);
		if (usedVarToStmt->find(modifiedVarId) != usedVarToStmt->end()) {
			unordered_set<int> usedStmts = usedVarToStmt->at(modifiedVarId);
			for (auto affectedStmt : usedStmts) {
				if (isStmtValidResult(curStmt, affectorStmts, affectedStmt, affectedStmts)) {
					setResultTupleToTable(affectResultTable, curStmt, affectedStmt);
				}
			}
		}

		unordered_set<int> usedVars = pkb->getVarUsedByStmt(curStmt);
		for (auto usedVarId : usedVars) {
			if (usedVarToStmt->find(usedVarId) == usedVarToStmt->end()) {
				usedVarToStmt->insert({ usedVarId, unordered_set<int>() });
			}

			if (modifiedVarId == usedVarId) {
				isModVarUsed = true;
			} else {
				if (usedVarToStmt->find(modifiedVarId) != usedVarToStmt->end()) {
					unordered_set<int> usedStmts = usedVarToStmt->at(modifiedVarId);
					for (auto affectedStmt : usedStmts) {
						usedVarToStmt->at(usedVarId).insert(affectedStmt);
					}
				}
			}

			usedVarToStmt->at(usedVarId).insert(curStmt);
		}

		if (!isModVarUsed) {
			usedVarToStmt->erase(modifiedVarId);
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
		break;
	}

	case WHILE:
		/* falls through */
	case IF:
		if (contTableStack.find(curStmt) == contTableStack.end()) {
			contTableStack.insert({ curStmt, unordered_set<unordered_map<int, unordered_set<int>>, Hasher>() });
		}
		if (contTableStack.at(curStmt).empty() || contTableStack.at(curStmt).find(*usedVarToStmt) == contTableStack.at(curStmt).end()) {
			contTableStack.at(curStmt).insert(*usedVarToStmt);
		}
		else {
			isTableChanged = false;
		}
		break;
	}

	if (pkb->getPreviousStmt(curStmt).size() != 0 && isTableChanged) {
		unordered_set<int> prevStmts = pkb->getPreviousStmt(curStmt);
		for (auto prevStmtIter = ++prevStmts.begin(); prevStmtIter != prevStmts.end(); ++prevStmtIter) {
			unordered_map<int, unordered_set<int>> copyUsedVarToStmt = *usedVarToStmt;
			reverseDfs(pkb, affectResultTable, *prevStmtIter, affectorStmts, &copyUsedVarToStmt, affectedStmts);
		}
		reverseDfs(pkb, affectResultTable, *prevStmts.begin(), affectorStmts, usedVarToStmt, affectedStmts);
	}
}

Type AffectsStar::getStmtType(PKB* pkb, int stmtId) {
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

bool AffectsStar::isStmtValidResult(int affectorStmtId, map<int, bool>* validAffectorResults, int affectedStmtId, map<int, bool>* validAffectedResults) {
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

void AffectsStar::setResultTupleToTable(ResultTable* affectResultTable, int affectorStmtId, int affectedStmtId) {
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

void AffectsStar::setBooleanToTable(ResultTable* affectResultTable) {
	if (affectResultTable->getSynCount() > 0) {
		if (affectResultTable->getTupleSize() > 0) {
			affectResultTable->setBoolean(true);
		}
		else {
			affectResultTable->setBoolean(false);
		}
	}
}

Parameter AffectsStar::getLeftChild() {
	return leftChild;
}

Parameter AffectsStar::getRightChild() {
	return rightChild;
}

vector<Parameter> AffectsStar::getSynList() {
	return synList;
}

ClauseType AffectsStar::getClauseType() {
	return PATTERN;
}
