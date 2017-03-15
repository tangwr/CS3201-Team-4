#pragma once

#include <string>
#include <stack>

using namespace std;

class ExpOperation {
public:
	static stack<string> evaluatePrefix(stack<string> infix);
	static bool isValidExp(string exp);

private:
	static int getWeight(string exp);
};