#ifndef QueryTreeH
#define QueryTreeH


#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "Type.h"
#include "Clause.h"

using namespace std;

class QueryTree {
private:

	unordered_map<string, Type> select;
	unordered_map<string, Type> comonVar;
	bool isCommonVar;
	vector<Clause*> limits;
	vector<Clause*> unlimits;

public:
	QueryTree();
    void insertSelect(string, Type);
	void insertComonVar(string, Type);
	void insertLimits(Clause*);
	void insertUnLimits(Clause*);
	void setIsComonVar(bool);
	
	vector<Clause*> getLimits();
	vector<Clause*> getUnLimits();
	unordered_map<string, Type> getSelect();
	unordered_map<string, Type> getComonVar();
	bool getIsComonVar();

};
#endif