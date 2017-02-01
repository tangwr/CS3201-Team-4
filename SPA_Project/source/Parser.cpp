#include <algorithm>
#include <iostream>

#include "Parser.h"
#include "PrefixEvaluator.h"
#include "TNodeType.h"

Parser::Parser(PKB *pkbSource, string source) {
	tokenizer = new Tokenizer(source);
	pkb = pkbSource;
	stmtNum = 0;
}

void Parser::parse() {
	createProg();
	cout << "end" << endl;
}

void Parser::createProg() {
	cout << "createProg" << endl;
	token = tokenizer->getToken();

	//TNodeProg *progNode = (TNodeProg*) pkb->createTNode(TNodeType::progNode);
	//pkb->setAsRoot(progNode);

	while (token.compare(STRING_PROC) == COMPARE_EQUAL) {
		createProc();
		//TNodeProc *procNode = createProc();	
		//pkb->setParent(progNode, procNode);
		//pkb->addProgProcNode(progNode, procNode);
	}

	//pkb->setName(progNode, progNode->getChild().at(0)->getName());
}

void Parser::createProc() {
	cout << "createProc" << endl;

	match(STRING_PROC);

	string procName = token;

	match(STRING_NAME);
	
	//TNodeProc *procNode = (TNodeProc*) pkb->createTNode(TNodeType::procNode);
	//pkb->setName(procNode, procName);

	match(STRING_OPEN_BRACKET);

	createStmtLst();
	//TNodeStmtLst *stmtLstNode = createStmtLst();
	//pkb->setParent(procNode, stmtLstNode);
	//pkb->setProcStmtLstNode(procNode, stmtLstNode);

	match(STRING_CLOSE_BRACKET);

	cout << "endofProc----------------------------------------------" << endl;
	//return *procNode
}

void Parser::createStmtLst() {
	cout << "createStmtLst" << endl;
	//TNodeStmtLstNode *stmtLstNode = (TNodeStmtLstNode*) pkb->createTNode(TNodeType::stmtLstNode);

	do {
		createStmt();
		//TNodeStmt *stmtNode = createStmt();
		//pkb->setValue(stmtNode, stmtNum++);
		//pkb->setParent(stmtLstNode, stmtNode);
		//pkb->addStmtLstStmtNode(stmtLstNode, stmtNode);
	} while (token.compare("}") != COMPARE_EQUAL);

	//return *stmtLstNode;
}

void Parser::createStmt() {
	cout << "     createStmt" << endl;
	string stmtType = token;
	
	if (stmtType.compare(STRING_WHILE) == COMPARE_EQUAL) {
		createWhile();
		//return createWhile();
	} else if (stmtType.compare(STRING_IF) == COMPARE_EQUAL) {
		//createIf();
		//return createIf();
	} else if (stmtType.compare(STRING_CALL) == COMPARE_EQUAL) {
		//createCall();
		//return createCall();
	} else {
		createAssign();
		//return createAssign();
	}
}

void Parser::createWhile() {
	cout << "createWhile" << endl;
	match(STRING_WHILE);

	string varName = token;

	match(STRING_NAME);

	//TNodeWhileNode *whileNode = (TNodeWhileNode*) pkb->createTNode(TNodeType::whileNode);
	createVar(varName);
	//TNodeVarNode *varNode = createVar();
	//pkb->setParent(whileNode, varNode);
	//pkb->setWhileVarNode(whileNode, varNode);

	match(STRING_OPEN_BRACKET);

	createStmtLst();
	//TNodeStmtLstNode *stmtLstNode = createStmtLst();
	//pkb->setParent(whileNode, stmtLstNode);
	//pkb->setWhileStmtLstNode(whileNode, stmtLstNode);

	match(STRING_CLOSE_BRACKET);

	//return *whileNode;
}

