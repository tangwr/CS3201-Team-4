#pragma once

#include <string>
#include <queue>

#include <stack>

using namespace std;

class PrefixEvaluator {
public:
	PrefixEvaluator();
	stack<string> evaluatePrefix(stack<string> infix);

private:
	int getWeight(string exp);
};