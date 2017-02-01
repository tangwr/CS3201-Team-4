#pragma once

#include <string>

using namespace std;

class Controller {
public:
	Controller();
	void processSource(string);
	string processQuery(string);
};