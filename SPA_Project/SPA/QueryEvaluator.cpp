#include "QueryEvaluator.h"

QueryEvaluator::QueryEvaluator() {
}

/*

Public Methods

*/
vector<string> QueryEvaluator::evaluate(QueryTree* qt) {
	//vector<clause> c = qt.getClause();
	vector<"object">checkConditionList = qt.getCheckConditionList;
	vector<"object">retrieveResultsList = qt.getRetrieveResultsList;
	vector<string> v = {};

	bool isRetrieveResults = true;
	foreach("object" obj : checkConditionList) {
		if (checkCondition(obj) == false) {
			isRetriveResults = false;
			break
		}
	}

	if (isRetriveResults == false) {
		return v;
	}

	foreach("object" obj : retrieveResultsList) {
		v = getResult(obj);
	}

	return v;
}


/*

Private Methods

*/

//Check the condition base on clause type
bool QueryEvaluator::checkCondition("object" obj) {


	ClauseType clause = obj.getClause();
	string leftChild = obj.getLeftChild();
	string rightChild = obj.getRightChild();
	DeclareType leftChildType = obj.getLeftChildType();
	DeclareType rightChildType = obj.getRightChildType();

	switch (clause) {
	case FOLLOW:
		return checkStmtStmtCondition(clause, leftChild, rightChild, leftChildType, rightChildType);
	case FOllOWSTAR:
		return checkStmtStmtCondition(clause, leftChild, rightChild, leftChildType, rightChildType);
	case PARENT:
		return checkStmtStmtCondition(clause, leftChild, rightChild, leftChildType, rightChildType);
	case PARENTSTAR:
		return checkStmtStmtCondition(clause, leftChild, rightChild, leftChildType, rightChildType);
	case MODIFIES:
		return checkStmtEmtCondition(leftChild, rightChild, leftChildType, rightChildType);
	case USES:
		return checkStmtEmtCondition(leftChild, rightChild, leftChildType, rightChildType);
	case PATTERN:
		return checkPattern(leftChild, rightChild, leftChildType, rightChildType);

	}
}

//Check the subset of two vectors
bool QueryEvaluator::isSubsetList(vector<int> subList, vector<int> setList) {
	sort(subList.begin(), subList.end());
	sort(setList.begin(), setList.end());

	bool result = includes(setList.begin(), setList.end(), subList.begin(), subList.end());

	return result;
}

//For  Follows & Parents only
bool QueryEvaluator::checkStmtStmtCondition(ClauseType clause, string leftChild, string rightChild, DeclareType leftChildType, DeclareType rightChildType) {

	if (leftChildType == UNDERSCORE || rightChildType == UNDERSCORE) {
		return true;
	}

	//Follows(1,2)   Parent(1,2)
	if (leftChildType == INT && rightChildType == INT) {
		int leftChild_stmtNo = stoi(leftChild);
		int rightChild_stmtNo = stoi(rightChild);

		bool results = verifyStmtNoRelation(clause, leftChild_stmtNo, rightChild_stmtNo)
			return false;
	}
	if (leftChildType == INT && rightChildType != INT) {
		int leftChild_stmtNo = stoi(leftChild);
		vector<int> leftChildList = getClauseTypeList(clause, leftChild_stmtNo, LEFT_CHILD);
		vector<int> rightChildList = getDeclareTypeList(rightChildType);
		bool result = isSubsetList(leftChildList, rightChildList);

		return result;
	}
	if (leftChildType != INT && rightChildType == INT) {
		int rightChild_stmtNo = stoi(rightChild);
		vector<int> rightChildList = getClauseTypeList(clause, rightChild_stmtNo, RIGHT_CHILD);
		vector<int> leftChildList = getDeclareTypeList(leftChildType);
		bool result = isSubsetList(rightChildList, leftChildList);

		return result;
	}
	if (leftChildType != INT && rightChildType != INT) {
		return true;
	}

}

