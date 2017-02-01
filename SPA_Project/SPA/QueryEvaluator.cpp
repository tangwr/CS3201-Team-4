#include "QueryEvaluator.h"

QueryEvaluator::QueryEvaluator() {
}

vector<string> QueryEvaluator::evaluate(QueryTree* qt) {
	//vector<clause> c = qt.getClause();

}

//Assume I got limit list & condition list

bool QueryEvaluator::checkCondition() {

	ClauseType clause; 
	string leftChild, rightChild;
	Type leftChildType, rightChildType;

	switch (clause) {
	case FOLLOW:
		return checkClauseCondition(clause, leftChild, rightChild, leftChildType, rightChildType);
	case FOllOWSTAR:
		return checkClauseCondition(clause, leftChild, rightChild, leftChildType, rightChildType);
	case PARENT:
		return checkClauseCondition(clause, leftChild, rightChild, leftChildType, rightChildType);
	case PARENTSTAR:
		return checkClauseCondition(clause, leftChild, rightChild, leftChildType, rightChildType);
	case PATTERN:
		return checkPattern(leftChild, rightChild, leftChildType, rightChildType);
	case MODIFIES:
		return checkModifies(leftChild, rightChild, leftChildType, rightChildType);
	case USES:
		return checkUses(leftChild, rightChild, leftChildType, rightChildType);
	}
}

//For  Follows & Parents only
bool QueryEvaluator::checkClauseCondition(ClauseType clause, string leftChild, string rightChild, Type leftChildType, Type rightChildType) {
	
	if (leftChildType == UNDERSCORE || rightChildType == UNDERSCORE) {
		return true;
	}

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
		vector<int> followsList = getClauseTypeList(clause, left_child_num, LEFT_CHILD);
		vector<int> typeList = getDeclareTypeList(rightChildType);
		bool result = isSubsetList(followsList, typeList);

		return result;
	}
	if (leftChildType != INT && rightChildType == INT) {
		int right_child_num = stoi(rightChild);
		vector<int> followsList = getClauseTypeList(clause, right_child_num, RIGHT_CHILD);
		vector<int> typeList = getDeclareTypeList(leftChildType);
		bool result = isSubsetList(followsList, typeList);

		return result;
	}
	if (leftChildType != INT && rightChildType != INT) {
		return true;
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


vector<int> QueryEvaluator::getDeclareTypeList(Type declareType) {
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
		ConstantTable variable_T;
		return constant_T.getConstantList();
	}
}

bool QueryEvaluator::isSubsetList(vector<int> subList, vector<int> setList) {
	sort(subList.begin(), subList.end());
	sort(setList.begin(), setList.end());

	bool result = includes(setList.begin(), setList.end(), subList.begin(), subList.end());

	return result;
}


//For Modies & use
bool QueryEvaluator::check_stmt_ent_condition(ClauseType clause, string leftChild, string rightChild, Type leftChildType, Type rightChildType) {


	if (leftChildType == UNDERSCORE || rightChildType == UNDERSCORE) {
		return true;
	}

	if (leftChildType == INT) {
		int left_child_num = stoi(leftChild);
		vector<int> stmtList = get_stmt_ent_list(clause, left_child_num);
		vector<int> entList = getEntRefList(rightChild, rightType);
		bool result = isSubsetList(entList, stmtList);

		return result;
	}
	else {
		vector<int> stmtList = getDeclareTypeList(leftChildType);
		vector<int> entList = getEntRefList(rightChild, rightType);
		bool result = isSubsetList(entList, stmtList);

		return result;
	}
}


vector<int> QueryEvaluator::get_stmt_ent_list(ClauseType clause, int stmtNo) {
	switch (clause) {
	case PATTERN:

	case MODIFIES:
		modifiesTable modifies_T;
		return modifies_T.getStmtModify(stmtNo);
	case USES:
		usesTable uses_T;
		return uses_T.getConstUsedByStmt(stmtNo); //  getVarUsedByStmt
	}
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
		ConstantTable variable_T;
		return constant_T.getConstantList();
	case STR:
		???????????
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


vector<string> QueryEvaluator::getAssignResult() {

}

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
