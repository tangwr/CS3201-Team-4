#include "FollowsTable.h"

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<int, int> followeeMap;  // <followee, follower>    <3,4>
unordered_map<int, int> followerMap;  // <follower, followee>    <4,3>
unordered_map<int, vector<int>> followeeListMap;
unordered_map<int, vector<int>> followerListMap;

FollowsTable::FollowsTable(void)
{
}


/*
	set direct follow relationship
	Input: followeeId, followerId
	Output: true, if insert success. false, if followee or follower already exist
*/
bool FollowsTable::setFollowDirectRel(int followeeId, int followerId)
{
	unordered_map<int, int>::iterator it;
	it = followeeMap.find(followeeId);
	if (it == followeeMap.end()) 
		return false;
	else {
		it = followerMap.find(followerId);
		if (it != followerMap.end())
			return false;
		else {
			followeeMap.insert(make_pair(followeeId, followerId));
			followerMap.insert(make_pair(followerId, followeeId));
			// star table
			insertFollowRel(followeeId, followerId);
			return true;
		}
	}
}

bool FollowsTable::insertFollowRel(int followeeId, int followerId)
{
	if (followeeId == followerId)
		return false;
	vector<int> list1, list2;
	unordered_map<int, vector<int>>::iterator it1, it2;
	it1 = followeeListMap.find(followeeId);
	it2 = followerListMap.find(followerId);
	
	if (it1 == followeeListMap.end()) {
		list1 = it1->second;
		followeeListMap.erase(it1);
	}
	list1.push_back(followerId);
	followeeListMap.insert(make_pair(followeeId, list1));

	if (it2 == followerListMap.end()) {
		list2 = it2->second;
		followerListMap.erase(it2);
	}
	list2.push_back(followeeId);
	followerListMap.insert(make_pair(followerId, list2));
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
	return -1;
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
	return -1;
}

/*
vector<int> FollowsTable::getFollowsList(int stmtId)
{
	vector<int> list;
	int idx = getDirectFollow(stmtId);
	while (idx != -1) {
		list.push_back(idx);
		idx = getDirectFollow(idx);
	}
	return list;
}

vector<int> FollowsTable::getFollowedByList(int stmtId)
{
	vector<int> list;
	int idx = getDirectFollow(stmtId);
	while (idx != -1) {
		list.push_back(idx);
		idx = getDirectFollowedBy(idx);
	}
	return list;
}
*/

vector<int> FollowsTable::getFollowStar(int stmtId) {
	unordered_map<int, vector<int>>::iterator it;
	it = followeeListMap.find(stmtId);
	if (it != followeeListMap.end())
		return it->second;
	else
		return vector<int>();
}
vector<int> FollowsTable::getFollowedByStar(int stmtId) {
	unordered_map<int, vector<int>>::iterator it;
	it = followerListMap.find(stmtId);
	if (it != followerListMap.end())
		return it->second;
	else
		return vector<int>();

}