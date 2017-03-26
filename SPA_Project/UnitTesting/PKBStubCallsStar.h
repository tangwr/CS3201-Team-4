#pragma once

#include "PKB.h"

class PKBStubCallsStar : public PKB {
public:
	PKBStubCallsStar();

	unordered_set<int> getAllProcId();
	bool isProcInTable(string procName);
	int getProcIdByName(string procName);

	unordered_set<int> getProcCalledByStarProc(int callerProcId);

private:
	unordered_set<int> procId;
	unordered_set<string> procStmts;
	unordered_map<string, int> procIdTable;
	unordered_map<int, unordered_set<int>> procCallTable;

};