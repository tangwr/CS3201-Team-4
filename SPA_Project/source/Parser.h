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

/**
* The parser is used to validate that the source is syntactically correct 
* and populate the direct relationships into the PKB.
*/
class Parser {
public:
	/**
	* Takes in the source code in string to set the relavant information into the PKB.
	*
	* @param pkbSource    the PKB object to store the information
	* @param source       string form of the source code
	*/
	Parser(PKB *pkbSource, string source);
	~Parser();

	/**
	* Process the given source and set the relavant information into the PKB.
	* Exception will be thrown if there is error found in source code
	*
	* @throws Exception    if there is error found during parsing
	*/
	void parse();

private:
	PKB *pkb;
	Tokenizer *tokenizer;
	string token;
	int curStmtNum;
	int curDummyStmtNum;
	unordered_set<int> procInSource;
	unordered_set<string> keyWords;

	void createProg();
	void createProc();
	int createStmtLst(int procId, int contId);
	int createStmt(int procId, int stmtId);
	int createWhile(int procId, int whileStmtId);
	int createIf(int procId, int ifStmtId);
	int createCall(int procId, int callStmtId);
	int createAssign(int procId, int assignStmtId);
	int createVar(string varName);
	int createConst(int constValue);
	void ensureAllCalledProcExisted();

	string extractExp();
	string createExpPrefix(int assignStmtId, string infix);
	void match(string matchRe);
	void misMatch(string matchRe);
};