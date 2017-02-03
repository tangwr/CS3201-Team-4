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
	virtual list<string> evaluate(PKB *pkb, unordered_map<string, Type> select) = 0;
	virtual bool hasRel(PKB *pkb);
};
#endif