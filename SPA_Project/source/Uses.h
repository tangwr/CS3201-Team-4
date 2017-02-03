#ifndef UsesH
#define UsesH

#include <string>
#include <unordered_map>
#include "Clause.h"
#include "ClauseType.h"
#include "Type.h"
#include "PKB.h"

using namespace std;

class Uses : public Clause {
private:
	ClauseType cltype;
	string leftChild;
	string rightChild;
	Type leftChildType;
	Type rightChildType;
	PKB *pkb;
	bool isRel;

public:

	Uses(string, string, Type, Type);
	list<string> evaluate(PKB *pkb, unordered_map<string, Type> select);
	bool hasRel(PKB *pkb);

};
#endif