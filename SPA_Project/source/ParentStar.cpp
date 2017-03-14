#include "Type.h"
#include "ParentStar.h"
#include "Clause.h"

ParentStar::ParentStar(Parameter lc, Parameter rc) {
	leftChild = lc;
	rightChild = rc;
}

ResultTable ParentStar::evaluate(PKB* pkb) {
	if (isNumber(leftChild)) {
		if (isNumber(rightChild)) {
			//return getParentStarNumNum(pkb);
		}
		else if (isSynonym(rightChild)) {
			return getParentStarNumSyn(pkb, getTypeStmt(rightChild.getParaType(), pkb), stoi(leftChild.getParaName()));
		}
	}
	else if (isSynonym(leftChild)) {
		if (isNumber(rightChild)) {
			return getParentStarSynNum(pkb, getTypeStmt(leftChild.getParaType(), pkb), stoi(rightChild.getParaName()));
		}
		else if (isSynonym(rightChild)) {
			return getParentStarSynSyn(pkb, getTypeStmt(leftChild.getParaType(), pkb), getTypeStmt(rightChild.getParaType(), pkb));
		}
	}
	return result;
}

ResultTable ParentStar::evaluate(PKB* pkb, ResultTable resultTable) {
	unordered_set<int> left = resultTable.getSynValue(leftChild);
	unordered_set<int> right = resultTable.getSynValue(rightChild);
	if (resultTable.getSynCount() == 0) {
		return evaluate(pkb);
	}
	else if (resultTable.getSynCount() == 1) {
		if (left.size() != 0) {
			return getParentStarSynNum(pkb, left, stoi(rightChild.getParaName()));
		}
		else if (right.size() != 0) {
			return getParentStarNumSyn(pkb, right, stoi(leftChild.getParaName()));
		}
	}
	else if (resultTable.getSynCount() == 2) {
		if (left.size() == 0) {
			return getParentStarSynSyn(pkb, getTypeStmt(leftChild.getParaType(), pkb), right);
		}
		else if (right.size() == 0) {
			return getParentStarSynSyn(pkb, left, getTypeStmt(rightChild.getParaType(), pkb));
		}
		else {
			return getParentStarSynSyn(pkb, &resultTable);
		}
	}
	return result;
}

ResultTable ParentStar::getParentStarSynNum(PKB* pkb, unordered_set<int> left, int right) {
	result.setSynList(vector<Parameter>({ leftChild }));
	if (isValidStmtNo(right, pkb)) { //if right is a valid statement number, follows(syn, num)
		unordered_set<int> parentStar = pkb->getStmtParentStarStmt(right);
		for (auto& it : parentStar) {
			if (left.find(it) != left.end()) {
				result.insertTuple(vector<int>(it));
			}
		}
	}
	return result;
}

ResultTable ParentStar::getParentStarNumSyn(PKB* pkb, unordered_set<int> right, int left) {
	result.setSynList(vector<Parameter>({ rightChild }));
	if (isValidStmtNo(left, pkb)) { //if right is a valid statement number, follows(syn, num)
		unordered_set<int> childrenStar = pkb->getStmtChildrenStarStmt(left);
		for (auto& it : childrenStar) {
			if (right.find(it) != right.end()) {
				result.insertTuple(vector<int>(it));
			}
		}
	}
	return result;
}

ResultTable ParentStar::getParentStarSynSyn(PKB* pkb, unordered_set<int> left, unordered_set<int> right) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		return result;
	}
	for (auto& rightIterator : right) {
		unordered_set<int> parentStar = pkb->getStmtParentStarStmt(rightIterator);
		for (auto& it : parentStar) {
			if (left.find(it) != left.end()) {
				result.insertTuple(vector<int>(it, rightIterator));
			}
		}
	}
	
	return result;
}

