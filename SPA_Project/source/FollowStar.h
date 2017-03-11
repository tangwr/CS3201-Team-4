#ifndef FollowStarH
#define FollowStarH

#include <string>
#include <unordered_set>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "ResultTable.h"

using namespace std;

class FollowStar : public Clause {
private:

	Parameter leftChild;
	Parameter rightChild;
	ResultTable result;
	bool isNumber(Parameter);
	bool isSynonym(Parameter);
	bool isValidStmtNo(int, PKB*);
	bool isFollowStar(PKB*, int, int);
	bool isLeftChild(Parameter);
	bool isStmtType(int, Parameter, PKB*);
	ResultTable getAllFollowsStar(vector<int>, PKB*);
	ResultTable getAllFollowedByStar(vector<int>, PKB*);

	unordered_set<int> getTypeStmt(Type, PKB*);
	ResultTable getFollowStarNumNum(PKB*, int, int);
	ResultTable getFollowStarNumSyn(PKB*, unordered_set<int>, int);
	ResultTable getFollowStarSynNum(PKB*, unordered_set<int>, int);
	ResultTable getFollowStarSynSyn(PKB*, unordered_set<int>, unordered_set<int>);
	ResultTable getFollowStarSynSyn(PKB*, ResultTable*);

	ResultTable getFollowStar(PKB*, unordered_set<int>, unordered_set<int>);
	vector<Parameter> synList;
	/*
	string leftChild;
	string rightChild;
	Type leftChildType;
	Type rightChildType;
	PKB *pkb;
	bool isRel;

	vector<int> result, left, right;
	unordered_set<int> tempResult;
	bool isValidStmtNo(int, PKB*);
	unordered_set<int> getAllFollowsStar(vector<int>, PKB*);
	unordered_set<int> getAllFollowedByStar(vector<int>, PKB*);
	vector<int> filterType(unordered_set<int>, Type, PKB*);
	bool isStmtType(int, Type, PKB*);
	vector<int> getTypeStmt(Type, PKB*);
	bool isNumber(Type);
	bool isSynonym(Type);
	*/

public:

	FollowStar(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	ResultTable evaluate(PKB*);
	ResultTable evaluate(PKB*, ResultTable*);
	void insertSynList(Parameter);
	vector<Parameter> getSynList();
	/*
	FollowStar(string, Type, string, Type);
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
