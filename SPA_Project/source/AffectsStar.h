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

class AffectsStar : public Clause {
public:
	AffectsStar(Parameter lc, Parameter rc);

	vector<Parameter> getSynList();
	Parameter getLeftChild();
	Parameter getRightChild();
	ClauseType getClauseType();
	ResultTable evaluate(PKB* pkb, ResultTable intResultTable);

private:
	class Hasher {
	public:
		size_t operator()(const unordered_map<int, int> &hashElement) const {
			size_t key = 0;
			for (auto iter : hashElement) {
				key ^= hash<int>()(iter.first);
			}
			return key;
		}

		size_t operator()(const unordered_map<int, unordered_set<int>> &hashElement) const {
			size_t key = 0;
			for (auto iter : hashElement) {
				key ^= hash<int>()(iter.first * iter.second.size());
			}
			return key;
		}
	};

	Parameter leftChild;
	Parameter rightChild;
	vector<Parameter> synList;

	bool hasFoundAllResult;
	unordered_map<int, unordered_set<unordered_map<int, unordered_set<int>>, Hasher>> whileTableStack;
	unordered_map<int, unordered_set<unordered_map<int, unordered_set<int>>, Hasher>> contTableStack;

	void setSynToTable(ResultTable* pattResultTable);
	void setResultToTable(PKB* pkb, ResultTable* intResultTable, ResultTable* affectResultTable);
	void setBooleanToTable(ResultTable* pattResultTable);

	void dfsToSetResultTable(PKB* pkb, ResultTable* intResultTable, ResultTable* affectResultTable,
								unordered_set<int> validAffectorStmts, unordered_set<int> validAffectedStmts);
	void fowardDfs(PKB* pkb, ResultTable* affectResultTable, int curStmt,
					map<int, bool>* affectorStmts, unordered_map<int, unordered_set<int>>* modifiedVarToStmt, map<int, bool>* affectedStmts);
	void reverseDfs(PKB* pkb, ResultTable* affectResultTable, int curStmt,
					map<int, bool>* affectorStmts, unordered_map<int, unordered_set<int>>* usedVarToStmt, map<int, bool >* affectedStmts);

	unordered_set<int> getValidStmts(PKB* pkb, ResultTable* intResultTable, Parameter child);
	Type getStmtType(PKB* pkb, int initialStmt);
	bool isStmtValidResult(int affectorStmtId, map<int, bool>* validAffectorResults, int affectedStmtId, map<int, bool>* validAffectedResults);
	void setResultTupleToTable(ResultTable* affectResultTable, int affectorStmtId, int affectedStmtId);
};