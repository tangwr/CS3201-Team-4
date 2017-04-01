#pragma once

#include "Parameter.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>

class ResultTable {

private: 
	vector<Parameter> synList;
	vector<vector<int>> tupleList;
	unordered_map<string, int> synNameMap;
	bool isBoolean;
	bool isInitialEmpty;
	int getParamId(Parameter p);
	string convertTupleToString(vector<int> tuple);
	ResultTable nestedSelect(vector<Parameter> paramList);
	ResultTable hashSelect(vector<Parameter> paramList);
	void nestedJoin(ResultTable rt);
	void hashJoin(ResultTable rt);
public:
	ResultTable();
	bool setInitialEmpty(bool status);
	bool isNewTable();
	bool insertTuple(vector<int> tuple);
	bool setBoolean(bool b);
	bool setSynList(vector<Parameter> list);
	bool isSynInTable(Parameter p);
	int getTupleSize();
	int getSynCount();
	int getSynIndex(Parameter p);
	int getCount(Parameter p);
	bool getBoolean();
	vector<Parameter> getSynList();
	vector<vector<int>> getTupleList();
	void join(ResultTable rt);
	ResultTable select(vector<Parameter> paramList);
	void removeDuplicateTuple();
	unordered_set<int> getSynValue(Parameter param);
	void printTable();
	
};