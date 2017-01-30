#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class FollowsTable {
public:
	FollowsTable();
	int insertFollows(int stmtNo1, int stmtNo2);
	int getFollows(int stmtNo);    
	int getFollowedBy(int stmtNo);
	vector<int> getFollowsList(int stmtNo);
	vector<int> getFollowedByList(int stmtNo);
};