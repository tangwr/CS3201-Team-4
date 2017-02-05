#pragma once

#include <string>
#include <vector>
#include <stack>

#include "PKB.h"
#include "Tokenizer.h"

using namespace std;

typedef string stmt;

const string STRING_NAME = "([a-zA-Z][a-zA-Z0-9]*)";
const string STRING_DIGIT = "([0-9]+)";
const string STRING_OPERATOR = "([+\\-*])";

const string STRING_SEMICOLON = ";";
const string STRING_OPEN_CBRACKET = "\\{";
const string STRING_CLOSE_CBRACKET = "\\}";
const string STRING_OPEN_RBRACKET = "\\(";
const string STRING_CLOSE_RBRACKET = "\\)";
const string STRING_EQUAL = "=";
const string STRING_OR = "|";

const string STRING_PROC = "procedure";
const string STRING_IF = "if";
const string STRING_ELSE = "else";
const string STRING_WHILE = "while";
const string STRING_CALL = "call";

const int COMPARE_EQUAL = 0;

class Parser {
public:
	Parser(PKB *pkbSource, string source);
	void parse();

private:
	PKB *pkb;
	Tokenizer *tokenizer;
	string token;
	int stmtNum;

	void createProg();
	void createProc();
	void createStmtLst();
	void createStmtLst(int stmtId);
	void createStmt(int stmtId);
	void createWhile(int whileStmtId);
	void createAssign(int assignStmtId);
	int createVar(string varName);
	int createConst(int constValue);

	string createExpPrefix(int assignStmtId, stack<string> infix);
	stack<string> extractExp();

	void match(string matchRe);
};