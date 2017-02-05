#ifndef ClauseH
#define ClauseH

#include <string>
#include <list>
#include <unordered_map>
#include "ClauseType.h"
#include "Type.h"
#include "PKB.h"

using namespace std;


class Clause {
public:
	virtual vector<int> getWithRelToLeft(PKB *pkb) = 0;
	virtual vector<int> getWithRelToRight(PKB *pkb);
	virtual bool hasRel(PKB *pkb);
	virtual string getLeftChild();
	virtual string getRightChild();
	virtual Type getLeftChildType();
	virtual Type getRightChildType();

};
#endif