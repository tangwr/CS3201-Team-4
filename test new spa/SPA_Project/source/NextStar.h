#ifndef NextStarH
#define NextStarH

#include <string>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "ResultTable.h"

using namespace std;

class NextStar : public Clause {
private:
	Parameter leftChild;
	Parameter rightChild;
	vector<Parameter> synList;


public:
	NextStar(Parameter lc, Parameter rc);

};
#endif
