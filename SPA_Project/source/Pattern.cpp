#include "Pattern.h"
#include "ExpOperation.h"
#include "Tokenizer.h"
#include "VectorSetOperation.h"


Pattern::Pattern(Parameter lc, Parameter rc, Parameter f) {
	leftChild = lc;
	rightChild = rc;
	factor = f;
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
	if (rightChild.getParaType() == STRINGVARIABLE) {
		int varId = pkb->getVarIdByName(rightChild.getParaName());
		leftPatternStmts = getTypeStmtModifiedByVar(pkb, varId);
	}
	else {
		leftPatternStmts = getAllTypeStmts(pkb);
	}
	return leftPatternStmts;
}

vector<int> Pattern::getSecondPatternStmts(PKB* pkb) {
	vector<int> results;

	if (factor.getParaType() == Type::STRINGVARIABLE) {
		string prefix = getPrefix(factor.getParaName());
		results = getAssignStmtWithPrefix(pkb, prefix);
	}
	else {
		results = getAllTypeStmts(pkb);
	}
	return results;
}

vector<int> Pattern::getAllTypeStmts(PKB* pkb) {
	switch (leftChild.getParaType()) {
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
	switch (leftChild.getParaType()) {
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

void Pattern::setSynList(Parameter lc, Parameter rc, Parameter factor) {
	if (lc.getParaType() != Type::CONSTANT && lc.getParaType() != Type::BOOLEAN && lc.getParaType() != Type::ANYTHING
		&& lc.getParaType() != Type::STRINGVARIABLE && lc.getParaType() != Type::INTEGER) {
		synList.push_back(lc);
	}
	if (rc.getParaType() != Type::CONSTANT && rc.getParaType() != Type::BOOLEAN && rc.getParaType() != Type::ANYTHING
		&& rc.getParaType() != Type::STRINGVARIABLE && rc.getParaType() != Type::INTEGER) {
		synList.push_back(rc);
	}
	if (factor.getParaType() != Type::CONSTANT && factor.getParaType() != Type::BOOLEAN && factor.getParaType() != Type::ANYTHING
		&& factor.getParaType() != Type::STRINGVARIABLE && factor.getParaType() != Type::INTEGER) {
		synList.push_back(factor);
	}
}

/*
void Pattern::setFactor(string f) {
	factor = f;
}

string Pattern::getFactor() {
	return factor;
}
*/

bool Pattern::getUnderScore() {
	return hasUnderScore;
}

Parameter Pattern::getLeftChild() {
	return leftChild;
}

Parameter Pattern::getRightChild() {
	return rightChild;
}

Parameter Pattern::getFactor() {
	return factor;
}

vector<Parameter> Pattern::getSynList() {
	return synList;
}
/*
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
*/
