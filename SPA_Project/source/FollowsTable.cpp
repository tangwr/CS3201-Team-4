#include "FollowsTable.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

FollowsTable::FollowsTable(void)
{
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
			// star table
			insertStmtFollowStmtRel(followeeId, followerId);
			return true;
		}
	}
}



bool FollowsTable::insertStmtFollowStmtRel(int followeeId, int followerId)
{
	if (followeeId == followerId)
		return false;
	unordered_set<int> list1, list2;
	unordered_map<int, unordered_set<int>>::iterator it1, it2;
	it1 = followeeListMap.find(followeeId);
	it2 = followerListMap.find(followerId);
	
	if (it1 != followeeListMap.end()) {
		list1 = it1->second;
		followeeListMap.erase(it1);
	}
	list1.insert(followerId);
	followeeListMap.insert(make_pair(followeeId, list1));

	if (it2 != followerListMap.end()) {
		list2 = it2->second;
		followerListMap.erase(it2);
	}
	list2.insert(followeeId);
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

vector<int> FollowsTable::getStmtFollowStarStmt(int stmtId) {
	unordered_map<int, unordered_set<int>>::iterator it;
	it = followeeListMap.find(stmtId);
    if (it != followeeListMap.end())
        //return it->second;
        return vector<int>(it->second.begin(), it->second.end());//decide if pkb only or global
    else
        return vector<int>();

}
vector<int> FollowsTable::getStmtFollowedByStarStmt(int stmtId) {
	unordered_map<int, unordered_set<int>>::iterator it;
	it = followerListMap.find(stmtId);
	if (it != followerListMap.end())
		//return it->second;
        return vector<int>(it->second.begin(), it->second.end());
	else
		return vector<int>();

}

void FollowsTable::printContents()
{
	cout << "---PRINT FOLLOWSTABLE---" << endl;
	for (pair<int, int> it : followeeMap) {
		cout << "StmtId: " << it.second;
		cout << " Directly Follows StmtId " << it.first << endl;
	}
	for (pair<int, unordered_set<int>> it : followeeListMap) {
		cout << "Stmts that follows StmtId: " << it.first;
		cout << " are ";
		printUnorderedSet(it.second);
		cout << endl;
	}
	for (pair<int, unordered_set<int>> it : followerListMap) {
		cout << "Stmts that StmtId" << it.first;
		cout << " Follows are ";
		printUnorderedSet(it.second);
		cout << endl;
	}

	cout << "---END PRINT FOLLOWSTABLE---" << endl;
}

bool FollowsTable::hasFollowRel()
{
	return followeeMap.empty();
}

void FollowsTable::printUnorderedSet(unordered_set<int> uSet) {
    for (int element : uSet) {
        cout << element << ' ';
    }
}

void FollowsTable::printVector(vector<int> vec)
{
	for (int t : vec) {
		cout << t << ' ';
	}
}