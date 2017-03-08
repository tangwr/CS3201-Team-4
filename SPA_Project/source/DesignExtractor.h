#pragma once

#include "PKB.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <vector>


using namespace std;

class DesignExtractor {
public:
	DesignExtractor(PKB *pkbSource);
	void extractStarRelations();

private:
	PKB *pkb;
    void extractProcModifiesUsesStar();
    void recursiveTablePopulation(int procId, unordered_map<int, bool> *isProcInPath, unordered_map<int, bool> *isProcValidated);
	//void extractStarRelations();
	void extractParentStar();
	void extractFollowsStar();
    void extractModifiesStar();
    void extractUsesStar();
    void populateProcRel(int procId, int containerStmtId);
};
