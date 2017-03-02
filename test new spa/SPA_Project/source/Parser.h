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
	vector<pair<int, string>> callProcs;

	void createProg();
	void createProc();
	void createStmtLst(int procId);
	void createStmtLst(int procId, int stmtId);
	void createStmt(int procId, int stmtId);
	void createWhile(int procId, int whileStmtId);
	void createIf(int procId, int ifStmtId);
	void createCall(int callStmtId);
	void createAssign(int assignStmtId);
	int createVar(string varName);
	int createConst(int constValue);
	void populateCall();

	string createExpPrefix(int assignStmtId, stack<string> infix);
	stack<string> extractExp();

	void match(string matchRe);
};