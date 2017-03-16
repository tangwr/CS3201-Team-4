#include "Pattern.h"
#include "ExpOperation.h"
#include "Tokenizer.h"

const int NOT_FOUND = -1;

Pattern::Pattern(Parameter lc, Parameter rc, Parameter f, bool isSubExp) {
	leftChild = lc;
	rightChild = rc;
	factor = f;
	hasUnderScore = isSubExp;

	if (leftChild.isSynonym()) {
		synList.push_back(leftChild);
	}
	if (rightChild.isSynonym()) {
		synList.push_back(rightChild);
	}
	if (factor.getParaType() == STRINGVARIABLE) {
		prefix = getPrefix(factor.getParaName());
	}
}

ResultTable Pattern::evaluate(PKB* pkb, ResultTable intResultTable) {
	ResultTable pattResultTable;
	setSynToTable(&pattResultTable);
	setResultToTable(pkb, &intResultTable, &pattResultTable);
	setBooleanToTable(&pattResultTable);
	return pattResultTable;
}

void Pattern::setSynToTable(ResultTable* pattResultTable) {
	pattResultTable->setSynList(synList);
}

void Pattern::setResultToTable(PKB* pkb, ResultTable* intResultTable, ResultTable* pattResultTable) {
	switch (intResultTable->getSynCount()) {
	case 0:
		setStmtsFromVars(pkb, pattResultTable, getVars(pkb));
		break;
	case 1:
		if (intResultTable->isSynInTable(leftChild)) {
			setVarsFromStmts(pkb, pattResultTable, intResultTable->getSynValue(leftChild));
		}
		else if (intResultTable->isSynInTable(rightChild)) {
			setStmtsFromVars(pkb, pattResultTable, intResultTable->getSynValue(rightChild));
		}
		break;
	case 2:
		matchTuplePattern(pkb, intResultTable, pattResultTable);
		break;
	}
}

void Pattern::setBooleanToTable(ResultTable* pattResultTable) {
	if (pattResultTable->getTupleSize() > 0) {
		pattResultTable->setBoolean(true);
	} else {
		pattResultTable->setBoolean(false);
	}
}

void Pattern::setVarsFromStmts(PKB* pkb, ResultTable* pattResultTable, unordered_set<int> stmts) {
	for (auto stmtId : stmts) {
		if (!isValidStmtType(pkb, stmtId)) {
			continue;
		}

		int varInStmt = getVarWithStmt(pkb, stmtId);
		switch (rightChild.getParaType()) {
		case STRINGVARIABLE:
			if (varInStmt == pkb->getVarIdByName(rightChild.getParaName())) {
				setResultTupleToTable(pkb, pattResultTable, stmtId, varInStmt);
			}
			break;
		case VARIABLE:
			/* falls through */
		case ANYTHING:
			if (varInStmt != NOT_FOUND) {
				setResultTupleToTable(pkb, pattResultTable, stmtId, varInStmt);
			}
			break;
		}
	}
}

void Pattern::setStmtsFromVars(PKB* pkb, ResultTable* pattResultTable, unordered_set<int> vars) {
	for (auto varId : vars) {
		unordered_set<int> stmtWithVar = getStmtsWithVar(pkb, varId);
		for (auto stmtId : stmtWithVar) {
			setResultTupleToTable(pkb, pattResultTable, stmtId, varId);
		}
	}
}

unordered_set<int> Pattern::getStmtsWithVar(PKB* pkb, int varId) {
	unordered_set<int> stmtWithVar;
	switch (leftChild.getParaType()) {
	case ASSIGN:
		stmtWithVar = pkb->getStmtInAssignWithVar(varId);
		break;
	case WHILE:
		stmtWithVar = pkb->getStmtInWhileWithCtrlVar(varId);
		break;
	case IF:
		stmtWithVar = pkb->getStmtInIfWithCtrlVar(varId);
		break;
	}
	return stmtWithVar;
}

int Pattern::getVarWithStmt(PKB* pkb, int stmtId) {
	int varInStmt;
	switch (leftChild.getParaType()) {
	case ASSIGN:
		varInStmt = pkb->getVarAtLeftOfAssignStmt(stmtId);
		break;
	case WHILE:
		varInStmt = pkb->getCtrlVarInWhileStmt(stmtId);
		break;
	case IF:
		varInStmt = pkb->getCtrlVarInIfStmt(stmtId);
		break;
	}
	return varInStmt;
}

