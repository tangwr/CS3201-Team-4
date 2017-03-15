#include "Type.h"
#include "Uses.h"
#include "Clause.h"

Uses::Uses(Parameter lc, Parameter rc) {
    leftChild = lc;
	rightChild = rc;

	
}
//ResultTable Uses::evaluate(PKB *pkb, vector<Parameter> paramList, vector<vector<int>> valueList) {
ResultTable Uses::evaluate(PKB *pkb, ResultTable restrictedTable){

	ResultTable resultTable;

	Parameter param1, param2;
	vector<Parameter> synList;
	vector<int> tuple, firstSynList, secondSynList;
	bool isLeftSyn, isRightSyn, boolRel;
	Type lcType = leftChild.getParaType();
	Type rcType = rightChild.getParaType();

	vector<Parameter> paramList = restrictedTable.getSynList(); // restricted paramlist
	//vector<vector<int>> valueList = restrictedTable.getTupleList(); // valueList

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
		valueList1 = restrictedTable.getSynValue(param1);
		valueSet1 = convertVectorToSet(valueList1);
	}

	if (paramList.size() == 2) {
		param1 = paramList.at(0);
		paramType1 = param1.getParaType();
		valueList1 = restrictedTable.getSynValue(param1);
		valueSet1 = convertVectorToSet(valueList1);

		param2 = paramList.at(1);
		paramType2 = param2.getParaType();
		valueList2 = restrictedTable.getSynValue(param2);
		valueSet2 = convertVectorToSet(valueList2);
	}
	//end change
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
				tuple.clear();
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
	Type rcType = rightChild.getParaType();
	vector<int> results = evaluateRelation(pkb, rcType);

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
	vector<int> resultList;// , stmtList, varList, procList;
	vector<int> useStmtList, useVarList, useProcList;
	int stmtId, procId, varId;
	string lcName = leftChild.getParaName();
	string rcName = rightChild.getParaName();

	switch (synType) {
	case STMT:
		stmtSet = getRestrictedSet(synType);
		useStmtList = getUseStmtListOfVar(stmtSet);
		resultList = useStmtList;
		break;
	case ASSIGN:
		stmtSet = getRestrictedSet(synType);
		useStmtList = getUseStmtListOfVar(stmtSet);
		resultList = useStmtList;
		break;
	case WHILE:
		stmtSet = getRestrictedSet(synType);
		useStmtList = getUseStmtListOfVar(stmtSet);
		resultList = useStmtList;
		break;
	case IF:
		stmtSet = getRestrictedSet(synType);
		useStmtList = getUseStmtListOfVar(stmtSet);
		resultList = useStmtList;
		break;
	case PROCEDURE:
		procSet = getRestrictedSet(synType);
		useProcList = getUseProcListOfVar(procSet);
		resultList = useProcList;
		break;
	case VARIABLE:
		varSet = getRestrictedSet(synType);
		useVarList = getUseVarListOfStmt(varSet);
		resultList = useVarList;
		break;
	case INTEGER:
		stmtId = stoi(lcName);
		stmtSet.insert(stmtId);
		useStmtList = getUseStmtListOfVar(stmtSet);
		resultList = useStmtList;
		break;
	case STRINGVARIABLE:
		if (pkb->isProcInTable(lcName) == true) {
			procId = pkb->getProcIdByName(lcName);
			procSet.insert(procId);
			useProcList = getUseProcListOfVar(procSet);
			resultList = useProcList;
			break;
		}
		varId = pkb->getVarIdByName(rcName);
		if (varId != -1) {
			varSet.insert(varId);
			useVarList = getUseVarListOfStmt(varSet);
			resultList = useVarList;
			break;
		}
		break;
	}

	return resultList;
}


