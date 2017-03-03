#include "Type.h"
#include "Uses.h"
#include "Clause.h"

Uses::Uses(Parameter lc, Parameter rc) {
    leftChild = lc;
	rightChild = rc;

	if (lc.getParaType() != Type::CONSTANT && lc.getParaType() != Type::BOOLEAN && lc.getParaType() != Type::ANYTHING
		&& lc.getParaType() != Type::STRINGVARIABLE && lc.getParaType() != Type::INTEGER) {
		synList.push_back(lc);
	}
	if (rc.getParaType() != Type::CONSTANT && rc.getParaType() != Type::BOOLEAN && rc.getParaType() != Type::ANYTHING
		&& rc.getParaType() != Type::STRINGVARIABLE && rc.getParaType() != Type::INTEGER) {
		synList.push_back(rc);
	}
}


ResultTable Uses::evaluate(PKB *pkb, vector<Parameter> paramList, vector<vector<int>> valueList) {
	ResultTable resultTable;

	vector<Parameter> synList;
	vector<int> tuple, firstSynList, secondSynList;
	bool isLeftSyn, isRightSyn, boolRel;
	Type lcType = leftChild.getParaType();
	Type rcType = rightChild.getParaType();

	isLeftSyn = isSynonym(lcType);
	isRightSyn = isSynonym(rcType);

	if (isValidParameter(leftChild) == false || isValidParameter(rightChild) == false) {
		resultTable.setBoolean(false);
		return resultTable;
	}

	if (paramList.size() == 1) {
		paramType1 = paramList.at(0).getParaType();
		valueList1 = valueList.at(0);
	}

	if (paramList.size() == 2) {
		paramType1 = paramList.at(0).getParaType();
		valueList1 = valueList.at(0);
		paramType2 = paramList.at(1).getParaType();
		valueList2 = valueList.at(1);
	}

	if (isLeftSyn == false && isRightSyn == false) {
		boolRel = hasRelation(pkb);
		resultTable.setBoolean(boolRel);
	}
	if (isLeftSyn == true && isRightSyn == false) {
		synList.push_back(leftChild);
		resultTable.setSynList(synList);
		firstSynList = evaluateRelation(pkb, lcType);
	}
	if (isLeftSyn == false && isRightSyn == true) {
		synList.push_back(rightChild);
		resultTable.setSynList(synList);
		firstSynList = evaluateRelation(pkb, rcType);
	}
	if (isLeftSyn == true && isRightSyn == true) {
		synList.push_back(leftChild);
		synList.push_back(rightChild);
		resultTable.setSynList(synList);
		firstSynList = evaluateRelation(pkb, lcType);
		secondSynList = evaluateRelation(pkb, rcType);
	}

	if (firstSynList.empty() == false && secondSynList.empty() == false) {
		for (int firstSyn : firstSynList) {
			for (int secondSyn : secondSynList) {
				tuple.push_back(firstSyn);
				tuple.push_back(secondSyn);
				resultTable.insertTuple(tuple);
			}
		}
	}
	if (firstSynList.empty() == false && secondSynList.empty() == true) {
		for (int firstSyn : firstSynList) {
			tuple.push_back(firstSyn);
			resultTable.insertTuple(tuple);
		}
	}

	return resultTable;
}

bool Uses::isValidParameter(Parameter param) {
	bool isValidParam = false;
	bool isProcString = false;
	int varId;
	Type paramType = param.getParaType();
	string paramName = param.getParaName();

	switch (paramType) {
	case STMT:
	case ASSIGN:
	case WHILE:
	case IF:
	case PROCEDURE:
	case VARIABLE:
	case ANYTHING:
		isValidParam = true;
		break;
	case STRINGVARIABLE: //'string' procs & var
		isProcString = pkb->isProcInTable(paramName);
		varId = pkb->getVarIdByName(paramName);
		if (isProcString == true || varId != -1) {
			isValidParam = true;
		}
		break;
	case INTEGER:
		isValidParam = pkb->isStmtInModifyTable(stoi(paramName));
		break;
	}

	return isValidParam;
}

bool Uses::isSynonym(Type synType) {

	bool isSyn = false;

	switch (synType) {
	case STMT:
	case ASSIGN:
	case WHILE:
	case IF:
	case PROCEDURE:
	case VARIABLE:
		isSyn = true;
		break;
	case STRINGVARIABLE: //'string' procs
	case INTEGER:
	case ANYTHING:
		isSyn = false;
		break;
	}

	return isSyn;
}

bool Uses::hasRelation(PKB *pkb) {
	bool boolRel = false;
	Type lcType = leftChild.getParaType();
	vector<int> results = evaluateRelation(pkb, lcType);

	if (results.empty()) {
		boolRel = false;
	}
	else {
		boolRel = true;
	}

	return boolRel;
}

