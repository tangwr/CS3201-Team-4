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
private:

	//unordered_map<string, Type> select;
	//unordered_map<string, Type> comonVar;
	//bool isCommonVar;
	//vector<Clause*> limits;
	//vector<Clause*> unlimits;
	vector<Parameter> select;
	vector<Clause*> resultList;

public:
	QueryTree();
   // void insertSelect(string, Type);
	//void insertComonVar(string, Type);
	//void insertLimits(Clause*);
	//void insertUnLimits(Clause*);
	//void setIsComonVar(bool);
	void insertSelect(Parameter p);
	void insertResult(Clause*);
	
	//vector<Clause*> getLimits();
	//vector<Clause*> getUnLimits();
	//unordered_map<string, Type> getSelect();
	//unordered_map<string, Type> getComonVar();
	//bool getIsComonVar();
	vector<Clause*> getResult();
	vector<Parameter> getSelect();

};
#endif
