#pragma once
#include "FollowsTable.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#define INVALID_INDEX -1

using namespace std;

FollowsTable::FollowsTable(void) {

}


/*
	set direct follow relationship
	Input: followeeId, followerId
	Output: true, if insert success. false, if followee or follower already exist
*/
bool FollowsTable::setStmtFollowStmtRel(int followeeId, int followerId)
{
	unordered_map<int, int>::iterator it;
	it = followeeMap.find(followeeId);
	if (it != followeeMap.end()) 
		return false;
	else {
		it = followerMap.find(followerId);
		if (it != followerMap.end())
			return false;
		else {
			followeeMap.insert(make_pair(followeeId, followerId));
			followerMap.insert(make_pair(followerId, followeeId));
			insertStmtFollowStmtRel(followeeId, followerId);
			return true;
		}
	}
}



bool FollowsTable::insertStmtFollowStmtRel(int followeeId, int followerId)//star
{
	if (followeeId == followerId)
		return false;
	unordered_set<int> set1, set2;
	unordered_map<int, unordered_set<int>>::iterator it1, it2;
	it1 = followeeListMap.find(followeeId);
	it2 = followerListMap.find(followerId);
	
	if (it1 != followeeListMap.end()) {
		set1 = it1->second;
		followeeListMap.erase(it1);
	}
	set1.insert(followerId);
	followeeListMap.insert(make_pair(followeeId, set1));

	if (it2 != followerListMap.end()) {
		set2 = it2->second;
		followerListMap.erase(it2);
	}
	set2.insert(followeeId);
	followerListMap.insert(make_pair(followerId, set2));
	return true;
}

/*
	get the statementId that directly follows the given statement
	Input: followee statement Id
	Output: follower statement Id if success, -1 if failure.
*/
int FollowsTable::getDirectFollow(int followeeId)
{
	unordered_map<int, int>::iterator it;
	it = followeeMap.find(followeeId);
	if (it != followeeMap.end()) {
		return it->second;
	}
	return INVALID_INDEX;
}


/*
	get the statementId that directly followed by the given statement
	Input: follower statement Id
	Output: followee statement Id if success, -1 if failure.
*/
int FollowsTable::getDirectFollowedBy(int followerId)
{
	unordered_map<int, int>::iterator it;
	it = followerMap.find(followerId);
	if (it != followerMap.end()) {
		return it->second;
	}
	return INVALID_INDEX;
}

unordered_set<int> FollowsTable::getStmtFollowStarStmt(int stmtId) {
	unordered_map<int, unordered_set<int>>::iterator it;
    unordered_set<int> resultSet;
	it = followeeListMap.find(stmtId);
    if (it != followeeListMap.end()) {
        resultSet = it->second;
    }
    return resultSet;
}
unordered_set<int> FollowsTable::getStmtFollowedByStarStmt(int stmtId) {
	unordered_map<int, unordered_set<int>>::iterator it;
    unordered_set<int> resultSet;
	it = followerListMap.find(stmtId);
    if (it != followerListMap.end()) {
        resultSet = it->second;
    }
    return resultSet;
}

bool FollowsTable::hasFollowRel()
{
    return !followeeMap.empty();
}

void FollowsTable::printContents()
{
	cout << "---PRINT FOLLOWSTABLE---" << endl;

    cout << "StmtId : Direct Follower StmtId" << endl;
	for (pair<int, int> it : followeeMap) {
        cout << it.first << " : " << it.second << endl;
	}
    cout << endl;

    cout << "StmtId : List of follower stmtId" << endl;
	for (pair<int, unordered_set<int>> it : followeeListMap) {
        cout << it.first << " : ";
		TableOperations::printUnorderedSet(it.second);
		cout << endl;
	}
    cout << endl;

    cout << "StmtId : List of followee stmtId" << endl;
	for (pair<int, unordered_set<int>> it : followerListMap) {
        cout << it.first << " : ";
		TableOperations::printUnorderedSet(it.second);
		cout << endl;
	}
    cout << endl;

	cout << "---END PRINT FOLLOWSTABLE---" << endl;
}