#pragma once

#include <string>
#include <vector>
#include <stack>

#include "PKB.h"
#include "Tokenizer.h"

using namespace std;

typedef string stmt;

class Parser {
public:
	Parser(PKB *pkb, string source);
	~Parser();
	void parse();

private:
	const string STRING_NAME = "([a-zA-Z][a-zA-Z0-9]*)";
	const string STRING_DIGIT = "([0-9]+)";
	const string STRING_OPERATOR = "([+\\-*])";

	const string STRING_SEMICOLON = ";";
	const string STRING_OPEN_BRACKET = "\\{";
	const string STRING_CLOSE_BRACKET = "\\}";
	const string STRING_EQUAL = "=";
	const string STRING_OR = "|";

	const string STRING_PROC = "procedure";
	const string STRING_IF = "if";
	const string STRING_ELSE = "else";
	const string STRING_WHILE = "while";
	const string STRING_CALL = "call";

	const int COMPARE_EQUAL = 0;

	PKB *pkb;
	Tokenizer *tokenizer;
	string token;
	int stmtNum;

	void createProg();
	void createProc();
	void createStmtLst();
	void createStmt();
	void createWhile();
	void createAssign();
	void createExp(stack<string>* prefix);
	void createOper(stack<string>* prefix);
	void createVar(string varName);
	void createConst(int constValue);
	stack<string> extractExp();
	void match(string matchRe);
	string getString(stack<string> stk);
	/*
	void splitProgLine(string&, vector<stmt>&);
	string trimFront(string&, int, int);
	void createAST(vector<stmt>&);
	*/
};