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