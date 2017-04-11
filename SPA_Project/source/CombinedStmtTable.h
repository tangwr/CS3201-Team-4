#pragma once

#include <unordered_set>

using namespace std;

class CombinedStmtTable{

public:
	CombinedStmtTable();
	bool insertStmt(int stmtId);
	unordered_set<int> getAllStmtId();
	int getSize();

private:
	unordered_set<int> allStmtSet;
	int size;


};