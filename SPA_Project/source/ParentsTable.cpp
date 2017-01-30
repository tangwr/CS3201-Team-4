#include "ParentsTable.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

map<int, int> parentsMap;

ParentsTable::ParentsTable(void)
{
}

int ParentsTable::insertParent(int stmtNo1, int stmtNo2)
{
	map<int, int>::iterator it;
	it = parentsMap.find(stmtNo1);
	if (it != parentsMap.end()) {
		throw "ExistingParentRelationException";
	}

	parentsMap.insert(make_pair(stmtNo1, stmtNo2));
	return stmtNo1;
}

/*
GetFollows return the stmt No that is the children of the given stmt.
getFollows (3) = 4 if Follows (3,4)

return -1 if no result
*/
int ParentsTable::getChildren(int stmtNo)
{
	map<int, int>::iterator it;
	it = parentsMap.find(stmtNo);
	if (it != parentsMap.end()) {
		return it->second;
	}
	return -1;
}


/*
GetFollowedBy return the stmt No that is the child of by the given stmt.
getFollowedBy (4) = 3 if Follows (3,4)

return -1 if no result
*/
int ParentsTable::getParent(int stmtNo)
{
	map<int, int>::iterator it = parentsMap.begin();
	while (it != parentsMap.end())
	{
		if (it->second == stmtNo)
			return it->first;
		it++;
	}
	return -1;
}


vector<int> ParentsTable::getChildrenList(int stmtNo)
{
	vector<int> list;
	int idx = getChildren(stmtNo);
	while (idx != -1) {
		list.push_back(idx);
		idx = getChildren(idx);
	}
	return list;
}

vector<int> ParentsTable::getParentList(int stmtNo)
{
	vector<int> list;
	int idx = getParent(stmtNo);
	while (idx != -1) {
		list.push_back(idx);
		idx = getParent(idx);
	}
	return list;
}
