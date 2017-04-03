#include "CombinedStmtTable.h"

CombinedStmtTable::CombinedStmtTable() {
	this->size = 0;
}

bool CombinedStmtTable::insertStmt(int stmtId) {
	allStmtSet.insert(stmtId);
	size++;
	return true;
}

unordered_set<int> CombinedStmtTable::getAllStmtId() {
	return allStmtSet;
}

int CombinedStmtTable::getSize() {
	return size;
}