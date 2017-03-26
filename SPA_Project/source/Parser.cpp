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
const string STRING_SEPARATOR = "|";
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
const int INITIAL_STMT_NUM = 1;
const int NOT_FOUND = -1;


Parser::Parser(PKB *pkbSource, string source) {
	tokenizer = new Tokenizer(source);
	pkb = pkbSource;
	curStmtNum = INITIAL_STMT_NUM;
}

void Parser::parse() {
	createProg();
}

void Parser::createProg() {
	token = tokenizer->getToken();

	while (token.compare(STRING_PROC) == COMPARE_EQUAL) {
		createProc();
	}

	ensureAllCalledProcExisted();
}

void Parser::createProc() {
	match(STRING_PROC);

	string procName = token;

	match(STRING_NAME);
	
	int procId = pkb->insertProc(procName);
	if (procInSource.find(procId) != procInSource.end()) {
		throw ERROR_MESSAGE;
	}
	procInSource.insert(procId);

	match(STRING_OPEN_CBRACKET);

	createStmtLst(procId, NOT_FOUND);

	match(STRING_CLOSE_CBRACKET);
}

pair<int, vector<int>> Parser::createStmtLst(int procId, int contStmtId) {
	int firstStmt = curStmtNum;
	int prevStmt = NOT_FOUND;
	vector<int> prevStmts;

	if (contStmtId != NOT_FOUND) {
		pkb->setContainerStmtStmtLstContainsStmtRel(contStmtId, firstStmt);
	} else {
		pkb->setProcStmtLstContainsStmtRel(procId, firstStmt);
	}

	do {
		pkb->setProcToStmtRel(procId, curStmtNum);

		if (contStmtId != NOT_FOUND) {
			pkb->setStmtParentStmtRel(contStmtId, curStmtNum);
		}

		if (prevStmt != NOT_FOUND) {
			pkb->setStmtFollowStmtRel(prevStmt, curStmtNum);
		}
		prevStmt = curStmtNum;

		for (int index = INITAL_INDEX; index < (int)prevStmts.size(); index++) {
			pkb->setStmtNextStmtRel(prevStmts[index], curStmtNum);
		}
		
		prevStmts = createStmt(procId, curStmtNum++);
	} while (token.compare(STRING_CLOSE_BRACKET) != COMPARE_EQUAL);
	
	return make_pair(firstStmt, prevStmts);
}

vector<int> Parser::createStmt(int procId, int stmtId) {
	string stmtType = token;
	
	if (stmtType.compare(STRING_WHILE) == COMPARE_EQUAL) {
		return createWhile(procId, stmtId);
	} else if (stmtType.compare(STRING_IF) == COMPARE_EQUAL) {
		return createIf(procId, stmtId);
	} else if (stmtType.compare(STRING_CALL) == COMPARE_EQUAL) {
		return createCall(procId, stmtId);
	} else {
		return createAssign(procId, stmtId);
	}
}

vector<int> Parser::createWhile(int procId, int whileStmtId) {
	match(STRING_WHILE);

	string varName = token;

	match(STRING_NAME);

	int varId = createVar(varName);
	pkb->setVarToWhileStmt(whileStmtId, varId);
	pkb->setStmtUseVarRel(whileStmtId, varId);

	match(STRING_OPEN_CBRACKET);

	pair<int, vector<int>> stmtLst = createStmtLst(procId, whileStmtId);
	int firstStmtId = stmtLst.first;
	vector<int> lastStmts = stmtLst.second;

	match(STRING_CLOSE_CBRACKET);

	pkb->setStmtNextStmtRel(whileStmtId, firstStmtId);
	for (int index = INITAL_INDEX; index < (int)lastStmts.size(); index++) {
		pkb->setStmtNextStmtRel(lastStmts[index], whileStmtId);
	}

	return vector<int>() = { whileStmtId };
}

vector<int> Parser::createIf(int procId, int ifStmtId) {
	match(STRING_IF);

	string varName = token;

	match(STRING_NAME);

	int varId = createVar(varName);
	pkb->setVarToIfStmt(ifStmtId, varId);
	pkb->setStmtUseVarRel(ifStmtId, varId);

	match(STRING_THEN);
	match(STRING_OPEN_CBRACKET);

	pair<int, vector<int>> thenStmtLst = createStmtLst(procId, ifStmtId);

	match(STRING_CLOSE_CBRACKET);
	match(STRING_ELSE);
	match(STRING_OPEN_CBRACKET);

	pair<int, vector<int>> elseStmtLst = createStmtLst(procId, ifStmtId);

	match(STRING_CLOSE_CBRACKET);

	pkb->setStmtNextStmtRel(ifStmtId, thenStmtLst.first);
	pkb->setStmtNextStmtRel(ifStmtId, elseStmtLst.first);

	return VectorSetOperation<int>::setUnion(thenStmtLst.second, elseStmtLst.second);
}

vector<int> Parser::createCall(int procId, int callStmtId) {
	match(STRING_CALL);

	string procName = token;

	match(STRING_NAME);

	int calledProcId;
	if (!pkb->isProcInTable(procName)) {
		calledProcId = pkb->insertProc(procName);
	}
	else {
		calledProcId = pkb->getProcIdByName(procName);
	}
	pkb->setProcCallProcRel(procId, calledProcId);
	pkb->setStmtCallProcRel(callStmtId, calledProcId);

	match(STRING_SEMICOLON);

	return vector<int>() = { callStmtId };
}

vector<int> Parser::createAssign(int procId, int assignStmtId) {
	string varName = token;

	match(STRING_NAME);

	int varId = createVar(varName);
	
	pkb->setStmtModifyVarRel(assignStmtId, varId);
	pkb->setVarAtLeftOfAssignStmt(assignStmtId, varId);

	match(STRING_EQUAL);

	string infix = extractExp();
	string prefix = createExpPrefix(assignStmtId, infix);

	pkb->setExpToAssignStmt(assignStmtId, prefix);

	match(STRING_SEMICOLON);

	return vector<int>() = { assignStmtId };
}

string Parser::extractExp() {
	string infix;
	do {
		string exp = token;
		match(STRING_NAME + STRING_OR + STRING_DIGIT + STRING_OR
			+ STRING_OPERATOR + STRING_OR + STRING_OPEN_RBRACKET
			+ STRING_OR + STRING_CLOSE_RBRACKET);
		infix += exp;
	} while (token.compare(STRING_SEMICOLON) != COMPARE_EQUAL);

	if (!ExpOperation::isValidExp(infix)) {
		throw ERROR_MESSAGE;
	}
	return infix;
}

string Parser::createExpPrefix(int assignStmtId, string infix) {
	stack<string> prefix = ExpOperation::evaluatePrefix(infix);

	string expStr;
	string expWord;

	while (!prefix.empty()) {
		expWord = prefix.top();
		expStr += prefix.top() + STRING_SEPARATOR;
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

void Parser::ensureAllCalledProcExisted() {
	unordered_set<int> procs = pkb->getAllProcId();
	for (auto procId : procs) {
		if (procInSource.find(procId) == procInSource.end()) {
			throw ERROR_MESSAGE;
		}
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

Parser::~Parser() {
	delete tokenizer;
}
