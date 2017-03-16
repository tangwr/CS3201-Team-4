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
	//PKB *pkb;
	//bool isRel;
	vector<Parameter> synList;

	Type paramType1, paramType2;
	vector<int> valueList1, valueList2;
	unordered_set<int> valueSet1, valueSet2;

	bool isValidParameter(PKB *pkb, Parameter param);
	bool isSynonym(Type synType);
	bool hasRelation(PKB *pkb);
	//vector<int> evaluateRelation(PKB *pkb, Type synType);
	unordered_set<int> evaluateRelation(PKB *pkb, Type synType);
	//vector<int> getModifyStmtListOfVar();
	//vector<int> getModifyProcListOfVar();
	//vector<int> getModifyVarListOfStmt();

	//vector<int> getModifyStmtListOfVar(PKB *pkb, unordered_set<int> stmtListSet);
	//vector<int> getModifyProcListOfVar(PKB *pkb, unordered_set<int> procListSet);
	//vector<int> getModifyVarListOfStmt(PKB *pkb, unordered_set<int> varListSet);

	unordered_set<int> getModifyStmtListOfVar(PKB *pkb, unordered_set<int> stmtListSet);
	unordered_set<int> getModifyProcListOfVar(PKB *pkb, unordered_set<int> procListSet);
	unordered_set<int> getModifyVarListOfStmt(PKB *pkb, unordered_set<int> varListSet);

	//vector<int> convertSetToVector(unordered_set<int> unorderedSet);
	//unordered_set<int> convertVectorToSet(vector<int> vectorList);

	unordered_set<int> mergeSet(unordered_set<int> s1, unordered_set<int> s2);

	//vector<int> getRestrictedList(Type synType);
	unordered_set<int> getRestrictedSet(PKB *pkb, Type synType);

public:
	Modifies(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	vector<Parameter> getSynList();
	ResultTable evaluate(PKB *pkb, ResultTable intResultTable);
	void insertSynList(Parameter p);
	ClauseType getClauseType();

	//testing
	//void setPKB(PKB* pkbInput);

	//ResultTable evaluate(PKB *pkb, vector<Parameter> paramList, vector<vector<int>> valueList);

	//bool hasRel(PKB *pkb);
	//vector<int> getWithRelToLeft(PKB *pkb);
	//vector<int> getWithRelToRight(PKB *pkb);

	

};
#endif