//Verify the (stmt_no, stmt_no) for Follows & Parents
bool QueryEvaluator::verifyStmtNoRelation(ClauseType clause, int leftChild_stmtNo, int rightChild_stmtNo) {
	switch (clause) {
	case FOLLOW:
		FollowsTable follows_T;
		int follow_stmtNo = follows_T.getDirectFollows(rightChild_stmtNo);

		if (leftChild_stmtNo == follow_stmtNo) {
			return true;
		}
		return false;
	case FOllOWSTAR:
		FollowsTable follows_T;
		vector<int> followedByList = follows_T.getFollowedByList(leftChild_stmtNo);
		vector<int> rightChildList = {}
		rightChildList.push_back(rightChild_stmtNo);

		return isSubsetList(rightChildList, followedByList);

	case PARENT:
		ParentsTable parents_T;
		int parent_stmtNo = parents_T.getParent(rightChild_stmtNo);

		if (leftChild_stmtNo == parent_stmtNo) {
			return true;
		}
		return false;
	case PARENTSTAR:
		ParentsTable parents_T;
		vector<int> childrenList = parents_T.getChildrenList(leftChild_stmtNo);
		vector<int> rightChildList = {}
		rightChildList.push_back(rightChild_stmtNo);

		return isSubsetList(rightChildList, childrenList);
	}
}

vector<int> QueryEvaluator::getClauseTypeList(ClauseType clause, int stmtNo, CHILD child) {
	switch (clause) {
	case FOLLOW:
		FollowsTable follows_T;
		vector<int> v;
		int stmt_num;

		if (child == LEFT_CHILD) {
			stmt_num = follows_T.getDirectFollow(stmtNo);
			v.push_back(stmt_num);
		}
		if (child == RIGHT_CHILD) {
			stmt_num = follows_T.getDirectFollowedBy(stmtNo);
			v.push_back(stmt_num);
		}
		return v;

	case FOllOWSTAR:
		FollowsTable follows_T;

		if (child == LEFT_CHILD) {
			return follows_T.getFollowList(stmtNo);
		}
		if (child == RIGHT_CHILD) {
			return follows_T.getFollowedByList(stmtNo);
		}



	case PARENT:
		ParentsTable parents_T;
		vector<int> v;
		int stmt_num;

		if (child == LEFT_CHILD) {
			stmt_num = parents_T.getChildren(stmtNo);
			v.push_back(stmt_num);
		}
		if (child == RIGHT_CHILD) {
			stmt_num = parents_T.getParent(stmtNo);
			v.push_back(stmt_num);
		}
		return v;

	case PARENTSTAR:
		ParentsTable parents_T;

		if (child == LEFT_CHILD) {
			return parents_T.getChildrenList(stmtNo);
		}
		if (child == RIGHT_CHILD) {
			return parents_T.getParentList(stmtNo);
		}

	}
}

vector<int> QueryEvaluator::getDeclareTypeList(DeclareType declare) {
	switch (declare) {
	case ASSIGN:
		AssignTable assign_T;
		return assign_T.getAssignList();
	case PROG_LINE:
		ProgLineTable progLine_T;
		return progLine_T.getProgLineList();
	case STMT:
		StmtTable stmt_T;
		return stmt_T.getStmtList();
	case WHILES:
		WhilesTable whiles_T;
		return whiles_T.getWhilesList();
	case VARIABLE:
		VariableTable variable_T;
		return variable_T.getVariableList();
	case CONSTANT:
		ConstantTable variable_T;
		return constant_T.getConstantList();
	}
}


//For Modifies & Use Checking Condition
bool QueryEvaluator::checkStmtEmtCondition(string leftChild, string rightChild, DeclareType leftChildType, DeclareType rightChildType) {
	if (leftChildType == UNDERSCORE || rightChildType == UNDERSCORE) {
		return true;
	}
	if (leftChildType == INT && rightChild != INT) {
		int leftChild_stmtNo = stoi(leftChild);
		vector<int> v = {};
		v.push_back(leftChild_stmtNo);

		vector<int> rightChildList = getChildTypeList(rightChildType);
		return isSubsetList(v, rightChildList);

	}
	if (leftChildType != INT && rightChild != INT) {
		vector<int> leftChildList = getChildTypeList(leftChildType);
		vector<int> rightChildList = getChildTypeList(rightChildType);

		return isSubsetList(leftChildList, rightChildList);
	}

}

