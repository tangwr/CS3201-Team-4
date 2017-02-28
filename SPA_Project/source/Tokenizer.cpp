#include "Tokenizer.h"

Tokenizer::Tokenizer(string source) {
	sourceStr = new string(source);
	tokenRe = new regex("([a-zA-Z][a-zA-Z0-9]*)|([;=\\+\\*\\-\\{\\}\\(\\)<>\\,\\\"#_])|([0-9]+)|\\S+");
	rend = new regex_token_iterator<string::iterator>();
	tokenIter = new regex_token_iterator<string::iterator>(sourceStr->begin(), sourceStr->end(), *tokenRe);
}

string Tokenizer::peekToken() {
	if (hasNextToken()) {
		return *(*tokenIter);
	}
	else {
		return "";
	}
}

string Tokenizer::getToken() {
	if (hasNextToken()) {
		return *(*tokenIter)++;
	}
	else {
		return "";
	}
}

bool Tokenizer::hasNextToken() {
	return *tokenIter != *rend;
}

bool Tokenizer::match(string token, string matchRe) {
	if (regex_match(token, regex(matchRe))) {
		return true;
	}
	return false;
}

Tokenizer::~Tokenizer() {
	delete sourceStr;
	delete tokenIter;
	delete rend;
}