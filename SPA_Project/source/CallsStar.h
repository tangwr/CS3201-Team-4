#ifndef CallsStarH
#define CallsStarH

#include <string>
#include <unordered_map>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "VectorSetOperation.h"
#include "ResultTable.h"

using namespace std;

class CallsStar : public Clause {

public:

	CallsStar(Parameter lc, Parameter rc);
	ResultTable* evaluate(PKB *pkb, ResultTable* intResultTable);
	void insertSynList(Parameter p);
	vector<Parameter> getSynList();
	ClauseType getClauseType();

private:
	Parameter leftChild;
	Parameter rightChild;
	vector<Parameter> synList;
	ResultTable resultTable;

	Type paramType1, paramType2;
	string paramName1, paramName2;
	//vector<int> valueList1, valueList2;
	unordered_set<int> valueSet1, valueSet2;

	bool isValidParameter(PKB *pkb, Parameter param);
	bool isSynonym(Type synType);
	bool hasRelation(PKB *pkb);

	unordered_set<int> evaluateRelation(PKB *pkb, Type synType, string synName);

	unordered_set<int> getCallProcSet(PKB *pkb, Type paraType, string paraName);

	unordered_set<int> mergeSet(unordered_set<int> s1, unordered_set<int> s2);

	unordered_set<int> getRestrictedSet(PKB *pkb, Type synType, string synName);

};

#endif