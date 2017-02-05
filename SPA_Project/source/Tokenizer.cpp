#include "Tokenizer.h"

Tokenizer::Tokenizer(string source) {
	sourceStr = new string(source);
	tokenRe = new regex("([a-zA-Z][a-zA-Z0-9]*)|([;=\\+\\*\\-\\{\\}\\(\\)])|([0-9]+)|\\S+");
	rend = new regex_token_iterator<string::iterator>();
	tokenIter = new regex_token_iterator<string::iterator>(sourceStr->begin(), sourceStr->end(), *tokenRe);
}

string Tokenizer::getToken() {
	return *(*tokenIter)++;
}

bool Tokenizer::hasNextToken() {
	return *tokenIter != *rend;
}

Tokenizer::~Tokenizer() {
	delete sourceStr;
	delete tokenIter;
	delete rend;
}