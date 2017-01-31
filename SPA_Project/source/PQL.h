#pragma once
#include <string>
#include <list>

using namespace std;

#include "QueryTree.h"

class PQL {
public:
	QueryTree getQuery(String query);
	std::list<string> evaluate(QueryTree qt);
	std::list<string> getResult(std::list<string> rs);
}


#pragma once
