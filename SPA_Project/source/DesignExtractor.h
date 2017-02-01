#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"

class DesignExtractor {
public:
	DesignExtractor(PKB* pkb);
	void run();
};