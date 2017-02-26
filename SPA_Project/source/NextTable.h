#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class NextTable {
private:

    unordered_map<int, unordered_set<int>> nextMap; //stmt, list of next stmt
    unordered_map<int, unordered_set<int>> previousMap; //stmt, list of previous stmt
    int size;
    void printUnorderedSet(unordered_set<int> uSet);

public:
    NextTable();
    int getSize();
    void printContents();
    bool setStmtNextStmt(int currentStmtId, int nextStmtId);//sets both next and previous
    unordered_set<int> getNextStmt(int stmtId);
    unordered_set<int> getPreviousStmt(int stmtId);

};