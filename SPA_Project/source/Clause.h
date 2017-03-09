#ifndef ClauseH
#define ClauseH

#include <string>
#include <list>
#include <unordered_map>
#include "Type.h"
#include "PKB.h"
#include "Parameter.h"
using namespace std;


class Clause {
public:
	virtual vector<int> getWithRelToLeft(PKB *pkb) = 0;
	virtual vector<int> getWithRelToRight(PKB *pkb) = 0;
	virtual vector<Parameter> getSynList() = 0;
	virtual bool hasRel(PKB *pkb) = 0;
	virtual Parameter getLeftChild() = 0;
	virtual Parameter getRightChild() = 0;
        virtual ClauseType getType() = 0;
	/*
	virtual string getLeftChild() = 0;
	virtual string getRightChild() = 0;
	virtual Type getLeftChildType() = 0;
	virtual Type getRightChildType() = 0;
	*/

};
#endif
