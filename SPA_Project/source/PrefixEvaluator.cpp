#include "PrefixEvaluator.h"

PrefixEvaluator::PrefixEvaluator() {}

stack<string> PrefixEvaluator::evaluatePrefix(stack<string> infix) {
	stack<string> prefix;
	stack<string> operators;
	string exp;

	while (!infix.empty()) {
		exp = infix.top();
		infix.pop();

		if (exp.compare(")") == 0) {
			operators.push(exp);
			continue;
		}

		if (exp.compare("(") == 0) {
			while (!operators.empty() && operators.top().compare(")") != 0) {
				prefix.push(operators.top());
				operators.pop();
			}
			if (!operators.empty()) {
				operators.pop();
			}
			continue;
		}

		if (getWeight(exp) == 0) {
			prefix.push(exp);
		}
		else {
			while (!operators.empty() && operators.top().compare(")") != 0 &&
				getWeight(exp) < getWeight(operators.top())) {
				prefix.push(operators.top());
				operators.pop();
			}
			operators.push(exp);
		}
	}
	while (!operators.empty()) {
		prefix.push(operators.top());
		operators.pop();
	}

	return prefix;
}

int PrefixEvaluator::getWeight(string exp) {
	if (exp.compare("*") == 0 || exp.compare("/") == 0) {
		return 2;
	}
	else if (exp.compare("+") == 0 || exp.compare("-") == 0) {
		return 1;
	}
	else {
		return 0;
	}
}