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
	//void extractStarRelations();
	void extractParentStar();
	void extractFollowsStar();
};
