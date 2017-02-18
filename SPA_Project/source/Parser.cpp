#include <algorithm>
#include <iostream>

#include "Parser.h"
#include "ExpOperation.h"

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
const string STRING_THEN = "then";
const string STRING_ELSE = "else";
const string STRING_WHILE = "while";
const string STRING_CALL = "call";

const string ERROR_MESSAGE = "Error found in SIMPLE source code during parsing.";

const int COMPARE_EQUAL = 0;
const int INITAL_INDEX = 0;
const int START_COUNT_INDEX = 1;


Parser::Parser(PKB *pkbSource, string source) {
	tokenizer = new Tokenizer(source);
	pkb = pkbSource;
	stmtNum = START_COUNT_INDEX;
}

void Parser::parse() {
	createProg();
	populateCall();
	/*
	cout << "call relation:" << endl;
	for (int i = 0; i < (int)callProcs.size(); i++) {
		cout << callProcs[i].first << ", " << callProcs[i].second << endl;
	}
	cout << endl;
	*/
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
	
	int procId = pkb->insertProc(procName);

	match(STRING_OPEN_CBRACKET);

	createStmtLst(procId);

	match(STRING_CLOSE_CBRACKET);
}

void Parser::createStmtLst(int procId) {
	vector<int> stmts;

	do {
		stmts.push_back(stmtNum);
		createStmt(procId, stmtNum++);
	} while (token.compare(STRING_CLOSE_BRACKET) != COMPARE_EQUAL);

	//pkb->setProcToStmtRel(procId, stmts[0]);
	for (int index = 1; index < (int) stmts.size(); index++) {
		pkb->setStmtFollowStmtRel(stmts[index - 1], stmts[index]);
		//pkb->setProcToStmtRel(procId, stmts[index]);
	}
}

void Parser::createStmtLst(int procId, int stmtId) {
	vector<int> stmts;

	do {
		stmts.push_back(stmtNum);
		createStmt(procId, stmtNum++);
	} while (token.compare(STRING_CLOSE_BRACKET) != COMPARE_EQUAL);

	pkb->setStmtParentStmtRel(stmtId, stmts[0]);
	//pkb->setProcToStmtRel(procId, stmts[0]);
	for (int index = 1; index < (int) stmts.size(); index++) {
		pkb->setStmtFollowStmtRel(stmts[index - 1], stmts[index]);
		pkb->setStmtParentStmtRel(stmtId, stmts[index]);
		//pkb->setProcToStmtRel(procId, stmts[index]);
	}
}

void Parser::createStmt(int procId, int stmtId) {
	string stmtType = token;
	
	if (stmtType.compare(STRING_WHILE) == COMPARE_EQUAL) {
		createWhile(procId, stmtId);
	} else if (stmtType.compare(STRING_IF) == COMPARE_EQUAL) {
		createIf(procId, stmtId);
	} else if (stmtType.compare(STRING_CALL) == COMPARE_EQUAL) {
		createCall(stmtId);
	} else {
		createAssign(stmtId);
	}
}

void Parser::createWhile(int procId, int whileStmtId) {
	match(STRING_WHILE);

	string varName = token;

	match(STRING_NAME);

	int varId = createVar(varName);
	pkb->setVarToWhileStmt(whileStmtId, varId);
	pkb->setStmtUseVarRel(whileStmtId, varId);

	match(STRING_OPEN_CBRACKET);

	createStmtLst(procId, whileStmtId);

	match(STRING_CLOSE_CBRACKET);
}

void Parser::createIf(int procId, int ifStmtId) {
	match(STRING_IF);

	string varName = token;

	match(STRING_NAME);

	int varId = createVar(varName);
	pkb->setVarToIfStmt(ifStmtId, varId);
	pkb->setStmtUseVarRel(ifStmtId, varId);

	match(STRING_THEN);
	match(STRING_OPEN_CBRACKET);

	createStmtLst(procId, ifStmtId);

	match(STRING_CLOSE_CBRACKET);
	match(STRING_ELSE);
	match(STRING_OPEN_CBRACKET);

	createStmtLst(procId, ifStmtId);

	match(STRING_CLOSE_CBRACKET);
}

void Parser::createCall(int callStmtId) {
	match(STRING_CALL);

	string procName = token;

	match(STRING_NAME);

	callProcs.push_back(make_pair(callStmtId, procName));

	match(STRING_SEMICOLON);
}

void Parser::createAssign(int assignStmtId) {
	string varName = token;

	match(STRING_NAME);

	int varId = createVar(varName);
	
	pkb->setStmtModifyVarRel(assignStmtId, varId);

	match(STRING_EQUAL);

	stack<string> infix = extractExp();
	string prefix = createExpPrefix(assignStmtId, infix);

	pkb->setExpToAssignStmt(assignStmtId, prefix);

	match(STRING_SEMICOLON);
}

stack<string> Parser::extractExp() {
	stack<string> infix;
	string expStr;

	do {
		string exp = token;
		match(STRING_NAME + STRING_OR + STRING_DIGIT + STRING_OR + STRING_OPERATOR + STRING_OR + STRING_OPEN_RBRACKET + STRING_OR + STRING_CLOSE_RBRACKET);
		infix.push(exp);
		expStr += exp;
	} while (token.compare(STRING_SEMICOLON) != COMPARE_EQUAL);

	if (!ExpOperation::isValidExp(expStr)) {
		throw ERROR_MESSAGE;
	}

	return infix;
}

string Parser::createExpPrefix(int assignStmtId, stack<string> infix) {
	stack<string> prefix = ExpOperation::evaluatePrefix(infix);

	string expStr;
	string expWord;

	while (!prefix.empty()) {
		expWord = prefix.top();
		expStr += prefix.top() + STRING_OR;
		prefix.pop();

		if (regex_match(expWord, regex(STRING_NAME))) {
			int varId = createVar(expWord);
			pkb->setStmtUseVarRel(assignStmtId, varId);
		}
		else if (regex_match(expWord, regex(STRING_DIGIT))) {
			int constId = createConst(atoi(expWord.c_str()));
			pkb->setStmtUseConstRel(assignStmtId, constId);
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

void Parser::populateCall() {
	for (int index = INITAL_INDEX; index < (int)callProcs.size(); index++) {
		//if (!pkb->isProcInProcTable(callProcs[index].second)) {
		//	throw ERROR_MESSAGE;
		//}
		//
		//int procId = pkb->getProcIdByName(callProcs[index].second);
		//pkb->setStmtCallProcRel(callProcs[index].first, procId);
	}
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
		throw ERROR_MESSAGE;
	}
}