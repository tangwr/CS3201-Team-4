#include "ConstTable.h"

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

ConstTable::ConstTable(void) {
	ctsize = 0;
}

//int ConstTable::insertConst(int constName)
//{
//	unordered_map<int, int>::iterator it = constMap.find(constName);
//
//	if (it != constMap.end())
//		return it->second;
//	else
//	{
//		int constId = ctsize;
//		constList.push_back(constName);
//		constMap.insert(make_pair(constName, constId));
//		ctsize++;
//		return constId;   // index of the variable in the vector
//	}
//}
//new for constset
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

//int ConstTable::getConstName(int constId)
//{
//	if (constId >= ctsize) throw "InvalidReferenceException";
//	else return constList.at(constId);
//}
//
//int ConstTable::getConstIndex(int constName)
//{
//	unordered_map<int, int>::iterator it = constMap.find(constName);
//
//	if (it != constMap.end())
//		return it->second;
//	else
//		return -1;
//}

//bool ConstTable::checkConstExist(int constName)
//{
//	unordered_map<int, int>::iterator it = constMap.find(constName);
//
//	if (it != constMap.end())
//		return true;
//	else
//		return false;
//}

bool ConstTable::checkConstExist(int constValue) {
    if (this->constSet.find(constValue) == this->constSet.end()) {
        return false;
    }
    else {
        return true;
    }
}

//int ConstTable::getValueById(int constId)
//{
//	if (constId >= ctsize) throw "InvalidReferenceException";
//	else return constList.at(constId);
//}

/*
	Return list of constants
*/
//vector<int> ConstTable::getAllConst()
//{
//	return constList;
//}
//vector<int> ConstTable::getAllConstId() {
//    vector<int> allConstIdLst;
//    for (auto entry : this->constMap) {
//        allConstIdLst.push_back(entry.second);
//    }
//    return allConstIdLst;
//}

unordered_set<int> ConstTable::getAllConst() {
    return this->constSet;
}


//void ConstTable::printContents()
//{
//    cout << "---PRINT CONST TABLE---" << endl;
//
//    cout << "ConstId : Value" << endl;
//
//    for (pair<int, int> element : constMap) {
//        cout << element.second << " : " << element.first << endl;
//    }
//	//for (int it : constList)
//	//	cout << it << endl;
//
//    cout << "---END PRINT CONST TABLE---" << endl;
//}

void ConstTable::printContents() {
    cout << "---PRINT CONST TABLE---" << endl;

    cout << "Constants in table: " << endl;
    for (int constValue : constSet) {
        cout << constValue << " ";
    }
    cout << endl;
    cout << "---END PRINT CONST TABLE---" << endl;
}
