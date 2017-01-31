#include "QueryEvaluator.h"

//Public method

QueryEvaluator::QueryEvaluator(){
}

std::list<std::string> QueryEvaluator::evaluate(QueryTree qt) {
	std::list<std::string> results;
	results = evaluateQuery(qt);
	return results
}


//Private method
std::list<std::string> QueryEvaluator::evaluateQuery(QueryTree qt) {
	/*
		IDENT: LETTER(LETTER | DIGIT | '#')*
		synonym: IDENT
		stmtRef: synonym | '_' | INTEGER
		entRef: synonym | '_' | "IDENT"
		Modifies/Uses ('stmtRef', 'entRef')
		Parent/Follow ('stmtRef', 'stmtRef')
	*/


	/*
		Get the individual parts of the query string
		Example:
			assignment a, a1; variable v;
			- Select a such that Uses(a,v) pattern a1(v,_)

			assign a, statement s, variable v;
			- Select a pattern a("x", _"y"_)
			- Select s such that Follows(1,s)
			- Select s such that Follows(s,2)
			- Select s usch that Follows*(1,s)
			- Select s such that Follows*(s,2)
			- Select s such that Parent(2,s)
			- Select s such that Parent(s,3)
			- Select s such that Parent*(2,s)
			- Select s such that Parent*(s,3)
			- Select v such that Modifies(1,v)
			- Select a such that Modifies(a,"x")
			- Select BOOLEAN such that Modifies(3,"x")

	*/
	//Declaration
	std::vector<std::string> stmt = qt.stmt;
	std::vector<std::string> assign = qt.assign;
	std::vector<std::string> whileS = qt.whileS;
	std::vector<std::string> variable = qt.variable;
	std::vector<std::string> constant = qt.constant;
	std::vector<std::string> prog_line = qt.prog_line;
	
	//Select synonym the value to be return
	std::vector<std::string> synonym = qt.synonym; //a.k.a 'syntax'

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