#ifndef CallsH
#define CallsH

#include <string>
#include <unordered_map>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "VectorSetOperation.h"
#include "ResultTable.h"

using namespace std;

class Calls : public Clause {
private:
	Parameter leftChild;
	Parameter rightChild;
	PKB *pkb;
	bool isRel;
	vector<Parameter> synList;

	Type paramType1, paramType2;
	string paramName1, paramName2;
	vector<int> valueList1, valueList2;

	bool isValidParameter(Parameter param);
	bool isSynonym(Type synType);
	bool hasRelation(PKB *pkb);
	vector<int> evaluateRelation(PKB *pkb, Type synType, string synName);

	//vector<int> getCallLeftProcList();
	//vector<int> getCallRightProcList();
	vector<int> getCallProcList(Type paraType, string paraName);

	vector<int> convertSetToVector(unordered_set<int> unorderedSet);
	unordered_set<int> convertVectorToSet(vector<int> vectorList);

	unordered_set<int> mergeSet(unordered_set<int> s1, unordered_set<int> s2);

	//vector<int> getRestrictedList(Type synType, string synName);
	unordered_set<int> getUnRestrictedSet(Type synType, string synName);
	
public:
	Calls(Parameter lc, Parameter rc);

	bool hasRel(PKB *pkb);
	vector<int> getWithRelToLeft(PKB *pkb);
	vector<int> getWithRelToRight(PKB *pkb);
	
	Parameter getLeftChild();
	Parameter getRightChild();
	vector<Parameter> getSynList();

	void insertSynList(Parameter p);

	//ResultTable evaluate(PKB *pkb, vector<Parameter> paramList, vector<vector<int>> valueList);
	ResultTable evaluate(PKB *pkb, ResultTable restrictedTable);

};

#endif