vector<int> QueryEvaluator::getChildTypeList(DeclareType child) {
	switch (child) {
	case ASSIGN:
		AssignTable assign_T;
		return assign_T.getAllAssignStmtNo();
	case PROG_LINE:
		ProgLineTable progLine_T;
		return progLine_T.getAllProgLineStmtNo();
	case STMT:
		StmtTable stmt_T;
		return stmt_T.getAllStmtStmtNo();
	case WHILES:
		WhileTable while_T;
		return while_T.getAllWhileStmtNo();
	case VARIABLE:
		VariableTable variable_T;
		return variable_T.getAllWhileStmtNo();
	case CONSTANT:
		ConstantTable constant_T;
		return constant_T.getAllConstantStmtNo();
	case STR:
		break;
	}

}

vector<string> QueryEvaluator::vectorIntToString(vector<int> vInt) {
	vector<string> vString = {};

	for (int i : vInt) {
		vString.push_back(to_string(i));
	}

	return vString;
}

vector<string> QueryEvaluator::intersection(vector<int> v1, vector<int> v2) {
	vector<int> v3 = {};

	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));

	return vectorIntToString(v3);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Getting results

vector<string> QueryEvaluator::getResult("object" obj) {

	DeclareType selectType = obj.getSelect();
	ClauseType clause = obj.getClause();
	string leftChild = obj.getLeftChild();
	string rightChild = obj.getRightChild();
	DeclareType leftChildType = obj.getLeftChildType();
	DeclareType rightChildType = obj.getRightChildType();

	switch (clause) {
	case FOLLOW:
		return getStmtStmtResults(clause, leftChild, rightChild, leftChildType, rightChildType);
	case FOllOWSTAR:
		return getStmtStmtResults(clause, leftChild, rightChild, leftChildType, rightChildType);
	case PARENT:
		return getStmtStmtResults(clause, leftChild, rightChild, leftChildType, rightChildType);
	case PARENTSTAR:
		return getStmtStmtResults(clause, leftChild, rightChild, leftChildType, rightChildType);
	case MODIFIES:
		return getStmtEmtResults(leftChild, rightChild, leftChildType, rightChildType);
	case USES:
		return getStmtEmtResults(leftChild, rightChild, leftChildType, rightChildType);
	case PATTERN:
		//return checkPattern(leftChild, rightChild, leftChildType, rightChildType);

	}

}

vector<string> QueryEvaluator::getStmtStmtResults(ClauseType clause, string leftChild, string rightChild, DeclareType leftChildType, DeclareType rightChildType) {
	vector<string> v = {};

	if (leftChildType == UNDERSCORE) {
		v = getChildTypeList(rightChildType);
		return vectorIntToString(v);
	}
		
	if(rightChildType == UNDERSCORE) {
		v = getChildTypeList(leftChildType);
		return vectorIntToString(v);
	}

	
	if (leftChildType == INT && rightChildType != INT) {
		int leftChild_stmtNo = stoi(leftChild);
		vector<int> leftChildList = getClauseTypeList(clause, leftChild_stmtNo, LEFT_CHILD);
		vector<int> rightChildList = getDeclareTypeList(rightChildType);
		bool result = isSubsetList(leftChildList, rightChildList);

		if (result == true) {
			return vectorIntToString(leftChildList);
		}

		return v;
	}
	if (leftChildType != INT && rightChildType == INT) {
		int rightChild_stmtNo = stoi(rightChild);
		vector<int> rightChildList = getClauseTypeList(clause, rightChild_stmtNo, RIGHT_CHILD);
		vector<int> leftChildList = getDeclareTypeList(leftChildType);
		bool result = isSubsetList(rightChildList, leftChildList);

		if (result == true) {
			return vectorIntToString(rightChildList);
		}

		return v;
	}
	if (leftChildType != INT && rightChildType != INT) {
		
		vector<int> leftChildList = getDeclareTypeList(leftChildType);
		vector<int> rightChildList = getDeclareTypeList(rightChildType);

		return intersection(leftChildList, rightChildList);

	}

}

