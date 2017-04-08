#pragma once

#include <vector>
#include <map>
#include <stack>

#include "PKB.h"
#include "Clause.h"
#include "ClauseType.h"
#include "Parameter.h"
#include "ResultTable.h"

using namespace std;

class Affects : public Clause {
public:
	Affects(Parameter lc, Parameter rc);

	vector<Parameter> getSynList();
	Parameter getLeftChild();
	Parameter getRightChild();
	ClauseType getClauseType();
	ResultTable evaluate(PKB* pkb, ResultTable intResultTable);

private:
	Parameter leftChild;
	Parameter rightChild;
	vector<Parameter> synList;
	bool hasFoundAllResult;

	void setSynToTable(ResultTable* pattResultTable);
	void setResultToTable(PKB* pkb, ResultTable* intResultTable, ResultTable* affectResultTable);

	void dfsToSetResultTable(PKB* pkb, ResultTable* intResultTable, ResultTable* affectResultTable, 
							unordered_set<int> validAffectorStmts, unordered_set<int> validAffectedStmts);
	void fowardDfs(PKB* pkb, ResultTable* affectResultTable, int procId, int startStmt, map<int, bool>* affectorStmts, map<int, bool>* affectedStmts);
	void reverseDfs(PKB* pkb, ResultTable* affectResultTable, int startStmt, map<int, bool>* affectorStmts, map<int, bool>* affectedStmts);

	unordered_set<int> getValidStmts(PKB* pkb, ResultTable* intResultTable, Parameter child);
	Type getStmtType(PKB* pkb, int initialStmt);
	bool mergeTable(unordered_map<int, unordered_set<int>>* merger, unordered_map<int, unordered_set<int>>* merged);
	bool isStmtValidResult(int affectorStmtId, map<int, bool>* validAffectorResults, int affectedStmtId, map<int, bool>* validAffectedResults);
	void setResultTupleToTable(ResultTable* affectResultTable, int affectorStmtId, int affectedStmtId);
};