unordered_set<int> Pattern::getVars(PKB* pkb) {
	unordered_set<int> vars;
	switch (rightChild.getParaType()) {
	case STRINGVARIABLE: {
			int varId = pkb->getVarIdByName(rightChild.getParaName());
			if (varId != NOT_FOUND) {
				vars = { varId };
			}
		}
		break;
	case ANYTHING:
		/* falls through */
	case VARIABLE:
		vars = pkb->getAllVarId();
		break;
	}
	return vars;
}

void Pattern::setResultTupleToTable(PKB* pkb, ResultTable* pattResultTable, int stmtId, int varId) {
	switch (leftChild.getParaType()) {
	case ASSIGN:
		if (hasPattern(pkb, stmtId)) {
			if (rightChild.isSynonym()) {
				pattResultTable->insertTuple({ stmtId, varId });
			} else {
				pattResultTable->insertTuple({ stmtId });
			}
		}
		break;
	case WHILE:
		/* falls through */
	case IF:
		if (rightChild.isSynonym()) {
			pattResultTable->insertTuple({ stmtId, varId });
		} else {
			pattResultTable->insertTuple({ stmtId });
		}
		break;
	}
}

void Pattern::matchTuplePattern(PKB* pkb, ResultTable* intResultTable, ResultTable* pattResultTable) {
	if (!leftChild.isSynonym() || !rightChild.isSynonym()) {
		return;
	}

	int stmtSynIndex = intResultTable->getSynIndex(leftChild);
	int varSynIndex = intResultTable->getSynIndex(rightChild);

	vector<vector<int>> tupleList = intResultTable->getTupleList();
	for (int tupleIndex = 0; tupleIndex < (int)tupleList.size(); tupleIndex++) {
		switch (leftChild.getParaType()) {
		case ASSIGN:
			if (pkb->getVarAtLeftOfAssignStmt(tupleList[tupleIndex][stmtSynIndex]) == tupleList[tupleIndex][varSynIndex]
				&& hasPattern(pkb, tupleList[tupleIndex][stmtSynIndex])) {
				pattResultTable->insertTuple({ tupleList[tupleIndex][stmtSynIndex], tupleList[tupleIndex][varSynIndex] });
			}
		case WHILE:
			if (pkb->getCtrlVarInWhileStmt(tupleList[tupleIndex][stmtSynIndex]) == tupleList[tupleIndex][varSynIndex]) {
				pattResultTable->insertTuple({ tupleList[tupleIndex][stmtSynIndex], tupleList[tupleIndex][varSynIndex] });
			}
		case IF:
			if (pkb->getCtrlVarInIfStmt(tupleList[tupleIndex][stmtSynIndex]) == tupleList[tupleIndex][varSynIndex]) {
				pattResultTable->insertTuple({ tupleList[tupleIndex][stmtSynIndex], tupleList[tupleIndex][varSynIndex] });
			}
		}
	}
}

bool Pattern::hasPattern(PKB* pkb, int assignStmtId) {
	switch (factor.getParaType()) {
	case ANYTHING:
		return true;
	case STRINGVARIABLE:
		if (hasUnderScore) {
			if (pkb->getExpInAssignStmt(assignStmtId).find(prefix) != string::npos) {
				return true;
			}
		}
		else {
			if (pkb->getExpInAssignStmt(assignStmtId).compare(prefix) == 0) {
				return true;
			}
		}
	}
	return false;
}

bool Pattern::isValidStmtType(PKB* pkb, int stmtId) {
	switch (leftChild.getParaType()) {
	case ASSIGN:
		if (pkb->isStmtInAssignTable(stmtId)) {
			return true;
		}
		break;
	case WHILE:
		if (pkb->isStmtInWhileTable(stmtId)) {
			return true;
		}
		break;
	case IF:
		if (pkb->isStmtInIfTable(stmtId)) {
			return true;
		}
		break;
	}
	return false;
}

string Pattern::getPrefix(string infixString) {
	stack<string> prefix = ExpOperation::evaluatePrefix(infixString);
	string prefixString;
	while (!prefix.empty()) {
		prefixString += prefix.top() + "|";
		prefix.pop();
	}

	return prefixString;
}


void Pattern::setUnderScore(bool us) {
	hasUnderScore = us;
}

void Pattern::setFactor(Parameter f) {
	factor = f;
}

bool Pattern::getUnderScore() {
	return hasUnderScore;
}

Parameter Pattern::getLeftChild() {
	return leftChild;
}

Parameter Pattern::getRightChild() {
	return rightChild;
}

Parameter Pattern::getFactor() {
	return factor;
}

vector<Parameter> Pattern::getSynList() {
	return synList;
}

ClauseType Pattern::getClauseType() {
	return PATTERN;
}