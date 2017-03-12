#ifndef NextH
#define NextH

#include <string>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "unordered_set"
#include "ResultTable.h"

using namespace std;

class Next : public Clause {
private:
	Parameter leftChild;
	Parameter rightChild;
	ResultTable result;
	vector<Parameter> synList;
	bool isNumber(Parameter);
	bool isSynonym(Parameter);
	bool isNext(PKB*, int, int);
	bool isValidStmtNo(int, PKB*);
	unordered_set<int> getTypeStmt(Type, PKB*);
	ResultTable getNextNumNum(PKB*, int, int);
	ResultTable getNextNumSyn(PKB*, unordered_set<int>, int);
	ResultTable getNextSynNum(PKB*, unordered_set<int>, int);
	ResultTable getNextSynSyn(PKB*, unordered_set<int>, unordered_set<int>);
	ResultTable getNextSynSyn(PKB*, ResultTable*);


public:
	Next(Parameter lc, Parameter rc);
	ResultTable evaluate(PKB*);
	ResultTable evaluate(PKB*, ResultTable*);
	Parameter getLeftChild();
	Parameter getRightChild();
	void insertSynList(Parameter);
	vector<Parameter> getSynList();

};
#endif
