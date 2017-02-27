#pragma once

#include "Parameter.h"
#include <vector>

class ResultTable {

private: 
	vector<Parameter> synList;
	vector<vector<int>> tupleList;
	bool isBoolean;
	int getParamId(Parameter p);
public:
	ResultTable();
	bool insertTuple(vector<int> tuple);
	bool setBoolean(bool b);
	bool setSynList(vector<Parameter> list);
	int getsize();
	int getcount(Parameter p);
	vector<Parameter> getSynList();
	vector<vector<int>> getTupleList();
};