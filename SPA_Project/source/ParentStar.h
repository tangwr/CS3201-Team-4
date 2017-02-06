#ifndef ParentStarH
#define ParentStarH

#include <string>
#include "Clause.h"
//#include "ClauseType.h"
#include "Type.h"
#include "PKB.h"

using namespace std;

class ParentStar : public Clause {
private:
	//ClauseType cltype;
	string leftChild;
	string rightChild;
	Type leftChildType;
	Type rightChildType;
	PKB *pkb;
	bool isRel;

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