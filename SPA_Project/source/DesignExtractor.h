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
private:
	PKB *pkb;
    void extractProcModifiesUsesStar();
    void recursiveTablePopulation(int procId, unordered_map<int, bool> *isProcInPath, unordered_map<int, bool> *isProcValidated);
    void populateProcRel(int procId, int containerStmtId);

public:
    DesignExtractor(PKB *pkbSource);
    void extractStarRelations();
};
