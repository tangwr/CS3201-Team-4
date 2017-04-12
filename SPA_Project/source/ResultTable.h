#pragma once

#include "Parameter.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <string>


/*
ResultTable is a data structure created to store query results and 
intermediate table used by Query Evaluator. Each time query evaluator
evaluates the certain clause, the clause will return valid assignments
for each synonym as a resultTable. And when query evaluator merges 
result of a clause, it merges the current intermediate resultTable 
with the returning resultTable from clause to a new intermediate 
resultTable.
*/
class ResultTable {

public:
	ResultTable();

	/*
	set the table to be initially empty so that I can join with other table 

	@status: boolean of initial emptiness
	@return: whether the execution is successful
	*/
	bool setInitialEmpty(bool status);

	/*
	insert tuple to the current table

	@tuple: tuple to insert
	@return: whether the execution is successful
	*/
	bool insertTuple(vector<int> tuple);

	/*
	set the boolean value for empty table representing validity

	@status: boolean of validity value
	@return: whether the execution is successful
	*/
	bool setBoolean(bool status);

	/*
	set the synonym list for the table

	@list: synonym list of this table
	@return: whether the execution is successful
	*/
	bool setSynList(vector<Parameter> list);
	
	/*
	check whether a given synonym is inside the table

	@p: given synonym
	@return: whether synonym exists
	*/
	bool isSynInTable(Parameter p);

	/*
	check whether table is new, i.e. initially empty

	@return: whether table is new
	*/
	bool isNewTable();

	/*
	get the number of tuples that table contains

	@return: number of tuples
	*/
	int getTupleSize();

	/*
	get the number of synonym that table contains

	@return: number of synonyms
	*/
	int getSynCount();

	/*
	get the validity value of the table

	@return: validity of table
	*/
	bool getBoolean();

	/*
	get the index of a given synonym in the table 
	
	@p: given synonym
	@return: index of the synonym
	*/
	int getSynIndex(Parameter p);

	/*
	get the number of different value for a given synonym in the table

	@p: given synonym
	@return: number of different values of the synonym
	*/
	int getCount(Parameter p);

	/*
	get the synonym list of the table

	@return: synonym list of the tasble 
	*/
	vector<Parameter> getSynList();

	/*
	get the tuple list of the table

	@return: get the tuple list of the table
	*/
	vector<vector<int>> getTupleList();

	/*
	join the current table with a given table 

	@rt: given result table to join with 
	@return: none
	*/
	void join(ResultTable* rt);

	/*
	get the subtable that contains only synonyms in the given list
	and their value tuple without duplicates

	@paramList: list of synonyms to be selected
	@return: table that contains only selected synonyms
	*/
	ResultTable* select(vector<Parameter> paramList);

	/*
	remove any duplicate tuples in the table

	@return: none
	*/
	void removeDuplicateTuple();

	/* 
	return all different values for a given synonym in the table 

	@param: given synonym
	@return: a set containing all value for the given parameter
	*/
	unordered_set<int> getSynValue(Parameter param);

	/*
	print out the content of the table
	*/
	void printTable();

private: 
	vector<Parameter> synList;
	vector<vector<int>> tupleList;
	unordered_map<string, int> synNameMap;
	bool isBoolean;
	bool isInitialEmpty;
	int getParamId(Parameter p);
	string convertTupleToString(vector<int> tuple);
	ResultTable nestedSelect(vector<Parameter> paramList);
	ResultTable* hashSelect(vector<Parameter> paramList);
	void nestedJoin(ResultTable rt);
	void hashJoin(ResultTable* rt);

	
};