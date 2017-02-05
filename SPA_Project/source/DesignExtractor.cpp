#pragma once

#include "DesignExtractor.h"

using namespace std;
/*
Unused Code:
unordered_map<int, int> parentsMap, followsMap, followedByMap;
unordered_map<int, vector<int>> childrensMap;
stack<int> statementStack;

int assignedStatementNum;


void processAssign(Tnode currentNode);
void processWhile(Tnode currentNode);
void processProcedure(Tnode currentNode);
void processVariable(Tnode currentNode);
void processArithmetic(Tnode currentNode);
void processStatementList(Tnode* currentNode);
void processChildren(Tnode parent);
*/

DesignExtractor::DesignExtractor(PKB* pkbSource) {
	pkb = pkbSource;
}

void DesignExtractor::extractStarRelations() {
	extractFollowsStar();
	extractParentStar();
}

void DesignExtractor::extractFollowsStar() {
	int statementNum = 0, numOfStatements = pkb->getTotalStmtNum(), followStar = 0;
	for (int i = 0; i < numOfStatements; i++) {
		statementNum = i;
		followStar = pkb->getFollowDirect(statementNum);
		followStar = pkb->getFollowDirect(statementNum);
		while (followStar != -1) {
			cout << "Follower: " << statementNum << ", Follows: " << followStar << endl;
			pkb->insertFollowRel(statementNum, followStar);
			followStar = pkb->getFollowDirect(followStar);
		}
	}
}

void DesignExtractor::extractParentStar() {
	int statementNum = 0, numOfStatements = pkb->getTotalStmtNum(), parentStar = 0;
	for (int i = 0; i < numOfStatements; i++) {
		statementNum = i;
		parentStar = pkb->getParentDirect(statementNum);
		parentStar = pkb->getParentDirect(statementNum);
		while (parentStar != -1) {
			pkb->insertParentRel(statementNum, parentStar);
			parentStar = pkb->getParentDirect(parentStar);
		}
	}
}

/*
Unused code:

//performs depth first search and extract information from AST
void initialiseTables(TNode* currentNode) {
	switch (getType(currentNode)) {
	case Procedure:
		processProcedure((TNodeProc*)currentNode);
		break;
	case Variable:
		processVariable((TNodeVar*)currentNode);
		break;
	case while:
		processWhile((TNodeWhile*)currentNode);
		break;
	case assign:
		processAssign((TNodeAssign*)currentNode);
		break;
	case statementList:
		processStatementList((TNodeStmtLst*)currentNode);
		break;
	case minus:
	case plus:
	case times:
		processArithmetic((TNodeExpr*)currentNode);
		break;

	}
}

void processStatementList(TNodeStmtLst* currentNode) {
	vector<int> childrenStatements = getStmtLstChildren();
	int numberOfStatements = childrenStatements.size();
	for (int i = 0; i < numberOfStatements; i++) {
		followsMap.insert(childrenStatements[i], childrenStatements[i + 1]);
		followedByMap.insert(childrenStatements[i + 1], childrenStatements[i]);
	}
}

void processChildren(TNode parent) {
	for (int i = 0; i < parent.childList.size; i++) {
		initialiseTables(parent.childList.get(i));
	}
}

void processArithmetic(TNodeExpr* currentNode) {
	vector<TNode*> childList = getExprChildren();
	int numChildren = childList.size();
	for (int i = 0; i < numChildren; i++) {
		TNode* child = childList[i];
		if(getType(child) == variable)
			addUses(assignedStateNum, child.name);
	}
	processChildren(currentNode);
}

void processVariable(TNodeVar* currentNode) {
	addVariable(getName(currentNode));
	processChildren(currentNode);
}

void processProcedure(TNodeProc* currentNode) {
	addProcedure(getName(currentNode));
	processChildren(currentNode);
}

void processWhile(TNodeWhile* currentNode) {
	int statementNum = getStatementNum(currentNode);
	if (!statementStack.empty()) {
		parentsMap.insert(statementNum, statementStack.top());
		auto iterator = childrensMap.find(statementStack.top());
		if (iterator != childrensMap.end()) {
			vector<int> childrenList = iterator->second;
			childrenList.push_back(statementNum);
		}
		else {
			childrensMap.insert(statementStack.top(), statementNum);
		}
	}
	statementStack.push(statementNum);
	addStatement(statementNum, while);
	addUses(statementNum, getCtrlVar(currentNode));
	processChildren(currentNode);
	statementStack.pop();
}

void processAssign(TNodeAssign* currentNode) {
	int statementNum = getStatementNum(currentNode);
	if (!statementStack.empty()) {
		parentsMap.insert(statementNum, statementStack.top());
		childrensMap.insert(statementStack.top(), statementNum);
	}
	addStatement(statementNum, getType(currentNode));
	addModifies(statementNum, getModifiedVar(currentNode));
	assignedStatementNum = statementNum;
	processChildren(currentNode);
}


void extractFollowsStar() {
	int statementNum = 0, numOfStatements = getNumOfStatements();
	for (int i = 0; i< numOfStatements; i++) {
		statementNum = i;
		vector<int> listOfFollows;
		unordered_map<int, int>::const_iterator iterator = followsMap.find(statementNum);
		while (iterator != followsMap.end()) {
			listOfFollows.push_back(iterator->second);
			iterator++;
		}
		addFollows(statementNum, listOfFollows);
	}
}

void extractParentStar() {
	int statementNum = 0, numOfStatements = getNumOfStatements();
	for (int i = 0; i< numOfStatements; i++) {
		statementNum = i;
		vector<int> listOfParents;
		unordered_map<int, int>::const_iterator iterator = parentsMap.find(statementNum);
		while (iterator != parentsMap.end()) {
			listOfParents.push_back(iterator->second);
			iterator++;
		}
		addParents(statementNum, listOfParents);
	}
}

void extractFollowedByStar() {
	
	int statementNum = 0, numOfStatements = getNumOfStatements();
	for (int i = 0; i< numOfStatements; i++) {
		statementNum = i;
		vector<int> listOfFollowedBy;
		unordered_map<int, int>::const_iterator iterator = followedByMap.find(statementNum);
		while (iterator != followsMap.end()) {
			listOfFollowedBy.push_back(iterator->second);
			iterator++;
		}
		addFollowedBy(statementNum, listOfFollowedBy);
	}
}

void extractChildrenStar() {
	int statementNum = 0, numOfStatements = getNumOfStatements();
	for (int i = 0; i< numOfStatements; i++) {
		statementNum = i;
		vector<int> listOfDirectChildren, listOfChildrenStar;
		unordered_map<int, vector<int>>::const_iterator iterator = childrensMap.find(statementNum);
		if (iterator != childrensMap.end()) {
			listOfDirectChildren = iterator->second;
			for (int j = 0; j < listOfDirectChildren.size(); j++) {
				auto it = childrensMap.find(listOfDirectChildren[j]);
				while (it != childrensMap.end()) {
					listOfChildrenStar.push_back(it)
				}
			}

		}
	}
}
*/
