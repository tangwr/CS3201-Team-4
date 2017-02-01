#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class FollowsTable {
public:
	FollowsTable();
	bool setFollowDirectRel(int followeeId, int followerId);
	int getDirectFollow(int followeeId);    
	int getDirectFollowedBy(int followerId);
	vector<int> getFollowsList(int stmtNo);
	vector<int> getFollowedByList(int stmtNo);
};