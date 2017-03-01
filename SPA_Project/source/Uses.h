#ifndef UsesH
#define UsesH

#include <string>
#include <unordered_map>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "VectorSetOperation.h"

using namespace std;

class Uses : public Clause {
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

	//Uses(string, Type, string, Type);
	Uses(Parameter lc, Parameter rc);
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
