#include "Type.h"
#include "CallsStar.h"
#include "Clause.h"

CallsStar::CallsStar(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;

	if (leftChild.isSynonym()) {
		synList.push_back(leftChild);
	}
	if (rightChild.isSynonym()) {
		synList.push_back(rightChild);
	}
}

ResultTable CallsStar::evaluate(PKB *pkb, ResultTable intResultTable) {
	ResultTable resultTable;
	
	Parameter param1, param2;

	vector<int> tuple;
	unordered_set<int> firstSynList, secondSynList, callSet;
	bool isLeftSyn, isRightSyn, boolRel;


	Type lcType = leftChild.getParaType();
	Type rcType = rightChild.getParaType();
	string lcName = leftChild.getParaName();
	string rcName = rightChild.getParaName();

	vector<Parameter> paramList = intResultTable.getSynList(); // restricted paramlist
	vector<vector<int>> valueList = intResultTable.getTupleList(); // valueList

	isLeftSyn = isSynonym(lcType);
	isRightSyn = isSynonym(rcType);

	if (isValidParameter(pkb, leftChild) == false || isValidParameter(pkb, rightChild) == false) {
		resultTable.setBoolean(false);
		return resultTable;
	}

	if (paramList.size() == 1) {
		param1 = paramList.at(0);
		paramType1 = param1.getParaType();
		paramName1 = param1.getParaName();
		valueSet1 = intResultTable.getSynValue(param1);
	}

	if (paramList.size() == 2) {
		param1 = paramList.at(0);
		paramType1 = param1.getParaType();
		paramName1 = param1.getParaName();
		valueSet1 = intResultTable.getSynValue(param1);

		param2 = paramList.at(1);
		paramType2 = param2.getParaType();
		paramName2 = param2.getParaName();
		valueSet2 = intResultTable.getSynValue(param2);
	}


	if (isLeftSyn == false && isRightSyn == false) {
		boolRel = hasRelation(pkb);
		resultTable.setBoolean(boolRel);
	}
	if (isLeftSyn == true && isRightSyn == false) {
		resultTable.setSynList(synList);
		firstSynList = evaluateRelation(pkb, lcType, lcName);
	}
	if (isLeftSyn == false && isRightSyn == true) {
		resultTable.setSynList(synList);
		firstSynList = evaluateRelation(pkb, rcType, rcName);
	}
	if (isLeftSyn == true && isRightSyn == true) {
		resultTable.setSynList(synList);
		firstSynList = evaluateRelation(pkb, lcType, lcName);
		secondSynList = evaluateRelation(pkb, rcType, rcName);
	}

	if (firstSynList.empty() == false && secondSynList.empty() == false) {
		for (int firstSyn : firstSynList) {
			callSet = pkb->getProcCalledByStarProc(firstSyn);
			for (int secondSyn : secondSynList) {
				auto it = callSet.find(secondSyn);
				if (it != callSet.end()) {
					tuple.push_back(firstSyn);
					tuple.push_back(secondSyn);
					resultTable.insertTuple(tuple);
					tuple.clear();
				}
			}
		}
	}
	if (firstSynList.empty() == false && secondSynList.empty() == true) {
		for (int firstSyn : firstSynList) {
			tuple.push_back(firstSyn);
			resultTable.insertTuple(tuple);
			tuple.clear();
		}
	}
	
	return resultTable;
}

bool CallsStar::isValidParameter(PKB *pkb, Parameter param) {
	bool isValidParam = false;
	bool isProcString = false;
	int varId;

	Type paramType = param.getParaType();
	string paramName = param.getParaName();

	switch (paramType) {
	case PROCEDURE:
	case ANYTHING:
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
	unordered_set<int> results = evaluateRelation(pkb, lcType, lcName);

	if (results.empty()) {
		boolRel = false;
	}
	else {
		boolRel = true;
	}

	return boolRel;
}

unordered_set<int> CallsStar::evaluateRelation(PKB *pkb, Type synType, string synName) {
	vector<int> procList, callProcList, resultList, callList, stmtList;
	string lcName = leftChild.getParaName();
	string rcName = rightChild.getParaName();
	Type lcType = leftChild.getParaType();
	Type rcType = rightChild.getParaType();
	int procId, callProcId;
	unordered_set<int> callSet, procSet, stmtSet, mergeCallSet;
	unordered_set<int> callerProcSet, calledByProcSet, resultSet;

	switch (synType) {
	case PROCEDURE:
		procSet = getRestrictedSet(pkb, synType, synName);
		break;
	case STRINGVARIABLE:
		procId = pkb->getProcIdByName(synName);
		procSet.insert(procId);
		break;
	case ANYTHING:
		procSet = pkb->getAllProcId();
		break;
	}

	if (synName == lcName) {
		callerProcSet = procSet;
		calledByProcSet = getCallProcSet(pkb, rcType, rcName);
		for (int callerProcId : callerProcSet) {
			callSet = pkb->getProcCalledByStarProc(callerProcId);
			for (int calledProcId : calledByProcSet) {
				auto it = callSet.find(calledProcId);
				if (it != callSet.end()) {
					resultSet.insert(callerProcId);
					break;
				}
			}
		}
	}
	if (synName == rcName) {
		callerProcSet = getCallProcSet(pkb, lcType, lcName);
		calledByProcSet = procSet;
		for (int callerProcId : callerProcSet) {
			callSet = pkb->getProcCalledByStarProc(callerProcId);
			for (int calledProcId : calledByProcSet) {
				auto it = callSet.find(calledProcId);
				if (it != callSet.end()) {
					resultSet.insert(calledProcId);
				}
			}
		}
	}

	return resultSet;
}

unordered_set<int> CallsStar::getCallProcSet(PKB *pkb, Type paraType, string paraName) {
	vector<int> resultList;
	
	unordered_set<int> callSet, procSet, stmtSet, mergeCallSet;
	int procId, callProcId;

	switch (paraType) {
	case PROCEDURE:
		procSet = getRestrictedSet(pkb, paraType, paraName);
		break;
	case STRINGVARIABLE:
		procId = pkb->getProcIdByName(paraName);
		procSet.insert(procId);
		break;
	case ANYTHING:
		procSet = pkb->getAllProcId();
		break;
	}
	return procSet;

}

unordered_set<int> CallsStar::getRestrictedSet(PKB *pkb, Type synType, string synName) {
	unordered_set<int> stmtSet, procSet, restrictedSet;

	switch (synType) {
	case PROCEDURE:
		
		if (synName == paramName1) {
			restrictedSet = valueSet1;
		break;
		}
		if (synName == paramName2) {
			restrictedSet = valueSet2;
		break;
		}
		
		procSet = pkb->getAllProcId();
		restrictedSet = procSet;
		break;
	}

	return restrictedSet;
}

unordered_set<int> CallsStar::mergeSet(unordered_set<int> s1, unordered_set<int> s2) {
	s1.insert(s2.begin(), s2.end());

	return s1;
}

//Pulbic
Parameter CallsStar::getLeftChild() {
	return leftChild;
}

Parameter CallsStar::getRightChild() {
	return rightChild;
}


void CallsStar::insertSynList(Parameter p) {
	synList.push_back(p);
}

vector<Parameter> CallsStar::getSynList() {
	return synList;
}

ClauseType CallsStar::getClauseType() {
	return CALLSSTAR;
}

