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
	unordered_set<int> assignResult(PKB* pkb, unordered_set<int> callStmts, unordered_set<int> procs);
	unordered_set<int> getSynResultList(PKB* pkb, Parameter parameter);
	int getIdOfString(PKB* pkb);
	string getStringOfId(PKB* pkb, int id);
	unordered_set<int> getCallStmtWithCalledProcId(PKB* pkb, unordered_set<int> callStmts, unordered_set<int> procs);

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