vector<int> Uses::evaluateRelation(PKB *pkb, Type synType) {

	unordered_set<int> stmtSet, varSet, procSet;
	vector<int> resultList, stmtList, varList, procList;
	vector<int> useStmtList, useVarList, useProcList;
	int stmtId, procId, varId;
	string lcName = leftChild.getParaName();
	string rcName = rightChild.getParaName();

	switch (synType) {
	case STMT:
		stmtList = getRestrictedList(synType);
		useStmtList = getUseStmtListOfVar();
		resultList = VectorSetOperation<int>::setIntersection(stmtList, useStmtList);
		break;
	case ASSIGN:
		stmtList = getRestrictedList(synType);
		useStmtList = getUseStmtListOfVar();
		resultList = VectorSetOperation<int>::setIntersection(stmtList, useStmtList);
		break;
	case WHILE:
		stmtList = getRestrictedList(synType);
		useStmtList = getUseStmtListOfVar();
		resultList = VectorSetOperation<int>::setIntersection(stmtList, useStmtList);
		break;
	case IF:
		stmtList = getRestrictedList(synType);
		useStmtList = getUseStmtListOfVar();
		resultList = VectorSetOperation<int>::setIntersection(stmtList, useStmtList);
		break;
	case PROCEDURE:
		procList = getRestrictedList(synType);
		useProcList = getUseProcListOfVar();
		resultList = VectorSetOperation<int>::setIntersection(procList, useProcList);
		break;
	case VARIABLE:
		varList = getRestrictedList(synType);
		useVarList = getUseVarListOfStmt();
		resultList = VectorSetOperation<int>::setIntersection(varList, useVarList);
		break;
	case INTEGER:
		stmtId = stoi(lcName);
		stmtList.push_back(stmtId);
		useStmtList = getUseStmtListOfVar();
		resultList = VectorSetOperation<int>::setIntersection(stmtList, useStmtList);
		break;
	case STRINGVARIABLE:
		if (pkb->isProcInTable(lcName) == true) {
			procId = pkb->getProcIdByName(lcName);
			procList.push_back(procId);
			useProcList = getUseProcListOfVar();
			resultList = VectorSetOperation<int>::setIntersection(procList, useProcList);
			break;
		}
		varId = pkb->getVarIdByName(rcName);
		if (varId != -1) {
			varList.push_back(varId);
			useVarList = getUseVarListOfStmt();
			resultList = VectorSetOperation<int>::setIntersection(varList, useVarList);
			break;
		}
		break;
	}

	return resultList;
}

vector<int> Uses::getUseStmtListOfVar() {

	int varId;
	vector<int> stmtList, varIdList;
	unordered_set<int> stmtSet;

	string rcName = rightChild.getParaName();
	Type rcType = rightChild.getParaType();

	switch (rcType) {
	case VARIABLE:
		varIdList = getRestrictedList(rcType);
		for (int var : varIdList) {
			varId = pkb->getVarIdByName(rcName);
			stmtSet = pkb->getStmtUseVar(varId);
			stmtList = VectorSetOperation<int>::setUnion(convertSetToVector(stmtSet), stmtList);
		}
		break;
	case ANYTHING:
		stmtSet = pkb->getAllUseStmt();
		stmtList = convertSetToVector(stmtSet);
		break;
	case STRINGVARIABLE:
		varId = pkb->getVarIdByName(rcName);
		stmtSet = pkb->getStmtUseVar(varId);
		stmtList = convertSetToVector(stmtSet);
		break;
	}

	return stmtList;
}

vector<int> Uses::getUseProcListOfVar() {

	int procId, varId;
	vector<int> procList, varIdList;
	unordered_set<int> procSet;

	string rcName = rightChild.getParaName();
	Type rcType = rightChild.getParaType();

	switch (rcType) {
	case VARIABLE:
		varIdList = getRestrictedList(rcType);
		for (int var : varIdList) {
			varId = pkb->getVarIdByName(rcName);
			procSet = pkb->getProcUseVar(varId);
			procList = VectorSetOperation<int>::setUnion(convertSetToVector(procSet), procList);
		}
		break;
	case ANYTHING:
		varIdList = pkb->getAllVarId();
		for (int var : varIdList) {
			procSet = pkb->getProcUseVar(varId);
			procList = VectorSetOperation<int>::setUnion(convertSetToVector(procSet), procList);
		}
		break;
	case STRINGVARIABLE:
		varId = pkb->getVarIdByName(rcName);
		procSet = pkb->getProcUseVar(varId);
		procList = convertSetToVector(procSet);
		break;
	}

	return procList;
}

