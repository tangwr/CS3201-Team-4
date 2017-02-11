#ifndef ClauseH
#define ClauseH

#include <string>
#include <list>
#include <unordered_map>
#include "Type.h"
#include "ClauseType.h"
#include "PKB.h"

using namespace std;


class Clause {
public:
	virtual vector<int> getWithRelToLeft(PKB *pkb) = 0;
	virtual vector<int> getWithRelToRight(PKB *pkb) = 0;
	virtual bool hasRel(PKB *pkb) = 0;
	virtual string getLeftChild() = 0;
	virtual string getRightChild() = 0;
	virtual Type getLeftChildType() = 0;
	virtual Type getRightChildType() = 0;
	virtual ClauseType getClauseType() = 0;
};
#endif