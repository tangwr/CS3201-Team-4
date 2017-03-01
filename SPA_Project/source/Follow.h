#ifndef FollowH
#define FollowH

#include <string>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "ResultTable.h"

using namespace std;

class Follow : public Clause {
private:

	Parameter leftChild;
	Parameter rightChild;
	ResultTable* result;
	bool isNumber(Parameter);
	bool isSynonym(Parameter);
	bool isValidStmtNo(int, PKB*);
	bool isStmtType(int, Parameter, PKB*);
	vector<int> getTypeStmt(Type, PKB*);
	ResultTable* getFollowNumNum(PKB*);
	ResultTable* getFollowNumSyn(PKB*);
	ResultTable* getFollowSynNum(PKB*);
	ResultTable* getFollowSynSyn(PKB*);
	vector<Parameter> synList;
	/*
	string leftChild;
	string rightChild;
	Type leftChildType;
	Type rightChildType;
	PKB *pkb;
	bool isRel;
	vector<int> result, tempResult, left, right;
	bool isValidStmtNo(int, PKB*);
	vector<int> getAllFollows(vector<int>, PKB*);
	vector<int> getAllFollowedBy(vector<int>, PKB*);
	vector<int> filterType(vector<int>, Type, PKB*);
	bool isStmtType(int, Type, PKB*);
	vector<int> getTypeStmt(Type, PKB*);
	vector<int> getWithRelToRightNumSyn(PKB*);
	vector<int> getWithRelToRightSynSyn(PKB*);
	vector<int> getWithRelToLeftSynNum(PKB*);
	vector<int> getWithRelToLeftSynSyn(PKB*);
	bool hasRelSynNum(PKB*);
	bool hasRelSynSyn(PKB*);
	bool hasRelNumNum(PKB*, int);
	bool hasRelNumSyn(PKB*, int);
	bool isNumber(Type);
	bool isSynonym(Type);*/

public:
	Follow(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	vector<Parameter> getSynList();
	ResultTable* execute(PKB*);
	/*

	Follow(string, Type, string, Type);
	vector<int> getWithRelToLeft(PKB *pkb);
	vector<int> getWithRelToRight(PKB *pkb);
	string getLeftChild();
	string getRightChild();
	Type getLeftChildType();
	Type getRightChildType();
	bool hasRel(PKB *pkb);
	*/
};
#endif
