#pragma once
#include "QueryParser.h"
#include "QueryTree.h"
#include "Affects.h"
#include "AffectsStar.h"
#include "AffectsBip.h"
#include "AffectsBipStar.h"
#include "Clause.h"
#include "Follow.h"
#include "FollowStar.h"
#include "Modifies.h"
#include "Parent.h"
#include "ParentStar.h"
#include "Pattern.h"
#include "Uses.h"
#include "Calls.h"
#include "CallsStar.h"
#include "Next.h"
#include "NextBip.h"
#include "NextBipStar.h"
#include "NextStar.h"
#include "With.h"
#include "ExpOperation.h"
#include "Tokenizer.h"
#define TYPE_VALUE "value"
#define TYPE_SELECT "Select"
#define TYPE_CONSTANT "constant"
#define TYPE_ASSIGN "assign"
#define TYPE_WHILE "while"
#define TYPE_STMT "stmt"
#define TYPE_VARNAME "varName"
#define TYPE_PROG_LINE "prog_line"
#define TYPE_PROG "prog"
#define TYPE_ALL "all"
#define TYPE_AND "and"
#define TYPE_BOOLEAN "BOOLEAN"
#define TYPE_VARIABLE "variable"
#define TYPE_PATTERN "pattern"
#define TYPE_SUCH "such"
#define TYPE_THAT "that"
#define TYPE_PROCEDURE "procedure"
#define TYPE_STMTLST "stmtLst"
#define TYPE_IF "if"
#define TYPE_CALL "call"
#define TYPE_WITH "with"
#define TYPE_USES "Uses"
#define TYPE_MODIFIES "Modifies"
#define TYPE_CALLS "Calls"
#define TYPE_PARENT "Parent"
#define TYPE_FOLLOWS "Follows"
#define TYPE_NEXT "Next"
#define TYPE_AFFECTS "Affects"
#define TYPE_AFFECTSBIP "AffectsBip"
#define TYPE_NEXTBIP "NextBip"
#define TYPE_PROC_NAME "procName"
#define TYPE_LINE "line"
#define SYMBOL_NONE ""
#define SYMBOL_SEMICOLON ";"
#define SYMBOL_SPACE " "
#define SYMBOL_COMMA ","
#define SYMBOL_QUOTE "\""
#define SYMBOL_UNDERSCORE "_"
#define SYMBOL_OPEN_BRACKET "\\("
#define SYMBOL_CLOSE_BRACKET "\\)"
#define SYMBOL_PATTERN_CLOSE ")"
#define SYMBOL_STMT_NO "#"
#define SYMBOL_TUPLE_OPEN_BRACKET "<"
#define SYMBOL_TUPLE_CLOSE_BRACKET ">"
#define SYMBOL_STAR "*"
#define SYMBOL_EQUALS "="
#define SYMBOL_FULL_STOP "."
#define SYMBOL_START '0'
#define VARIABLE_NAME "([a-zA-Z][a-zA-Z0-9]*)"
#define ERROR_STRING "The query is invalid"
#define ERROR_DECLARATION "The declaration is invalid"
#define ERROR_DUPLICATE_VAR "The varName is exist"
#define ERROR_SELECT "The select is invalid"
#define ERROR_SUCH_THAT "The such that clasue is invalid"
#define ERROR_LEFT_CHILD "The clause's left child is invalid"
#define ERROR_RIGHT_CHILD "The clause's right child is invalid"
#define ERROR_FACTOR "The Pattern's factor is invalid"
#define ERROR_CHILD_TYPE "The left child's type is not equal to right child's type for With"
#define ERROR_SELECT_BOOLEAN "The result is false"
#define EQUAL 0
#define EMPTY 0
#define SIZE 10
#define TRUE true
#define FALSE false
#define IDENT "([a-zA-Z][a-zA-Z0-9#]*)"

using namespace std;

const vector<string> TYPES = { "variable", "constant", "stmt", "assign", "while","prog_line", "procedure", "stmtLst", "if", "call" };
const vector<string> KEYS = { "Pattern", "and", "such", "that", "call", "prog_line", "Select", "constant", "stmt", "stmtLst", "assign", "while", 
"if", "procedure", "Calls", "Calls*", "Modifies", "Uses", "Affects", "Affects*", "Parent", "Parent*", "Follows", "Follows*","Next", 
"Next*", "with" };

QueryParser::QueryParser() {}

QueryTree QueryParser::parse(string query) {
	tokenizer = new Tokenizer(query);
	QueryTree queryTree;
	isSelectBoolean = FALSE;
	usedMap.clear();
	varMap.clear();
	getDeclaration(&queryTree);
	getSelect(&queryTree);
	if (tokenizer->hasNextToken()) {
		getClause(&queryTree);
	}

	unordered_map<string, Parameter>::iterator it;
	for (auto parameter : usedMap) {
		queryTree.insertUsed(parameter.second);
	}
	delete tokenizer;
	return queryTree;
}

void QueryParser::getDeclaration(QueryTree *qt) {
	while (tokenizer->peekToken().compare(TYPE_SELECT) != EQUAL) {
		getDeclare(qt);
	}
}

void QueryParser::getDeclare(QueryTree *qt) {
	string synTypeStr = tokenizer->getToken();
	Type synType;
	if (synTypeStr.compare(TYPE_ASSIGN) == EQUAL) {
		synType = ASSIGN;
	}
	else if (synTypeStr.compare(TYPE_CALL) == EQUAL) {
		synType = CALL;
	}
	else if (synTypeStr.compare(TYPE_WHILE) == EQUAL) {
		synType = WHILE;
	}
	else if (synTypeStr.compare(TYPE_IF) == EQUAL) {
		synType = IF;
	}
	else if (synTypeStr.compare(TYPE_PROCEDURE) == EQUAL) {
		synType = PROCEDURE;
	}
	else if (synTypeStr.compare(TYPE_VARIABLE) == EQUAL) {
		synType = VARIABLE;
	}
	else if (synTypeStr.compare(TYPE_STMTLST) == EQUAL) {
		synType = STMTLST;
	}
	else if (synTypeStr.compare(TYPE_STMT) == EQUAL) {
		synType = STMT;
	}
	else if (synTypeStr.compare(TYPE_PROG) == EQUAL) {
		string underscore = tokenizer->getToken();
		match(underscore, SYMBOL_UNDERSCORE);
		string line = tokenizer->getToken();
		match(line, TYPE_LINE);
		synType = PROG_LINE;
	}
	else if (synTypeStr.compare(TYPE_CONSTANT) == EQUAL) {
		synType = CONSTANT;
	}
	else {
		throwError(ERROR_STRING);
	}

	string nextToken;
	do {
		string synName = getSyn(synType);
		varMap[synName] = Parameter(synName, synType);
		nextToken = tokenizer->getToken();
	} while (nextToken.compare(SYMBOL_COMMA) == EQUAL);

	match(nextToken, SYMBOL_SEMICOLON);
}

string QueryParser::getSyn(Type synType) {
	string token = tokenizer->getToken();
	if (find(KEYS.begin(), KEYS.end(), token) == KEYS.end()) {
		if (!isVarNameExists(token)) {
			match(token, VARIABLE_NAME);
		}
		else {
			throwError(ERROR_DUPLICATE_VAR);
		}
	}
	else {
		throwError(ERROR_DECLARATION);
	}
	return token;
}

