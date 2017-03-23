#include "ParentsTable.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

ParentsTable::ParentsTable(void)
{
}

bool ParentsTable::setStmtParentStmtRel(int father, int child)
{
	unordered_map<int, int>::iterator it;
	it = parentsMap.find(child);
	if (it != parentsMap.end()) {
		return false;
	}
	parentsMap.insert(make_pair(child, father));

	unordered_map<int, unordered_set<int>>::iterator it2;
    unordered_set<int> childSet;
	it2 = childsMap.find(father);
	if (it2 != childsMap.end()) {
		childSet = it2->second;
		childsMap.erase(it2);
		childSet.insert(child);
		childsMap.insert(make_pair(father, childSet));
	}
	else {
		childSet.insert(child);
		childsMap.insert(make_pair(father, childSet));
	}

	// star table 
	insertStmtParentStmtRel(father, child);

	return true;
}

bool ParentsTable::insertStmtParentStmtRel(int father, int child)
{
	if (father == child)
		return false;
	unordered_set<int> parentSet, childSet;
	unordered_map<int, unordered_set<int>>::iterator it1, it2;
	it1 = parentListMap.find(child);
	it2 = childListMap.find(father);

	if (it1 != parentListMap.end()) {
		parentSet = it1->second;
		parentListMap.erase(it1);
	}
	parentSet.insert(father);
	parentListMap.insert(make_pair(child, parentSet));

	if (it2 != childListMap.end()) {
		childSet = it2->second;
		childListMap.erase(it2);
	}
	childSet.insert(child);
	childListMap.insert(make_pair(father, childSet));
	return true;
}




/*
return list of childrens
return empty list if no result
*/
unordered_set<int> ParentsTable::getStmtChildrenStmt(int stmtId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
    unordered_set<int> resultSet;
	it = childsMap.find(stmtId);
	if (it != childsMap.end()) {
		resultSet = it->second;
	}
    return resultSet;
}


/*
return -1 if no result
*/
int ParentsTable::getParent(int stmtId)
{
	unordered_map<int, int>::iterator it = parentsMap.begin();
	it = parentsMap.find(stmtId);
	if (it != parentsMap.end()) {
		return it->second;
	}
	return -1;
}

unordered_set<int> ParentsTable::getStmtChildrenStarStmt(int stmtId)
{
	unordered_map<int, unordered_set<int>>::iterator it;
    unordered_set<int> resultSet;
	it = childListMap.find(stmtId);
    if (it != childListMap.end()) {
        resultSet = it->second;
    }
    return resultSet;
}
unordered_set<int> ParentsTable::getStmtParentStarStmt(int stmtId)
{
    unordered_map<int, unordered_set<int>>::iterator it;
    unordered_set<int> resultSet;
    it = parentListMap.find(stmtId);
    if (it != parentListMap.end()){
        resultSet = it->second;
    }
    return resultSet;
}

bool ParentsTable::hasParentRel()
{
	return !parentsMap.empty();
}

void ParentsTable::printContents()
{
	cout << "---PRINT PARENTSTABLE---" << endl;

    cout << "Direct parent : Direct child" << endl;
	for (pair<int, int> it : parentsMap) {
        cout << it.second << " : " << it.first << endl;
	}
    cout << endl;

    cout << "child : parent* " << endl;
	for (pair<int, unordered_set<int>> it : parentListMap) {
        cout << it.first << " : ";
		TableOperations::printUnorderedSet(it.second);
		cout << endl;
	}
    cout << endl;

    cout << "parent stmtId : child *" << endl;
	for (pair<int, unordered_set<int>> it : childListMap) {
        cout << it.first << " : ";
		TableOperations::printUnorderedSet(it.second);
		cout << endl;
	}

	cout << "---END PRINT PARENTSTABLE---" << endl;
}