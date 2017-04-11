#include "ResultTable.h"

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
		ans.insert(v.at(id));  
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

void ResultTable::join(ResultTable rt)
{
	hashJoin(rt);
	return;
}

void ResultTable::nestedJoin(ResultTable rt)
{
	if (isInitialEmpty) {
		setSynList( rt.getSynList());
		tupleList = rt.getTupleList();
		isInitialEmpty = rt.isNewTable();
		return;
	}
	if (rt.isInitialEmpty) {
		return;
	}

	vector<Parameter> resSynList = synList;
	vector<vector<int>> newTupleList;
	int commonSyn = 0;
	vector<Parameter> commonSynList;
	vector<pair<int, int>> idMap; 
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

	for (vector<int> tuple1 : tupleList)
		for (vector<int> tuple2 : rt.getTupleList()) {
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
				newTupleList.push_back(resTuple);
			}
		}

	
	setSynList(resSynList);
	tupleList = newTupleList;
	return;

}

void ResultTable::hashJoin(ResultTable rt)
{

	if (isInitialEmpty) {
		setSynList(rt.getSynList());
		tupleList = rt.getTupleList();
		isInitialEmpty = rt.isNewTable();
		return;
	}
	if (rt.isInitialEmpty)
		return;

	vector<Parameter> resSynList = synList;
	int commonSyn = 0;
	unordered_set<int> commonSynIdSet2ndTable; 
	unordered_map<int, int> commonSyn2ndTo1stMap;
	vector<vector<int>> newTupleList;
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
			resSynList.push_back(it);
		}
		else {
			commonSynIdSet2ndTable.insert(rt.getParamId(it));
		}
	}

	unordered_map<string, vector<vector<int>>> hashMap2ndTable;
	
	for (vector<int> tuple : rt.getTupleList()) {
		vector<int> keyVector, valueVector;
		for (int idx = 0; idx < rt.getSynCount(); idx++) {
			if (commonSynIdSet2ndTable.find(idx) == commonSynIdSet2ndTable.end()) {
				valueVector.push_back(tuple.at(idx));
			}
			else {
				keyVector.push_back(tuple.at(idx));
			}
		}

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

	for (vector<int> tuple1 : tupleList) {
		vector<int> tmpVector;
		
		for (int i = 0; i < rt.getSynCount(); i++) {
			auto it = commonSyn2ndTo1stMap.find(i);
			if (it != commonSyn2ndTo1stMap.end()) {
				tmpVector.push_back(tuple1.at(it->second));
			}
		}
		string hashString = convertTupleToString(tmpVector);

		auto it = hashMap2ndTable.find(hashString);
		if (it != hashMap2ndTable.end()) {
			vector<vector<int>> mappedTupleList = it->second;
			for (vector<int> appendingTuple : mappedTupleList) {
				vector<int> newTuple = tuple1; 
				newTuple.insert(newTuple.end(), appendingTuple.begin(), appendingTuple.end());
				newTupleList.push_back(newTuple);
			}	

		}
	}
	setSynList(resSynList);
	tupleList = newTupleList;
	return;
}

ResultTable ResultTable::select(vector<Parameter> paramList)
{
	return hashSelect(paramList);
}

void ResultTable::removeDuplicateTuple()
{
	tupleList = select(synList).getTupleList();
}

ResultTable ResultTable::nestedSelect(vector<Parameter> paramList)
{
	unordered_map<int, int> idMap;  
	for (int i = 0; i < (int)paramList.size(); i++) {
		bool isExist = false;
		for (int j = 0; j<(int)synList.size(); j++)
			if (paramList.at(i).getParaName().compare(synList.at(j).getParaName()) == 0) {
				isExist = true;
				idMap.insert(make_pair(i, j));
			}
		if (isExist == false)
			return ResultTable(); 
	}

	ResultTable res;

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
	unordered_map<int, int> idMap;  
	for (int i = 0; i < (int)paramList.size(); i++) {
		bool isExist = false;
		for (int j = 0; j<(int)synList.size(); j++)
			if (paramList.at(i).getParaName().compare(synList.at(j).getParaName()) == 0) {
				isExist = true;
				idMap.insert(make_pair(i, j));
			}
		if (isExist == false)
			return ResultTable();  
	}

	ResultTable res;


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
	string hashString;
	hashString += "\"";
	for (int i = 0; i < (int)tuple.size(); i++) {
		hashString += "@" + to_string(tuple.at(i)) + "%";
	}
	hashString += "\"";
	return hashString;
}
