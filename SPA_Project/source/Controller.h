#pragma once

#include <string>
#include <list>

#include "PKB.h"
#include "PQL.h"

using namespace std;

class Controller {
public:
	Controller();
	void processSource(string);
	list<string> processQuery(string);
	~Controller();

	PKB *pkb;
	PQL *pql;
};