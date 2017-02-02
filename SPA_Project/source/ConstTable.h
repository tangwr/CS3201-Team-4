#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ConstTable {

public:
	ConstTable(void);
	int insertConst( int value);
	int getSize();
	int getConstName(int constId);
	int getConstIndex(int constName);
	bool checkConstExist(int constName);
	int getValueById(int constId);
};