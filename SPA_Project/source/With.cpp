#pragma once

#include "With.h"
#include "UnorderedSetOperation.h"

#define ERROR -1
#define NOT_FOUND -1
#define INTIAL_INDEX 1
#define LEFT_ASSIGNMENT 0
#define RIGHT_ASSIGNMENT 1

#define STRING_EMPTY ""

With::With(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;

	if (leftChild.isSynonym()) {
		synList.push_back(leftChild);
	}
	if (rightChild.isSynonym() && !rightChild.isSame(leftChild)) {
		synList.push_back(rightChild);
	}
}

ResultTable With::evaluate(PKB* pkb, ResultTable intResultTable) {
	ResultTable withResultTable;
	setSynToTable(&withResultTable);
	setResultToTable(pkb, &intResultTable, &withResultTable);
	return withResultTable;
}

void With::setSynToTable(ResultTable* withResultTable) {
	withResultTable->setSynList(synList);
}

void With::setResultToTable(PKB* pkb, ResultTable* intResultTable, ResultTable* withResultTable) {
	switch (synList.size()) {
	case 0:
		setBooleanResult(pkb, intResultTable, withResultTable);
		break;
	case 1:
		/* falls through */
	case 2:
		switch (intResultTable->getSynCount()) {
		case 0:
			/* falls thorugh */
		case 1:
			setSynonymResult(pkb, intResultTable, withResultTable);
			break;
		case 2:
			setMatchingTupleResult(pkb, intResultTable, withResultTable);
			break;
		}
		break;
	}
}

void With::setBooleanResult(PKB* pkb, ResultTable* intResultTable, ResultTable* withResultTable) {
	if (leftChild.getParaName() == rightChild.getParaName()) {
		withResultTable->setBoolean(true);
	} else {
		withResultTable->setBoolean(false);
	}
}

void With::setSynonymResult(PKB* pkb, ResultTable* intResultTable, ResultTable* withResultTable) {
	unordered_set<int> rightResultList = getResultList(pkb, intResultTable, withResultTable, rightChild, leftChild);
	unordered_set<int> leftResultList = getResultList(pkb, intResultTable, withResultTable, leftChild, rightChild);
	if (leftChild.isSynonym()) {
		assignResult(pkb, withResultTable, leftResultList, rightResultList);
	} else {
		assignResult(pkb, withResultTable, leftResultList, rightResultList);
	}
}

void With::setMatchingTupleResult(PKB* pkb, ResultTable* intResultTable, ResultTable* withResultTable) {
	vector<vector<int>> tupleList = intResultTable->getTupleList();
	for (int tupleIndex = INTIAL_INDEX; tupleIndex < (int)tupleList.size(); tupleIndex++) {
		if (tupleList[tupleIndex][LEFT_ASSIGNMENT] == tupleList[tupleIndex][RIGHT_ASSIGNMENT]) {
			withResultTable->insertTuple({ tupleList[tupleIndex][LEFT_ASSIGNMENT],tupleList[tupleIndex][RIGHT_ASSIGNMENT] });
		}
	}
}

unordered_set<int> With::getResultList(PKB* pkb, ResultTable* intResultTable, ResultTable* withResultTable, Parameter child, Parameter oppChild) {
	unordered_set<int> resultList;
	if (child.isSynonym()) {
		if (intResultTable->isSynInTable(child)) {
			resultList = intResultTable->getSynValue(child);
		} else {
			resultList = getSynResultList(pkb, child);
		}
	} else if (child.isInteger()) {
		resultList = { stoi(child.getParaName()) };
	} else if (child.isString()) {
		int id = getIdOfString(pkb, child, oppChild.getParaType());
		if (id != NOT_FOUND) {
			resultList = { id };
		}
	}
	return resultList;
}