void QueryParser::getSelect(QueryTree *qt) {
	tokenizer->getToken();
	string token = tokenizer->peekToken();

	if (token.compare(SYMBOL_TUPLE_OPEN_BRACKET) == EQUAL) {
		tokenizer->getToken();
		string nextToken;
		string finalToken;
		Parameter selectSyn;
		do {
			string selectName = getSelectSyn();
			selectSyn = varMap[selectName];
			nextToken = tokenizer->getToken();
			if (nextToken.compare(SYMBOL_FULL_STOP) == EQUAL) {
				string correctType = tokenizer->peekToken();
				Type synType = varMap[selectName].getParaType();
				if (synType == CALL || synType == PROCEDURE) {
					if (correctType.compare(TYPE_PROC_NAME) == EQUAL) {
						if (synType == CALL) {
							selectSyn.setAttributeProc(TRUE);
						}
					}
					else if (correctType.compare(TYPE_STMT) == EQUAL) {
						tokenizer->getToken();
						string stmtNo = tokenizer->peekToken();
						match(stmtNo, SYMBOL_STMT_NO);
						selectSyn.setAttributeProc(FALSE);
					}
					else {
						throwError(ERROR_STRING);
					}


				}
				else if (synType == STMT || synType == WHILE || synType == ASSIGN || synType == IF) {
					match(correctType, TYPE_STMT);
					tokenizer->getToken();
					string stmtNo = tokenizer->peekToken();
					match(stmtNo, SYMBOL_STMT_NO);

				}
				else if (synType == CONSTANT) {
					match(correctType, TYPE_VALUE);
				}
				else if (synType == VARIABLE) {
					match(correctType, TYPE_VARNAME);
				}
				else {
					throwError(ERROR_STRING);
				}
				tokenizer->getToken();
				finalToken = tokenizer->getToken();
			}
			else {
				selectSyn.setAttributeProc(FALSE);
				finalToken = nextToken;
			}
			qt->insertSelect(selectSyn);
		} while (finalToken.compare(SYMBOL_COMMA) == EQUAL);

		match(finalToken, SYMBOL_TUPLE_CLOSE_BRACKET);
	}
	else {
		Parameter selectSyn;
		if (isVarNameExists(token)) {
			selectSyn = varMap[token];
			tokenizer->getToken();
			string dot = tokenizer->peekToken();
			if (dot.compare(SYMBOL_FULL_STOP) == EQUAL) {
				tokenizer->getToken();
				string correctType = tokenizer->peekToken();
				Type synType = varMap[token].getParaType();
				if (synType == CALL || synType == PROCEDURE) {
					if (correctType.compare(TYPE_PROC_NAME) == EQUAL) {
						if (synType == CALL) {
							selectSyn.setAttributeProc(TRUE);
						}
					}
					else if (correctType.compare(TYPE_STMT) == EQUAL) {
						tokenizer->getToken();
						string stmtNo = tokenizer->peekToken();
						match(stmtNo, SYMBOL_STMT_NO);
						selectSyn.setAttributeProc(FALSE);
					}
					else {
						throwError(ERROR_STRING);
					}
					tokenizer->getToken();
				}
				else if (synType == STMT || synType == WHILE || synType == ASSIGN || synType == IF) {
					match(correctType, TYPE_STMT);
					tokenizer->getToken();
					string stmtNo = tokenizer->peekToken();
					match(stmtNo, SYMBOL_STMT_NO);
					tokenizer->getToken();
				}
				else if (synType == CONSTANT) {
					match(correctType, TYPE_VALUE);
					tokenizer->getToken();
				}
				else if (synType == VARIABLE) {
					match(correctType, TYPE_VARNAME);
					tokenizer->getToken();
				}
				else {
					throwError(ERROR_STRING);
				}
			}
			else
			{
				selectSyn.setAttributeProc(FALSE);
			}
			qt->insertSelect(selectSyn);
		}
		else if (token.compare(TYPE_BOOLEAN) == EQUAL) {
			isSelectBoolean = TRUE;
			qt->insertSelect(Parameter(TYPE_BOOLEAN, BOOLEAN));
			tokenizer->getToken();
		}
		else {
			throwError(ERROR_SELECT);
			tokenizer->getToken();
		}
	}
}

