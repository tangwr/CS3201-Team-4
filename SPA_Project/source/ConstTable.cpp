#pragma once
#include "ConstTable.h"
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

ConstTable::ConstTable(void) {
	ctsize = 0;
}


bool ConstTable::insertConst(int value) {
    if (this->constSet.find(value) != this->constSet.end()) {
        return false;
    }
    this->constSet.insert(value);
    this->ctsize++;
    return true;
}

int ConstTable::getSize()
{
	return ctsize;
}

bool ConstTable::checkConstExist(int constValue) {
    if (this->constSet.find(constValue) == this->constSet.end()) {
        return false;
    }
    else {
        return true;
    }
}

unordered_set<int> ConstTable::getAllConst() {
    return this->constSet;
}

void ConstTable::printContents() {
    cout << "---PRINT CONST TABLE---" << endl;

    cout << "Constants in table: " << endl;
    for (int constValue : constSet) {
        cout << constValue << " ";
    }
    cout << endl;
    cout << "---END PRINT CONST TABLE---" << endl;
}