vector<string> QueryEvaluator::getStmtEmtResults(string leftChild, string rightChild, DeclareType leftChildType, DeclareType rightChildType) {
	if (leftChildType == UNDERSCORE || rightChildType == UNDERSCORE) {
		return true;
	}
	if (leftChildType == INT && rightChild != INT) {
		int leftChild_stmtNo = stoi(leftChild);
		vector<int> v = {};
		v.push_back(leftChild_stmtNo);

		vector<int> rightChildList = getChildTypeList(rightChildType);
		bool result = isSubsetList(v, rightChildList);
		if (result == true) {
			return vectorIntToString(v);
		}
		else {
			vector<string> s = {};
			return s;
		}

	}
	if (leftChildType != INT && rightChild != INT) {
		vector<int> leftChildList = getChildTypeList(leftChildType);
		vector<int> rightChildList = getChildTypeList(rightChildType);

		bool result = isSubsetList(leftChildList, rightChildList);

		
		if (result == true) {
			return intersection(leftChildList, rightChildList);
		}
		else {
			vector<string> s = {};
			return s;
		}
	}

}

vector<string> QueryEvaluator::getPatternResults(DeclareType patternType, clause, string leftChild, string rightChild, DeclareType leftChildType, DeclareType rightChildType) {

}

/*

vector<string> QueryEvaluator::getAssignResult(ClauseType clause, string leftChild, string rightChild, DeclareType leftChildType, DeclareType rightChildType) {
	AssignTable assign_T;
	switch (clause) {
	case FOLLOW:
	case FOllOWSTAR:
	case PARENT:
	case PARENTSTAR:
		if (leftChildType == UNDERSCORE || rightChildType == UNDERSCORE) {
			return vectorIntToString(assign_T.getAllAssignStmtNo());
		}


		if (leftChildType == INT && rightChildType != INT) {
			int leftChild_stmtNo = stoi(leftChild);
			vector<int> leftChildList = getClauseTypeList(clause, leftChild_stmtNo, LEFT_CHILD);

			return vectorIntToString(leftChildList);
		}
		if (leftChildType != INT && rightChildType == INT) {
			int rightChild_stmtNo = stoi(rightChild);
			vector<int> rightChildList = getClauseTypeList(clause, rightChild_stmtNo, RIGHT_CHILD);

			return vectorIntToString(rightChildList);
		}
		if (leftChildType != INT && rightChildType != INT) {
			return vectorIntToString(assign_T.getAllAssignStmtNo());
		}

	case MODIFIES:

	case USES:

	case PATTERN:


	}
}
*/

/*
vector<string> QueryEvaluator::getStmtStmtResult(ClauseType clause, string leftChild, string rightChild, DeclareType leftChildType, DeclareType rightChildType) {

	if (leftChildType == UNDERSCORE || rightChildType == UNDERSCORE) {
		return true;
	}

	//Follows(1,2)   Parent(1,2)
	if (leftChildType == INT && rightChildType == INT) {
		int leftChild_stmtNo = stoi(leftChild);
		int rightChild_stmtNo = stoi(rightChild);

		bool results = verifyStmtNoRelation(clause, leftChild_stmtNo, rightChild_stmtNo)
			return false;
	}
	if (leftChildType == INT && rightChildType != INT) {
		int leftChild_stmtNo = stoi(leftChild);
		vector<int> leftChildList = getClauseTypeList(clause, leftChild_stmtNo, LEFT_CHILD);
		vector<int> rightChildList = getDeclareTypeList(rightChildType);
		bool result = isSubsetList(leftChildList, rightChildList);

		return result;
	}
	if (leftChildType != INT && rightChildType == INT) {
		int rightChild_stmtNo = stoi(rightChild);
		vector<int> rightChildList = getClauseTypeList(clause, rightChild_stmtNo, RIGHT_CHILD);
		vector<int> leftChildList = getDeclareTypeList(leftChildType);
		bool result = isSubsetList(rightChildList, leftChildList);

		return result;
	}
	if (leftChildType != INT && rightChildType != INT) {
		return true;
	}

}
*/

vector<string> QueryEvaluator::getStatementResult() {

}

vector<string> QueryEvaluator::getVariableResult() {

}

vector<string> QueryEvaluator::getWhileResult() {

}

vector<string> QueryEvaluator::getConstantResult() {

}

vector<string> QueryEvaluator::getProgLineResult() {

}

vector<string> QueryEvaluator::getBooleanResult() {

}







