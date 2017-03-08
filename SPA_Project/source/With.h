#ifndef WithH
#define WithH

#include <string>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "ResultTable.h"

using namespace std;

class With : public Clause {
private:
	Parameter leftChild;
	Parameter rightChild;
	vector<Parameter> synList;


public:
	With(Parameter lc, Parameter rc);
	vector<Parameter> getSynList();
	Parameter getLeftChild();
	Parameter getRightChild();
	void insertSynList(Parameter p);
};
#endif
