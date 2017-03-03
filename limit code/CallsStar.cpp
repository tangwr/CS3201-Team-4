#include "Type.h"
#include "CallsStar.h"
#include "Clause.h"

CallsStar::CallsStar(Parameter lc, Parameter rc) {
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

ResultTable CallsStar::evaluate(PKB *pkb, vector<Parameter> paramList, vector<vector<int>> valueList) {
	ResultTable resultTable;

	vector<Parameter> synList;
	vector<int> tuple, firstSynList, secondSynList;
	bool isLeftSyn, isRightSyn, boolRel;


	Type lcType = leftChild.getParaType();
	Type rcType = rightChild.getParaType();
	string lcName = leftChild.getParaName();
	string rcName = rightChild.getParaName();

	isLeftSyn = isSynonym(lcType);
	isRightSyn = isSynonym(rcType);

	if (isValidParameter(leftChild) == false || isValidParameter(rightChild) == false) {
		resultTable.setBoolean(false);
		return resultTable;
	}

	if (paramList.size() == 1) {
		paramType1 = paramList.at(0).getParaType();
		paramName1 = paramList.at(0).getParaName();
		valueList1 = valueList.at(0);
	}

	if (paramList.size() == 2) {
		paramType1 = paramList.at(0).getParaType();
		paramName1 = paramList.at(0).getParaName();
		valueList1 = valueList.at(0);
		paramType2 = paramList.at(1).getParaType();
		paramName2 = paramList.at(2).getParaName();
		valueList2 = valueList.at(1);
	}


	if (isLeftSyn == false && isRightSyn == false) {
		boolRel = hasRelation(pkb);
		resultTable.setBoolean(boolRel);
	}
	if (isLeftSyn == true && isRightSyn == false) {
		synList.push_back(leftChild);
		resultTable.setSynList(synList);
		firstSynList = evaluateRelation(pkb, lcType, lcName);
	}
	if (isLeftSyn == false && isRightSyn == true) {
		synList.push_back(rightChild);
		resultTable.setSynList(synList);
		firstSynList = evaluateRelation(pkb, rcType, rcName);
	}
	if (isLeftSyn == true && isRightSyn == true) {
		synList.push_back(leftChild);
		synList.push_back(rightChild);
		resultTable.setSynList(synList);
		firstSynList = evaluateRelation(pkb, lcType, lcName);
		secondSynList = evaluateRelation(pkb, rcType, rcName);
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

bool CallsStar::isValidParameter(Parameter param) {
	bool isValidParam = false;
	bool isProcString = false;
	int varId;

	Type paramType = param.getParaType();
	string paramName = param.getParaName();

	switch (paramType) {
	case PROCEDURE:
		isValidParam = true;
		break;
	case STRINGVARIABLE: //'string' procs & var
		isProcString = pkb->isProcInTable(paramName);
		if (isProcString == true) {
			isValidParam = true;
		}
		break;
	}

	return isValidParam;
}

bool CallsStar::isSynonym(Type synType) {

	bool isSyn = false;

	switch (synType) {
	case PROCEDURE:
		isSyn = true;
		break;
	case ANYTHING:
	case STRINGVARIABLE: //'string' procs
		isSyn = false;
		break;
	}

	return isSyn;
}

bool CallsStar::hasRelation(PKB *pkb) {
	bool boolRel = false;
	Type lcType = leftChild.getParaType();
	string lcName = leftChild.getParaName();
	vector<int> results = evaluateRelation(pkb, lcType, lcName);

	if (results.empty()) {
		boolRel = false;
	}
	else {
		boolRel = true;
	}

	return boolRel;
}

vector<int> CallsStar::evaluateRelation(PKB *pkb, Type synType, string synName) {
	vector<int> procList, callProcList, resultList, callList;
	string lcName = leftChild.getParaName();
	string rcName = rightChild.getParaName();
	int procId;
	unordered_set<int> callSet, procSet;

	switch (synType) {
	case PROCEDURE:
		procList = getRestrictedList(synType, synName);
		for (int procId : procList) {
			callSet = pkb->getProcCalledByProc(procId);
			callList = VectorSetOperation<int>::setUnion(convertSetToVector(callSet), callList);
		}
		if (synName == lcName) {
			callProcList = getCallRightProcList();
		}
		if (synName == rcName) {
			callProcList = getCallLeftProcList();
		}
		resultList = VectorSetOperation<int>::setIntersection(callList, callProcList);
		break;
	case STRINGVARIABLE:
		procId = pkb->getProcIdByName(synName);
		callSet = pkb->getProcCalledByProc(procId);
		callList = convertSetToVector(callSet);
		if (synName == lcName) {
			callProcList = getCallRightProcList();
		}
		if (synName == rcName) {
			callProcList = getCallLeftProcList();
		}
		resultList = VectorSetOperation<int>::setIntersection(callList, callProcList);
		break;
	case ANYTHING:
		procSet = pkb->getAllProcId();
		procList = convertSetToVector(procSet);
		for (int procId : procList) {
			callSet = pkb->getProcCalledByProc(procId);
			callList = VectorSetOperation<int>::setUnion(convertSetToVector(callSet), callList);
		}
		if (synName == lcName) {
			callProcList = getCallRightProcList();
		}
		if (synName == rcName) {
			callProcList = getCallLeftProcList();
		}
		resultList = VectorSetOperation<int>::setIntersection(callList, callProcList);
		break;
	}

	return resultList;
}

vector<int> CallsStar::getCallLeftProcList() {
	Type lcType = leftChild.getParaType();
	string lcName = leftChild.getParaName();
	vector<int> procList, callList;
	unordered_set<int> callSet, procSet;
	int procId;

	switch (lcType) {
	case PROCEDURE:
		procList = getRestrictedList(lcType, lcName);
		for (int procId : procList) {
			callSet = pkb->getProcCalledByProc(procId);
			callList = VectorSetOperation<int>::setUnion(convertSetToVector(callSet), callList);
		}
		break;
	case STRINGVARIABLE:
		procId = pkb->getProcIdByName(lcName);
		callSet = pkb->getProcCalledByProc(procId);
		callList = convertSetToVector(callSet);
		break;
	case ANYTHING:
		procSet = pkb->getAllProcId();
		procList = convertSetToVector(procSet);
		for (int procId : procList) {
			callSet = pkb->getProcCalledByProc(procId);
			callList = VectorSetOperation<int>::setUnion(convertSetToVector(callSet), callList);
		}
		break;
	}

	return callList;

}

vector<int> CallsStar::getCallRightProcList() {
	Type rcType = rightChild.getParaType();
	string rcName = rightChild.getParaName();
	vector<int> procList, callList;
	unordered_set<int> callSet, procSet;
	int procId;

	switch (rcType) {
	case PROCEDURE:
		procList = getRestrictedList(rcType, rcName);
		for (int procId : procList) {
			callSet = pkb->getProcCalledByProc(procId);
			callList = VectorSetOperation<int>::setUnion(convertSetToVector(callSet), callList);
		}
		break;
	case STRINGVARIABLE:
		procId = pkb->getProcIdByName(rcName);
		callSet = pkb->getProcCalledByProc(procId);
		callList = convertSetToVector(callSet);
		break;
	case ANYTHING:
		procSet = pkb->getAllProcId();
		procList = convertSetToVector(procSet);
		for (int procId : procList) {
			callSet = pkb->getProcCalledByProc(procId);
			callList = VectorSetOperation<int>::setUnion(convertSetToVector(callSet), callList);
		}
		break;
	}

	return callList;

}

vector<int> CallsStar::getRestrictedList(Type synType, string synName) {
	vector<int> restrictedList;
	unordered_set<int> stmtSet, procSet;

	switch (synType) {
	case PROCEDURE:
		if (synName == paramName1) {
			restrictedList = valueList1;
			break;
		}
		if (synName == paramName2) {
			restrictedList = valueList2;
			break;
		}
		procSet = pkb->getAllProcId();
		restrictedList = convertSetToVector(procSet);
		break;
	}

	return restrictedList;
}

vector<int> CallsStar::convertSetToVector(unordered_set<int> unorderedSet) {
	vector<int> vectorList;
	copy(unorderedSet.begin(), unorderedSet.end(), back_inserter(vectorList));

	return vectorList;
}




bool CallsStar::hasRel(PKB *pkbSource) {
	return false;
}

vector<int> CallsStar::getWithRelToLeft(PKB *pkb) {
	vector<int> v;
	return v;

}

vector<int> CallsStar::getWithRelToRight(PKB *pkb) {
	vector<int> v;
	return v;
}

Parameter CallsStar::getLeftChild() {
	return leftChild;
}

Parameter CallsStar::getRightChild() {
	return rightChild;
}

vector<Parameter> CallsStar::getSynList() {
	return synList;
}