/*

bool QueryEvaluator::checkStmtEntCondition(ClauseType clause, string leftChild, string rightChild, DeclareType leftChildType, DeclareType rightChildType) {


if (leftChildType == UNDERSCORE || rightChildType == UNDERSCORE) {
return true;
}

if (leftChildType == INT && rightChild != INT) {
int leftChild_stmtNo = stoi(leftChild);
vector<int> stmtList = getStmtlist(clause, leftChild_stmtNo, rightChildType);
vector<int> entList = getEntRefList(rightChild, rightType);
bool result = isSubsetList(entList, stmtList);

return result;
}
if(leftChildType != INT && rightChildType != INT){
vector<int> stmtList = getDeclareTypeList(leftChildType);
vector<int> entList = getEntRefList(rightChild, rightType);
bool result = isSubsetList(entList, stmtList);

return result;
}
}


vector<int> QueryEvaluator::getStmtlist(ClauseType clause, int stmtNo, DeclareType rigthChildType) {
switch (clause) {

case MODIFIES:
modifiesTable modifies_T;

return modifies_T.getStmtModify(stmtNo);
case USES:
usesTable uses_T;
return uses_T.getConstUsedByStmt(stmtNo); //  getVarUsedByStmt
}
}

vector<int> QueryEvaluator::getStmtChildTypeList(int stmtNo, DeclareType rightChildType){

}

vector<int> QueryEvaluator::getEntRefList(string child, Type childType) {
switch (declareType) {
case ASSIGN:
AssignTable assign_T;
return assign_T.getAssignList();
case PROG_LINE:
ProgLineTable progLine_T;
return progLine_T.getProgLineList();
case STMT:
StmtTable stmt_T;
return stmt_T.getStmtList();
case WHILES:
WhilesTable whiles_T;
return whiles_T.getWhilesList();
case VARIABLE:
VariableTable variable_T;
return variable_T.getVariableList();
case CONSTANT:
ConstantTable constant_T;
return constant_T.getConstantList();
case STR:
VariableTable variable_T;
int varIndex = variable_T.getVarIndex(child);
}
}

bool QueryEvaluator::checkModifies(string leftChild, string rightChild, Type leftChildType, Type rightChildType) {
ModifiesTable modfies_T;

if (leftChildType == UNDERSCORE || rightChildType == UNDERSCORE) {
return true;
}

if (leftChildType == INT) {
int left_child_num = stoi(leftChild);
vector<int> modifiesList = modifies_T.getStmtModify(left_child_num);
vector<int> entList = getEntRefList(rightChild, rightType);
bool result = isSubsetList(followsList, entList);

return result;
}
else {
vector<int> modifiesList = getDeclareTypeList(leftChildType);
vector<int> entList = getEntRefList(rightChild, rightType);
bool result = isSubsetList(entList, modifiesList);

return result;
}
}

*/










/*
bool QueryEvaluator::checkFollow(string leftChild, string rightChild, Type leftChildType, Type rightChildType) {
FollowsTable follow_T;

if (leftChildType == INT && rightChildType == INT) {
int left_child_num = stoi(leftChild);
int right_child_num = stoi(rightChild);

if (left_child_num == right_child_num) {
return true;
}
return false;
}
if (leftChildType == INT && rightChildType != INT) {
int left_child_num = stoi(leftChild);
vector<int> followsList = follow_T.getFollowsList(left_child_num);
vector<int> typeList = getDeclareTypeList(rightChildType);
bool result = isSubsetList(followsList, typeList);
}
if (leftChildType != INT && rightChildType == INT) {
int right_child_num = stoi(rightChild);
vector<int> followsList = follow_T.getFollowsList(right_child_num);
vector<int> typeList = getDeclareTypeList(leftChildType);
bool result = isSubsetList(followsList, typeList);
}
if (leftChildType != INT && rightChildType != INT) {
return true;
}

}

bool QueryEvaluator::checkFollowStar() {

}

bool QueryEvaluator::checkParent() {

}

bool QueryEvaluator::checkParentStar() {

}

bool QueryEvaluator::checkPattern() {

}

bool QueryEvaluator::checkModifies() {

}

bool QueryEvaluator::checkUses() {

}
*/



