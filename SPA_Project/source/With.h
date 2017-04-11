#pragma once

#include <string>
#include <unordered_set>

#include "Clause.h"
#include "ClauseType.h"
#include "Type.h"
#include "PKB.h"
#include "ResultTable.h"

using namespace std;

class With : public Clause {
private:
	Parameter leftChild;
	Parameter rightChild;
	vector<Parameter> synList;

	void setSynToTable(ResultTable* withResultTable);
	void setResultToTable(PKB* pkb, ResultTable* intResultTable, ResultTable* withResultTable);

	void setBooleanResult(PKB* pkb, ResultTable* intResultTable, ResultTable* withResultTable);
	void setSynonymResult(PKB* pkb, ResultTable* intResultTable, ResultTable* withResultTable);
	void setMatchingTupleResult(PKB* pkb, ResultTable* intResultTable, ResultTable* withResultTable);

	unordered_set<int> getResultList(PKB* pkb, ResultTable* intResultTable, ResultTable* withResultTable, Parameter child, Parameter oppChild);
	void assignResult(PKB* pkb, ResultTable* withResultTable, unordered_set<int> callStmts, unordered_set<int> procs);
	unordered_set<int> getSynResultList(PKB* pkb, Parameter parameter);
	void setResultTupleToTable(ResultTable* pattResultTable, int left, int right);
	int getIdOfString(PKB* pkb, Parameter child, Type type);
	string getStringOfId(PKB* pkb, int id, Type type);

public:
	With(Parameter lc, Parameter rc);
	ResultTable evaluate(PKB* pkb, ResultTable intResultTable);
	vector<Parameter> getSynList();
	Parameter getLeftChild();
	Parameter getRightChild();
	void insertSynList(Parameter p);
	ClauseType getClauseType();
};
