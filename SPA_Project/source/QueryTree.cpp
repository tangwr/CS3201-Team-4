#include "QueryTree.h"
#include "Type.h"
#include "Clause.h"
#include "Parameter.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

QueryTree::QueryTree() {
	
}

void QueryTree::insertSelect(Parameter p) {
	select.push_back(p);
}

void QueryTree::insertUsed(Parameter p) {
	used.push_back(p);
}

void QueryTree::insertResult(Clause* result) {
	resultList.push_back(result);
}

vector<Clause*> QueryTree::getResult() {
	return resultList;
}

vector<Parameter> QueryTree::getSelectParameter() {
	return select;
}

vector<Parameter> QueryTree::getUsedParameter() {
	return used;
}

int QueryTree::getClauseSize() {
	return resultList.size();
}

Clause* QueryTree::getClause(int index){
	Clause* result = resultList.at(index);
    return result; 
}

