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
	vector<Clause*> limits;
	vector<Clause*> unlimits;

public:
	QueryTree();
    void insertSelect(string, Type);
	void insertLimits(Clause*);
	void insertUnLimits(Clause*);
	
	vector<Clause*> getLimits();
	vector<Clause*> getUnLimits();
	unordered_map<string, Type> getSelect();

};
#endif