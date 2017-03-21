#include "ResultTable.h"
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <string>

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
	auto it = synNameMap.find(p.getParaName());
	if (it != synNameMap.end())
		return it->second;
	else
		return -1;
}

bool ResultTable::setSynList(vector<Parameter> list)
{
	synNameMap.clear();
	synList = list;
	for (int i = 0; i < (int)list.size(); i++) {
		synNameMap.insert(make_pair(list.at(i).getParaName(), i));
	}
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
	return getParamId(p);
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
	return hashJoin(rt);
}

ResultTable ResultTable::nestedJoin(ResultTable rt)
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
	for (Parameter it : rt.getSynList()) {
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

ResultTable ResultTable::hashJoin(ResultTable rt)
{

	// if self is initial empty table, return rt 
	if (isInitialEmpty)
		return rt;
	if (rt.isInitialEmpty)
		return *this;

	// create joined table 
	ResultTable res = ResultTable();
	vector<Parameter> resSynList = synList;

	int commonSyn = 0;
	unordered_set<int> commonSynIdSet2ndTable;  // id of 2nd table syn, that is common syn with table 1
	unordered_map<int, int> commonSyn2ndTo1stMap;
	for (Parameter it : rt.getSynList()) {
		bool isExist = false;
		for (Parameter p : synList) {
			if (p.getParaName().compare(it.getParaName()) == 0) {
				commonSyn++;
				commonSyn2ndTo1stMap.insert(make_pair(rt.getParamId(it), getParamId(p)));
				isExist = true;
			}
		}
		if (isExist == false) {
			// not a common synonmym, push to Synlist
			resSynList.push_back(it);
		}
		else {
			// is a common syn, add to 2nd table idx set
			commonSynIdSet2ndTable.insert(rt.getParamId(it));
		}
	}
	res.setSynList(resSynList);

	// create hash table for table rt
	unordered_map<string, vector<vector<int>>> hashMap2ndTable;
	
	for (vector<int> tuple : rt.getTupleList()) {
		vector<int> keyVector, valueVector;
		for (int idx = 0; idx < rt.getSynCount(); idx++) {
			if (commonSynIdSet2ndTable.find(idx) == commonSynIdSet2ndTable.end()) {
				// not a common synonym, push the index to valueVetor
				valueVector.push_back(tuple.at(idx));
			}
			else {
				// is a common synonym, push to keyVector
				keyVector.push_back(tuple.at(idx));
			}
		}

		// insert the tuple to hashTable
		string hashString = convertTupleToString(keyVector);
		vector<vector<int>> tmpVector;
		auto it = hashMap2ndTable.find(hashString);
		if (it == hashMap2ndTable.end()) {
			tmpVector.push_back(valueVector);
			hashMap2ndTable.insert(make_pair(hashString, tmpVector));
		}
		else {
			tmpVector = hashMap2ndTable[hashString];
			tmpVector.push_back(valueVector);
			it->second = tmpVector;
		}
	}

	// loop through tuples from self table, for each tuple, get the keyvector, 
	// compare with the hashmap, if match, create new tuple for each mapped 2nd tuple

	for (vector<int> tuple1 : tupleList) {
		vector<int> tmpVector;
		
		// update keyvector for each synonym
		for (int i = 0; i < rt.getSynCount(); i++) {
			auto it = commonSyn2ndTo1stMap.find(i);
			if (it != commonSyn2ndTo1stMap.end()) {
				tmpVector.push_back(tuple1.at(it->second));
			}
		}
		string hashString = convertTupleToString(tmpVector);

		// check whether the hashtable contain the string 
		auto it = hashMap2ndTable.find(hashString);
		if (it != hashMap2ndTable.end()) {
			// if match, 
			vector<vector<int>> mappedTupleList = it->second;
			for (vector<int> appendingTuple : mappedTupleList) {
				vector<int> newTuple = tuple1; 
				newTuple.insert(newTuple.end(), appendingTuple.begin(), appendingTuple.end());
				res.insertTuple(newTuple);
			}	

		}
	}
	return res;
}

ResultTable ResultTable::select(vector<Parameter> paramList)
{
	return hashSelect(paramList);
}

ResultTable ResultTable::nestedSelect(vector<Parameter> paramList)
{
	// original select, slow O(N2)
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
	int idx = getParamId(param);
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
