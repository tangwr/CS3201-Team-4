#pragma once

#include <string>
#include <sstream>
#include <regex>

using namespace std;

class Tokenizer {
public:
	Tokenizer(string source);
	~Tokenizer();
	string peekToken();
	string getToken();
	bool hasNextToken();
	bool match(string token, string matchRe);

private:
	string *sourceStr;
	regex *tokenRe;
	regex_token_iterator<string::iterator> *tokenIter;
	regex_token_iterator<string::iterator> *rend;
};