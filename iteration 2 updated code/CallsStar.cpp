#include "Type.h"
#include "CallsStar.h"
#include "Clause.h"

CallsStar::CallsStar(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;

}

//ResultTable CallsStar::evaluate(PKB *pkb, vector<Parameter> paramList, vector<vector<int>> valueList) {
ResultTable CallsStar::evaluate(PKB *pkb, ResultTable intResultTable) {
	ResultTable resultTable;

	Parameter param1, param2;
	vector<Parameter> synList;
	vector<int> tuple, firstSynList, secondSynList;
	bool isLeftSyn, isRightSyn, boolRel;


	Type lcType = leftChild.getParaType();
	Type rcType = rightChild.getParaType();
	string lcName = leftChild.getParaName();
	string rcName = rightChild.getParaName();

	vector<Parameter> paramList = intResultTable.getSynList(); // restricted paramlist
	vector<vector<int>> valueList = intResultTable.getTupleList(); // valueList

	isLeftSyn = isSynonym(lcType);
	isRightSyn = isSynonym(rcType);

	if (isValidParameter(leftChild) == false || isValidParameter(rightChild) == false) {
		resultTable.setBoolean(false);
		return resultTable;
	}

	//Change  valueList <<s>,<s>> || <<s,v>,<s,v>>
	if (paramList.size() == 1) {
		param1 = paramList.at(0);
		paramType1 = param1.getParaType();
		paramName1 = param1.getParaName();
		//valueList1 = intResultTable.getSynValue(param1);
		//valueSet1 = convertVectorToSet(valueList1);
		valueSet1 = intResultTable.getSynValue(param1);
	}

	if (paramList.size() == 2) {
		param1 = paramList.at(0);
		paramType1 = param1.getParaType();
		paramName1 = param1.getParaName();
		//valueList1 = intResultTable.getSynValue(param1);
		//valueSet1 = convertVectorToSet(valueList1);
		valueSet1 = intResultTable.getSynValue(param1);

		param2 = paramList.at(1);
		paramType2 = param2.getParaType();
		paramName2 = param2.getParaName();
		//valueList2 = intResultTable.getSynValue(param2);
		//valueSet2 = convertVectorToSet(valueList2);
		valueSet2 = intResultTable.getSynValue(param2);
	}
	// end

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
		procSet = getRestrictedSet(synType, synName);
		/*
		for (int procId : procSet) {
			//callSet = pkb->getProcCalledByStarProc(procId); // call star
			mergeCallSet = mergeSet(mergeCallSet, callSet);
		}
		*/
		break;
	case STRINGVARIABLE:
		procId = pkb->getProcIdByName(synName);
		procSet.insert(procId);
		/*
		//stmtSet = pkb->getStmtInProc(procId);
		for (int stmtId : stmtSet) {
			callProcId = pkb->getProcCalledByStmt(stmtId);
			if (callProcId != -1) {
				mergeCallSet.insert(callProcId);
			}
		}
		*/
		break;
	case ANYTHING:
		procSet = pkb->getAllProcId();
		/*
		for (int procId : procSet) {
			callSet = pkb->getProcCalledByProc(procId);
			mergeCallSet = mergeSet(mergeCallSet, callSet);
		}
		*/
		break;
	}

	if (synName == lcName) {
		callerProcSet = procSet;
		calledByProcSet = getCallProcSet(rcType, rcName);
		//callProcList = getCallRightProcList();
		//callProcList = getCallProcList(rcType, rcName);
	}
	if (synName == rcName) {
		callerProcSet = getCallProcSet(lcType, lcName);
		calledByProcSet = procSet;
		//callProcList = getCallLeftProcList();
		//callProcList = getCallProcList(lcType, lcName);
	}

	/*
	for (int procid : callProcList) {
		auto it = mergeCallSet.find(procid);
		if (it != mergeCallSet.end()) {
			resultList.push_back(procid);
		}
	}
	*/
	for (int callerProcId : callerProcSet) {
		//callSet = pkb->getProcCalledByStarProc(callerProcId);
		for (int calledProcId : calledByProcSet) {
			auto it = callSet.find(calledProcId);
			if (it != callSet.end()) {
				resultSet.insert(callerProcId);
				break;
			}
		}
	}
	resultList = convertSetToVector(resultSet);
	return resultList;
}
/*
vector<int> CallsStar::getCallProcList(Type paraType, string paraName) {
	vector<int> resultList;
	//vector<int>  procList, callList, stmtList;
	unordered_set<int> callSet, procSet, stmtSet, mergeCallSet;
	int procId, callProcId;

	switch (paraType) {
	case PROCEDURE:
		procSet = getRestrictedSet(paraType, paraName);
		for (int procId : procSet) {
			callSet = pkb->getProcCalledByProc(procId);
			mergeCallSet = mergeSet(mergeCallSet, callSet);
			//callList = VectorSetOperation<int>::setUnion(convertSetToVector(callSet), callList);
		}
		break;
	case STRINGVARIABLE:
		procId = pkb->getProcIdByName(paraName);
		//stmtSet = pkb->getStmtInProc(procId);
		for (int stmtId : stmtSet) {
			callProcId = pkb->getProcCalledByStmt(stmtId);
			if (callProcId != -1) {
				mergeCallSet.insert(callProcId);
				//callList.push_back(callProcId);
			}
		}
		break;
	case ANYTHING:
		procSet = pkb->getAllProcId();
		//procList = convertSetToVector(procSet);
		for (int procId : procSet) {
			callSet = pkb->getProcCalledByProc(procId);
			mergeCallSet = mergeSet(mergeCallSet, callSet);
			//callList = VectorSetOperation<int>::setUnion(convertSetToVector(callSet), callList);
		}
		break;
	}

	resultList = convertSetToVector(mergeCallSet);

	return resultList;

}
*/
unordered_set<int> CallsStar::getCallProcSet(Type paraType, string paraName) {
	vector<int> resultList;
	//vector<int>  procList, callList, stmtList;
	unordered_set<int> callSet, procSet, stmtSet, mergeCallSet;
	int procId, callProcId;

	switch (paraType) {
	case PROCEDURE:
		procSet = getRestrictedSet(paraType, paraName);
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

//vector<int> CallsStar::getRestrictedList(Type synType, string synName) {
unordered_set<int> CallsStar::getRestrictedSet(Type synType, string synName) {
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
		//restrictedList = convertSetToVector(procSet);
		break;
	}

	return restrictedSet;
}

vector<int> CallsStar::convertSetToVector(unordered_set<int> unorderedSet) {
	vector<int> vectorList;
	copy(unorderedSet.begin(), unorderedSet.end(), back_inserter(vectorList));

	return vectorList;
}

unordered_set<int> CallsStar::convertVectorToSet(vector<int> vectorList) {
	unordered_set<int> set;

	for (int v : vectorList) {
		set.insert(v);
	}
	return set;
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

/*
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
*/

/*
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
*/