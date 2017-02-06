#ifndef ParentStarH
#define ParentStarH

#include <string>
#include <unordered_set>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"

using namespace std;

class ParentStar : public Clause {
private:
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

public:

	ParentStar(string, Type, string, Type);
	vector<int> getWithRelToLeft(PKB *pkb);
	vector<int> getWithRelToRight(PKB *pkb);
	string getLeftChild();
	string getRightChild();
	Type getLeftChildType();
	Type getRightChildType();
	bool hasRel(PKB *pkb);

};
#endif