void With::assignResult(PKB* pkb, ResultTable* withResultTable, unordered_set<int> leftResult, unordered_set<int> rightResult) {
	Parameter assigner;
	Parameter assigned;
	unordered_set<int> assignerResult;
	unordered_set<int> assignedResult;
	if (leftChild.isSynonym()) {
		assigner = rightChild;
		assigned = leftChild;

		assignerResult = rightResult;
		assignedResult = leftResult;
	} else {
		assigner = leftChild;
		assigned = rightChild;

		assignerResult = leftResult;
		assignedResult = rightResult;
	}
	
	unordered_set<int> resultList;
	switch (assigned.getParaType()) {
	case PROG_LINE:
		/* falls through */
	case STMT:
		/* falls through */
	case ASSIGN:
		/* falls through */
	case WHILE:
		/* falls through */
	case IF:
		/* falls through */
	case CONSTANT:
		resultList = UnorderedSetOperation<int>::setIntersection(assignerResult, assignedResult);
		for (auto value : resultList) {
			setResultTupleToTable(withResultTable, value, value);
		}
		break;

	case CALL:
		if (assigned.getAttributeProc()) {
			for (auto id : assignerResult) {
				int assignerId = id;
				if (assigner.getParaType() == CALL) {
					assignerId = pkb->getProcCalledByStmt(id);
				}

				string idString;
				if (assigner.getParaType() == STRINGVARIABLE) {
					idString = getStringOfId(pkb, assignerId, assigned.getParaType());
				} else {
					idString = getStringOfId(pkb, assignerId, assigner.getParaType());
				}

				if (pkb->isProcInTable(idString)) {
					int procId = pkb->getProcIdByName(idString);
					unordered_set<int> callStmts = pkb->getStmtCallProc(procId);
					for (auto callStmtId : callStmts) {
						if (assignedResult.find(callStmtId) != assignedResult.end()) {
							if (leftChild.isSynonym()) {
								setResultTupleToTable(withResultTable, callStmtId, id);
							} else {
								setResultTupleToTable(withResultTable, id, callStmtId);
							}
						}
					}
				}
			}
		} else {
			resultList = UnorderedSetOperation<int>::setIntersection(leftResult, rightResult);
			for (auto stmtId : resultList) {
				setResultTupleToTable(withResultTable, stmtId, stmtId);
			}
			break;
		}
		break;
	case PROCEDURE:
		for (auto id : assignerResult) {
			int assignerId = id;
			if (assigner.getParaType() == CALL) {
				assignerId = pkb->getProcCalledByStmt(id);
			}

			string idString;
			if (assigner.getParaType() == STRINGVARIABLE) {
				idString = getStringOfId(pkb, assignerId, assigned.getParaType());
			} else {
				idString = getStringOfId(pkb, assignerId, assigner.getParaType());
			}
			
			if (pkb->isProcInTable(idString)) {
				int procId = pkb->getProcIdByName(idString);
				if (assignedResult.find(procId) != assignedResult.end()) {
					if (leftChild.isSynonym()) {
						setResultTupleToTable(withResultTable, procId, id);
					} else {
						setResultTupleToTable(withResultTable, id, procId);
					}
				}
			}
		}
		break;
	case VARIABLE:
		for (auto id : assignerResult) {
			int assignerId = id;
			if (assigner.getParaType() == CALL) {
				assignerId = pkb->getProcCalledByStmt(id);
			}

			string idString;
			if (assigner.getParaType() == STRINGVARIABLE) {
				idString = getStringOfId(pkb, assignerId, assigned.getParaType());
			} else {
				idString = getStringOfId(pkb, assignerId, assigner.getParaType());
			}

			if (pkb->isVarInTable(idString)) {
				int varId = pkb->getVarIdByName(idString);
				if (assignedResult.find(varId) != assignedResult.end()) {
					if (leftChild.isSynonym()) {
						setResultTupleToTable(withResultTable, varId, id);
					} else {
						setResultTupleToTable(withResultTable, id, varId);
					}
				}
			}
		}
		break;
	}
}

int With::getIdOfString(PKB* pkb, Parameter child, Type type) {
	switch (type) {
	case CALL:
		/* falls through */
	case PROCEDURE:
		return pkb->getProcIdByName(child.getParaName());
	case VARIABLE:
		return pkb->getVarIdByName(child.getParaName());
	default:
		return ERROR;
	}
}

string With::getStringOfId(PKB* pkb, int id, Type type) {
	switch (type) {
	case CALL:
		/* falls through */
	case PROCEDURE:
		return pkb->getProcNameById(id);
	case VARIABLE:
		return pkb->getVarNameById(id);
	default:
		return STRING_EMPTY;
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
		resultList = pkb->getAllConst();
		break;
	}
	return resultList;
}

void With::setResultTupleToTable(ResultTable* withResultTable, int left, int right) {
	switch (withResultTable->getSynCount()) {
	case 0:
		withResultTable->setBoolean(true);
		break;
	case 1:
		if (leftChild.isSynonym() && rightChild.isSynonym()) {
			if (left == right) {
				withResultTable->insertTuple({ left });
			}
		} else if (leftChild.isSynonym()) {
			withResultTable->insertTuple({ left });
		} else {
			withResultTable->insertTuple({ right });
		}
		break;
	case 2:
		withResultTable->insertTuple({ left, right });
		break;
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