vector<int> Uses::getUseVarListOfStmt() {
	int varId, stmtId, procId;
	vector<int> stmtList, varIdList, procIdList;
	unordered_set<int> stmtSet, varSet;

	string lcName = leftChild.getParaName();
	Type lcType = leftChild.getParaType();

	switch (lcType) {
	case STMT:
		stmtList = getRestrictedList(lcType);
		break;
	case ASSIGN:
		stmtList = getRestrictedList(lcType);
		break;
	case WHILE:
		stmtList = getRestrictedList(lcType);
		break;
	case IF:
		stmtList = getRestrictedList(lcType);
		break;
	case INTEGER:
		stmtId = stoi(lcName);
		stmtList.push_back(stmtId);
		break;
	case PROCEDURE:
		if (lcType == paramType1) {
			procIdList = valueList1;
			for (int proc : procIdList) {
				//stmtSet = pkb->getStmtUsedInProc(procId);
				stmtList = VectorSetOperation<int>::setUnion(convertSetToVector(stmtSet), stmtList);
			}
			break;
		}
		if (lcType == paramType2) {
			procIdList = valueList2;
			for (int proc : procIdList) {
				//stmtSet = pkb->getStmtUsedInProc(procId);
				stmtList = VectorSetOperation<int>::setUnion(convertSetToVector(stmtSet), stmtList);
			}
			break;
		}
		stmtSet = pkb->getAllStmtId();
		stmtList = convertSetToVector(stmtSet);
		break;
	case STRINGVARIABLE: //'string' procs
		procId = pkb->getProcIdByName(lcName);
		//stmtSet = pkb->getStmtUsedInProc(procId);
		stmtList = convertSetToVector(stmtSet);
		break;
	}

	for (int stmtId : stmtList) {
		varSet = pkb->getVarUsedByStmt(stmtId);
		varIdList = VectorSetOperation<int>::setUnion(varIdList, convertSetToVector(varSet));
	}
	return varIdList;
}

vector<int> Uses::getRestrictedList(Type synType) {
	vector<int> restrictedList;
	unordered_set<int> stmtSet, procSet;

	switch (synType) {
	case STMT:
		if (synType == paramType1) {
			restrictedList = valueList1;
			break;
		}
		if (synType == paramType2) {
			restrictedList = valueList2;
			break;
		}
		stmtSet = pkb->getAllStmtId();
		restrictedList = convertSetToVector(stmtSet);
		break;
	case ASSIGN:
		if (synType == paramType1) {
			restrictedList = valueList1;
			break;
		}
		if (synType == paramType2) {
			restrictedList = valueList2;
			break;
		}
		stmtSet = pkb->getAllAssignStmt();
		restrictedList = convertSetToVector(stmtSet);
		break;
	case WHILE:
		if (synType == paramType1) {
			restrictedList = valueList1;
			break;
		}
		if (synType == paramType2) {
			restrictedList = valueList2;
			break;
		}
		stmtSet = pkb->getAllWhileStmt();
		restrictedList = convertSetToVector(stmtSet);
		break;
	case IF:
		if (synType == paramType1) {
			restrictedList = valueList1;
			break;
		}
		if (synType == paramType2) {
			restrictedList = valueList2;
			break;
		}
		stmtSet = pkb->getAllIfId();
		restrictedList = convertSetToVector(stmtSet);
		break;
	case PROCEDURE:
		if (synType == paramType1) {
			restrictedList = valueList1;
			break;
		}
		if (synType == paramType2) {
			restrictedList = valueList2;
			break;
		}
		procSet = pkb->getAllProcId();
		restrictedList = convertSetToVector(procSet);
		break;
	case VARIABLE:
		if (synType == paramType1) {
			restrictedList = valueList1;
			break;
		}
		if (synType == paramType2) {
			restrictedList = valueList2;
			break;
		}
		restrictedList = pkb->getAllVarId();
	}

	return restrictedList;
}

vector<int> Uses::convertSetToVector(unordered_set<int> unorderedSet) {
	vector<int> vectorList;
	copy(unorderedSet.begin(), unorderedSet.end(), back_inserter(vectorList));

	return vectorList;
}

//Public 
bool Uses::hasRel(PKB *pkbSource) {
	return false;
}

vector<int> Uses::getWithRelToLeft(PKB *pkb) {
	vector<int> v;
	return v;
}

vector<int> Uses::getWithRelToRight(PKB *pkb) {
	vector<int> v;
	return v;
}

Parameter Uses::getLeftChild() {
	return leftChild;
}

Parameter Uses::getRightChild() {
	return rightChild;
}

vector<Parameter> Uses::getSynList() {
	return synList;
}

//Testing
void Uses::setPKB(PKB* pkbInput) {
	this->pkb = pkbInput;
}