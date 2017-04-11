#ifndef PatternH
#define PatternH

#include <string>
#include <unordered_set>

#include "Clause.h"
#include "ClauseType.h"
#include "Type.h"
#include "PKB.h"
#include "ResultTable.h"

using namespace std;

class Pattern : public Clause {
public:
	Pattern(Parameter lc, Parameter rc, Parameter factor, bool isSubExp);
	ResultTable evaluate(PKB* pkb, ResultTable intResultTable);

	void setUnderScore(bool);
	void setFactor(Parameter factor);

	bool getUnderScore();
	Parameter getFactor();
	vector<Parameter> getSynList();
	ClauseType getClauseType();

private:
	Parameter leftChild;
	Parameter rightChild;
	Parameter factor;
	bool hasUnderScore;
	vector<Parameter> synList;
	string prefix;

	void setSynToTable(ResultTable* pattResultTable);
	void setResultToTable(PKB* pkb, ResultTable* intResultTable, ResultTable* pattResultTable);

	void setStmtsFromVars(PKB* pkb, ResultTable* pattResultTable, unordered_set<int> vars);
	void setVarsFromStmts(PKB* pkb, ResultTable* pattResultTable, unordered_set<int> stmts);
	void matchTuplePattern(PKB* pkb, ResultTable* intResultTable, ResultTable* pattResultTable);
	void setResultTupleToTable(PKB* pkb, ResultTable* pattResultTable, int stmtId, int varId);

	unordered_set<int> getStmtsWithVar(PKB* pkb, int varId);
	int getVarWithStmt(PKB* pkb, int stmtId);
	unordered_set<int> getVars(PKB* pkb);

	bool hasPattern(PKB* pkb, int assignStmtId);
	bool isValidStmtType(PKB* pkb, int stmtId);
	string getPrefix(string infixString);
};
#endif
