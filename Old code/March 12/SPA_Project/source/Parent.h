#ifndef ParentH
#define ParentH

#include <string>
#include <unordered_map>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"

using namespace std;

class Parent : public Clause {
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

	Parent(string, Type, string, Type);
	bool hasRel(PKB *pkb);
	vector<int> getWithRelToLeft(PKB *pkb);
	vector<int> getWithRelToRight(PKB *pkb);
	//string getLeftChild();
	//string getRightChild();
	Type getLeftChildType();
	Type getRightChildType();
	//ClauseType getClauseType();

};
#endif
