#include "QueryTree.h"
#include "Type.h"
#include "Clause.h"
#include "ClauseType.h"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

const string existingValue = "The value is exist already";

QueryTree::QueryTree() {
	
}

void QueryTree::insertSelect(string key, Type value) {
	select.insert(std::pair<string, Type>(key, value));
}

void QueryTree::insertLimits(Clause* limit) {
	limits.push_back(limit);
}

void QueryTree::insertUnLimits(Clause* unlimit) {
	unlimits.push_back(unlimit);
}

vector<Clause*> QueryTree::getLimits() {
	return limits;
}

vector<Clause*> QueryTree::getUnLimits() {
	return unlimits;
}

unordered_map<string, Type> QueryTree::getSelect() {
	return select;
}