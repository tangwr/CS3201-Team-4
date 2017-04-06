#include "NextBipTable.h"

NextBipTable::NextBipTable() {
	this->size = 0;
}

int NextBipTable::getSize() {
	return this->size;
}

bool NextBipTable::setStmtNextBipStmtRel(int currentStmtId, int nextStmtId) {
	//nextBip
	unordered_map<int, unordered_set<int>>::iterator it;
	it = nextBipMap.find(currentStmtId);
	unordered_set<int> nextBipSet;

	if (it != nextBipMap.end()) {
		//currentStmtId has some nextBip
		nextBipSet = it->second;
		if (nextBipSet.find(nextStmtId) != nextBipSet.end()) {
			//already exist
			return false;
		}
		nextBipMap.erase(it);
	}
	nextBipSet.insert(nextStmtId);
	nextBipMap.insert(make_pair(currentStmtId, nextBipSet));

	//previousBip
	unordered_map<int, unordered_set<int>>::iterator it2;
	it2 = previousBipMap.find(nextStmtId);
	unordered_set<int> previousBipSet;

	if (it2 != previousBipMap.end()) {
		previousBipSet = it2->second;
		if (previousBipSet.find(nextStmtId) != previousBipSet.end()) {
			return false;
		}
		previousBipMap.erase(it2);
	}
	previousBipSet.insert(currentStmtId);
	previousBipMap.insert(make_pair(nextStmtId, previousBipSet));

	this->size++;
	return true;
}

unordered_set<int> NextBipTable::getNextBipStmt(int stmtId) {
	unordered_map<int, unordered_set<int>>::iterator it;
	unordered_set<int> nextBipSet;
	it = nextBipMap.find(stmtId);
	if (it != nextBipMap.end()) {
		return it->second;
	}
	else {
		return nextBipSet;
	}
}

unordered_set<int> NextBipTable::getPreviousBipStmt(int stmtId) {
	unordered_map<int, unordered_set<int>>::iterator it;
	unordered_set<int> previousBipSet;
	it = previousBipMap.find(stmtId);
	if (it != previousBipMap.end()) {
		return it->second;
	}
	else {
		return previousBipSet;
	}
}

void NextBipTable::printContents() {

	cout << "---PRINT NEXTBIPTABLE---" << endl;

	cout << "StmtId : Next bip stmtId" << endl;//can have more than one next
	for (pair<int, unordered_set<int>> it : nextBipMap) {
		cout << it.first << " : ";
		TableOperations::printUnorderedSet(it.second);
		cout << endl;
	}
	cout << endl;

	cout << "StmtId : previous bip stmtId" << endl;
	for (pair<int, unordered_set<int>> it : previousBipMap) {
		cout << it.first << " : ";
		TableOperations::printUnorderedSet(it.second);
		cout << endl;
	}
	cout << endl;

	cout << "---END PRINT NEXTTABLE---" << endl;

}