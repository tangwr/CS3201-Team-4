#include "Type.h"
#include "Uses.h"
#include "Clause.h"

Uses::Uses(Parameter lc, Parameter rc) {
    leftChild = lc;
	rightChild = rc;
	paramType1 = INVALID;
	paramType2 = INVALID;

	if (leftChild.isSynonym()) {
		synList.push_back(leftChild);
	}
	if (rightChild.isSynonym()) {
		synList.push_back(rightChild);
	}
	
}

ResultTable* Uses::evaluate(PKB *pkb, ResultTable* intResultTable){
	Parameter param1, param2;
	
	vector<int> tuple;
	unordered_set<int> firstSynList, secondSynList, procStmtSet;
	bool isLeftSyn = false, isRightSyn = false, boolRel = false;
	Type lcType = leftChild.getParaType();
	Type rcType = rightChild.getParaType();

	vector<Parameter> paramList = intResultTable->getSynList(); // restricted paramlist

	isLeftSyn = isSynonym(lcType);
	isRightSyn = isSynonym(rcType);

	if (isValidParameter(pkb, leftChild) == false || isValidParameter(pkb, rightChild) == false) {
		resultTable.setBoolean(false);
		return &resultTable;
	}

	if (paramList.size() == 1) {
		param1 = paramList.at(0);
		paramType1 = param1.getParaType();
		valueSet1 = intResultTable->getSynValue(param1);
	}

	if (paramList.size() == 2) {
		param1 = paramList.at(0);
		paramType1 = param1.getParaType();
		valueSet1 = intResultTable->getSynValue(param1);

		param2 = paramList.at(1);
		paramType2 = param2.getParaType();
		valueSet2 = intResultTable->getSynValue(param2);
	}
	
	if (isLeftSyn == false && isRightSyn == false) {
		boolRel = hasRelation(pkb);
		resultTable.setBoolean(boolRel);
		resultTable.setSynList(synList);
	}
	if (isLeftSyn == true && isRightSyn == false) {
		resultTable.setSynList(synList);
		firstSynList = evaluateRelation(pkb, lcType);
	}
	if (isLeftSyn == false && isRightSyn == true) {
		resultTable.setSynList(synList);
		firstSynList = evaluateRelation(pkb, rcType);
	}
	if (isLeftSyn == true && isRightSyn == true) {
		resultTable.setSynList(synList);
		firstSynList = evaluateRelation(pkb, lcType);
		secondSynList = evaluateRelation(pkb, rcType);
	}

	if (firstSynList.empty() == false && secondSynList.empty() == false) {
		if (lcType == PROCEDURE) {
			for (int procId : firstSynList) {
				procStmtSet = pkb->getUseStmtInProc(procId);
				for (int secondSyn : secondSynList) {
					for (int stmtId : procStmtSet) {
						if (pkb->checkStmtVarUseRelExist(stmtId, secondSyn)) {
							tuple.push_back(procId);
							tuple.push_back(secondSyn);
							resultTable.insertTuple(tuple);
							tuple.clear();
							break;
						}
					}
				}
			}
		}
		else {
			for (int firstSyn : firstSynList) {
				for (int secondSyn : secondSynList) {
					if (pkb->checkStmtVarUseRelExist(firstSyn, secondSyn)) {
						tuple.push_back(firstSyn);
						tuple.push_back(secondSyn);
						resultTable.insertTuple(tuple);
						tuple.clear();
					}
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
	
	return &resultTable;
}

bool Uses::isValidParameter(PKB *pkb, Parameter param) {
	bool isValidParam = false;
	bool isProcString = false;
	//int varId;
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
	case CALL:
	case PROG_LINE:
		isValidParam = true;
		break;
	case STRINGVARIABLE:
	{//'string' procs & var
		isProcString = pkb->isProcInTable(paramName);
		int varId = pkb->getVarIdByName(paramName);
		if (isProcString == true || varId != -1) {
			isValidParam = true;
		}
		break;
	}
	case INTEGER:
		isValidParam = pkb->isStmtInUseTable(stoi(paramName));
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
	case CALL:
	case PROG_LINE:
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
	unordered_set<int> results = evaluateRelation(pkb, lcType);

	if (results.empty()) {
		boolRel = false;
	}
	else {
		boolRel = true;
	}

	return boolRel;
}

unordered_set<int> Uses::evaluateRelation(PKB *pkb, Type synType) {

	unordered_set<int> stmtSet, varSet, procSet;
	unordered_set<int> resultList;
	unordered_set<int> useStmtList, useVarList, useProcList;
	//int stmtId, procId, varId;
	string lcName = leftChild.getParaName();
	string rcName = rightChild.getParaName();
	Type lcType = leftChild.getParaType();
	Type rcType = rightChild.getParaType();

	switch (synType) {
	case PROG_LINE:
	case STMT:
		stmtSet = getRestrictedSet(pkb, synType);
		useStmtList = getUseStmtListOfVar(pkb, stmtSet);
		resultList = useStmtList;
		break;
	case ASSIGN:
		stmtSet = getRestrictedSet(pkb, synType);
		useStmtList = getUseStmtListOfVar(pkb, stmtSet);
		resultList = useStmtList;
		break;
	case WHILE:
		stmtSet = getRestrictedSet(pkb, synType);
		useStmtList = getUseStmtListOfVar(pkb, stmtSet);
		resultList = useStmtList;
		break;
	case IF:
		stmtSet = getRestrictedSet(pkb, synType);
		useStmtList = getUseStmtListOfVar(pkb, stmtSet);
		resultList = useStmtList;
		break;
	case CALL:
		stmtSet = getRestrictedSet(pkb, synType);
		useStmtList = getUseStmtListOfVar(pkb, stmtSet);
		resultList = useStmtList;
		break;
	case PROCEDURE:
		procSet = getRestrictedSet(pkb, synType);
		useProcList = getUseProcListOfVar(pkb, procSet);
		resultList = useProcList;
		break;
	case VARIABLE:
		varSet = getRestrictedSet(pkb, synType);
		useVarList = getUseVarListOfStmt(pkb, varSet);
		resultList = useVarList;
		break;
	case INTEGER:
	{
		int stmtId = stoi(lcName);
		stmtSet.insert(stmtId);
		useStmtList = getUseStmtListOfVar(pkb, stmtSet);
		resultList = useStmtList;
		break;
	}
	case STRINGVARIABLE:
	{
		if (pkb->isProcInTable(lcName) == true && synType == lcType) {
			int procId = pkb->getProcIdByName(lcName);
			procSet.insert(procId);
			useProcList = getUseProcListOfVar(pkb, procSet);
			resultList = useProcList;
			break;
		}
		int varId = pkb->getVarIdByName(rcName);
		if (varId != -1 && synType == rcType) {
			varSet.insert(varId);
			useVarList = getUseVarListOfStmt(pkb, varSet);
			resultList = useVarList;
			break;
		}
		break;
	}
	}

	return resultList;
}


unordered_set<int> Uses::getUseStmtListOfVar(PKB *pkb, unordered_set<int> stmtListSet) {
	//int varId;
	unordered_set<int> resultStmtList, varIdList;
	unordered_set<int> stmtSet, mergeStmtSet, varSet;

	string rcName = rightChild.getParaName();
	Type rcType = rightChild.getParaType();

	switch (rcType) {
	case VARIABLE:
		varSet = getRestrictedSet(pkb, rcType);
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
	{
		int varId = pkb->getVarIdByName(rcName);
		stmtSet = pkb->getStmtUseVar(varId);
		mergeStmtSet = stmtSet;
		break;
	}
	}

	for (int stmtId : stmtListSet) {
		auto it = mergeStmtSet.find(stmtId);
		if (it != mergeStmtSet.end()) {
			resultStmtList.insert(stmtId);
		}
	}

	return resultStmtList;
}

unordered_set<int> Uses::getUseProcListOfVar(PKB *pkb, unordered_set<int> procListSet) {

	//int procId, varId;
	unordered_set<int> resultProcList;
	unordered_set<int> procSet, mergeProcSet, varSet;

	string rcName = rightChild.getParaName();
	Type rcType = rightChild.getParaType();

	switch (rcType) {
	case VARIABLE:
		varSet = getRestrictedSet(pkb, rcType);
		for (int var : varSet) {
			procSet = pkb->getProcUseVar(var);
			mergeProcSet = mergeSet(mergeProcSet, procSet);
		}
		break;
	case ANYTHING:
		varSet = pkb->getAllVarId();
		for (int var : varSet) {
			procSet = pkb->getProcUseVar(var);
			mergeProcSet = mergeSet(mergeProcSet, procSet);
		}
		break;
	case STRINGVARIABLE:
	{
		int varId = pkb->getVarIdByName(rcName);
		procSet = pkb->getProcUseVar(varId);
		mergeProcSet = procSet;
		break;
	}
	}

	for (int procId : procListSet) {
		auto it = mergeProcSet.find(procId);
		if (it != mergeProcSet.end()) {
			resultProcList.insert(procId);
		}
	}

	return resultProcList;
}

unordered_set<int> Uses::getUseVarListOfStmt(PKB *pkb, unordered_set<int> varListSet) {
	//int stmtId, procId;
	vector<int> resultVarList;
	unordered_set<int> stmtSet, varSet, mergeStmtSet, mergeVarSet;
	unordered_set<int> stmtListSet, varIdListSet, procIdListSet;

	string lcName = leftChild.getParaName();
	Type lcType = leftChild.getParaType();

	switch (lcType) {
	case PROG_LINE:
	case STMT:
		stmtListSet = getRestrictedSet(pkb, lcType);
		break;
	case ASSIGN:
		stmtListSet = getRestrictedSet(pkb, lcType);
		break;
	case WHILE:
		stmtListSet = getRestrictedSet(pkb, lcType);
		break;
	case IF:
		stmtListSet = getRestrictedSet(pkb, lcType);
		break;
	case CALL:
		stmtListSet = getRestrictedSet(pkb, lcType);
		break;
	case INTEGER:
	{
		int stmtId = stoi(lcName);
		stmtListSet.insert(stmtId);
		break;
	}
	case PROCEDURE:
		
		if (lcType == paramType1) {
			procIdListSet = valueSet1;
			for (int procId : procIdListSet) {
				stmtSet = pkb->getUseStmtInProc(procId);
				mergeStmtSet = mergeSet(mergeStmtSet, stmtSet);
			}
			stmtListSet = mergeStmtSet;
			break;
		}
		if (lcType == paramType2) {
			procIdListSet = valueSet2;
			for (int procId : procIdListSet) {
				stmtSet = pkb->getUseStmtInProc(procId);
				mergeStmtSet = mergeSet(mergeStmtSet, stmtSet);
			}
			stmtListSet = mergeStmtSet;
			break;
		}
		
		stmtSet = pkb->getAllStmtId();
		stmtListSet = stmtSet;
		break;
	case STRINGVARIABLE: //'string' procs
	{
		int procId = pkb->getProcIdByName(lcName);
		stmtSet = pkb->getUseStmtInProc(procId);
		stmtListSet = stmtSet;
		break;
	}
	}

	for (int stmtid : stmtListSet) {
		varSet = pkb->getVarUsedByStmt(stmtid);
		for (int varId : varListSet) {
			auto it = varSet.find(varId);
			if (it != varSet.end()) {
				mergeVarSet.insert(varId);
			}
		}
	}
	return mergeVarSet;
}


unordered_set<int> Uses::getRestrictedSet(PKB *pkb, Type synType) {
	vector<int> varList;
	unordered_set<int> stmtSet, procSet, callSet, restrictedSet;

	switch (synType) {
	case PROG_LINE:
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
		break;
	case CALL:
		if (synType == paramType1) {
			restrictedSet = valueSet1;
			break;
		}
		if (synType == paramType2) {
			restrictedSet = valueSet2;
			break;
		}
		callSet = pkb->getAllCallId();
		restrictedSet = callSet;
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
		restrictedSet = pkb->getAllVarId();
	}

	return restrictedSet;
}

unordered_set<int> Uses::mergeSet(unordered_set<int> s1, unordered_set<int> s2) {
	s1.insert(s2.begin(), s2.end());

	return s1;
}

//Public 
void Uses::insertSynList(Parameter p) {
	synList.push_back(p);
}

vector<Parameter> Uses::getSynList() {
	return synList;
}

ClauseType Uses::getClauseType() {
	return USES;
}
