#include "ExpOperation.h"
#include "Tokenizer.h"

const int COMPARE_EQUAL = 0;

const int WEIGHT_LOW = 0;
const int WEIGHT_MIDDLE = 1;
const int WEIGHT_HIGH = 2;

const string STRING_TIMES = "*";
const string STRING_DIVIDES = "/";
const string STRING_PLUS = "+";
const string STRING_MINUS = "-";

const string STRING_NAME = "([a-zA-Z][a-zA-Z0-9]*)";
const string STRING_INTEGER = "([0-9]+)";
const string STRING_OPERATOR = "([+\\-*])";
const string STRING_OPEN_RBRACKET = "\\(";
const string STRING_CLOSE_RBRACKET = "\\)";

const string STRING_OR = "|";

stack<string> ExpOperation::evaluatePrefix(string infixString) {
	Tokenizer tokenizer(infixString);
	stack<string> infix;
	while (tokenizer.hasNextToken()) {
		infix.push(tokenizer.getToken());
	}

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

bool ExpOperation::isValidExp(string exp) {
	Tokenizer tokenizer(exp);
	int bracketCount = 0;

	string token = tokenizer.getToken();
	string prevToken;

	if (!tokenizer.match(token, STRING_NAME + STRING_OR + STRING_INTEGER + STRING_OR + STRING_OPEN_RBRACKET)) {
		return false;
	}

	while (tokenizer.hasNextToken()) {
		prevToken = token;
		token = tokenizer.getToken();

		if (tokenizer.match(prevToken, STRING_OPERATOR + STRING_OR + STRING_OPEN_RBRACKET)) {
			if (tokenizer.match(prevToken, STRING_OPEN_RBRACKET)) {
				bracketCount++;
			}
			if (!tokenizer.match(token, STRING_NAME + STRING_OR + STRING_INTEGER + STRING_OR + STRING_OPEN_RBRACKET)) {
				return false;
			}
		}
		else if (tokenizer.match(prevToken, STRING_NAME + STRING_OR + STRING_INTEGER + STRING_OR + STRING_CLOSE_RBRACKET)) {
			if (!tokenizer.match(token, STRING_OPERATOR + STRING_OR + STRING_CLOSE_RBRACKET)) {
				return false;
			}
			if (tokenizer.match(token, STRING_CLOSE_RBRACKET)) {
				bracketCount--;
				if (bracketCount < 0) {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}

	if (!tokenizer.match(token, STRING_NAME + STRING_OR + STRING_INTEGER + STRING_OR + STRING_CLOSE_RBRACKET)) {
		return false;
	}

	return true;
}


int ExpOperation::getWeight(string exp) {
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