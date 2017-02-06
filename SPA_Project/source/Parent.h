#ifndef ParentH
#define ParentH

#include <string>
#include <unordered_map>
#include "Clause.h"
//#include "ClauseType.h"
#include "Type.h"
#include "PKB.h"

using namespace std;

class Parent : public Clause {
private:
	//ClauseType cltype;
	string leftChild;
	string rightChild;
	Type leftChildType;
	Type rightChildType;
	PKB *pkb;
	bool isRel;

public:

	Parent(string, Type, string, Type);
	bool hasRel(PKB *pkb);
	vector<int> getWithRelToLeft(PKB *pkb);
	vector<int> getWithRelToRight(PKB *pkb);
	string getLeftChild();
	string getRightChild();
	Type getLeftChildType();
	Type getRightChildType();

};
#endif