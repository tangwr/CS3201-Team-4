#ifndef NextStarH
#define NextStarH

#include <string>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "unordered_set"
#include "ResultTable.h"

using namespace std;

class NextStar : public Clause {
private:
	Parameter leftChild;
	Parameter rightChild;
	vector<Parameter> synList;
	ResultTable result;
	bool isNumber(Parameter);
	bool isSynonym(Parameter);
	bool isValidStmtNo(int, PKB*);
	bool isStmtType(int, Parameter, PKB*);
	void getAllNextStar(int, unordered_set<int>, PKB*);
	void getAllPrevStar(int, unordered_set<int>, PKB*);
	vector<int> getTypeStmt(Type, PKB*);
	ResultTable getNextStarNumNum(PKB*);
	ResultTable getNextStarNumSyn(PKB*);
	ResultTable getNextStarSynNum(PKB*);
	ResultTable getNextStarSynSyn(PKB*);


public:
	NextStar(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	ResultTable execute(PKB*);
	void insertSynList(Parameter);
	vector<Parameter> getSynList();
	ClauseType getClauseType();
	ResultTable evaluate(PKB* pkb, ResultTable intResultTable);
};
#endif
