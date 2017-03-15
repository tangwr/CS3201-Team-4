#ifndef ModifiesH
#define ModifiesH

#include <string>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include <unordered_set>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "VectorSetOperation.h"
#include "ResultTable.h"

using namespace std;

class Modifies : public Clause {
private:
	
	Parameter leftChild;
	Parameter rightChild;
	PKB *pkb;
	bool isRel;
	vector<Parameter> synList;

	Type paramType1, paramType2;
	vector<int> valueList1, valueList2;

	bool isValidParameter(Parameter param);
	bool isSynonym(Type synType);
	bool hasRelation(PKB *pkb);
	vector<int> evaluateRelation(PKB *pkb, Type synType);

	vector<int> getModifyStmtListOfVar();
	vector<int> getModifyProcListOfVar();
	vector<int> getModifyVarListOfStmt();

	vector<int> convertSetToVector(unordered_set<int> unorderedSet);

	vector<int> getRestrictedList(Type synType);

public:
	Modifies(Parameter lc, Parameter rc);

	bool hasRel(PKB *pkb);
	vector<int> getWithRelToLeft(PKB *pkb);
	vector<int> getWithRelToRight(PKB *pkb);

	Parameter getLeftChild();
	Parameter getRightChild();
	vector<Parameter> getSynList();

	void insertSynList(Parameter p);

	ResultTable evaluate(PKB *pkb, vector<Parameter> paramList, vector<vector<int>> valueList);

	//testing
	void setPKB(PKB* pkbInput);

};
#endif
