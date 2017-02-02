#include "QueryEvaluatorOld.h"

//Public method

QueryEvaluator::QueryEvaluator(){
}

std::list<std::string> QueryEvaluator::evaluate(QueryTree qt) {
	
	std::list<std::string> results;
	results = evaluateQuery(qt);
	return results;
}


//Private method
std::list<std::string> QueryEvaluator::evaluateQuery(QueryTree qt) {
	
	//Retreive the return results
	std::vector<std::string> select = qt.select;
	std::string booleanRelation = qt.booleanRelation;
	//Retrieve Declaration
	std::vector<std::string> assign = qt.assign;
	std::vector<std::string> statement = qt.statement;
	std::vector<std::string> variable = qt.variable;	
	std::vector<std::string> constant = qt.constant;
	std::vector<std::string> progLine = qt.progLine;
	//Clause
	std::unordered_map < std::string, std::unordered_map<std::string, std::string>> limit = qt.limit;
	std::unordered_map < std::string, std::unordered_map<std::string, std::string>> unlimit = qt.unlimit;

	
	

	//The clause
	
	/*
		'such that' clause
		relRef: Modifies, Uses, Parent, Parent*, Follows, Follows*
	*/
	std::string relRef = qt.relRef;
	std::string relRef_value = qt.relRef_value;
	std::string relRef_left_value = getLeftValue(relRef_value);
	std::string relRef_right_value = getRightValue(relRef_value);

	/*
		'pattern' clause 
		syn-assign (entRef, expression-spec)
		syn-assign must be declared as stnonym of assignment (degin entity 'assign')
	*/
	std::string syn_assign = qt.syn_assign;
	std::string syn_assign_value = qt.syn_assign_value;
	std::string syn_assign_left_value = getLeftValue(syn_assign_value);
	std::string syn_assign_right_value = getRightValue(syn_assign_value);


	//need to differtiate if value is integer or string
	isInteger(relRef_left_value);
	isInteger(relRef_right_value);
	isInteger(syn_assign_left_value);
	isInteger(syn_assign_right_value);
	
	//check type of value


	//check condition


	//get the return results

}

//Check if the token exists in the table 
bool QueryEvaluator::validateQuery(<datatype> table, std::string token) {
	bool result;

	return result;
}




std::string QueryEvaluator::getLeftValue(std::string input)
{
	int delim_pos = getDelimPos(input, ',');
	std::string value = input.substr(1, delim_pos - 1);
	
	return removeSpaces(value);
}

std::string QueryEvaluator::getRightValue(std::string input)
{
	int delim_pos = getDelimPos(input, ',') + 1;
	std::string value = input.substr(delim_pos, input.length() - delim_pos - 1);
	
	return removeSpaces(value);
}

int QueryEvaluator::getDelimPos(std::string input, char delim) {
	int delim_pos = 0;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == delim) {
			delim_pos = i;
		}
	}

	return delim_pos;
}

std::string QueryEvaluator::removeSpaces(std::string input)
{
	int length = input.length();
	for (int i = 0; i < length; i++) {
		if (input[i] == ' ')
		{
			input.erase(i, 1);
			length--;
			i--;
		}
	}
	return input;
}

bool QueryEvaluator::isInteger(std::string s) {
	return s.find_first_not_of("0123456789") == std::string::npos;
}


///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

//Check the condition of such that & pattern
bool QueryEvaluator::checkCondition(std::string clause, std::string left_value, std::string right_value, declareType left_type, declareType right_type) {
	clauseString clauseType = getClauseType(clause);

	if (left_type == UNKNOWN) {
		if (isInteger(left_value)) {
			left_type = INT;
		}
		else {
			left_type = STR;
		}
	}
	
	
	if (right_type == UNKNOWN) {
		if (isInteger(right_value)) {
			right_type = INT;
		}
		else {
			right_type = STR;
		}
	}


	switch (clauseType) {
	case MODIFIES:
		return checkModifies(left_value, right_value, left_type, right_type);
	case USES:
		return checkUses(left_value, right_value, left_type, right_type);
	case PARENT:
		return checkParent(left_value, right_value, left_type, right_type);
	case PARENT_S:
		return checkParent_s(left_value, right_value, left_type, right_type);
	case FOLLOW:
		return checkFollow(left_value, right_value, left_type, right_type);
	case FOLLOW_S:
		return checkFollow_s(left_value, right_value, left_type, right_type);
	}
		 

}

bool QueryEvaluator::checkModifies(std::string left_value, std::string right_value, declareType left_type, declareType right_type) {
	
	ModifiesTable mt;

	if (isInteger(left_value)) {
		int int_left = std::stoi(left_value);
	}
	else {

	}
}

bool QueryEvaluator::checkUses(std::string left_value, std::string right_value, declareType left_type, declareType right_type) {

}



bool QueryEvaluator::checkParent(std::string left_value, std::string right_value, declareType left_type, declareType right_type) {
	
	ParentTable parentT;
	if (left_type == STR && right_type == STR) {
		return false;
	}
	
	if (left_type != INT && right_type == INT) {
		int parent_stmt_no = parentT.getParent(std::stoi(right_value));
		switch (left_type) {
		case ASSIGN:
			return false;// assignT.isAssign(parent_stmt_no);
		case VARIABLE:
			return false; // variableT.isVariable(parent_stmt_no);
		case WHILE:
			return false; // whileT.isWhile(parent_stmt_no);
		case STMT:
			return false;// stmtT.isStmt(parent_stmt_no);
		}
	}
	if (left_type == INT && right_type != INT) {
		int child_stmt_no = parentT.getChildren(std::stoi(left_value));
		switch (right_type) {
		case ASSIGN:
			return false;//assignT.isAssign(child_stmt_no);
		case VARIABLE:
			return false;//variableT.isVariable(child_stmt_no);
		case WHILE:
			return false;// whileT.isWhile(child_stmt_no);
		case STMT:
			return false; // stmtT.isStmt(child_stmt_no);
	}
	
	if (left_type == INT && right_type == INT) {
		int parent_stmt_no1 = std::stoi(left_value);
		int parent_stmt_no2 = parentT.getParent(std::stoi(right_value));

		if (parent_stmt_no1 == parent_stmt_no2) {
			return true;
		}
		return false;
	}
	return false;
	
	if (isInteger(left_value)) {
		int child_stmt_no = pt.getChildern(std::stoi(left_value));
		if (isInteger(right_value)) {
			if (child_stmt_no == std::stoi(right_value)) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	
}
bool QueryEvaluator::checkParent_s(std::string left_value, std::string right_value, declareType left_type, declareType right_type) {
	
	
}

bool QueryEvaluator::checkFollow(std::string left_value, std::string right_value, declareType left_type, declareType right_type) {

}

bool QueryEvaluator::checkFollow_s(std::string left_value, std::string right_value, declareType left_type, declareType right_type) {

}



clauseString getClauseType(std::string clause) {
	std::transform(clause.begin(), clause.end(), clause.begin(), ::tolower);
	if (clause == "modifies") return MODIFIES;
	if (clause == "uses") return USES;
	if (clause == "parent") return PARENT;
	if (clause == "parent*") return PARENT_S;
	if (clause == "follow") return FOLLOW;
	if (clause == "follow*") return FOLLOW_S;
}