string QueryParser::getSelectSyn() {
	string token = tokenizer->getToken();
	if (!isVarNameExists(token)) {
		throwError(ERROR_SELECT);
	}
	return token;
}
void QueryParser::getClause(QueryTree *qt) {
	while (tokenizer->hasNextToken()) {
		string token = tokenizer->getToken();
		if (token.compare(TYPE_SUCH) == EQUAL) {
			//after the such I need to check the that
			match(tokenizer->peekToken(), TYPE_THAT);
			getSuchThat(qt);
		}
		else if (token.compare(TYPE_PATTERN) == EQUAL) {
			getPattern(qt);
		}
		else if (token.compare(TYPE_WITH) == EQUAL) {
			getWith(qt);
		}
		else {
			throwError(ERROR_STRING);
		}
	}
}
void QueryParser::getSuchThat(QueryTree *qt) {
	string token = tokenizer->getToken();
	string compareStr = tokenizer->getToken();
	string star = tokenizer->peekToken();

	if (compareStr.compare(TYPE_MODIFIES) == EQUAL) {
		getModifies(qt);
	}
	else if (compareStr.compare(TYPE_USES) == EQUAL) {
		getUses(qt);
	}
	else if (compareStr.compare(TYPE_CALLS) == EQUAL && star.compare(SYMBOL_STAR) != EQUAL) {
		getCalls(qt);
	}
	else if (compareStr.compare(TYPE_CALLS) == EQUAL && star.compare(SYMBOL_STAR) == EQUAL) {
		tokenizer->getToken();
		getCallsStar(qt);
	}
	else if (compareStr.compare(TYPE_PARENT) == EQUAL && star.compare(SYMBOL_STAR) != EQUAL) {
		getParent(qt);
	}
	else if (compareStr.compare(TYPE_PARENT) == EQUAL && star.compare(SYMBOL_STAR) == EQUAL) {
		tokenizer->getToken();
		getParentStar(qt);
	}
	else if (compareStr.compare(TYPE_FOLLOWS) == EQUAL && star.compare(SYMBOL_STAR) != EQUAL) {
		getFollows(qt);
	}
	else if (compareStr.compare(TYPE_FOLLOWS) == EQUAL && star.compare(SYMBOL_STAR) == EQUAL) {
		tokenizer->getToken();
		getFollowsStar(qt);
	}
	else if (compareStr.compare(TYPE_NEXT) == EQUAL && star.compare(SYMBOL_STAR) != EQUAL) {
		getNext(qt);
	}
	else if (compareStr.compare(TYPE_NEXT) == EQUAL && star.compare(SYMBOL_STAR) == EQUAL) {
		tokenizer->getToken();
		getNextStar(qt);
	}
	else if (compareStr.compare(TYPE_AFFECTS) == EQUAL && star.compare(SYMBOL_STAR) != EQUAL) {
		getAffects(qt);
	}
	else if (compareStr.compare(TYPE_AFFECTS) == EQUAL && star.compare(SYMBOL_STAR) == EQUAL) {
		tokenizer->getToken();
		getAffectsStar(qt);
	}
	else if (compareStr.compare(TYPE_NEXTBIP) == EQUAL && star.compare(SYMBOL_STAR) != EQUAL) {
		getNextBip(qt);
	}
	else if (compareStr.compare(TYPE_NEXTBIP) == EQUAL && star.compare(SYMBOL_STAR) == EQUAL) {
		tokenizer->getToken();
		getNextBipStar(qt);
	}
	else if (compareStr.compare(TYPE_AFFECTSBIP) == EQUAL && star.compare(SYMBOL_STAR) != EQUAL) {
		getAffectsBip(qt);
	}
	else if (compareStr.compare(TYPE_AFFECTSBIP) == EQUAL && star.compare(SYMBOL_STAR) == EQUAL) {
		tokenizer->getToken();
		getAffectsBipStar(qt);
	}
	else {
		throwError(ERROR_SUCH_THAT);
	}

	if (tokenizer->peekToken().compare(TYPE_AND) == EQUAL) {
		getSuchThat(qt);
	}
}
void QueryParser::getModifies(QueryTree* qt) {
	Parameter leftChild;
	Parameter rightChild;
	string token = tokenizer->getToken();

	match(token, SYMBOL_OPEN_BRACKET);
	string lc = tokenizer->getToken();
	if (isVarNameExists(lc)) {
		leftChild = varMap[lc];
		string key = leftChild.getParaName();
		Type lcType = leftChild.getParaType();
		if (lcType == VARIABLE || lcType == CONSTANT || lcType == BOOLEAN || lcType == STMTLST || lcType == STRINGVARIABLE) {
			throwError(ERROR_LEFT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = leftChild;
		}
	}
	else if (isPositiveInteger(lc)) {
		leftChild.setParaName(lc);
		leftChild.setParaType(INTEGER);
	}
	else if (lc.compare(SYMBOL_QUOTE) == EQUAL) {

		string proceName = tokenizer->getToken();
		match(proceName, IDENT);
		leftChild.setParaName(proceName);
		leftChild.setParaType(STRINGVARIABLE);
		if (tokenizer->peekToken().compare(SYMBOL_QUOTE) != EQUAL) {
			throwError(ERROR_LEFT_CHILD);
		}
		tokenizer->getToken();
	}
	else {
		throwError(ERROR_LEFT_CHILD);
	}

	string comma = tokenizer->getToken();
	match(comma, SYMBOL_COMMA);
	string rc = tokenizer->getToken();
	if (isVarNameExists(rc)) {
		rightChild = varMap[rc];
		string key = rightChild.getParaName();
		Type rcType = rightChild.getParaType();
		if (rcType != VARIABLE) {
			throwError(ERROR_RIGHT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = rightChild;
		}
	}
	else if (rc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		rightChild.setParaName(rc);
		rightChild.setParaType(ANYTHING);
	}
	else if (rc.compare(SYMBOL_QUOTE) == EQUAL) {

		string proceName = tokenizer->getToken();
		match(proceName, IDENT);
		rightChild.setParaName(proceName);
		rightChild.setParaType(STRINGVARIABLE);
		if (tokenizer->peekToken().compare(SYMBOL_QUOTE) != EQUAL) {
			throwError(ERROR_LEFT_CHILD);
		}
		tokenizer->getToken();
	}
	else {
		throwError(ERROR_RIGHT_CHILD);
	}

	string closeBracket = tokenizer->getToken();
	match(closeBracket, SYMBOL_CLOSE_BRACKET);
	Modifies *m = new Modifies(leftChild, rightChild);
	qt->insertResult(m);
}
void QueryParser::getUses(QueryTree* qt) {
	Parameter leftChild;
	Parameter rightChild;
	string token = tokenizer->getToken();

	match(token, SYMBOL_OPEN_BRACKET);
	string lc = tokenizer->getToken();

	if (isVarNameExists(lc)) {
		leftChild = varMap[lc];
		string key = leftChild.getParaName();
		Type lcType = leftChild.getParaType();
		if (lcType == VARIABLE || lcType == CONSTANT || lcType == BOOLEAN || lcType == STMTLST || lcType == STRINGVARIABLE) {
			throwError(ERROR_LEFT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = leftChild;
		}
	}
	else if (isPositiveInteger(lc)) {
		leftChild.setParaName(lc);
		leftChild.setParaType(INTEGER);
	}
	else if (lc.compare(SYMBOL_QUOTE) == EQUAL) {

		string proceName = tokenizer->getToken();
		match(proceName, IDENT);
		leftChild.setParaName(proceName);
		leftChild.setParaType(STRINGVARIABLE);
		if (tokenizer->peekToken().compare(SYMBOL_QUOTE) != EQUAL) {
			throwError(ERROR_LEFT_CHILD);
		}
		tokenizer->getToken();
	}
	else {
		throwError(ERROR_LEFT_CHILD);
	}

	string comma = tokenizer->getToken();
	match(comma, SYMBOL_COMMA);
	string rc = tokenizer->getToken();
	if (isVarNameExists(rc)) {
		rightChild = varMap[rc];
		string key = rightChild.getParaName();
		Type rcType = rightChild.getParaType();
		if (rcType != VARIABLE) {
			throwError(ERROR_RIGHT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = rightChild;
		}
	}
	else if (rc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		rightChild.setParaName(rc);
		rightChild.setParaType(ANYTHING);
	}
	else if (rc.compare(SYMBOL_QUOTE) == EQUAL) {

		string proceName = tokenizer->getToken();
		match(proceName, IDENT);
		rightChild.setParaName(proceName);
		rightChild.setParaType(STRINGVARIABLE);
		if (tokenizer->peekToken().compare(SYMBOL_QUOTE) != EQUAL) {
			throwError(ERROR_LEFT_CHILD);
		}
		tokenizer->getToken();
	}
	else {
		throwError(ERROR_RIGHT_CHILD);
	}

	string closeBracket = tokenizer->getToken();
	match(closeBracket, SYMBOL_CLOSE_BRACKET);
	Uses *u = new Uses(leftChild, rightChild);
	qt->insertResult(u);
}
void QueryParser::getCalls(QueryTree* qt) {
	Parameter leftChild;
	Parameter rightChild;

	string token = tokenizer->getToken();

	match(token, SYMBOL_OPEN_BRACKET);
	string lc = tokenizer->getToken();

	if (isVarNameExists(lc)) {
		leftChild = varMap[lc];
		if (leftChild.getParaType() != PROCEDURE) {
			throwError(ERROR_LEFT_CHILD);
		}
		string key = leftChild.getParaName();
		if (!isUsedExists(key)) {
			usedMap[key] = leftChild;
		}
	}
	else if (lc.compare(SYMBOL_QUOTE) == EQUAL) {

		string proceName = tokenizer->getToken();
		match(proceName, IDENT);
		leftChild.setParaName(proceName);
		leftChild.setParaType(STRINGVARIABLE);
		if (tokenizer->peekToken().compare(SYMBOL_QUOTE) != EQUAL) {
			throwError(ERROR_LEFT_CHILD);
		}
		tokenizer->getToken();
	}
	else if (lc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		leftChild.setParaName(lc);
		leftChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_LEFT_CHILD);
	}

	string comma = tokenizer->getToken();
	match(comma, SYMBOL_COMMA);
	string rc = tokenizer->getToken();
	if (isVarNameExists(rc)) {
		rightChild = varMap[rc];
		if (rightChild.getParaType() != PROCEDURE) {
			throwError(ERROR_RIGHT_CHILD);
		}
		string key = rightChild.getParaName();
		if (!isUsedExists(key)) {
			usedMap[key] = rightChild;
		}
	}
	else if (rc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		rightChild.setParaName(rc);
		rightChild.setParaType(ANYTHING);
	}
	else if (rc.compare(SYMBOL_QUOTE) == EQUAL) {

		string proceName = tokenizer->getToken();
		match(proceName, IDENT);
		rightChild.setParaName(proceName);
		rightChild.setParaType(STRINGVARIABLE);
		if (tokenizer->peekToken().compare(SYMBOL_QUOTE) != EQUAL) {
			throwError(ERROR_LEFT_CHILD);
		}
		tokenizer->getToken();
	}
	else {
		throwError(ERROR_RIGHT_CHILD);
	}

	string closeBracket = tokenizer->getToken();
	match(closeBracket, SYMBOL_CLOSE_BRACKET);
	Calls *c = new Calls(leftChild, rightChild);
	qt->insertResult(c);
}
void QueryParser::getCallsStar(QueryTree* qt) {
	Parameter leftChild;
	Parameter rightChild;

	string token = tokenizer->getToken();

	match(token, SYMBOL_OPEN_BRACKET);
	string lc = tokenizer->getToken();

	if (isVarNameExists(lc)) {
		leftChild = varMap[lc];
		if (leftChild.getParaType() != PROCEDURE) {
			throwError(ERROR_LEFT_CHILD);
		}
		string key = leftChild.getParaName();
		if (!isUsedExists(key)) {
			usedMap[key] = leftChild;
		}
	}
	else if (lc.compare(SYMBOL_QUOTE) == EQUAL) {

		string proceName = tokenizer->getToken();
		match(proceName, IDENT);
		leftChild.setParaName(proceName);
		leftChild.setParaType(STRINGVARIABLE);
		if (tokenizer->peekToken().compare(SYMBOL_QUOTE) != EQUAL) {
			throwError(ERROR_LEFT_CHILD);
		}
		tokenizer->getToken();
	}
	else if (lc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		leftChild.setParaName(lc);
		leftChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_LEFT_CHILD);
	}

	string comma = tokenizer->getToken();
	match(comma, SYMBOL_COMMA);
	string rc = tokenizer->getToken();
	if (isVarNameExists(rc)) {
		rightChild = varMap[rc];
		if (rightChild.getParaType() != PROCEDURE) {
			throwError(ERROR_RIGHT_CHILD);
		}
		string key = rightChild.getParaName();
		if (!isUsedExists(key)) {
			usedMap[key] = rightChild;
		}
	}
	else if (rc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		rightChild.setParaName(rc);
		rightChild.setParaType(ANYTHING);
	}
	else if (rc.compare(SYMBOL_QUOTE) == EQUAL) {

		string proceName = tokenizer->getToken();
		match(proceName, IDENT);
		rightChild.setParaName(proceName);
		rightChild.setParaType(STRINGVARIABLE);
		if (tokenizer->peekToken().compare(SYMBOL_QUOTE) != EQUAL) {
			throwError(ERROR_LEFT_CHILD);
		}
		tokenizer->getToken();
	}
	else {
		throwError(ERROR_RIGHT_CHILD);
	}

	string closeBracket = tokenizer->getToken();
	match(closeBracket, SYMBOL_CLOSE_BRACKET);
	CallsStar *cs = new CallsStar(leftChild, rightChild);
	qt->insertResult(cs);
}
void QueryParser::getParent(QueryTree* qt) {
	Parameter leftChild;
	Parameter rightChild;

	string token = tokenizer->getToken();

	match(token, SYMBOL_OPEN_BRACKET);
	string lc = tokenizer->getToken();

	if (isVarNameExists(lc)) {
		leftChild = varMap[lc];
		string key = leftChild.getParaName();
		Type lcType = leftChild.getParaType();
		if (lcType == VARIABLE || lcType == CONSTANT || lcType == BOOLEAN || lcType == STRINGVARIABLE ||
			lcType == PROCEDURE || lcType == STMTLST) {
			throwError(ERROR_LEFT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = leftChild;
		}
	}
	else if (isPositiveInteger(lc)) {
		leftChild.setParaName(lc);
		leftChild.setParaType(INTEGER);
	}
	else if (lc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		leftChild.setParaName(lc);
		leftChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_LEFT_CHILD);
	}

	string comma = tokenizer->getToken();
	match(comma, SYMBOL_COMMA);
	string rc = tokenizer->getToken();
	if (isVarNameExists(rc)) {
		rightChild = varMap[rc];
		string key = rightChild.getParaName();
		Type rcType = rightChild.getParaType();
		if (rcType == VARIABLE || rcType == CONSTANT || rcType == BOOLEAN || rcType == STRINGVARIABLE ||
			rcType == PROCEDURE || rcType == STMTLST) {
			throwError(ERROR_RIGHT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = rightChild;
		}
	}
	else if (isPositiveInteger(rc)) {
		rightChild.setParaName(rc);
		rightChild.setParaType(INTEGER);
	}
	else if (rc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		rightChild.setParaName(rc);
		rightChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_RIGHT_CHILD);
	}

	string closeBracket = tokenizer->getToken();
	match(closeBracket, SYMBOL_CLOSE_BRACKET);
	Parent *p = new Parent(leftChild, rightChild);
	qt->insertResult(p);
}
void QueryParser::getParentStar(QueryTree* qt) {
	Parameter leftChild;
	Parameter rightChild;

	string token = tokenizer->getToken();

	match(token, SYMBOL_OPEN_BRACKET);
	string lc = tokenizer->getToken();

	if (isVarNameExists(lc)) {
		leftChild = varMap[lc];
		string key = leftChild.getParaName();
		Type lcType = leftChild.getParaType();
		if (lcType == VARIABLE || lcType == CONSTANT || lcType == BOOLEAN || lcType == STRINGVARIABLE ||
			lcType == PROCEDURE || lcType == STMTLST) {
			throwError(ERROR_LEFT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = leftChild;
		}
	}
	else if (isPositiveInteger(lc)) {
		leftChild.setParaName(lc);
		leftChild.setParaType(INTEGER);
	}
	else if (lc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		leftChild.setParaName(lc);
		leftChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_LEFT_CHILD);
	}

	string comma = tokenizer->getToken();
	match(comma, SYMBOL_COMMA);
	string rc = tokenizer->getToken();
	if (isVarNameExists(rc)) {
		rightChild = varMap[rc];
		string key = rightChild.getParaName();
		Type rcType = rightChild.getParaType();
		if (rcType == VARIABLE || rcType == CONSTANT || rcType == BOOLEAN || rcType == STRINGVARIABLE ||
			rcType == PROCEDURE || rcType == STMTLST) {
			throwError(ERROR_RIGHT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = rightChild;
		}
	}
	else if (isPositiveInteger(rc)) {
		rightChild.setParaName(rc);
		rightChild.setParaType(INTEGER);
	}
	else if (rc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		rightChild.setParaName(rc);
		rightChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_RIGHT_CHILD);
	}

	string closeBracket = tokenizer->getToken();
	match(closeBracket, SYMBOL_CLOSE_BRACKET);
	ParentStar *ps = new ParentStar(leftChild, rightChild);
	qt->insertResult(ps);
}
void QueryParser::getFollows(QueryTree* qt) {
	Parameter leftChild;
	Parameter rightChild;

	string token = tokenizer->getToken();

	match(token, SYMBOL_OPEN_BRACKET);
	string lc = tokenizer->getToken();

	if (isVarNameExists(lc)) {
		leftChild = varMap[lc];
		string key = leftChild.getParaName();
		Type lcType = leftChild.getParaType();
		if (lcType == VARIABLE || lcType == CONSTANT || lcType == BOOLEAN || lcType == STRINGVARIABLE ||
			lcType == PROCEDURE || lcType == STMTLST) {
			throwError(ERROR_LEFT_CHILD);
		}

		if (!isUsedExists(key)) {
			usedMap[key] = leftChild;
		}
	}
	else if (isPositiveInteger(lc)) {
		leftChild.setParaName(lc);
		leftChild.setParaType(INTEGER);
	}
	else if (lc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		leftChild.setParaName(lc);
		leftChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_LEFT_CHILD);
	}

	string comma = tokenizer->getToken();
	match(comma, SYMBOL_COMMA);
	string rc = tokenizer->getToken();
	if (isVarNameExists(rc)) {
		rightChild = varMap[rc];
		string key = rightChild.getParaName();
		Type rcType = rightChild.getParaType();
		if (rcType == VARIABLE || rcType == CONSTANT || rcType == BOOLEAN || rcType == STRINGVARIABLE ||
			rcType == PROCEDURE || rcType == STMTLST) {
			throwError(ERROR_RIGHT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = rightChild;
		}
	}
	else if (isPositiveInteger(rc)) {
		rightChild.setParaName(rc);
		rightChild.setParaType(INTEGER);
	}
	else if (rc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		rightChild.setParaName(rc);
		rightChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_RIGHT_CHILD);
	}

	string closeBracket = tokenizer->getToken();
	match(closeBracket, SYMBOL_CLOSE_BRACKET);
	Follow *f = new Follow(leftChild, rightChild);

	qt->insertResult(f);
}
void QueryParser::getFollowsStar(QueryTree* qt) {
	Parameter leftChild;
	Parameter rightChild;

	string token = tokenizer->getToken();

	match(token, SYMBOL_OPEN_BRACKET);
	string lc = tokenizer->getToken();

	if (isVarNameExists(lc)) {
		leftChild = varMap[lc];
		string key = leftChild.getParaName();
		Type lcType = leftChild.getParaType();
		if (lcType == VARIABLE || lcType == CONSTANT || lcType == BOOLEAN || lcType == STRINGVARIABLE ||
			lcType == PROCEDURE || lcType == STMTLST) {
			throwError(ERROR_LEFT_CHILD);
		}

		if (!isUsedExists(key)) {
			usedMap[key] = leftChild;
		}
	}
	else if (isPositiveInteger(lc)) {
		leftChild.setParaName(lc);
		leftChild.setParaType(INTEGER);
	}
	else if (lc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		leftChild.setParaName(lc);
		leftChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_LEFT_CHILD);
	}

	string comma = tokenizer->getToken();
	match(comma, SYMBOL_COMMA);
	string rc = tokenizer->getToken();
	if (isVarNameExists(rc)) {
		rightChild = varMap[rc];
		string key = rightChild.getParaName();
		Type rcType = rightChild.getParaType();
		if (rcType == VARIABLE || rcType == CONSTANT || rcType == BOOLEAN || rcType == STRINGVARIABLE ||
			rcType == PROCEDURE || rcType == STMTLST) {
			throwError(ERROR_RIGHT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = rightChild;
		}
	}
	else if (isPositiveInteger(rc)) {
		rightChild.setParaName(rc);
		rightChild.setParaType(INTEGER);
	}
	else if (rc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		rightChild.setParaName(rc);
		rightChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_RIGHT_CHILD);
	}

	string closeBracket = tokenizer->getToken();
	match(closeBracket, SYMBOL_CLOSE_BRACKET);
	FollowStar *fs = new FollowStar(leftChild, rightChild);

	qt->insertResult(fs);
}
void QueryParser::getNext(QueryTree* qt) {
	Parameter leftChild;
	Parameter rightChild;

	string token = tokenizer->getToken();

	match(token, SYMBOL_OPEN_BRACKET);
	string lc = tokenizer->getToken();

	if (isVarNameExists(lc)) {
		leftChild = varMap[lc];
		string key = leftChild.getParaName();
		Type lcType = leftChild.getParaType();
		if (lcType == VARIABLE || lcType == CONSTANT || lcType == BOOLEAN || lcType == STRINGVARIABLE ||
			lcType == PROCEDURE || lcType == STMTLST) {
			throwError(ERROR_LEFT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = leftChild;
		}
	}
	else if (isPositiveInteger(lc)) {
		leftChild.setParaName(lc);
		leftChild.setParaType(INTEGER);
	}
	else if (lc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		leftChild.setParaName(lc);
		leftChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_LEFT_CHILD);
	}

	string comma = tokenizer->getToken();
	match(comma, SYMBOL_COMMA);
	string rc = tokenizer->getToken();
	if (isVarNameExists(rc)) {
		rightChild = varMap[rc];
		string key = rightChild.getParaName();
		Type rcType = rightChild.getParaType();
		if (rcType == VARIABLE || rcType == CONSTANT || rcType == BOOLEAN || rcType == STRINGVARIABLE ||
			rcType == PROCEDURE || rcType == STMTLST) {
			throwError(ERROR_RIGHT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = rightChild;
		}
	}
	else if (isPositiveInteger(rc)) {
		rightChild.setParaName(rc);
		rightChild.setParaType(INTEGER);
	}
	else if (rc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		rightChild.setParaName(rc);
		rightChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_RIGHT_CHILD);
	}

	string closeBracket = tokenizer->getToken();
	match(closeBracket, SYMBOL_CLOSE_BRACKET);
	Next *n = new Next(leftChild, rightChild);

	qt->insertResult(n);
}
void QueryParser::getNextStar(QueryTree* qt) {
	Parameter leftChild;
	Parameter rightChild;
	string token = tokenizer->getToken();

	match(token, SYMBOL_OPEN_BRACKET);
	string lc = tokenizer->getToken();

	if (isVarNameExists(lc)) {
		leftChild = varMap[lc];
		string key = leftChild.getParaName();
		Type lcType = leftChild.getParaType();
		if (lcType == VARIABLE || lcType == CONSTANT || lcType == BOOLEAN || lcType == STRINGVARIABLE ||
			lcType == PROCEDURE || lcType == STMTLST) {
			throwError(ERROR_LEFT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = leftChild;
		}
	}
	else if (isPositiveInteger(lc)) {
		leftChild.setParaName(lc);
		leftChild.setParaType(INTEGER);
	}
	else if (lc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		leftChild.setParaName(lc);
		leftChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_LEFT_CHILD);
	}

	string comma = tokenizer->getToken();
	match(comma, SYMBOL_COMMA);
	string rc = tokenizer->getToken();
	if (isVarNameExists(rc)) {
		rightChild = varMap[rc];
		string key = rightChild.getParaName();
		Type rcType = rightChild.getParaType();
		if (rcType == VARIABLE || rcType == CONSTANT || rcType == BOOLEAN || rcType == STRINGVARIABLE ||
			rcType == PROCEDURE || rcType == STMTLST) {
			throwError(ERROR_RIGHT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = rightChild;
		}
	}
	else if (isPositiveInteger(rc)) {
		rightChild.setParaName(rc);
		rightChild.setParaType(INTEGER);
	}
	else if (rc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		rightChild.setParaName(rc);
		rightChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_RIGHT_CHILD);
	}

	string closeBracket = tokenizer->getToken();
	match(closeBracket, SYMBOL_CLOSE_BRACKET);
	NextStar *ns = new NextStar(leftChild, rightChild);

	qt->insertResult(ns);
}
void QueryParser::getNextBip(QueryTree* qt) {
	Parameter leftChild;
	Parameter rightChild;

	string token = tokenizer->getToken();

	match(token, SYMBOL_OPEN_BRACKET);
	string lc = tokenizer->getToken();

	if (isVarNameExists(lc)) {
		leftChild = varMap[lc];
		string key = leftChild.getParaName();
		Type lcType = leftChild.getParaType();
		if (lcType == VARIABLE || lcType == CONSTANT || lcType == BOOLEAN || lcType == STRINGVARIABLE ||
			lcType == PROCEDURE || lcType == STMTLST) {
			throwError(ERROR_LEFT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = leftChild;
		}
	}
	else if (isPositiveInteger(lc)) {
		leftChild.setParaName(lc);
		leftChild.setParaType(INTEGER);
	}
	else if (lc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		leftChild.setParaName(lc);
		leftChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_LEFT_CHILD);
	}

	string comma = tokenizer->getToken();
	match(comma, SYMBOL_COMMA);
	string rc = tokenizer->getToken();
	if (isVarNameExists(rc)) {
		rightChild = varMap[rc];
		string key = rightChild.getParaName();
		Type rcType = rightChild.getParaType();
		if (rcType == VARIABLE || rcType == CONSTANT || rcType == BOOLEAN || rcType == STRINGVARIABLE ||
			rcType == PROCEDURE || rcType == STMTLST) {
			throwError(ERROR_RIGHT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = rightChild;
		}
	}
	else if (isPositiveInteger(rc)) {
		rightChild.setParaName(rc);
		rightChild.setParaType(INTEGER);
	}
	else if (rc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		rightChild.setParaName(rc);
		rightChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_RIGHT_CHILD);
	}

	string closeBracket = tokenizer->getToken();
	match(closeBracket, SYMBOL_CLOSE_BRACKET);
	NextBip *n = new NextBip(leftChild, rightChild);

	qt->insertResult(n);
}
void QueryParser::getNextBipStar(QueryTree* qt) {
	Parameter leftChild;
	Parameter rightChild;
	string token = tokenizer->getToken();

	match(token, SYMBOL_OPEN_BRACKET);
	string lc = tokenizer->getToken();

	if (isVarNameExists(lc)) {
		leftChild = varMap[lc];
		string key = leftChild.getParaName();
		Type lcType = leftChild.getParaType();
		if (lcType == VARIABLE || lcType == CONSTANT || lcType == BOOLEAN || lcType == STRINGVARIABLE ||
			lcType == PROCEDURE || lcType == STMTLST) {
			throwError(ERROR_LEFT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = leftChild;
		}
	}
	else if (isPositiveInteger(lc)) {
		leftChild.setParaName(lc);
		leftChild.setParaType(INTEGER);
	}
	else if (lc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		leftChild.setParaName(lc);
		leftChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_LEFT_CHILD);
	}

	string comma = tokenizer->getToken();
	match(comma, SYMBOL_COMMA);
	string rc = tokenizer->getToken();
	if (isVarNameExists(rc)) {
		rightChild = varMap[rc];
		string key = rightChild.getParaName();
		Type rcType = rightChild.getParaType();
		if (rcType == VARIABLE || rcType == CONSTANT || rcType == BOOLEAN || rcType == STRINGVARIABLE ||
			rcType == PROCEDURE || rcType == STMTLST) {
			throwError(ERROR_RIGHT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = rightChild;
		}
	}
	else if (isPositiveInteger(rc)) {
		rightChild.setParaName(rc);
		rightChild.setParaType(INTEGER);
	}
	else if (rc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		rightChild.setParaName(rc);
		rightChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_RIGHT_CHILD);
	}

	string closeBracket = tokenizer->getToken();
	match(closeBracket, SYMBOL_CLOSE_BRACKET);
	NextBipStar *ns = new NextBipStar(leftChild, rightChild);

	qt->insertResult(ns);
}
void QueryParser::getAffects(QueryTree* qt) {
	Parameter leftChild;
	Parameter rightChild;

	string token = tokenizer->getToken();

	match(token, SYMBOL_OPEN_BRACKET);
	string lc = tokenizer->getToken();

	if (isVarNameExists(lc)) {
		leftChild = varMap[lc];
		string key = leftChild.getParaName();
		Type lcType = leftChild.getParaType();
		if (lcType == VARIABLE || lcType == CONSTANT || lcType == BOOLEAN || lcType == STRINGVARIABLE ||
			lcType == PROCEDURE || lcType == STMTLST || lcType == WHILE || lcType == IF || lcType == CALL) {
			throwError(ERROR_LEFT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = leftChild;
		}
	}
	else if (isPositiveInteger(lc)) {
		leftChild.setParaName(lc);
		leftChild.setParaType(INTEGER);
	}
	else if (lc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		leftChild.setParaName(lc);
		leftChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_LEFT_CHILD);
	}

	string comma = tokenizer->getToken();
	match(comma, SYMBOL_COMMA);
	string rc = tokenizer->getToken();
	if (isVarNameExists(rc)) {
		rightChild = varMap[rc];
		string key = rightChild.getParaName();
		Type rcType = rightChild.getParaType();
		if (rcType == VARIABLE || rcType == CONSTANT || rcType == BOOLEAN || rcType == STRINGVARIABLE ||
			rcType == PROCEDURE || rcType == STMTLST || rcType == WHILE || rcType == IF || rcType == CALL) {
			throwError(ERROR_RIGHT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = rightChild;
		}
	}
	else if (isPositiveInteger(rc)) {
		rightChild.setParaName(rc);
		rightChild.setParaType(INTEGER);
	}
	else if (rc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		rightChild.setParaName(rc);
		rightChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_RIGHT_CHILD);
	}

	string closeBracket = tokenizer->getToken();
	match(closeBracket, SYMBOL_CLOSE_BRACKET);
	Affects *a = new Affects(leftChild, rightChild);
	qt->insertResult(a);
}
void QueryParser::getAffectsStar(QueryTree* qt) {
	Parameter leftChild;
	Parameter rightChild;

	string token = tokenizer->getToken();

	match(token, SYMBOL_OPEN_BRACKET);
	string lc = tokenizer->getToken();

	if (isVarNameExists(lc)) {
		leftChild = varMap[lc];
		string key = leftChild.getParaName();
		Type lcType = leftChild.getParaType();
		if (lcType == VARIABLE || lcType == CONSTANT || lcType == BOOLEAN || lcType == STRINGVARIABLE ||
			lcType == PROCEDURE || lcType == STMTLST || lcType == WHILE || lcType == IF || lcType == CALL) {
			throwError(ERROR_LEFT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = leftChild;
		}
	}
	else if (isPositiveInteger(lc)) {
		leftChild.setParaName(lc);
		leftChild.setParaType(INTEGER);
	}
	else if (lc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		leftChild.setParaName(lc);
		leftChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_LEFT_CHILD);
	}

	string comma = tokenizer->getToken();
	match(comma, SYMBOL_COMMA);
	string rc = tokenizer->getToken();
	if (isVarNameExists(rc)) {
		rightChild = varMap[rc];
		string key = rightChild.getParaName();
		Type rcType = rightChild.getParaType();
		if (rcType == VARIABLE || rcType == CONSTANT || rcType == BOOLEAN || rcType == STRINGVARIABLE ||
			rcType == PROCEDURE || rcType == STMTLST || rcType == WHILE || rcType == IF || rcType == CALL) {
			throwError(ERROR_RIGHT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = rightChild;
		}
	}
	else if (isPositiveInteger(rc)) {
		rightChild.setParaName(rc);
		rightChild.setParaType(INTEGER);
	}
	else if (rc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		rightChild.setParaName(rc);
		rightChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_RIGHT_CHILD);
	}

	string closeBracket = tokenizer->getToken();
	match(closeBracket, SYMBOL_CLOSE_BRACKET);
	AffectsStar *as = new AffectsStar(leftChild, rightChild);
	qt->insertResult(as);
}
void QueryParser::getAffectsBip(QueryTree* qt) {
	Parameter leftChild;
	Parameter rightChild;

	string token = tokenizer->getToken();

	match(token, SYMBOL_OPEN_BRACKET);
	string lc = tokenizer->getToken();

	if (isVarNameExists(lc)) {
		leftChild = varMap[lc];
		string key = leftChild.getParaName();
		Type lcType = leftChild.getParaType();
		if (lcType == VARIABLE || lcType == CONSTANT || lcType == BOOLEAN || lcType == STRINGVARIABLE ||
			lcType == PROCEDURE || lcType == STMTLST || lcType == WHILE || lcType == IF || lcType == CALL) {
			throwError(ERROR_LEFT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = leftChild;
		}
	}
	else if (isPositiveInteger(lc)) {
		leftChild.setParaName(lc);
		leftChild.setParaType(INTEGER);
	}
	else if (lc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		leftChild.setParaName(lc);
		leftChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_LEFT_CHILD);
	}

	string comma = tokenizer->getToken();
	match(comma, SYMBOL_COMMA);
	string rc = tokenizer->getToken();
	if (isVarNameExists(rc)) {
		rightChild = varMap[rc];
		string key = rightChild.getParaName();
		Type rcType = rightChild.getParaType();
		if (rcType == VARIABLE || rcType == CONSTANT || rcType == BOOLEAN || rcType == STRINGVARIABLE ||
			rcType == PROCEDURE || rcType == STMTLST || rcType == WHILE || rcType == IF || rcType == CALL) {
			throwError(ERROR_RIGHT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = rightChild;
		}
	}
	else if (isPositiveInteger(rc)) {
		rightChild.setParaName(rc);
		rightChild.setParaType(INTEGER);
	}
	else if (rc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		rightChild.setParaName(rc);
		rightChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_RIGHT_CHILD);
	}

	string closeBracket = tokenizer->getToken();
	match(closeBracket, SYMBOL_CLOSE_BRACKET);
	AffectsBip *a = new AffectsBip(leftChild, rightChild);
	qt->insertResult(a);
}
void QueryParser::getAffectsBipStar(QueryTree* qt) {
	Parameter leftChild;
	Parameter rightChild;

	string token = tokenizer->getToken();

	match(token, SYMBOL_OPEN_BRACKET);
	string lc = tokenizer->getToken();

	if (isVarNameExists(lc)) {
		leftChild = varMap[lc];
		string key = leftChild.getParaName();
		Type lcType = leftChild.getParaType();
		if (lcType == VARIABLE || lcType == CONSTANT || lcType == BOOLEAN || lcType == STRINGVARIABLE ||
			lcType == PROCEDURE || lcType == STMTLST || lcType == WHILE || lcType == IF || lcType == CALL) {
			throwError(ERROR_LEFT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = leftChild;
		}
	}
	else if (isPositiveInteger(lc)) {
		leftChild.setParaName(lc);
		leftChild.setParaType(INTEGER);
	}
	else if (lc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		leftChild.setParaName(lc);
		leftChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_LEFT_CHILD);
	}

	string comma = tokenizer->getToken();
	match(comma, SYMBOL_COMMA);
	string rc = tokenizer->getToken();
	if (isVarNameExists(rc)) {
		rightChild = varMap[rc];
		string key = rightChild.getParaName();
		Type rcType = rightChild.getParaType();
		if (rcType == VARIABLE || rcType == CONSTANT || rcType == BOOLEAN || rcType == STRINGVARIABLE ||
			rcType == PROCEDURE || rcType == STMTLST || rcType == WHILE || rcType == IF || rcType == CALL) {
			throwError(ERROR_RIGHT_CHILD);
		}
		if (!isUsedExists(key)) {
			usedMap[key] = rightChild;
		}
	}
	else if (isPositiveInteger(rc)) {
		rightChild.setParaName(rc);
		rightChild.setParaType(INTEGER);
	}
	else if (rc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		rightChild.setParaName(rc);
		rightChild.setParaType(ANYTHING);
	}
	else {
		throwError(ERROR_RIGHT_CHILD);
	}

	string closeBracket = tokenizer->getToken();
	match(closeBracket, SYMBOL_CLOSE_BRACKET);
	AffectsBipStar *as = new AffectsBipStar(leftChild, rightChild);
	qt->insertResult(as);
}
void QueryParser::getPattern(QueryTree *qt) {
	Parameter leftChild;
	Parameter rightChild;
	Parameter factor;
	bool hasUnderScore = FALSE;

	string lc = tokenizer->getToken();

	if (!isVarNameExists(lc)) {
		throwError(ERROR_LEFT_CHILD);
	}
	leftChild = varMap[lc];
	Type lcType = leftChild.getParaType();
	if (lcType != ASSIGN && lcType != WHILE && lcType != IF) {
		throwError(ERROR_LEFT_CHILD);
	}
	string key = leftChild.getParaName();
	if (!isUsedExists(key)) {
		usedMap[key] = leftChild;
	}

	string openBracket = tokenizer->getToken();
	match(openBracket, SYMBOL_OPEN_BRACKET);
	string rc = tokenizer->getToken();
	if (lcType == ASSIGN || lcType == WHILE) {
		if (isVarNameExists(rc)) {
			rightChild = varMap[rc];
			Type rcType = rightChild.getParaType();
			if (rcType != VARIABLE) {
				throwError(ERROR_RIGHT_CHILD);
			}
			string key = rightChild.getParaName();
			if (!isUsedExists(key)) {
				usedMap[key] = rightChild;
			}
		}
		else if (rc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
			rightChild.setParaName(rc);
			rightChild.setParaType(ANYTHING);
		}
		else if (rc.compare(SYMBOL_QUOTE) == EQUAL) {

			string var = tokenizer->getToken();
			match(var, IDENT);
			rightChild.setParaName(var);
			rightChild.setParaType(STRINGVARIABLE);
			if (tokenizer->peekToken().compare(SYMBOL_QUOTE) != EQUAL) {
				throwError(ERROR_LEFT_CHILD);
			}
			tokenizer->getToken();
		}
		else {
			throwError(ERROR_RIGHT_CHILD);
		}

		string comma = tokenizer->getToken();
		match(comma, SYMBOL_COMMA);
		string fact = tokenizer->getToken();
		string close = tokenizer->peekToken();

		if (lcType == WHILE) {
			if (fact.compare(SYMBOL_UNDERSCORE) == EQUAL && close.compare(SYMBOL_PATTERN_CLOSE) == EQUAL) {
				factor.setParaName(fact);
				factor.setParaType(ANYTHING);
			}
			else {
				throwError(ERROR_FACTOR);
			}
		}
		else {
			if (fact.compare(SYMBOL_UNDERSCORE) == EQUAL && close.compare(SYMBOL_PATTERN_CLOSE) == EQUAL) {
				factor.setParaName(fact);
				factor.setParaType(ANYTHING);
			}
			else if (fact.compare(SYMBOL_UNDERSCORE) == EQUAL && close.compare(SYMBOL_PATTERN_CLOSE) != EQUAL) {

				string firstQuote = tokenizer->getToken();
				match(firstQuote, SYMBOL_QUOTE);
				string exp = SYMBOL_NONE;
				while (tokenizer->hasNextToken() && tokenizer->peekToken().compare(SYMBOL_QUOTE) != EQUAL) {
					exp += tokenizer->getToken();
				}
				if (!ExpOperation::isValidExp(exp)) {
					throwError(ERROR_FACTOR);
				}
				string lastQuote = tokenizer->getToken();
				match(lastQuote, SYMBOL_QUOTE);
				string lastUnderScore = tokenizer->getToken();
				if (lastUnderScore.compare(SYMBOL_UNDERSCORE) != EQUAL) {
					throwError(ERROR_FACTOR);
				}
				factor.setParaName(exp);
				factor.setParaType(STRINGVARIABLE);
				hasUnderScore = TRUE;
			}
			else if (fact.compare(SYMBOL_QUOTE) == EQUAL) {// pattern's expression 

				string exp = SYMBOL_NONE;
				while (tokenizer->hasNextToken() && tokenizer->peekToken().compare(SYMBOL_QUOTE) != EQUAL) {
					exp += tokenizer->getToken();
				}
				if (!ExpOperation::isValidExp(exp)) {
					throwError(ERROR_FACTOR);
				}
				factor.setParaName(exp);
				factor.setParaType(STRINGVARIABLE);

				tokenizer->getToken();
			}
			else {
				throwError(ERROR_FACTOR);
			}
		}
	}
	else {// for the pattern if
		if (isVarNameExists(rc)) {
			rightChild = varMap[rc];
			Type rcType = rightChild.getParaType();
			if (rcType != VARIABLE) {
				throwError(ERROR_RIGHT_CHILD);
			}
			string key = rightChild.getParaName();
			if (!isUsedExists(key)) {
				usedMap[key] = rightChild;
			}
		}
		else if (rc.compare(SYMBOL_UNDERSCORE) == EQUAL) {
			rightChild.setParaName(rc);
			rightChild.setParaType(ANYTHING);
		}
		else if (rc.compare(SYMBOL_QUOTE) == EQUAL) {

			string var = tokenizer->getToken();
			match(var, IDENT);
			rightChild.setParaName(var);
			rightChild.setParaType(STRINGVARIABLE);
			if (tokenizer->peekToken().compare(SYMBOL_QUOTE) != EQUAL) {
				throwError(ERROR_LEFT_CHILD);
			}
			tokenizer->getToken();
		}
		else {
			throwError(ERROR_RIGHT_CHILD);
		}


		string comma = tokenizer->getToken();
		match(comma, SYMBOL_COMMA);
		string fact = tokenizer->getToken();

		if (fact.compare(SYMBOL_UNDERSCORE) == EQUAL) {
			factor.setParaName(fact);
			factor.setParaType(ANYTHING);
		}
		else {
			throwError(ERROR_FACTOR);
		}

		string comma2 = tokenizer->getToken();
		match(comma2, SYMBOL_COMMA);
		string fact2 = tokenizer->getToken();

		if (fact2.compare(SYMBOL_UNDERSCORE) == EQUAL) {
		}
		else {
			throwError(ERROR_FACTOR);
		}
	}

	string closeBracket = tokenizer->getToken();
	match(closeBracket, SYMBOL_CLOSE_BRACKET);
	Pattern *p = new Pattern(leftChild, rightChild, factor, hasUnderScore);
	qt->insertResult(p);
	string andStr = tokenizer->peekToken();
	if (andStr.compare(TYPE_AND) == EQUAL) {
		tokenizer->getToken();
		getPattern(qt);
	}
}
void QueryParser::getWith(QueryTree *qt) {
	Parameter leftChild;
	Parameter rightChild;
	Type leftType;
	Type rightType;
	string lc = tokenizer->getToken();


	if (isVarNameExists(lc)) {
		leftChild = varMap[lc];
		Type lcType = leftChild.getParaType();
		string dot = tokenizer->peekToken();

		if (lcType == STMT || lcType == ASSIGN || lcType == WHILE || lcType == IF || lcType == PROG_LINE) {
			if (dot.compare(SYMBOL_FULL_STOP) == EQUAL) {
				if (lcType == PROG_LINE) {
					throwError(ERROR_LEFT_CHILD);
				}
				tokenizer->getToken();
				string lcValue = tokenizer->peekToken();
				match(lcValue, TYPE_STMT);
				tokenizer->getToken();
				string stmtNo = tokenizer->peekToken();
				match(stmtNo, SYMBOL_STMT_NO);
				tokenizer->getToken();
			}
			else {
				if (lcType != PROG_LINE) {
					throwError(ERROR_LEFT_CHILD);
				}
			}
			leftType = INTEGER;
		}
		else if (lcType == CALL) {
			if (dot.compare(SYMBOL_FULL_STOP) == EQUAL) {
				tokenizer->getToken();
				string lcValue = tokenizer->peekToken();
				if (lcValue.compare(TYPE_STMT) == EQUAL) {
					tokenizer->getToken();
					string stmtNo = tokenizer->peekToken();
					match(stmtNo, SYMBOL_STMT_NO);
					leftType = INTEGER;
					leftChild.setAttributeProc(FALSE);
				}
				else if (lcValue.compare(TYPE_PROC_NAME) == EQUAL) {
					leftType = STRINGVARIABLE;
					leftChild.setAttributeProc(TRUE);
				}
				else {
					throwError(ERROR_LEFT_CHILD);
				}
				tokenizer->getToken();
			}
			else {
				throwError(ERROR_STRING);
			}
		}
		else if (lcType == PROCEDURE) {
			match(dot, SYMBOL_FULL_STOP);
			tokenizer->getToken();
			string lcValue = tokenizer->peekToken();
			if (lcValue.compare(TYPE_PROC_NAME) != EQUAL) {
				throwError(ERROR_LEFT_CHILD);
			}
			tokenizer->getToken();
			leftType = STRINGVARIABLE;
		}
		else if (lcType == VARIABLE) {
			match(dot, SYMBOL_FULL_STOP);
			tokenizer->getToken();
			string lcValue = tokenizer->peekToken();
			if (lcValue.compare(TYPE_VARNAME) != EQUAL) {
				throwError(ERROR_LEFT_CHILD);
			}
			tokenizer->getToken();
			leftType = STRINGVARIABLE;
		}
		else if (lcType == CONSTANT) {
			match(dot, SYMBOL_FULL_STOP);
			tokenizer->getToken();
			string lcValue = tokenizer->peekToken();
			if (lcValue.compare(TYPE_VALUE) != EQUAL) {
				throwError(ERROR_LEFT_CHILD);
			}
			tokenizer->getToken();
			leftType = INTEGER;
		}
		else {
			throwError(ERROR_LEFT_CHILD);
		}
		string key = leftChild.getParaName();
		if (!isUsedExists(key)) {
			usedMap[key] = leftChild;
		}
	}
	else if (isPositiveInteger(lc)) {
		leftChild.setParaName(lc);
		leftChild.setParaType(INTEGER);
		leftType = INTEGER;
	}
	else if (lc.compare(SYMBOL_QUOTE) == EQUAL) {

		string proceName = tokenizer->getToken();
		match(proceName, IDENT);
		leftChild.setParaName(proceName);
		leftChild.setParaType(STRINGVARIABLE);
		if (tokenizer->peekToken().compare(SYMBOL_QUOTE) != EQUAL) {
			throwError(ERROR_LEFT_CHILD);
		}
		tokenizer->getToken();
		leftType = STRINGVARIABLE;
	}
	else {
		throwError(ERROR_LEFT_CHILD);
	}


	string equalSign = tokenizer->getToken();
	match(equalSign, SYMBOL_EQUALS);
	string rc = tokenizer->getToken();

	if (isVarNameExists(rc)) {
		rightChild = varMap[rc];
		Type rcType = rightChild.getParaType();
		string dot = tokenizer->peekToken();

		if (rcType == STMT || rcType == ASSIGN || rcType == WHILE || rcType == IF || rcType == PROG_LINE) {
			if (dot.compare(SYMBOL_FULL_STOP) == EQUAL) {
				if (rcType == PROG_LINE) {
					throwError(ERROR_RIGHT_CHILD);
				}
				tokenizer->getToken();
				string rcValue = tokenizer->peekToken();
				match(rcValue, TYPE_STMT);
				tokenizer->getToken();
				string stmtNo = tokenizer->peekToken();
				match(stmtNo, SYMBOL_STMT_NO);
				tokenizer->getToken();
				rightType = INTEGER;
			}
			else {
				if (rcType != PROG_LINE) {
					throwError(ERROR_RIGHT_CHILD);
				}
			}
			rightType = INTEGER;
		}
		else if (rcType == CALL) {
			if (dot.compare(SYMBOL_FULL_STOP) == EQUAL) {
				tokenizer->getToken();
				string rcValue = tokenizer->peekToken();
				if (rcValue.compare(TYPE_STMT) == EQUAL) {
					tokenizer->getToken();
					string stmtNo = tokenizer->peekToken();
					match(stmtNo, SYMBOL_STMT_NO);
					rightType = INTEGER;
					rightChild.setAttributeProc(FALSE);
				}
				else if (rcValue.compare(TYPE_PROC_NAME) == EQUAL) {
					rightType = STRINGVARIABLE;
					rightChild.setAttributeProc(TRUE);
				}
				else {
					throwError(ERROR_LEFT_CHILD);
				}
				tokenizer->getToken();
			}
			else {
				throwError(ERROR_STRING);
			}
		}
		else if (rcType == PROCEDURE) {
			match(dot, SYMBOL_FULL_STOP);
			tokenizer->getToken();
			string rcValue = tokenizer->peekToken();
			if (rcValue.compare(TYPE_PROC_NAME) != EQUAL) {
				throwError(ERROR_LEFT_CHILD);
			}
			tokenizer->getToken();
			rightType = STRINGVARIABLE;
		}
		else if (rcType == VARIABLE) {
			match(dot, SYMBOL_FULL_STOP);
			tokenizer->getToken();
			string rcValue = tokenizer->peekToken();
			if (rcValue.compare(TYPE_VARNAME) != EQUAL) {
				throwError(ERROR_LEFT_CHILD);
			}
			tokenizer->getToken();
			rightType = STRINGVARIABLE;
		}
		else if (rcType == CONSTANT) {
			match(dot, SYMBOL_FULL_STOP);
			tokenizer->getToken();
			string rcValue = tokenizer->peekToken();
			if (rcValue.compare(TYPE_VALUE) != EQUAL) {
				throwError(ERROR_LEFT_CHILD);
			}
			tokenizer->getToken();
			rightType = INTEGER;
		}
		else {
			throwError(ERROR_RIGHT_CHILD);
		}
		string key = rightChild.getParaName();
		if (!isUsedExists(key)) {
			usedMap[key] = rightChild;
		}
	}
	else if (isPositiveInteger(rc)) {
		rightChild.setParaName(rc);
		rightChild.setParaType(INTEGER);
		rightType = INTEGER;
	}
	else if (rc.compare(SYMBOL_QUOTE) == EQUAL) {
		string proceName = tokenizer->getToken();
		match(proceName, IDENT);
		rightChild.setParaName(proceName);
		rightChild.setParaType(STRINGVARIABLE);
		if (tokenizer->peekToken().compare(SYMBOL_QUOTE) != EQUAL) {
			throwError(ERROR_RIGHT_CHILD);
		}
		rightType = STRINGVARIABLE;
		tokenizer->getToken();
	}
	else {
		throwError(ERROR_RIGHT_CHILD);
	}

	if (leftType != rightType) {
		throwError(ERROR_CHILD_TYPE);
	}
	With *w = new With(leftChild, rightChild);

	qt->insertResult(w);

	string andStr = tokenizer->peekToken();
	if (andStr.compare(TYPE_AND) == EQUAL) {
		tokenizer->getToken();
		getWith(qt);
	}

}
bool QueryParser::isVarNameExists(string varName) {
	auto iter = varMap.find(varName);

	if (iter == varMap.end()) {
		return false;
	}

	return true;
}
bool QueryParser::isUsedExists(string name) {
	auto iter = usedMap.find(name);

	if (iter == usedMap.end()) {
		return false;
	}

	return true;
}
bool QueryParser::isPositiveInteger(string str) {
	if (str.empty() || !isdigit(str.at(0)) || str.at(0) == SYMBOL_START) {
		return false;
	}

	char *p;
	strtol(str.c_str(), &p, SIZE);

	return (*p == EMPTY);
}
void QueryParser::match(string token, string matchRe) {

	if (!tokenizer->match(token, matchRe)) {
		if (isSelectBoolean) {
			throwError(ERROR_SELECT_BOOLEAN);
		}
		else {
			throwError(ERROR_STRING);
		}
	}
}

void QueryParser::throwError(string errorMsg) {
	delete tokenizer;
	if (isSelectBoolean) {
		throw logic_error(ERROR_SELECT_BOOLEAN);
	}
	else {
		throw runtime_error(ERROR_STRING);
	}
}
