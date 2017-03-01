#include "NextTable.h"

void NextTable::printUnorderedSet(unordered_set<int> uSet) {
    for (int element : uSet) {
        cout << element << ' ';
    }
}

NextTable::NextTable() {
    this->size = 0;
}

int NextTable::getSize() {
    return this->size;
}

void NextTable::printContents() {

    cout << "---PRINT NEXTTABLE---" << endl;
    for (pair<int, unordered_set<int>> it : nextMap) {
        cout << "The next statements of StmtId: " << it.first;
        cout << " are stmtId ";
        //printVector(it.second);
        printUnorderedSet(it.second);
        cout << endl;
    }
    for (pair<int, unordered_set<int>> it : previousMap) {
        cout << "The previous statements of StmtId: " << it.first;
        cout << " are stmtId ";
        //printVector(it.second);
        printUnorderedSet(it.second);
        cout << endl;
    }

    cout << "---END PRINT NEXTTABLE---" << endl;

}

bool NextTable::setStmtNextStmtRel(int currentStmtId, int nextStmtId) {
    //next
    unordered_map<int, unordered_set<int>>::iterator it;
    it = nextMap.find(currentStmtId);
    unordered_set<int> nextSet;

    if (it != nextMap.end()) {
        //currentStmtId has some next
        nextSet = it->second;
        if (nextSet.find(nextStmtId) != nextSet.end()) {
            //already exist
            return false;
        }
        nextMap.erase(it);
    }
    nextSet.insert(nextStmtId);
    nextMap.insert(make_pair(currentStmtId, nextSet));

    //previous
    unordered_map<int, unordered_set<int>>::iterator it2;
    it2 = previousMap.find(nextStmtId);
    unordered_set<int> previousSet;

    if (it2 != previousMap.end()) {
        previousSet = it2->second;
        if (previousSet.find(nextStmtId) != previousSet.end()) {
            return false;
        }
        previousMap.erase(it2);
    }
    previousSet.insert(currentStmtId);
    previousMap.insert(make_pair(nextStmtId, previousSet));

    this->size++;
    return true;
}

unordered_set<int> NextTable::getNextStmt(int stmtId) {

    unordered_map<int, unordered_set<int>>::iterator it;
    unordered_set<int> nextSet;
    it = nextMap.find(stmtId);
    if (it != nextMap.end()) {
        return it->second;
    }
    else {
        return nextSet;;
    }
}

unordered_set<int> NextTable::getPreviousStmt(int stmtId) {
    unordered_map<int, unordered_set<int>>::iterator it;
    unordered_set<int> previousSet;
    it = previousMap.find(stmtId);
    if (it != previousMap.end()) {
        return it->second;
    }
    else {
        return previousSet;;
    }
}