#pragma once

#include "stdio.h"
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class TableOperations {
private:


public:

    static void printUnorderedSet(unordered_set<int> uSet);
    static void printTableVector(vector<int> vList);
    static bool isEqualUnorderedSet(unordered_set<int> uSet1, unordered_set<int> uSet2);
};