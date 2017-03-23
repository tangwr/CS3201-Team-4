#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "TableOperations.h"

using namespace std;

class FollowsTable {
private:
	unordered_map<int, int> followeeMap;  // <followee, follower>    <3,4>
	unordered_map<int, int> followerMap;  // <follower, followee>    <4,3>
    unordered_map<int, unordered_set<int>> followeeListMap;
    unordered_map<int, unordered_set<int>> followerListMap;//follower to list of followee
public:
	FollowsTable();
	bool setStmtFollowStmtRel(int followeeId, int followerId);
	bool insertStmtFollowStmtRel(int followeeId, int followerId);
	int getDirectFollow(int followeeId);    
	int getDirectFollowedBy(int followerId);
	unordered_set<int> getStmtFollowStarStmt(int followeeId);
	unordered_set<int> getStmtFollowedByStarStmt(int followerId);
    bool hasFollowRel();
    void printContents();
};