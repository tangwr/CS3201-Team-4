#ifndef FollowStarH
#define FollowStarH

#include <string>
#include <unordered_set>
#include "Clause.h"
//#include "ClauseType.h"
#include "Type.h"
#include "PKB.h"

using namespace std;

class FollowStar : public Clause {
private:
	//ClauseType cltype;
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

public:

	FollowStar(string, Type, string, Type);
	bool hasRel(PKB *pkb);
	vector<int> getWithRelToLeft(PKB *pkb);
	vector<int> getWithRelToRight(PKB *pkb);
	string getLeftChild();
	string getRightChild();
	Type getLeftChildType();
	Type getRightChildType();

};
#endif
