#include "PrefixEvaluator.h"

const int COMPARE_EQUAL = 0;

const int WEIGHT_LOW = 0;
const int WEIGHT_MIDDLE = 1;
const int WEIGHT_HIGH = 2;

const string STRING_TIMES = "*";
const string STRING_DIVIDES = "/";
const string STRING_PLUS = "+";
const string STRING_MINUS = "-";

PrefixEvaluator::PrefixEvaluator() {}

stack<string> PrefixEvaluator::evaluatePrefix(stack<string> infix) {
	stack<string> prefix;
	stack<string> operators;
	string exp;

	while (!infix.empty()) {
		exp = infix.top();
		infix.pop();

		if (exp.compare(")") == COMPARE_EQUAL) {
			operators.push(exp);
			continue;
		}

		if (exp.compare("(") == COMPARE_EQUAL) {
			while (!operators.empty() && operators.top().compare(")") != COMPARE_EQUAL) {
				prefix.push(operators.top());
				operators.pop();
			}
			if (!operators.empty()) {
				operators.pop();
			}
			continue;
		}

		if (getWeight(exp) == WEIGHT_LOW) {
			prefix.push(exp);
		}
		else {
			while (!operators.empty() && operators.top().compare(")") != COMPARE_EQUAL &&
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
	if (exp.compare(STRING_TIMES) == COMPARE_EQUAL || exp.compare(STRING_DIVIDES) == COMPARE_EQUAL) {
		return WEIGHT_HIGH;
	}
	else if (exp.compare(STRING_PLUS) == COMPARE_EQUAL || exp.compare(STRING_MINUS) == COMPARE_EQUAL) {
		return WEIGHT_MIDDLE;
	}
	else {
		return WEIGHT_LOW;
	}
}