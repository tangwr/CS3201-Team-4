#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class FollowsTable {
private:
	void printVector(vector<int> vec);
    void printUnorderedSet(unordered_set<int> uSet);
	unordered_map<int, int> followeeMap;  // <followee, follower>    <3,4>
	unordered_map<int, int> followerMap;  // <follower, followee>    <4,3>
	//unordered_map<int, vector<int>> followeeListMap;
	//unordered_map<int, vector<int>> followerListMap;
    unordered_map<int, unordered_set<int>> followeeListMap;
    unordered_map<int, unordered_set<int>> followerListMap;//follower to list of followee
public:
	FollowsTable();
	bool setStmtFollowStmtRel(int followeeId, int followerId);
	bool insertStmtFollowStmtRel(int followeeId, int followerId);
	int getDirectFollow(int followeeId);    
	int getDirectFollowedBy(int followerId);
	//vector<int> getFollowsList(int stmtNo);
	//vector<int> getFollowedByList(int stmtNo);
	unordered_set<int> getStmtFollowStarStmt(int followeeId);
	unordered_set<int> getStmtFollowedByStarStmt(int followerId);
	void printContents();

	bool hasFollowRel();

};