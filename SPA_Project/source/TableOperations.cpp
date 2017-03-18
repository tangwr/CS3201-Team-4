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
bool TableOperations::isEqualUnorderedSet(unordered_set<int> uSet1, unordered_set<int> uSet2) {
    //check size
    if (((int)uSet1.size) != ((int)uSet2.size)) {
        return false;
    }
    // check one contains the other
    for (int element : uSet1) {
        if (uSet2.find(element) == uSet2.end()) {
            return false;
        }
    }
    
    return true;
}