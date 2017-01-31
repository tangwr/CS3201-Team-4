#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "AST.h"

using namespace std;
typedef short PROC;

class TNode;

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer

class PKB {
public:
    PKB();
    TNode createNode(TNodeType nodeType);//returns created object
    void setAsRoot(TNode root);
    void setName(TNode node, string name);
    void setValue(TNode node, int value);//stmt number or constant

	static VarTable* varTable; 
	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST (PROC p);
	
	void addProcedure(String name);
	void addVariable(String name);
	void addStatement(int statementNum, TnodeType type);

	void addFollows(int statementNum, list<int> followList);
	void addParents(int statementNum, list<int> parentList);
	void addUses(int statementNum, String variable);
	void addModifies(int statementNum, String Variable);

private:
    AST ast;
};
