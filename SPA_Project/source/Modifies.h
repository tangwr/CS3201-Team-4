#ifndef ModifiesH
#define ModifiesH

#include <string>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "VectorSetOperation.h"

using namespace std;

class Modifies : public Clause {
private:
	//ClauseType cltype;
	//string leftChild;
	//string rightChild;
	//Type leftChildType;
	//Type rightChildType;
	Parameter leftChild;
	Parameter rightChild;
	PKB *pkb;
	bool isRel;
	

public:

	//Modifies(string,Type, string, Type);
	Modifies(Parameter lc, Parameter rc);
	bool hasRel(PKB *pkb);
	vector<int> getWithRelToLeft(PKB *pkb);
	vector<int> getWithRelToRight(PKB *pkb);
	/*
	string getLeftChild();
	string getRightChild();
	Type getLeftChildType();
	Type getRightChildType();
	*/

	Parameter getLeftChild();
	Parameter getRightChild();

};
#endif
