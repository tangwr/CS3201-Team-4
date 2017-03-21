#pragma once

#include "Parameter.h"
#include <vector>
#include <unordered_set>

class ResultTable {

private: 
	vector<Parameter> synList;
	vector<vector<int>> tupleList;
	bool isBoolean;
	bool isInitialEmpty;
	int getParamId(Parameter p);
	string convertTupleToString(vector<int> tuple);
	ResultTable hashSelect(vector<Parameter> paramList);
	ResultTable hashJoin(ResultTable rt);
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
	ResultTable join(ResultTable rt);	
	ResultTable select(vector<Parameter> paramList);
	unordered_set<int> getSynValue(Parameter param);
	void printTable();
	
};