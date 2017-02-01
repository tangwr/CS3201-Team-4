#pragma once

#include <string>
#include <sstream>
#include <regex>

using namespace std;

class Tokenizer {
public:
	Tokenizer(string source);
	~Tokenizer();
	string getToken();
	bool hasNextToken();

private:
	string *sourceStr;
	regex *tokenRe;
	regex_token_iterator<string::iterator> *tokenIter;
	regex_token_iterator<string::iterator> *rend;
};