vector<int> Uses::getUseStmtListOfVar(unordered_set<int> stmtListSet) {

	int varId;
	vector<int> resultStmtList, varIdList;
	unordered_set<int> stmtSet, mergeStmtSet, varSet;

	string rcName = rightChild.getParaName();
	Type rcType = rightChild.getParaType();

	switch (rcType) {
	case VARIABLE:
		varSet = getRestrictedSet(rcType);
		for (int var : varSet) {
			stmtSet = pkb->getStmtUseVar(var);
			mergeStmtSet = mergeSet(mergeStmtSet, stmtSet);
		}
		break;
	case ANYTHING:
		stmtSet = pkb->getAllUseStmt();
		mergeStmtSet = stmtSet;
		break;
	case STRINGVARIABLE:
		varId = pkb->getVarIdByName(rcName);
		stmtSet = pkb->getStmtUseVar(varId);
		mergeStmtSet = stmtSet;
		break;
	}

	for (int stmtId : stmtListSet) {
		auto it = mergeStmtSet.find(stmtId);
		if (it != mergeStmtSet.end()) {
			resultStmtList.push_back(stmtId);
		}
	}

	return resultStmtList;
}

vector<int> Uses::getUseProcListOfVar(unordered_set<int> procListSet) {

	int procId, varId;
	vector<int> resultProcList;// , varIdList;
	unordered_set<int> procSet, mergeProcSet, varSet;

	string rcName = rightChild.getParaName();
	Type rcType = rightChild.getParaType();

	switch (rcType) {
	case VARIABLE:
		varSet = getRestrictedSet(rcType);
		for (int var : varSet) {
			procSet = pkb->getProcUseVar(var);
			mergeProcSet = procSet;
		}
		break;
	case ANYTHING:
		//varIdList = pkb->getAllVarId();
		varSet = convertVectorToSet(pkb->getAllVarId());
		for (int var : varSet) {
			procSet = pkb->getProcUseVar(var);
			mergeProcSet = mergeSet(mergeProcSet, procSet);
		}
		break;
	case STRINGVARIABLE:
		varId = pkb->getVarIdByName(rcName);
		procSet = pkb->getProcUseVar(varId);
		mergeProcSet = procSet;
		break;
	}

	for (int procId : procListSet) {
		auto it = mergeProcSet.find(procId);
		if (it != mergeProcSet.end()) {
			resultProcList.push_back(procId);
		}
	}

	return resultProcList;
}

vector<int> Uses::getUseVarListOfStmt(unordered_set<int> varListSet) {
	int stmtId, procId;
	vector<int> resultVarList;
	unordered_set<int> stmtSet, varSet, mergeStmtSet, mergeVarSet;
	unordered_set<int> stmtListSet, varIdListSet, procIdListSet;

	string lcName = leftChild.getParaName();
	Type lcType = leftChild.getParaType();

	switch (lcType) {
	case STMT:
		stmtListSet = getRestrictedSet(lcType);
		break;
	case ASSIGN:
		stmtListSet = getRestrictedSet(lcType);
		break;
	case WHILE:
		stmtListSet = getRestrictedSet(lcType);
		break;
	case IF:
		stmtListSet = getRestrictedSet(lcType);
		break;
	case INTEGER:
		stmtId = stoi(lcName);
		stmtListSet.insert(stmtId);
		break;
	case PROCEDURE:
		
		if (lcType == paramType1) {
			procIdListSet = valueSet1;
			for (int proc : procIdListSet) {
				//stmtSet = pkb->getStmtUsedInProc(procId);
				mergeStmtSet = mergeSet(mergeStmtSet, stmtSet);
			}
			stmtListSet = mergeStmtSet;
			break;
		}
		if (lcType == paramType2) {
			procIdListSet = valueSet2;
			for (int proc : procIdListSet) {
				//stmtSet = pkb->getStmtUsedInProc(procId);
				mergeStmtSet = mergeSet(mergeStmtSet, stmtSet);
			}
			stmtListSet = mergeStmtSet;
			break;
		}
		
		stmtSet = pkb->getAllStmtId();
		stmtListSet = stmtSet;
		//stmtList = convertSetToVector(stmtSet);
		break;
	case STRINGVARIABLE: //'string' procs
		procId = pkb->getProcIdByName(lcName);
		//stmtSet = pkb->getStmtUsedInProc(procId);
		stmtListSet = stmtSet;
		//stmtList = convertSetToVector(stmtSet);
		break;
	}

	for (int stmtid : stmtListSet) {
		varSet = pkb->getVarUsedByStmt(stmtid);
		for (int varId : varListSet) {
			auto it = varSet.find(varId);
			if (it != varSet.end()) {
				mergeVarSet.insert(varId);
				//resultVarList.push_back(varId);
			}
		}
		//varIdList = VectorSetOperation<int>::setUnion(varIdList, convertSetToVector(varSet));
	}
	resultVarList = convertSetToVector(mergeVarSet);
	return resultVarList;
}

