#include "ResultTable.h"
#include <unordered_set>
#include <unordered_map>
#include <iostream>

using namespace std;

ResultTable::ResultTable()
{
	isInitialEmpty = false;
	isBoolean = false;
}

bool ResultTable::setInitialEmpty(bool status) {
	isInitialEmpty = status;
	return true;
}

bool ResultTable::isNewTable()
{
	return isInitialEmpty;
}

bool ResultTable::insertTuple(vector<int> tuple)
{
	if ((int)synList.size() != (int)tuple.size())
		return false;
	tupleList.push_back(tuple);
	return true;
}

bool ResultTable::setBoolean(bool b)
{
	if ((int)synList.size() != 0)
		return false;
	isBoolean = b;
	return true;

}

int ResultTable::getParamId(Parameter p)
{
	int idx = 0;
	if (synList.size() == 0)
		return -1;
	for (Parameter tmp : synList) {
		if (tmp.getParaName().compare(p.getParaName()) == 0)
			return idx;
		idx++;
	}
	return -1;
}

bool ResultTable::setSynList(vector<Parameter> list)
{
	synList = list;
	return true;
}

bool ResultTable::isSynInTable(Parameter p)
{
	if (getParamId(p) == -1)
		return false;
	else
		return true;
}

int ResultTable::getTupleSize()
{
	return (int)tupleList.size();
}

int ResultTable::getSynCount()
{
	return (int)synList.size();
}

int ResultTable::getSynIndex(Parameter p)
{
	for (int i = 0; i < getSynCount(); i++) {
		if (synList.at(i).getParaName().compare(p.getParaName()) == 0) {
			return i;
		}
	}
	return -1;
}

int ResultTable::getCount(Parameter p)
{
	unordered_set<int> ans;
	int id = getParamId(p);
	for (vector<int> v : tupleList)
		ans.insert(v.at(id));  // automatically skip when insert duplicate
	return (int)ans.size();
	
}

bool ResultTable::getBoolean()
{
	return isBoolean;
}

vector<Parameter> ResultTable::getSynList()
{
	return synList;
}

vector<vector<int>> ResultTable::getTupleList()
{
	return tupleList;
}

ResultTable ResultTable::join(ResultTable rt)
{

	// if self is initial empty table, return rt 
	if (isInitialEmpty)
		return rt;

	// cases: 0 / 1 / 2 common synonym if rt is a result from a clause

	// equi-join, can be done in nlogn + mlogm with sorting by equi-variable
	// now simply take O(mn) to compute equi-join

	// create joined table 
	ResultTable res = ResultTable();
	vector<Parameter> resSynList = synList;

	int commonSyn = 0;
	vector<Parameter> commonSynList;
	vector<pair<int, int>> idMap;  // first, id of syn in first 
	for (Parameter it : rt.getSynList()){
		bool isExist = false;
		for (Parameter p : synList) {
			if (p.getParaName().compare(it.getParaName()) == 0) {
				commonSyn++;
				commonSynList.push_back(it);
				idMap.push_back(make_pair(getParamId(p), rt.getParamId(it)));
				isExist = true;
			}
		}
		if (isExist == false) {
			resSynList.push_back(it);
		}
	}
	res.setSynList(resSynList);

	for (vector<int> tuple1 : tupleList)
		for (vector<int> tuple2 : rt.getTupleList()) {
			// detect whether common param has same value
			bool ismerge = true;
			for (pair<int, int> pr : idMap)
				if (tuple1.at(pr.first) != tuple2.at(pr.second)) {
					ismerge = false;
				}
			if (ismerge == true) {
				vector<int> resTuple = tuple1;
				for (int i = 0; i < rt.getSynCount(); i++) {
					bool shouldInsert = true;
					for (pair<int, int> pr : idMap)
						if (pr.second == i)
							shouldInsert = false;
					if (shouldInsert == true)
						resTuple.push_back(tuple2.at(i));
				}
				res.insertTuple(resTuple);
			}
		}

	return res;
}

ResultTable ResultTable::select(vector<Parameter> paramList)
{
	return hashSelect(paramList);

	// original select, slow O(N2)
	unordered_map<int, int> idMap;   // key: id in paramLst
	for (int i = 0; i < (int)paramList.size(); i++) {
		bool isExist = false;
		for (int j=0; j<(int)synList.size(); j++)
			if (paramList.at(i).getParaName().compare(synList.at(j).getParaName()) == 0) {
				isExist = true;
				idMap.insert(make_pair(i, j));
			}
		if (isExist == false)
			return ResultTable();  // select element not in table, return empty
	}

	ResultTable res;

	for (auto t : idMap)
		cout << t.first << "  " << t.second << endl;

	res.setSynList(paramList);
	for (vector<int> tuple : tupleList) {
		vector<int> insTuple;
		for (int i = 0; i < (int)paramList.size(); i++)
			insTuple.push_back(tuple.at(idMap[i]));
		bool isExist = false;
		for (vector<int> t : res.getTupleList())
			if (insTuple == t)
				isExist = true;
		if (isExist == false)
			res.insertTuple(insTuple);
	}

return res;

}

ResultTable ResultTable::hashSelect(vector<Parameter> paramList)
{
	unordered_map<int, int> idMap;   // key: id in paramLst
	for (int i = 0; i < (int)paramList.size(); i++) {
		bool isExist = false;
		for (int j = 0; j<(int)synList.size(); j++)
			if (paramList.at(i).getParaName().compare(synList.at(j).getParaName()) == 0) {
				isExist = true;
				idMap.insert(make_pair(i, j));
			}
		if (isExist == false)
			return ResultTable();  // select element not in table, return empty
	}

	ResultTable res;

	for (auto t : idMap)
		cout << t.first << "  " << t.second << endl;

	res.setSynList(paramList);
	unordered_set<string> tupleHashSet;
	for (vector<int> tuple : tupleList) {
		vector<int> insTuple;
		for (int i = 0; i < (int)paramList.size(); i++)
			insTuple.push_back(tuple.at(idMap[i]));

		if (tupleHashSet.find(convertTupleToString(insTuple)) == tupleHashSet.end()) {
			res.insertTuple(insTuple);
			tupleHashSet.insert(convertTupleToString(insTuple));
		}
	}
	return res;
}

unordered_set<int> ResultTable::getSynValue(Parameter param)
{
	unordered_set<int> ans;
	// if param not in table, return empty table
	if (!isSynInTable(param))
		return ans;
	int idx = getSynIndex(param);
	for (vector<int> tuple : tupleList) {
		ans.insert(tuple.at(idx));
	}
	return ans;
}

void ResultTable::printTable()
{
	for (Parameter p : synList)
		cout << p.getParaName() << "  ";
	cout << endl;

	for (vector<int> tuple : tupleList) {
		for (int i : tuple)
			cout << i << "  ";
		cout << endl;
	}
}

string ResultTable::convertTupleToString(vector<int> tuple)
{
	//<1,2,3> -> "@1%@2%@3%"
	// <> -> ""
	string hashString;
	hashString += "\"";
	for (int i = 0; i < (int)tuple.size(); i++) {
		hashString += "@";
		hashString += to_string(tuple.at(i));
		hashString += "%";
	}
	hashString += "\"";
	return hashString;
}


