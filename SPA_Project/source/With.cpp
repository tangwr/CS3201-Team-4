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
	unordered_set<int> resultList = assignResult(pkb, leftResultList, rightResultList);

	for (auto element : resultList) {
		withResultTable->insertTuple({ element });
	}
}

unordered_set<int> With::getRightResultList(PKB* pkb, ResultTable* intResultTable, ResultTable* withResultTable) {
	unordered_set<int> rightResultList;
	if (rightChild.isSynonym()) {
		if (intResultTable->isSynInTable(rightChild)) {
			rightResultList = intResultTable->getSynValue(rightChild);
		} else {
			rightResultList = getSynResultList(pkb, rightChild);
		}

		if (rightChild.getParaType() == CALL) {
			unordered_set<int> calledProcs;
			for (auto calledProcId : rightResultList) {
				calledProcs.insert(pkb->getProcCalledByStmt(calledProcId));
			}
			rightResultList = calledProcs;
		} else if (rightChild.getParaType() == CONSTANT) {
			unordered_set<int> constValues;
			for (auto constId : rightResultList) {
				constValues.insert(pkb->getConstValueById(constId));
			}
			rightResultList = constValues;
		}
	}
	else if (rightChild.isInteger()) {
		rightResultList = { stoi(rightChild.getParaName()) };
	}
	else if (rightChild.isString()) {
		int id = getIdOfString(pkb);
		if (id != NOT_FOUND) {
			rightResultList = { getIdOfString(pkb) };
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
		if (intResultTable->isSynInTable(leftChild)) {
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

unordered_set<int> With::assignResult(PKB* pkb, unordered_set<int> leftResult, unordered_set<int> rightResult) {
	unordered_set<int> resultList;
	switch (leftChild.getParaType()) {
	case PROG_LINE:
		/* falls through */
	case STMT:
		/* falls through */
	case ASSIGN:
		/* falls through */
	case WHILE:
		/* falls through */
	case IF:
		resultList = UnorderedSetOperation<int>::setIntersection(leftResult, rightResult);
		break;

	case CONSTANT:
		for (auto value : rightResult) {
			//if (pkb->isConstInTable(id)) {
				//int constId = pkb->getConstIdByValue(value);
				//if (leftResult.find(constId) != leftResult.end()) {
					//resultList.insert(constId);
				//}
			//}
		}
		break;
	case CALL:
		for (auto id : rightResult) {
			string idString = getStringOfId(pkb, id);
			if (pkb->isProcInTable(idString)) {
				int procId = pkb->getProcIdByName(idString);
				//unordered_set<int> callStmts = pkb->getStmtCallProc(procId);
				//for (auto callStmtId : callStmts) {
					//if (leftResult.find(callStmtId) != leftResult.end()) {
						//resultList.insert(id);
					//}
				//}
			}
		}
		break;
	case PROCEDURE:
		for (auto id : rightResult) {
			string idString = getStringOfId(pkb, id);
			if (pkb->isProcInTable(idString)) {
				int procId = pkb->getProcIdByName(idString);
				if (leftResult.find(procId) != leftResult.end()) {
					resultList.insert(procId);
				}
			}
		}
		break;
	case VARIABLE:
		for (auto id : rightResult) {
			string idString = getStringOfId(pkb, id);
			if (pkb->isVarInTable(idString)) {
				int varId = pkb->getVarIdByName(idString);
				if (leftResult.find(varId) != leftResult.end()) {
					resultList.insert(varId);
				}
			}
		}
		break;
	}
	return resultList;
}

int With::getIdOfString(PKB* pkb) {
	switch (leftChild.getParaType()) {
	case CALL:
		/* falls through */
	case PROCEDURE:
		return pkb->getProcIdByName(rightChild.getParaName());
	case VARIABLE:
		return pkb->getVarIdByName(rightChild.getParaName());
	default:
		return ERROR;
	}
}

string With::getStringOfId(PKB* pkb, int id) {
	Type idType;
	if (rightChild.getParaType() == STRINGVARIABLE) {
		idType = leftChild.getParaType();
	} else {
		idType = rightChild.getParaType();
	}

	switch (idType) {
	case CALL:
		/* falls through */
	case PROCEDURE:
		//return pkb->getProcNameById(id);
	case VARIABLE:
		return pkb->getVarNameById(id);
	default:
		return "";
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

unordered_set<int> With::getCallStmtWithCalledProcId(PKB* pkb, unordered_set<int> callStmts, unordered_set<int> procs) {
	unordered_set<int> resultList;
	for (auto callStmtId : callStmts) {
		if (procs.find(pkb->getProcCalledByStmt(callStmtId)) != procs.end()) {
			resultList.insert(callStmtId);
		}
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