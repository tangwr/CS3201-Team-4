#ifndef NextH
#define NextH

#include <string>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "ResultTable.h"

using namespace std;

class Next : public Clause {
private:
	Parameter leftChild;
	Parameter rightChild;
	vector<Parameter> synList;


public:
	Next(Parameter lc, Parameter rc);

};
#endif
