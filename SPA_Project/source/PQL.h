#pragma once
#include <string>
#include <list>

using namespace std;

#include "QueryTree.h"
#include "PKB.h"

class PQL {
private:
	PKB *pkb;
public:
	PQL(PKB *pkb);
	QueryTree getQuery(string query);
	std::list<string> evaluate(QueryTree qt);
	std::list<string> getResult(std::list<string> rs);
}


#pragma once