#include "With.h"
#include "UnorderedSetOperation.h"

using namespace std;

const int ERROR = -1;
const int NOT_FOUND = -1;

With::With(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;
}

ResultTable With::evaluate(PKB* pkb, ResultTable intResultTable) {
	ResultTable withResultTable;
	setSynToTable(&withResultTable);
	setResultToTable(pkb, &intResultTable, &withResultTable);
	setBooleanToTable(&withResultTable);
	return withResultTable;
}

void With::setSynToTable(ResultTable* withResultTable) {
	withResultTable->setSynList({ leftChild });
}

void With::setResultToTable(PKB* pkb, ResultTable* intResultTable, ResultTable* withResultTable) {
	unordered_set<int> rightResultList = getRightResultList(pkb, intResultTable, withResultTable);
	unordered_set<int> leftResultList = getLeftResultList(pkb, intResultTable, withResultTable);
	unordered_set<int> resultList = UnorderedSetOperation<int>::setIntersection(leftResultList, rightResultList);

	for (auto element : resultList) {
		withResultTable->insertTuple({ element });
	}
}

unordered_set<int> With::getRightResultList(PKB* pkb, ResultTable* intResultTable, ResultTable* withResultTable) {
	unordered_set<int> rightResultList;
	if (rightChild.isSynonym()) {
		if (intResultTable->hasSynonym(rightChild)) {
			rightResultList = intResultTable->getSynValue(rightChild);
		} else {
			rightResultList = getSynResultList(pkb, rightChild);
		}
	}
	else if (rightChild.isInteger()) {
		rightResultList = { stoi(rightChild.getParaName()) };
	}
	else if (rightChild.isString()) {
		int Id = getStringId(pkb);
		if (Id != NOT_FOUND) {
			rightResultList = { getStringId(pkb) };
		}
	}
	else {
		//error
	}
	return rightResultList;
}

unordered_set<int> With::getLeftResultList(PKB* pkb, ResultTable* intResultTable, ResultTable* withResultTable) {
	unordered_set<int> leftResultList;
	if (leftChild.isSynonym()) {
		if (intResultTable->hasSynonym(leftChild)) {
			leftResultList = intResultTable->getSynValue(leftChild);
		}
		else {
			leftResultList = getSynResultList(pkb, leftChild);
		}
	}
	else {
		//error
	}
	return leftResultList;
}

int With::getStringId(PKB* pkb) {
	switch (leftChild.getParaType()) {
	case PROCEDURE:
		return pkb->getProcIdByName(rightChild.getParaName());
	case VARIABLE:
		return pkb->getVarIdByName(rightChild.getParaName());
	default:
		return ERROR;
	}
}

unordered_set<int> With::getSynResultList(PKB* pkb, Parameter parameter) {
	unordered_set<int> resultList;
	switch (parameter.getParaType()) {
	case PROG_LINE:
		/* falls through */
	case STMT:
		resultList = pkb->getAllStmtId();
		break;
	case STMTLST:
		resultList = pkb->getAllStmtLst();
		break;

	case ASSIGN:
		resultList = pkb->getAllAssignStmt();
		break;
	case WHILE:
		resultList = pkb->getAllWhileStmt();
		break;
	case IF:
		resultList = pkb->getAllIfId();
		break;
	case CALL:
		resultList = pkb->getAllCallId();
		break;

	case PROCEDURE:
		resultList = pkb->getAllProcId();
		break;
	case VARIABLE:
		resultList = pkb->getAllVarId();
		break;
	case CONSTANT:
		resultList = pkb->getAllConstId();
		break;
	}
	return resultList;
}

void With::setBooleanToTable(ResultTable* withResultTable) {
	if (withResultTable->getTupleSize() > 0) {
		withResultTable->setBoolean(true);
	}
	else {
		withResultTable->setBoolean(false);
	}
}


vector<Parameter>With::getSynList() {
	return synList;
}

Parameter With::getLeftChild() {
	return leftChild;
}
Parameter With::getRightChild() {
	return rightChild;
}
void With::insertSynList(Parameter p) {
	synList.push_back(p);
}

ClauseType With::getClauseType() {
	return WITH;
}