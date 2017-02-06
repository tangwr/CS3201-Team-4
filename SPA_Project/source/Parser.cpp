#include <algorithm>
#include <iostream>

#include "Parser.h"
#include "PrefixEvaluator.h"

const string STRING_NAME = "([a-zA-Z][a-zA-Z0-9]*)";
const string STRING_DIGIT = "([0-9]+)";
const string STRING_OPERATOR = "([+\\-*])";

const string STRING_SEMICOLON = ";";
const string STRING_OPEN_CBRACKET = "\\{";
const string STRING_CLOSE_CBRACKET = "\\}";
const string STRING_OPEN_RBRACKET = "\\(";
const string STRING_CLOSE_RBRACKET = "\\)";
const string STRING_CLOSE_BRACKET = "}";
const string STRING_EQUAL = "=";
const string STRING_OR = "|";
const string STRING_EMPTY = "";

const string STRING_PROC = "procedure";
const string STRING_IF = "if";
const string STRING_ELSE = "else";
const string STRING_WHILE = "while";
const string STRING_CALL = "call";

const string ERROR_MESSAGE = "Error found in SIMPLE source code during parsing.";

const int COMPARE_EQUAL = 0;
const int START_COUNT_INDEX = 1;


Parser::Parser(PKB *pkbSource, string source) {
	tokenizer = new Tokenizer(source);
	pkb = pkbSource;
	stmtNum = START_COUNT_INDEX;
}

void Parser::parse() {
	createProg();
}

void Parser::createProg() {
	token = tokenizer->getToken();

	while (token.compare(STRING_PROC) == COMPARE_EQUAL) {
		createProc();
	}
}

void Parser::createProc() {
	match(STRING_PROC);

	string procName = token;

	match(STRING_NAME);
	
	pkb->insertProc(procName);

	match(STRING_OPEN_CBRACKET);

	createStmtLst();

	match(STRING_CLOSE_CBRACKET);
}

void Parser::createStmtLst() {
	vector<int> stmts;

	do {
		stmts.push_back(stmtNum);
		createStmt(stmtNum++);
	} while (token.compare(STRING_CLOSE_BRACKET) != COMPARE_EQUAL);

	for (int index = 1; index < (int) stmts.size(); index++) {
		pkb->setFollowDirectRel(stmts[index - 1], stmts[index]);
	}
}

void Parser::createStmtLst(int stmtId) {
	vector<int> stmts;

	do {
		stmts.push_back(stmtNum);
		createStmt(stmtNum++);
	} while (token.compare(STRING_CLOSE_BRACKET) != COMPARE_EQUAL);

	pkb->setParentDirectRel(stmtId, stmts[0]);
	for (int index = 1; index < (int) stmts.size(); index++) {
		pkb->setFollowDirectRel(stmts[index - 1], stmts[index]);
		pkb->setParentDirectRel(stmtId, stmts[index]);
	}
}

void Parser::createStmt(int stmtId) {
	string stmtType = token;
	
	if (stmtType.compare(STRING_WHILE) == COMPARE_EQUAL) {
		createWhile(stmtId);
	} else if (stmtType.compare(STRING_IF) == COMPARE_EQUAL) {
		//createIf();
	} else if (stmtType.compare(STRING_CALL) == COMPARE_EQUAL) {
		//createCall();
	} else {
		createAssign(stmtId);
	}
}

void Parser::createWhile(int whileStmtId) {
	match(STRING_WHILE);

	string varName = token;

	match(STRING_NAME);

	int varId = createVar(varName);
	pkb->setWhileCtrlVar(whileStmtId, varId);
	pkb->setStmtUseRel(whileStmtId, varId);

	match(STRING_OPEN_CBRACKET);

	createStmtLst(whileStmtId);

	match(STRING_CLOSE_CBRACKET);
}

void Parser::createAssign(int assignStmtId) {
	string varName = token;

	match(STRING_NAME);

	int varId = createVar(varName);
	
	pkb->setStmtModifyRel(assignStmtId, varId);

	match(STRING_EQUAL);

	stack<string> infix = extractExp();
	string prefix = createExpPrefix(assignStmtId, infix);

	pkb->setAssignExp(assignStmtId, prefix);

	match(STRING_SEMICOLON);
}

stack<string> Parser::extractExp() {
	stack<string> infix;

	do {
		string exp = token;
		match(STRING_NAME + STRING_OR + STRING_DIGIT + STRING_OR + STRING_OPERATOR + STRING_OR + STRING_OPEN_RBRACKET + STRING_OR + STRING_CLOSE_RBRACKET);
		infix.push(exp);
	} while (token.compare(STRING_SEMICOLON) != COMPARE_EQUAL);

	return infix;
}

string Parser::createExpPrefix(int assignStmtId, stack<string> infix) {
	PrefixEvaluator prefixEval;
	stack<string> prefix = prefixEval.evaluatePrefix(infix);

	string expStr;
	string expWord;

	while (!prefix.empty()) {
		expWord = prefix.top();
		expStr += prefix.top();
		prefix.pop();

		if (regex_match(expWord, regex(STRING_NAME))) {
			int varId = createVar(expWord);
			pkb->setStmtUseRel(assignStmtId, varId);
		}
		else if (regex_match(expWord, regex(STRING_DIGIT))) {
			int constId = createConst(atoi(expWord.c_str()));
			pkb->setStmtUseRelConst(assignStmtId, constId);
		}
	}
	return expStr;
}

int Parser::createVar(string varName) {
	return pkb->insertVar(varName);
}

int Parser::createConst(int constValue) {
	return pkb->insertConst(constValue);
}

void Parser::match(string matchRe) {
	if (regex_match(token, regex(matchRe))) {
		if (tokenizer->hasNextToken()) {
			token = tokenizer->getToken();
		}
		else {
			token = STRING_EMPTY;
		}
	} else {
		cout << ERROR_MESSAGE << endl;
		exit(0);
	}
}