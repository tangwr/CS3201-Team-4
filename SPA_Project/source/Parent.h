#ifndef ParentH
#define ParentH

#include <string>
#include <unordered_map>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "ResultTable.h"

using namespace std;

class Parent : public Clause {
private:
	Parameter leftChild;
	Parameter rightChild;
	ResultTable* result;
	bool isNumber(Parameter);
	bool isSynonym(Parameter);
	bool isValidStmtNo(int, PKB*);
	bool isStmtType(int, Parameter, PKB*);
	vector<int> getTypeStmt(Type, PKB*);
	ResultTable* getParentNumNum(PKB*);
	ResultTable* getParentNumSyn(PKB*);
	ResultTable* getParentSynNum(PKB*);
	ResultTable* getParentSynSyn(PKB*);
	/*
	string leftChild;
	string rightChild;
	Type leftChildType;
	Type rightChildType;
	PKB *pkb;
	bool isRel;
	vector<int> result, tempResult, left, right;
	bool isValidStmtNo(int, PKB*);
	vector<int> getAllChildren(vector<int>, PKB*);
	vector<int> getAllParents(vector<int>, PKB*);
	vector<int> filterType(vector<int>, Type, PKB*);
	bool isStmtType(int, Type, PKB*);
	vector<int> getTypeStmt(Type, PKB*);
	bool isNumber(Type);
	bool isSynonym(Type);
	*/

public:
	Parent(Parameter, Parameter);
	Parameter getLeftChild();
	Parameter getRightChild();
	ResultTable* execute(PKB*);
	/*
	Parent(string, Type, string, Type);
	bool hasRel(PKB *pkb);
	vector<int> getWithRelToLeft(PKB *pkb);
	vector<int> getWithRelToRight(PKB *pkb);
	string getLeftChild();
	string getRightChild();
	Type getLeftChildType();
	Type getRightChildType();
	ClauseType getClauseType();
	*/
};
#endif
