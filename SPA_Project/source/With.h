#ifndef WithH
#define WithH

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
	void setBooleanToTable(ResultTable* withResultTable);

	unordered_set<int> getRightResultList(PKB* pkb, ResultTable* intResultTable, ResultTable* withResultTable);
	unordered_set<int> getLeftResultList(PKB* pkb, ResultTable* intResultTable, ResultTable* withResultTable);
	void assignResult(PKB* pkb, ResultTable* withResultTable, unordered_set<int> callStmts, unordered_set<int> procs);
	unordered_set<int> getSynResultList(PKB* pkb, Parameter parameter);
	void setResultTupleToTable(ResultTable* pattResultTable, int left, int right);
	int getIdOfString(PKB* pkb);
	string getStringOfId(PKB* pkb, int id);

public:
	With(Parameter lc, Parameter rc);
	ResultTable evaluate(PKB* pkb, ResultTable intResultTable);
	vector<Parameter> getSynList();
	Parameter getLeftChild();
	Parameter getRightChild();
	void insertSynList(Parameter p);
	ClauseType getClauseType();
};
#endif
