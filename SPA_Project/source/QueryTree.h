#pragma once
#ifndef QueryTreeH
#define QueryTreeH


#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "Type.h"
#include "Clause.h"
#include "Parameter.h"

using namespace std;

class QueryTree {
public:
	QueryTree();
	/**
	* Take in the parameter and insert it into the vector select
	*
	* @param Parameter p
	*/
	void insertSelect(Parameter p);
	/**
	* Take in a pointer of Clause object and insert it into the vector of the results
	*
	* @param a pointer of the Clause object
	*/
	void insertResult(Clause*);
	/**
	* Take in a Parameter object and insert it into a vector of the used synonyms
	*
	* @param Parameter p
	*/
	void insertUsed(Parameter p);
	/**
	* get the vector of the results
	*
	* @return a vector of Clauses' pointers
	*/
	vector<Clause*> getResult();
	/**
	* get the vector of the selected Parameters
	*
	* @return a vector of Parameter objects
	*/
	vector<Parameter> getSelectParameter();
	/**
	* get the vector of the useds Parameters
	*
	* @return a vector of Parameter objects
	*/
	vector<Parameter> getUsedParameter();
	/**
	* get the size of the vector of the results
	*
	* @return the size of the vector of the results
	*/
	int getClauseSize();
	/**
	* get the specific Clause's pointer by given index 
	* 
	* @param the index 
	* @return the specific Clause's pointer in the resultList  
	*/
	Clause* getClause(int index);

private:
	vector<Parameter> select;
	vector<Parameter> used;
	vector<Clause*> resultList;

};
#endif
