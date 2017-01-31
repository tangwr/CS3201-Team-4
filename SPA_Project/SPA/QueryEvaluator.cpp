#include "QueryEvaluator.h"

//Public method

QueryEvaluator::QueryEvaluator(){

}

std::list<std::string> QueryEvaluator::evaluate(QueryTree qt) {
	std::list<std::string> results;

	return results
}


//Private method
std::list<std::string> QueryEvaluator::evaluateQuery(QueryTree qt) {
	<PKB_class> pkb;

	<datatype> varTable = pkb.getVarTable();
	<datatype> stmtTable = pkb.getStmtTable();
	<datatype> assignTable = pkb.getAssignTable();
	<datatype> parentTable = pkb.getParentTable();
	<datatype> modifyTable = pkb.getModifyTable();
	<datatype> followTable = pkb.getFollowTable();



	std::string syntax = qt.syntax;
	std::string assign = qt.assign;
	std::string variable = qt.variable;
	std::string statement = qt.statement;

	validateVariable = validateQuery(varTable, variable);
	validateStmt = validateQuery(stmtTable, statement);
	validateAssign = validateQuery(assignTable, assign);
	validateParent = validateQuery(parentTable, parent);
	validateModify = validateQuery(modifyTable, modify);
	validateFollow = validateQuery(followTable, follow);
	
}

//Check if the token exists in the table 
bool QueryEvaluator::validateQuery(<datatype> table, std::string token) {
	bool result;

	return result;
}
