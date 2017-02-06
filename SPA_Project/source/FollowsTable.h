#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class FollowsTable {
private:
	void printVector(vector<int> vec);
	unordered_map<int, int> followeeMap;  // <followee, follower>    <3,4>
	unordered_map<int, int> followerMap;  // <follower, followee>    <4,3>
	unordered_map<int, vector<int>> followeeListMap;
	unordered_map<int, vector<int>> followerListMap;
public:
	FollowsTable();
	bool setFollowDirectRel(int followeeId, int followerId);
	bool insertFollowRel(int followeeId, int followerId);
	int getDirectFollow(int followeeId);    
	int getDirectFollowedBy(int followerId);
	//vector<int> getFollowsList(int stmtNo);
	//vector<int> getFollowedByList(int stmtNo);
	vector<int> getFollowStar(int followeeId);
	vector<int> getFollowedByStar(int followerId);
	void printContents();

	bool hasFollowRel();

};