//Return unordered_set
//vector<int> Uses::getRestrictedList(Type synType) {
unordered_set<int> Uses::getRestrictedSet(Type synType) {
	vector<int> varList;
	unordered_set<int> stmtSet, procSet, restrictedSet;

	switch (synType) {
	case STMT:
		if (synType == paramType1) {
			restrictedSet = valueSet1;
			break;
		}
		if (synType == paramType2) {
			restrictedSet = valueSet2;
			break;
		}
		stmtSet = pkb->getAllStmtId();
		restrictedSet = stmtSet;
		//restrictedList = convertSetToVector(stmtSet);
		break;
	case ASSIGN:
		if (synType == paramType1) {
			restrictedSet = valueSet1;
			break;
		}
		if (synType == paramType2) {
			restrictedSet = valueSet2;
			break;
		}
		stmtSet = pkb->getAllAssignStmt();
		restrictedSet = stmtSet;
		//restrictedList = convertSetToVector(stmtSet);
		break;
	case WHILE:
		if (synType == paramType1) {
			restrictedSet = valueSet1;
			break;
		}
		if (synType == paramType2) {
			restrictedSet = valueSet2;
			break;
		}
		stmtSet = pkb->getAllWhileStmt();
		restrictedSet = stmtSet;
		//restrictedList = convertSetToVector(stmtSet);
		break;
	case IF:
		if (synType == paramType1) {
			restrictedSet = valueSet1;
			break;
		}
		if (synType == paramType2) {
			restrictedSet = valueSet2;
			break;
		}
		stmtSet = pkb->getAllIfId();
		restrictedSet = stmtSet;
		//restrictedList = convertSetToVector(stmtSet);
		break;
	case PROCEDURE:
		if (synType == paramType1) {
			restrictedSet = valueSet1;
			break;
		}
		if (synType == paramType2) {
			restrictedSet = valueSet2;
			break;
		}
		procSet = pkb->getAllProcId();
		restrictedSet = procSet;
		//restrictedList = convertSetToVector(procSet);
		break;
	case VARIABLE:
		if (synType == paramType1) {
			restrictedSet = valueSet1;
			break;
		}
		if (synType == paramType2) {
			restrictedSet = valueSet2;
			break;
		}
		varList = pkb->getAllVarId();
		restrictedSet = convertVectorToSet(varList);
	}

	return restrictedSet;
}

vector<int> Uses::convertSetToVector(unordered_set<int> unorderedSet) {
	vector<int> vectorList;
	copy(unorderedSet.begin(), unorderedSet.end(), back_inserter(vectorList));

	return vectorList;
}

unordered_set<int> Uses::convertVectorToSet(vector<int> vectorList) {
	unordered_set<int> set;
	
	for (int v : vectorList) {
		set.insert(v);
	}
	return set;
}

unordered_set<int> Uses::mergeSet(unordered_set<int> s1, unordered_set<int> s2) {
	s1.insert(s2.begin(), s2.end());

	return s1;
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

void Uses::insertSynList(Parameter p) {
	synList.push_back(p);
}

//Testing
void Uses::setPKB(PKB* pkbInput) {
	this->pkb = pkbInput;
}


//takes in para vector<int> stmtList
/*
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
//varId = pkb->getVarIdByName(rcName);
stmtSet = pkb->getStmtUseVar(var);
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
//varId = pkb->getVarIdByName(rcName);
procSet = pkb->getProcUseVar(var);
procList = VectorSetOperation<int>::setUnion(convertSetToVector(procSet), procList);
}
break;
case ANYTHING:
varIdList = pkb->getAllVarId();
for (int var : varIdList) {
procSet = pkb->getProcUseVar(var);
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
*/