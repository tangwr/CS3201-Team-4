#ifndef FollowH
#define FollowH

#include <string>
#include "Clause.h"
#include "ClauseType.h"
#include "Type.h"
#include "PKB.h"

using namespace std;

class Follow : public Clause {
private:
	ClauseType cltype;
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
	bool isNumber(Type);
	bool isSynonym(Type);

public:

	Follow(string, Type, string, Type);
	vector<int> getWithRelToLeft(PKB *pkb);
	vector<int> getWithRelToRight(PKB *pkb);
	string getLeftChild();
	string getRightChild();
	Type getLeftChildType();
	Type getRightChildType();
	bool hasRel(PKB *pkb);

};
#endif
