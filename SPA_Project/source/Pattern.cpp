#include "Pattern.h"
#include "ExpOperation.h"
#include "Tokenizer.h"
#include "VectorSetOperation.h"

Pattern::Pattern(string stmtSynonym, Type synType, string leftPattern, Type leftPatType, bool hasUnderscore, string rightPattern, Type rightPatType) {
	leftChild = stmtSynonym;
	leftChildType = synType;

	rightChild = leftPattern;
	rightChildType = leftPatType;

	isUnderScore = hasUnderscore;
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
	cout << endl << "result of getRightPatternStmts: ";
	return getVarFromAssignStmts(pkb, resultStmts);
}

vector<int> Pattern::getFirstPatternStmts(PKB* pkb) {
	vector<int> leftPatternStmts;
	if (rightChildType == STRINGVARIABLE) {
		int varId = pkb->getVarIdByName(rightChild);
		leftPatternStmts = getAssignStmtModifiedByVar(pkb, varId);
	}
	else {
		leftPatternStmts = pkb->getAllAssignStmt();
	}
	return leftPatternStmts;
}

vector<int> Pattern::getSecondPatternStmts(PKB* pkb) {
	vector<int> results;

	if (factorType == Type::STRINGVARIABLE) {
		string prefix = getPrefix(factor);

		vector<int> assignStmts = pkb->getAllAssignStmt();
		if (isUnderScore) {
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
	}
	else {
		results = pkb->getAllAssignStmt();
	}
	return results;
}

vector<int> Pattern::getAssignStmtModifiedByVar(PKB* pkb, int varId) {
	vector<int> assignStmts = pkb->getAllAssignStmt();
	vector <int> modifyStmts = pkb->getStmtModifyVar(varId);
	return VectorSetOperation<int>::setIntersection(assignStmts, modifyStmts);
}

vector<int> Pattern::getVarFromAssignStmts(PKB *pkb, vector<int> assignStmts) {
	vector<int> resultVars;
	for (int i = 0; i < (int)assignStmts.size(); i++) {
		vector<int> modifiedVars = pkb->getVarModifiedInStmt(assignStmts[i]);
		resultVars = VectorSetOperation<int>::setUnion(modifiedVars, resultVars);
	}
	return resultVars;
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
		prefixString += prefix.top();
		prefix.pop();
	}

	return prefixString;
}


void Pattern::setUnderScore(bool us) {
	isUnderScore = us;
}

void Pattern::setFactor(string f) {
	factor = f;
}

string Pattern::getFactor() {
	return factor;
}

bool Pattern::getUnderScore() {
	return isUnderScore;
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