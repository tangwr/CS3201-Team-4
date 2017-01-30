#include "FollowsTable.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

map<int, int> followsMap;

FollowsTable::FollowsTable(void)
{
}

int FollowsTable::insertFollows(int stmtNo1, int stmtNo2)
{
	map<int, int>::iterator it;
	it = followsMap.find(stmtNo1);
	if (it != followsMap.end()) {
		throw "ExistingFollowsRelationException";
	}

	followsMap.insert(make_pair(stmtNo1,stmtNo2));
	return stmtNo1;
}

/*
	GetFollows return the stmt No that follows the given stmt.
	getFollows (3) = 4 if Follows (3,4)

	return -1 if no result
*/
int FollowsTable::getFollows(int stmtNo)
{
	map<int, int>::iterator it;
	it = followsMap.find(stmtNo);
	if (it != followsMap.end()) {
		return it->second;
	}
	return -1;
}


/*
GetFollowedBy return the stmt No that is followed by the given stmt.
getFollowedBy (4) = 3 if Follows (3,4)

return -1 if no result
*/
int FollowsTable::getFollowedBy(int stmtNo)
{
	map<int, int>::iterator it = followsMap.begin();
	while (it != followsMap.end())
	{
		if (it->second == stmtNo)
			return it->first;
		it++;
	}
	return -1;
}


vector<int> FollowsTable::getFollowsList(int stmtNo)
{
	vector<int> list;
	int idx = getFollows(stmtNo);
	while (idx != -1) {
		list.push_back(idx);
		idx = getFollows(idx);
	}
	return list;
}

vector<int> FollowsTable::getFollowedByList(int stmtNo)
{
	vector<int> list;
	int idx = getFollowedBy(stmtNo);
	while (idx != -1) {
		list.push_back(idx);
		idx = getFollowedBy(idx);
	}
	return list;
}
