#include "QueryTree.h"
#include "Type.h"
#include "Clause.h"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

const string existingValue = "The value is exist already";

QueryTree::QueryTree() {
	
}

void QueryTree::setIsComonVar(bool result) {
	isCommonVar = result;
}
void QueryTree::insertSelect(string key, Type value) {
	select.insert(std::pair<string, Type>(key, value));
}
void QueryTree::insertComonVar(string key, Type value) {
	comonVar.insert(std::pair<string, Type>(key, value));
}
void QueryTree::insertLimits(Clause* limit) {
	limits.push_back(limit);
}

void QueryTree::insertUnLimits(Clause* unlimit) {
	unlimits.push_back(unlimit);
}

void QueryTree::clearComonMap() {
	comonVar.clear();
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
unordered_map<string, Type> QueryTree::getComonVar() {
	return comonVar;
}
bool QueryTree::getIsComonVar() {
	return isCommonVar;
}