ResultTable ParentStar::getParentStarSynSyn(PKB* pkb, ResultTable* resultTable) {
	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	if (isLeftChild(rightChild)) {
		return result;
	}
	vector<Parameter> synonyms = resultTable->getSynList();
	vector<vector<int>> tupleList = resultTable->getTupleList();

	if (isLeftChild(synonyms[0])) {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isParentStar(pkb, tupleList[i][0], tupleList[i][1])) {
				result.insertTuple(vector<int>(tupleList[i][0], tupleList[i][1]));
			}
		}
	}
	else {
		for (int i = 0; i < tupleList.size(); i++) {
			if (isParentStar(pkb, tupleList[i][1], tupleList[i][0])) {
				result.insertTuple(vector<int>(tupleList[i][1], tupleList[i][0]));
			}
		}
	}
	return result;
}

ResultTable ParentStar::getParentStarNumNum(PKB* pkb, int left, int right) {
	if (!isValidStmtNo(left, pkb)) {
		result.setBoolean(false);
		return result;
	}
	if (!isValidStmtNo(right, pkb)) {
		result.setBoolean(false);
		return result;
	}
	result.setBoolean(isParentStar(pkb, left, right));
	return result;
}

bool ParentStar::isParentStar(PKB* pkb, int left, int right) {
	unordered_set<int> parentStar = pkb->getStmtParentStarStmt(right);
	if (parentStar.find(left) != parentStar.end()) {
		return true;
	}
	else {
		return false;
	}
}

unordered_set<int> ParentStar::getTypeStmt(Type type, PKB* pkb) {
	switch (type) {
	case PROG_LINE:
	case STMT:
	case ANYTHING: {
		int numOfStmt = pkb->getNumOfStmt();
		unordered_set<int> stmtList(numOfStmt);
		for (int i = 0; i < numOfStmt; i++) {
			//stmtList[i] = i + 1;
		}
		return stmtList;
	}
	case WHILE:
		return pkb->getAllWhileStmt();
	case ASSIGN:
		return pkb->getAllAssignStmt();
	case IF:
		return pkb->getAllIfId();
	case CALL:
		return pkb->getAllCallId();
	}
	return unordered_set<int>();
}

bool ParentStar::isNumber(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == INTEGER);
}

bool ParentStar::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == ANYTHING || type == PROG_LINE || type == IF || type == CALL);
}

bool ParentStar::isLeftChild(Parameter parameter) {
	return (parameter.getParaName().compare(leftChild.getParaName()) == 0 && parameter.getParaType() == leftChild.getParaType());
}

bool ParentStar::isValidStmtNo(int stmtId, PKB* pkb) {
	return ((stmtId > 0) && (stmtId <= pkb->getNumOfStmt()));
}

void ParentStar::insertSynList(Parameter p) {
	synList.push_back(p);
}

