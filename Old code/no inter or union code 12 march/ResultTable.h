#pragma once

#include "Parameter.h"
#include <vector>

class ResultTable {
private:
	vector<Parameter> synList;
	vector<vector<int>> tupleList;
	bool isBoolean;
	bool isInitialEmpty;
	int getParamId(Parameter p);
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
	int getCount(Parameter p);
	bool getBoolean();
	vector<Parameter> getSynList();
	vector<vector<int>> getTupleList();
	ResultTable join(ResultTable rt);
	ResultTable select(vector<Parameter> paramList);
	vector<int> getSynValue(Parameter param);
	void printTable();
/*
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
	int getSynCount();
	int getCount(Parameter p);
	bool getBoolean();
	vector<Parameter> getSynList();
	vector<vector<int>> getTupleList();
	ResultTable join(ResultTable rt);
	ResultTable select(vector<Parameter> paramList); // pass in lc or rc parameter
	void printTable();
*/
};