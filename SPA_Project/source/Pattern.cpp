#include "Pattern.h"
#include "ExpOperation.h"
#include "Tokenizer.h"
#include "VectorSetOperation.h"

Pattern::Pattern(string stmtSynonym, Type synType, string leftPattern, Type leftPatType, string rightPattern, Type rightPatType, bool isUnderscore) {
	leftChild = stmtSynonym;
	leftChildType = synType;

	rightChild = leftPattern;
	rightChildType = leftPatType;

	hasUnderScore = isUnderscore;
	factor = rightPattern;
	factorType = rightPatType;
}

bool Pattern::hasRel(PKB *pkb) {
	vector<int> results = getWithRelToLeft(pkb);
	if ((int)results.size() <= 0) {
		return false;
	} else {
		return true;
	}
}

vector<int> Pattern::getWithRelToLeft(PKB *pkb) {
	vector<int> leftPatternStmts = getFirstPatternStmts(pkb);
	vector<int> rightPatternStmts = getSecondPatternStmts(pkb);
	return VectorSetOperation<int>::setIntersection(leftPatternStmts, rightPatternStmts);
}

vector<int> Pattern::getWithRelToRight(PKB *pkb) {
	vector<int> resultStmts = getSecondPatternStmts(pkb);
	return getVarFromStmts(pkb, resultStmts);
}

vector<int> Pattern::getFirstPatternStmts(PKB* pkb) {
	vector<int> leftPatternStmts;
	if (rightChildType == STRINGVARIABLE) {
		int varId = pkb->getVarIdByName(rightChild);
		leftPatternStmts = getTypeStmtModifiedByVar(pkb, varId);
	}
	else {
		leftPatternStmts = getAllTypeStmts(pkb);
	}
	return leftPatternStmts;
}

vector<int> Pattern::getSecondPatternStmts(PKB* pkb) {
	vector<int> results;

	if (factorType == Type::STRINGVARIABLE) {
		string prefix = getPrefix(factor);
		results = getAssignStmtWithPrefix(pkb, prefix);
	}
	else {
		results = getAllTypeStmts(pkb);
	}
	return results;
}

vector<int> Pattern::getAllTypeStmts(PKB* pkb) {
	switch (leftChildType) {
	case ASSIGN:
		return pkb->getAllAssignStmt();
	case WHILE:
		return pkb->getAllWhileStmt();
	case IF:
		//return pkb->getallIfStmt();
	default:
		return vector<int>();
	}
}

vector<int> Pattern::getTypeStmtModifiedByVar(PKB* pkb, int varId) {
	vector<int> stmts;
	switch (leftChildType) {
	case ASSIGN:
		stmts = pkb->getAllAssignStmt();
	case WHILE:
		stmts = pkb->getAllWhileStmt();
	case IF:
		//stmts = pkb->getallIfStmt();
	default:
		stmts = vector<int>();
	}

	vector <int> modifyStmts = pkb->getStmtModifyVar(varId);
	return VectorSetOperation<int>::setIntersection(stmts, modifyStmts);
}

vector<int> Pattern::getVarFromStmts(PKB *pkb, vector<int> stmts) {
	vector<int> resultVars;
	for (int i = 0; i < (int)stmts.size(); i++) {
		vector<int> modifiedVars = pkb->getVarModifiedInStmt(stmts[i]);
		resultVars = VectorSetOperation<int>::setUnion(modifiedVars, resultVars);
	}
	return resultVars;
}

vector<int> Pattern::getAssignStmtWithPrefix(PKB* pkb, string prefix) {
	vector<int> results;
	vector<int> assignStmts = pkb->getAllAssignStmt();
	if (hasUnderScore) {
		for (int i = 0; i < (int)assignStmts.size(); i++) {
			if (pkb->getExpInAssignStmt(assignStmts[i]).find(prefix) != string::npos) {
				results.push_back(assignStmts[i]);
			}
		}
	}
	else {
		for (int i = 0; i < (int)assignStmts.size(); i++) {
			if (pkb->getExpInAssignStmt(assignStmts[i]).compare(prefix) == 0) {
				results.push_back(assignStmts[i]);
			}
		}
	}
	return results;
}

string Pattern::getPrefix(string infixString) {
	Tokenizer tokenizer(infixString);
	stack<string> infix;
	while (tokenizer.hasNextToken()) {
		infix.push(tokenizer.getToken());
	}

	stack<string> prefix = ExpOperation::evaluatePrefix(infix);
	string prefixString;
	while (!prefix.empty()) {
		prefixString += prefix.top() + "|";
		prefix.pop();
	}

	return prefixString;
}


void Pattern::setUnderScore(bool us) {
	hasUnderScore = us;
}

void Pattern::setFactor(string f) {
	factor = f;
}

string Pattern::getFactor() {
	return factor;
}

bool Pattern::getUnderScore() {
	return hasUnderScore;
}

string Pattern::getLeftChild() {
	return leftChild;
}

string Pattern::getRightChild() {
	return rightChild;
}

Type Pattern::getLeftChildType() {
	return leftChildType;
}

Type Pattern::getRightChildType() {
	return rightChildType;
}

Type Pattern::getFactorType() {
	return factorType;
}

ClauseType Pattern::getClauseType() {
	return PATTERN;
}