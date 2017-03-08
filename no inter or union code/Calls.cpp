#include "Type.h"
#include "Calls.h"
#include "Clause.h"

Calls::Calls(Parameter lc, Parameter rc){
	leftChild = lc;
	rightChild = rc;
	
}

//ResultTable Calls::evaluate(PKB *pkb, vector<Parameter> paramList, vector<vector<int>> valueList) {
ResultTable Calls::evaluate(PKB *pkb, ResultTable restrictedTable){
	ResultTable resultTable;

	vector<Parameter> synList;
	vector<int> tuple, firstSynList, secondSynList;
	bool isLeftSyn, isRightSyn, boolRel;


	Type lcType = leftChild.getParaType();
	Type rcType = rightChild.getParaType();
	string lcName = leftChild.getParaName();
	string rcName = rightChild.getParaName();

	vector<Parameter> paramList = restrictedTable.getSynList(); // restricted paramlist
	vector<vector<int>> valueList = restrictedTable.getTupleList(); // valueList
	
	isLeftSyn = isSynonym(lcType);
	isRightSyn = isSynonym(rcType);

	if (isValidParameter(leftChild) == false || isValidParameter(rightChild) == false) {
		resultTable.setBoolean(false);
		return resultTable;
	}

	//Change  valueList <<s>,<s>> || <<s,v>,<s,v>>
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
	//end change

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

bool Calls::isValidParameter(Parameter param) {
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

bool Calls::isSynonym(Type synType) {

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

bool Calls::hasRelation(PKB *pkb) {
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

vector<int> Calls::evaluateRelation(PKB *pkb, Type synType, string synName) {
	vector<int> procList, callProcList, resultList, callList, stmtList;
	string lcName = leftChild.getParaName();
	string rcName = rightChild.getParaName();
	Type lcType = leftChild.getParaType();
	Type rcType = rightChild.getParaType();
	int procId, callProcId;
	unordered_set<int> callSet, procSet, stmtSet, mergeCallSet;

	switch (synType) {
	case PROCEDURE:
		procSet = getUnRestrictedSet(synType, synName);
		for (int procId : procSet) {
			callSet = pkb->getProcCalledByProc(procId);
			mergeCallSet = mergeSet(mergeCallSet, callSet);
		}	
		break;
	case STRINGVARIABLE:
		procId = pkb->getProcIdByName(synName);
		//stmtSet = pkb->getStmtInProc(procId);
		for (int stmtId : stmtSet) {
			callProcId = pkb->getProcCalledByStmt(stmtId);
			if (callProcId != -1) {
				mergeCallSet.insert(callProcId);
			}
		}
		break;
	case ANYTHING:
		procSet = pkb->getAllProcId();
		for (int procId : procSet) {
			callSet = pkb->getProcCalledByProc(procId);
			mergeCallSet = mergeSet(mergeCallSet, callSet);
		}
		break;
	}

	if (synName == lcName) {
		//callProcList = getCallRightProcList();
		callProcList = getCallProcList(rcType, rcName);
	}
	if (synName == rcName) {
		//callProcList = getCallLeftProcList();
		callProcList = getCallProcList(lcType, lcName);
	}

	for (int procid : callProcList) {
		auto it = mergeCallSet.find(procid);
		if (it != mergeCallSet.end()) {
			resultList.push_back(procid);
		}
	}

	return resultList;
}

vector<int> Calls::getCallProcList(Type paraType, string paraName) {
	vector<int> resultList;
	//vector<int>  procList, callList, stmtList;
	unordered_set<int> callSet, procSet, stmtSet, mergeCallSet;
	int procId, callProcId;

	switch (paraType) {
	case PROCEDURE:
		procSet = getUnRestrictedSet(paraType, paraName);
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

/*
vector<int> Calls::getCallLeftProcList() {
	Type lcType = leftChild.getParaType();
	string lcName = leftChild.getParaName();
	vector<int> procList, callList, stmtList;
	unordered_set<int> callSet, procSet, stmtSet;
	int procId, callProcId;

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
		//stmtSet = pkb->getStmtInProc(procId);
		stmtList = convertSetToVector(stmtSet);
		for (int stmtId : stmtList) {
			callProcId = pkb->getProcCalledByStmt(stmtId);
			if (callProcId != -1) {
				callList.push_back(callProcId);
			}
		}
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

vector<int> Calls::getCallRightProcList() {
	Type rcType = rightChild.getParaType();
	string rcName = rightChild.getParaName();
	vector<int> procList, callList, stmtList;
	unordered_set<int> callSet, procSet, stmtSet;
	int procId, callProcId;

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
		//stmtSet = pkb->getStmtInProc(procId);
		stmtList = convertSetToVector(stmtSet);
		for (int stmtId : stmtList) {
			callProcId = pkb->getProcCalledByStmt(stmtId);
			if (callProcId != -1) {
				callList.push_back(callProcId);
			}
		}
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

//vector<int> Calls::getRestrictedList(Type synType, string synName) {
unordered_set<int> Calls::getUnRestrictedSet(Type synType, string synName) {
	
	unordered_set<int> stmtSet, procSet, unRestrictedSet;

	switch (synType) {
	case PROCEDURE:
		/*
		if (synName == paramName1) {
			restrictedList = valueList1;
			break;
		}
		if (synName == paramName2) {
			restrictedList = valueList2;
			break;
		}
		*/
		procSet = pkb->getAllProcId();
		unRestrictedSet = procSet;
		//restrictedList = convertSetToVector(procSet);
		break;
	}

	return unRestrictedSet;
}

vector<int> Calls::convertSetToVector(unordered_set<int> unorderedSet) {
	vector<int> vectorList;
	copy(unorderedSet.begin(), unorderedSet.end(), back_inserter(vectorList));

	return vectorList;
}

unordered_set<int> Calls::convertVectorToSet(vector<int> vectorList) {
	unordered_set<int> set;

	for (int v : vectorList) {
		set.insert(v);
	}
	return set;
}

unordered_set<int> Calls::mergeSet(unordered_set<int> s1, unordered_set<int> s2) {
	s1.insert(s2.begin(), s2.end());

	return s1;
}

//Pulbic

bool Calls::hasRel(PKB *pkbSource) {
	return false;
}

vector<int> Calls::getWithRelToLeft(PKB *pkb) {
	vector<int> v;
	return v;

}

vector<int> Calls::getWithRelToRight(PKB *pkb) {
	vector<int> v;
	return v;
}

Parameter Calls::getLeftChild() {
	return leftChild;
}

Parameter Calls::getRightChild() {
	return rightChild;
}

vector<Parameter> Calls::getSynList() {
	return synList;
}

void Calls::insertSynList(Parameter p) {
	synList.push_back(p);
}