void Parser::createAssign() {
	cout << "createAssign" << endl;
	string varName = token;

	match(STRING_NAME);

	//TNodeAssignNode *assignNode = (TNodeAssignNode*) pkb->createTNode(TNodeType::assignNode);
	createVar(varName);
	//TNodeVarNode *varNode = createVar();
	//pkb->setParent(assignNode, varNode);
	//pkb->setAssignVarNode(assignNode, varNode);

	match(STRING_EQUAL);

	stack<string> prefix = extractExp();
	//pkb->setAssignExpString(getString(prefix));
	createExp(&prefix);
	//TNodeExpNode *expNode = createExp(prefix);
	//pkb->setParent(assignNode, expNode);
	//pkb->setAssignExpNode(assignNode, expNode);

	match(STRING_SEMICOLON);

	//return *assignNode;
}

string Parser::getString(stack<string> stk) {
	string str = "";
	while (!stk.empty()) {
		str += stk.top();
		stk.pop();
	}
	return str;
}

stack<string> Parser::extractExp() {	
	stack<string> infix;

	do {
		string exp = token;
		match(STRING_NAME + STRING_OR + STRING_DIGIT + STRING_OR + STRING_OPERATOR);
		infix.push(exp);
	} while (token.compare(STRING_SEMICOLON) != COMPARE_EQUAL);

	PrefixEvaluator prefixEval;
	stack<string> prefix = prefixEval.evaluatePrefix(infix);

	return prefix;
}

void Parser::createExp(stack<string>* prefix) {
	cout << "     createExp" << endl;
	//TNodeExpNode *expNode;
	string exp = prefix->top();

	if (regex_match(exp, regex(STRING_NAME))) {
		createVar(exp);
		//expNode = createVar(exp);
		prefix->pop();
	} else if (regex_match(exp, regex(STRING_DIGIT))) {
		createConst(atoi(exp.c_str()));
		//expNode = createConst(atoi(exp.c_str()));
		prefix->pop();
	} else {
		createOper(prefix);
		//expNode = createOper(stack<string> prefix);
	}
	//return *expNode;
}

void Parser::createOper(stack<string>* prefix) {
	cout << "     createOper" << endl;
	//TNodeOperNode *operNode;

	if (prefix->top().compare("+") == COMPARE_EQUAL) {
		cout << "createPlus" << endl;
		//operNode = (TNodeOperNode*) pkb->createTNode(TNodeType::plusNode);
	} else if (prefix->top().compare("-") == COMPARE_EQUAL) {
		cout << "createMinus" << endl;
		//operNode = (TNodeOperNode*) pkb->createTNode(TNodeType::minusNode);
	} else {
		cout << "createTimes" << endl;
		//operNode = (TNodeOperNode*) pkb->createTNode(TNodeType::timesNode);
	}
	prefix->pop();

	createExp(prefix);
	//TNodeExpNode *leftExp = createExp(prefix);
	//pkb->setParent(operNode, leftExp);
	//pkb->setOperLeftExp(operNode, leftExp);

	createExp(prefix);
	//TNodeExpNode *rightExp = createExp(prefix);
	//pkb->setParent(operNode, rightExp);
	//pkb->setOperRightExp(operNode, rightExp);

	//return *operNode;
}

void Parser::createVar(string varName) {
	cout << "createVar: " << varName << endl;

	//TNodeVarNode *varNode = (TNodeVarNode*) pkb->createTNode(TNodeType::varNode);
	//pkb->setName(varNode, varName);
	//return *varNode;
}

void Parser::createConst(int constValue) {
	cout << "createConst: " << constValue << endl;

	//TNodeConstNode *constNode = (TNodeConstNode*) pkb->createTNode(TNodeType::constNode);
	//pkb->setValue(constNode, constValue);
	//return *constNode;
}

void Parser::match(string matchRe) {
	if (regex_match(token, regex(matchRe))) {
		if (tokenizer->hasNextToken()) {
			token = tokenizer->getToken();
		}
		else {
			token = "";
		}
	} else {
		cout << "Error found in SIMPLE source code during parsing." << endl;
		exit(0);
	}
}

Parser::~Parser() {
	delete tokenizer;
}