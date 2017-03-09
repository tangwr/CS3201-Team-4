#pragma once

#include <string>
#include <vector>
#include <stack>
#include <tuple>
#include <unordered_set>
#include <unordered_map>

#include "PKB.h"
#include "Tokenizer.h"

using namespace std;

typedef string stmt;

class Parser {
public:
	Parser(PKB *pkbSource, string source);
	~Parser();
	void parse();

private:
	PKB *pkb;
	Tokenizer *tokenizer;
	string token;
	int curStmtNum;
	vector<tuple<int, int, string>> callTuples;

	void createProg();
	void createProc();
	pair<int, vector<int>> createStmtLst(int procId, int contId);
	vector<int> createStmt(int procId, int stmtId);
	void createWhile(int procId, int whileStmtId);
	vector<int> createIf(int procId, int ifStmtId);
	void createCall(int procId, int callStmtId);
	void createAssign(int procId, int assignStmtId);
	int createVar(string varName);
	int createConst(int constValue);
	void setProcAndStmtCallRel();

	string extractExp();
	string createExpPrefix(int assignStmtId, string infix);
	void match(string matchRe);
};