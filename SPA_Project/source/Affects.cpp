#include "Affects.h"

Affects::Affects(Parameter lc, Parameter rc) {
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

ResultTable Affects::evaluate(PKB* pkb, ResultTable intResultTable) {
	ResultTable affectResultTable;
	affectResultTable.setBoolean(false);

	setSynToTable(&affectResultTable);
	setResultToTable(pkb, &intResultTable, &affectResultTable);
	setBooleanToTable(&affectResultTable);

	return affectResultTable;
}

void Affects::setSynToTable(ResultTable* affectResultTable) {
	if (leftChild.isSynonym() && leftChild.isSame(rightChild)) {
		affectResultTable->setSynList({ leftChild });
	} else {
		affectResultTable->setSynList(synList);
	}
}

void Affects::setResultToTable(PKB* pkb, ResultTable* intResultTable, ResultTable* affectResultTable) {
	unordered_set<int> affectorValidStmts = getValidStmts(pkb, intResultTable, leftChild);
	unordered_set<int> affectedValidStmts = getValidStmts(pkb, intResultTable, rightChild);
	dfsToSetResultTable(pkb, intResultTable, affectResultTable, affectorValidStmts, affectedValidStmts);
	affectResultTable->removeDuplicateTuple();
}

unordered_set<int> Affects::getValidStmts(PKB* pkb, ResultTable* intResultTable, Parameter child) {
	switch (child.getParaType()) {
	case INTEGER:
		return{ stoi(child.getParaName()) };
	case ANYTHING:
		return pkb->getAllAssignStmt();
	case ASSIGN:
		/* falls through */
	case STMT:
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
	unordered_map<int, set<int>> affector;
	unordered_map<int, set<int>> affected;

	for (auto affectorStmtId : validAffectorStmts) {
		int procId = pkb->getProcContainingStmt(affectorStmtId);
		if (affector.find(procId) == affector.end()) {
			affector.insert({ procId, set<int>() });
		}
		affector.at(procId).insert(affectorStmtId);
	}

	for (auto affectedStmtId : validAffectedStmts) {
		int procId = pkb->getProcContainingStmt(affectedStmtId);
		if (affected.find(procId) == affected.end()) {
			affected.insert({ procId, set<int>() });
		}
		affected.at(procId).insert(affectedStmtId);
	}

	for (auto proc : affector) {
		int procId = proc.first;
		if (affected.find(procId) == affected.end()) {
			continue;
		}
		
		set<int> affectorStmts = proc.second;
		set<int> affectedStmts = affected.at(procId);

		if (affectorStmts.size() <= affectedStmts.size()) {
			unordered_map<int, int> modifiedVarToStmt;
			int minStmt = *affectorStmts.begin();
			fowardDfs(pkb, affectResultTable, minStmt, &affectorStmts, &modifiedVarToStmt, &affectedStmts);
		} else {
			unordered_map<int, unordered_set<int>> usedVarToStmts;
			int maxStmt = *affectedStmts.rbegin();
			reverseDfs(pkb, affectResultTable, maxStmt, &affectorStmts, &usedVarToStmts, &affectedStmts);
		}

		if (hasFoundAllResult) {
			return;
		}
	}
}

void Affects::fowardDfs(PKB* pkb, ResultTable* affectResultTable, int curStmt,
						set<int>* affectorStmts, unordered_map<int, int>* modifiedVarToStmt, set<int>* affectedStmts) {
	if (hasFoundAllResult) {
		return;
	}

	Type stmtType = getStmtType(pkb, curStmt);
	bool isTableChanged = true;
	switch (stmtType) {
	case ASSIGN: {
		unordered_set<int> usedVars = pkb->getVarUsedByStmt(curStmt);
		for (auto usedVarId : usedVars) {
			if (modifiedVarToStmt->find(usedVarId) != modifiedVarToStmt->end()) {
				int affectorStmt = modifiedVarToStmt->at(usedVarId);
				if (isStmtValidResult(affectorStmt, affectorStmts, curStmt, affectedStmts)) {
					setResultTupleToTable(affectResultTable, affectorStmt, curStmt);
				}
			}
		}

		int modifiedVar = pkb->getVarAtLeftOfAssignStmt(curStmt);
		if (modifiedVarToStmt->find(modifiedVar) != modifiedVarToStmt->end()) {
			modifiedVarToStmt->erase(modifiedVarToStmt->find(modifiedVar));
		}
		modifiedVarToStmt->insert({ modifiedVar, curStmt });
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

	case WHILE: {
		if (whileTableStack.find(curStmt) == whileTableStack.end()) {
			whileTableStack.insert({ curStmt, unordered_set<unordered_map<int, int>, Hasher>() });
		}

		if (whileTableStack.at(curStmt).empty() || whileTableStack.at(curStmt).find(*modifiedVarToStmt) == whileTableStack.at(curStmt).end()) {
			whileTableStack.at(curStmt).insert(*modifiedVarToStmt);
		} else {
			isTableChanged = false;
		}
		break;
	}

	case IF:
		break;
	}

	if (pkb->getNextStmt(curStmt).size() != 0 && isTableChanged) {
		unordered_set<int> nextStmts = pkb->getNextStmt(curStmt);
		for (auto nextStmtIter = ++nextStmts.begin(); nextStmtIter != nextStmts.end(); ++nextStmtIter) {
			unordered_map<int, int> copyModifiedVarToStmt = *modifiedVarToStmt;
			fowardDfs(pkb, affectResultTable, *nextStmtIter, affectorStmts, &copyModifiedVarToStmt, affectedStmts);
		}
		fowardDfs(pkb, affectResultTable, *nextStmts.begin(), affectorStmts, modifiedVarToStmt, affectedStmts);
	}
}

void Affects::reverseDfs(PKB* pkb, ResultTable* affectResultTable, int curStmt,
						set<int>* affectorStmts, unordered_map<int, unordered_set<int>>* usedVarToStmt, set<int>* affectedStmts) {
	if (hasFoundAllResult) {
		return;
	}

	Type stmtType = getStmtType(pkb, curStmt);
	bool isTableChanged = true;
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
		for (auto usedVar : usedVars) {
			if (usedVarToStmt->find(usedVar) == usedVarToStmt->end()) {
				usedVarToStmt->insert({ usedVar, unordered_set<int>() });
			}
			usedVarToStmt->at(usedVar).insert(curStmt);
		}
		break;
	}
	case CALL: {
		unordered_set<int> modifedVars = pkb->getVarModifiedInStmt(curStmt);
		for (auto modifiedVarId : modifedVars) {
			if (usedVarToStmt->find(modifiedVarId) != usedVarToStmt->end()) {
				usedVarToStmt->erase(modifiedVarId);
			}
		}
		break;
	}

	case WHILE:
		/* falls through */
	case IF: {
		if (contTableStack.find(curStmt) == contTableStack.end()) {
			contTableStack.insert({ curStmt, unordered_set<unordered_map<int, unordered_set<int>>, Hasher>() });
		}
		if (contTableStack.at(curStmt).empty() || contTableStack.at(curStmt).find(*usedVarToStmt) == contTableStack.at(curStmt).end()) {
			contTableStack.at(curStmt).insert(*usedVarToStmt);
		} else {
			isTableChanged = false;
		}
		break;
	}
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

bool Affects::isStmtValidResult(int affectorStmtId, set<int>* validAffectorResults, int affectedStmtId, set<int>* validAffectedResults) {
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
	if (leftChild.isSynonym()) {
		if (rightChild.isSynonym()) {
			affectResultTable->insertTuple({ affectorStmtId, affectedStmtId });
		} else {
			affectResultTable->insertTuple({ affectorStmtId });
		}
	} else {
		if (rightChild.isSynonym()) {
			affectResultTable->insertTuple({ affectedStmtId });
		} else {
			affectResultTable->setBoolean(true);
		}
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
