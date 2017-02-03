#ifndef ClauseH
#define ClauseH

#include <string>
#include <list>
#include "ClauseType.h"
#include "Type.h"
#include "PKB.h"
#include "QueryTree.h"

using namespace std;


class Clause {
public:
	virtual void evaluate(PKB) = 0;
	virtual bool hasRel(PKB);
};
#endif