Parameter ParentStar::getLeftChild() {
	return leftChild;
}
Parameter ParentStar::getRightChild() {
	return rightChild;
}
vector<Parameter> ParentStar::getSynList() {
	return synList;
}
/*
ResultTable ParentStar::evaluate(PKB* pkb) {
	if (isNumber(leftChild)) {
		if (isNumber(rightChild)) {
			return getParentStarNumNum(pkb);
		}
		else if (isSynonym(rightChild)) {
			return getParentStarNumSyn(pkb);
		}
	}
	else if (isSynonym(leftChild)) {
		if (isNumber(rightChild)) {
			return getParentStarSynNum(pkb);
		}
		else if (isSynonym(rightChild)) {
			return getParentStarSynSyn(pkb);
		}
	}
	return result;
}

ResultTable ParentStar::getParentStarNumNum(PKB* pkb) {
	int leftArgument = stoi(leftChild.getParaName());
	int rightArgument = stoi(rightChild.getParaName());
	if (!isValidStmtNo(leftArgument, pkb)) {
		result.setBoolean(false);
		return result;
	}
	if (!isValidStmtNo(rightArgument, pkb)) {
		result.setBoolean(false);
		return result;
	}

	vector<int> Parents = pkb->getStmtParentStarStmt(rightArgument);
	for (int i = 0; i < Parents.size(); i++) {
		if (Parents[i] == leftArgument) {
			result.setBoolean(true);
			break;
		}
	}
	result.setBoolean(false);
	return result;
}

ResultTable ParentStar::getParentStarNumSyn(PKB* pkb) {
	int leftArgument = stoi(leftChild.getParaName());
	if (!isValidStmtNo(leftArgument, pkb)) {
		return result;
	}
	else { //if left is a valid statement number, Parents(num, syn)
		result.setSynList(vector<Parameter>({ rightChild }));
		return getAllChildrenStar(vector<int>(leftArgument), pkb);
		//result = filterType(tempResult, rightChildType, pkb);
		//return result;
	}
}

ResultTable ParentStar::getParentStarSynNum(PKB* pkb) {
	int rightArgument = stoi(rightChild.getParaName());
	if (!isValidStmtNo(rightArgument, pkb)) {
		return result;
	}
	else { //if right is a valid statement number, Parents(syn, num)
		result.setSynList(vector<Parameter>({ leftChild }));
		return getAllParentStar(vector<int>(rightArgument), pkb);
	}
}

ResultTable ParentStar::getParentStarSynSyn(PKB* pkb) {
	if (leftChild.getParaName().compare(rightChild.getParaName()) == 0) {
		return result;
	}


	result.setSynList(vector<Parameter>({ leftChild, rightChild }));
	vector<int> right = getTypeStmt(rightChild.getParaType(), pkb);
	return getAllParentStar(right, pkb);
	//return result;
}

vector<int> ParentStar::getTypeStmt(Type type, PKB* pkb) {
	switch (type) {
	case PROG_LINE:
	case STMT:
	case ANYTHING: {
		int numOfStmt = pkb->getNumOfStmt();
		vector<int> stmtList(numOfStmt);
		for (int i = 0; i < numOfStmt; i++) {
			stmtList[i] = i + 1;
		}
		return stmtList;
	}
	case WHILE:
		return pkb->getAllWhileStmt();
	case ASSIGN:
		return pkb->getAllAssignStmt();
	}
	return vector<int>();
}


ResultTable ParentStar::getAllParentStar(vector<int> list, PKB* pkb) {
	vector<int> parentStar;
	for (int i = 0; i < list.size(); i++) {
		parentStar = pkb->getStmtParentStarStmt(list[i]);
		for (int j = 0; j < parentStar.size(); j++) {
			if (isStmtType(parentStar[j], leftChild, pkb)) {
				result.insertTuple(vector<int>(parentStar[j], list[i]));
			}
		}

	}
	return result;
}

ResultTable ParentStar::getAllChildrenStar(vector<int> list, PKB* pkb) {
	vector<int> childrenStar;
	for (int i = 0; i < list.size(); i++) {
		childrenStar = pkb->getStmtChildrenStarStmt(list[i]);
		for (int j = 0; j < childrenStar.size(); j++) {
			if (isStmtType(childrenStar[j], rightChild, pkb)) {
				result.insertTuple(vector<int>(list[i], childrenStar[j]));
			}
		}
	}
	return result;
}

bool ParentStar::isStmtType(int stmtId, Parameter parameter, PKB* pkb) {
	Type type = parameter.getParaType();
	if (stmtId < 1)
		return false;
	switch (type) {
	case WHILE:
		return pkb->isStmtInWhileTable(stmtId);
	case ASSIGN:
		return pkb->isStmtInAssignTable(stmtId);
	case PROG_LINE:
	case STMT:
	case ANYTHING:
		return true;
	}
	return false;
}

void ParentStar::insertSynList(Parameter p) {
	synList.push_back(p);
}

bool ParentStar::isNumber(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == INTEGER);
}

bool ParentStar::isSynonym(Parameter parameter) {
	Type type = parameter.getParaType();
	return (type == ASSIGN || type == WHILE || type == STMT || type == ANYTHING || type == PROG_LINE);
}

bool ParentStar::isValidStmtNo(int stmtId, PKB* pkb) {
	return ((stmtId > 0) && (stmtId <= pkb->getNumOfStmt()));
}

Parameter ParentStar::getLeftChild() {
	return leftChild;
}
Parameter ParentStar::getRightChild() {
	return rightChild;
}
vector<Parameter> ParentStar::getSynList() {
	return synList;
}*/
/*
ParentStar::ParentStar(string lc, Type lcType, string rc, Type rcType) {
leftChild = lc;
rightChild = rc;
leftChildType = lcType;
rightChildType = rcType;
}

vector<int> ParentStar::getWithRelToRight(PKB* pkb) {
//cout << "RIGHT" << endl;
if (isSynonym(rightChildType)) {
//cout << "RIGHT IS SYNONYM" << endl;
if (isNumber(leftChildType)) {
int leftArgument = stoi(leftChild);
if (!isValidStmtNo(leftArgument, pkb)) {
return result;
}
else { //if left is a valid statement number, parent*(num, syn)
vector<int> children = pkb->getStmtChildrenStarStmt(leftArgument);
result = filterType(children, rightChildType, pkb);
return result;
}
}
else if (isSynonym(leftChildType)) { //parent(syn,syn)
//cout << "LEFT IS SYNONYM" << endl;
left = getTypeStmt(leftChildType, pkb);
//cout << "LEFT SIZE IS " << left.size() << endl;
tempResult = getAllChildren(left, pkb);
//cout << "TEMP SIZE IS " << tempResult.size() << endl;
//cout << endl;
result = filterType(tempResult, rightChildType, pkb);
//cout << "RESULT SIZE IS " << result.size() << endl;
//cout << endl;
return result;
}
else {
return result;
}
}
else {
return result;
}
return result;
}

vector<int> ParentStar::getWithRelToLeft(PKB* pkb) {
//cout << "LEFT" << endl;
if (isSynonym(leftChildType)) {
//cout << "LEFT IS SYNONYM" << endl;
if (isNumber(rightChildType)) {
int rightArgument = stoi(rightChild);
if (!isValidStmtNo(rightArgument, pkb)) {
return result;
}
else { //if right is valid statement number, parent(syn, num)
vector<int> parents = pkb->getStmtParentStarStmt(rightArgument);
result = filterType(parents, leftChildType, pkb);
return result;
}
}
else if (isSynonym(rightChildType)) { //parent(syn, syn)
//cout << "RIGHT IS SYNONYM" << endl;
right = getTypeStmt(rightChildType, pkb);
//cout << "NUMBER OF " << rightChildType << " is: " << right.size() << endl;
tempResult = getAllParents(right, pkb);
//cout << "NUMBER OF TEMP RESULT is: " << tempResult.size() << endl;
result = filterType(tempResult, leftChildType, pkb);
//cout << "NUMBER OF RESULT is: " << result.size() << endl;
return result;
}
else { // parent(synonym, invalid)
return result;
}
}
else { //invalid left argument
return result;
}
return result;
}

bool ParentStar::isValidStmtNo(int stmtId, PKB* pkb) {
return ((stmtId > 0) && (stmtId <= pkb->getNumOfStmt()));
}

vector<int> ParentStar::getAllChildren(vector<int> list, PKB* pkb) {
vector<int> children;
unordered_set<int> allChildren;
for (int i = 0; i < list.size(); i++) {
children = pkb->getStmtChildrenStarStmt(list[i]);
for (int j = 0; j < children.size(); j++) {
allChildren.insert(children[j]);
}
}
vector<int> result(allChildren.size());
copy(allChildren.begin(), allChildren.end(), result.begin());

return result;
}

vector<int> ParentStar::getAllParents(vector<int> list, PKB* pkb) {
vector<int> parents;
unordered_set<int> allParents;
for (int i = 0; i < list.size(); i++) {
parents = pkb->getStmtParentStarStmt(list[i]);
//cout << "Iteration: " << i << endl;
for (int j = 0; j < parents.size(); j++) {
allParents.insert(parents[j]);
}
}
//cout << "HERE" << endl;
vector<int> listParent(allParents.size());
copy(allParents.begin(), allParents.end(), listParent.begin());
return listParent;
}

vector<int> ParentStar::filterType(vector<int> list, Type type, PKB* pkb) {
if (type == STMT || type == ANYTHING || type == PROG_LINE) {
return list;
}
vector<int> result;
for (int i = 0; i < list.size(); i++) {
if (isStmtType(list[i], type, pkb)) {
result.push_back(list[i]);
}
}
return result;
}

bool ParentStar::isStmtType(int stmtId, Type type, PKB* pkb) {
if (stmtId < 1)
return false;
switch (type) {
case WHILE:
//	cout << stmtId << " " << pkb->isStmtInWhileTable(stmtId) << endl;
return pkb->isStmtInWhileTable(stmtId);
case ASSIGN:
return pkb->isStmtInAssignTable(stmtId);
case STMT:
case PROG_LINE:
case ANYTHING:
return true;
}
//cout << stmtId << " false" << endl;
return false;
}

vector<int> ParentStar::getTypeStmt(Type type, PKB* pkb) {
switch (type) {
case STMT:
case PROG_LINE:
case ANYTHING: {
int numOfStmt = pkb->getNumOfStmt();
vector<int> stmtList(numOfStmt);
for (int i = 0; i < numOfStmt; i++) {
stmtList[i] = i + 1;
}
return stmtList;
}
case WHILE:
return pkb->getAllWhileStmt();
case ASSIGN:
return pkb->getAllAssignStmt();
}
vector<int> result;
return result;
}

bool ParentStar::isNumber(Type type) {
return (type == INTEGER);
}

bool ParentStar::isSynonym(Type type) {
return (type == ASSIGN || type == WHILE || type == STMT || type == ANYTHING || type == PROG_LINE);
}

bool ParentStar::hasRel(PKB *pkb) {
if (isSynonym(leftChildType)) {
if (isNumber(rightChildType)) {
int rightArgument = stoi(rightChild);
if (!isValidStmtNo(rightArgument, pkb)) {
return false; // return what!??!!??!?!?!?!?!?!?!?!?!?!?!?!
}
else { //if right is valid statement number, parent(syn, num)
int parent = pkb->getStmtParentStmt(rightArgument);
if (isStmtType(parent, leftChildType, pkb)) {
return true;
}
else {
return false;
}
}
}
else if (isSynonym(rightChildType)) { // parent(syn,syn)
right = getTypeStmt(rightChildType, pkb);
//cout << "NUMBER OF RIGHT IS " << right.size() << endl;
tempResult = getAllParents(right, pkb);
//cout << "NUMBER OF TEMP IS " << tempResult.size() << endl;
result = filterType(tempResult, leftChildType, pkb);
return (result.size() != 0);
}
else { // parent(synonym, invalid)
return false; // return what!??!?!?!?!?!?!?!??!
}
}
else if (isNumber(leftChildType)) {
int leftArgument = stoi(leftChild);
if (!isValidStmtNo(leftArgument, pkb)) {
return false; // return what!??!!??!?!?!?!?!?!?!?!?!?!?!?!
}
if (isNumber(rightChildType)) {
int rightArgument = stoi(rightChild);
if (!isValidStmtNo(rightArgument, pkb)) {
return false; // return what!??!!??!?!?!?!?!?!?!?!?!?!?!?!
}
else { //if right is valid statement number, parent(num, num)
vector<int> parent = pkb->getStmtParentStarStmt(rightArgument);
for (int i = 0; i < parent.size(); i++) {
if (parent[i] == leftArgument)
return true;
}
return false;
}
}
else if (isSynonym(rightChildType)) { //parent(num , syn)
vector<int> children = pkb->getStmtChildrenStmt(leftArgument);
result = filterType(children, rightChildType, pkb);
return (result.size() != 0);
}
else {
return false; // return what!?! ?!?!? !? !??! ?
}
}
else { //invalid left argument
return false;
}
return isRel;
}

string ParentStar::getLeftChild() {
return leftChild;
}
string ParentStar::getRightChild() {
return rightChild;
}
Type ParentStar::getLeftChildType() {
return leftChildType;
}
Type ParentStar::getRightChildType() {
return rightChildType;
}
*/
ClauseType ParentStar::getClauseType() {
	return PARENTSTAR;
}
