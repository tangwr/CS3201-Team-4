#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>

class QueryEvaluator {
private:
	std::string dummy = "unknown";

public:
	QueryEvaluator();
	std::list<std::string> evaluate();

};
