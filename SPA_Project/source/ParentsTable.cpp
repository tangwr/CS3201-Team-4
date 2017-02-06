#include "ParentsTable.h"

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

ParentsTable::ParentsTable(void)
{
}

bool ParentsTable::setParentDirectRel(int father, int child)
{
	unordered_map<int, int>::iterator it;
	it = parentsMap.find(child);
	if (it != parentsMap.end()) {
		return false;
	}
	parentsMap.insert(make_pair(child, father));

	unordered_map<int, vector<int>>::iterator it2;
	vector<int> list;
	it2 = childsMap.find(father);
	if (it2 != childsMap.end()) {
		list = it2->second;
		childsMap.erase(it2);
		list.push_back(child);
		childsMap.insert(make_pair(father, list));
	}
	else {
		list.push_back(child);
		childsMap.insert(make_pair(father, list));
	}

	// star table 
	insertParentRel(father, child);

	return true;
}
bool ParentsTable::insertParentRel(int father, int child)
{
	if (father == child)
		return false;
	vector<int> list1, list2;
	unordered_map<int, vector<int>>::iterator it1, it2;
	it1 = parentListMap.find(child);
	it2 = childListMap.find(father);

	if (it1 != parentListMap.end()) {
		list1 = it1->second;
		parentListMap.erase(it1);
	}
	list1.push_back(father);
	parentListMap.insert(make_pair(child, list1));

	if (it2 != childListMap.end()) {
		list2 = it2->second;
		childListMap.erase(it2);
	}
	list2.push_back(child);
	childListMap.insert(make_pair(father, list2));
	return true;
}




/*
return list of childrens
return empty list if no result
*/
vector<int> ParentsTable::getChildren(int stmtId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = childsMap.find(stmtId);
	if (it != childsMap.end()) {
		return it->second;
	}
	return vector<int>();
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

/*
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
*/

vector<int> ParentsTable::getChildrenStar(int stmtId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = childListMap.find(stmtId);
	if (it != childListMap.end())
		return it->second;
	else
		return vector<int>();
}
vector<int> ParentsTable::getParentStar(int stmtId)
{
	unordered_map<int, vector<int>>::iterator it;
	it = parentListMap.find(stmtId);
	if (it != parentListMap.end())
		return it->second;
	else
		return vector<int>();
}

bool ParentsTable::hasParentRel()
{
	return parentsMap.empty();
}

void ParentsTable::printContents()
{
	cout << "---PRINT PARENTSTABLE---" << endl;
	for (pair<int, int> it : parentsMap) {
		cout << "StmtId: " << it.second;
		cout << " is father of Stmt Id " << it.first <<endl;
	}
	for (pair<int, vector<int>> it : parentListMap) {
		cout << "StmtId: " << it.first;
		cout << " has parents StmtId ";
		printVector(it.second);
		cout << endl;
	}
	for (pair<int, vector<int>> it : childListMap) {
		cout << "ProcId: " << it.first;
		cout << " has children StmtId ";
		printVector(it.second);
		cout << endl;
	}

	cout << "---END PRINT PARENTSTABLE---" << endl;
}

void ParentsTable::printVector(vector<int> vec)
{
	for (int t : vec) {
		cout << t << ' ';
	}
}