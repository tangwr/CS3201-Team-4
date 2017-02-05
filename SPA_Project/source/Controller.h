#pragma once

#include <string>

#include "PKB.h"

using namespace std;

class Controller {
public:
	Controller();
	void processSource(string);
	string processQuery(string);
	PKB *pkb;
};