#ifndef NextStarH
#define NextStarH

#include <string>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "unordered_set"
#include "ResultTable.h"

using namespace std;

class NextStar : public Clause {
private:
	Parameter leftChild;
	Parameter rightChild;
	vector<Parameter> synList;
	ResultTable result;

public:
	NextStar(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	ResultTable evaluate(PKB*, ResultTable);
	void insertSynList(Parameter);
	vector<Parameter> getSynList();
	ClauseType getClauseType();
};
#endif
