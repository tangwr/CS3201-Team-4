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
	bool isLeftChild(Parameter);
	bool isRightChild(Parameter);
	bool isValidStmtNo(int, PKB*);
	bool isStmtType(int, Parameter, PKB*);
	vector<int> getTypeStmt(Type, PKB*);
	ResultTable getNextNumNum(PKB*);
	ResultTable getNextNumSyn(PKB*);
	ResultTable getNextNumSyn(PKB*, vector<vector<int>>);
	ResultTable getNextSynNum(PKB*);
	ResultTable getNextSynNum(PKB*, vector<vector<int>>);
	ResultTable getNextSynSyn(PKB*);
	ResultTable getNextSynSyn(PKB*, vector<vector<int>>);


public:
	Next(Parameter lc, Parameter rc);
	ResultTable execute(PKB*);
	Parameter getLeftChild();
	Parameter getRightChild();
	void insertSynList(Parameter);
	vector<Parameter> getSynList();

};
#endif
