#include "TableOperations.h"

void TableOperations::printUnorderedSet(unordered_set<int> uSet) {
    for (int element : uSet) {
        cout << element << ' ';
    }
}

void TableOperations::printTableVector(vector<int> vList) {
    for (int element : vList) {
        cout << element << ' ';
    }
}