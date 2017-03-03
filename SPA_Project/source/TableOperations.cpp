#include "TableOperations.h"

void TableOperations::printUnorderedSet(unordered_set<int> uSet) {
    for (int element : uSet) {
        cout << element << ' ';
    }
}