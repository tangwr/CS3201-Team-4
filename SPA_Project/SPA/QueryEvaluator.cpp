#include "QueryEvaluator.h"
#include "QueryTree.h"

QueryEvaluator::QueryEvaluator(){

}



std::list<std::string> QueryEvaluator::evaluate(QueryTree query) {
	std::list<std::string> results;

	return results
}



std::list<std::string> QueryEvaluator::evaluate1() {
	PKB p;
	<datatype> varTable = p.getVarTable();
	<datatype> stmtTable = p.getStmtTable();
	<datatype> assignTable = p.getAssignTable();
	<datatype> parentTable = p.getParentTable();
	<datatype> modifyTable = p.getModifyTable();
	<datatype> followTable = p.getFollowTable();

	std::list<std::string> results = {};

	return results;
}

void QueryEvaluator::getProcess() {
	Preprocess p;
	p.syn;
	p.stmt;
	p.assign;
	p.variable;
}