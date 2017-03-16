#ifndef UsesH
#define UsesH

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "VectorSetOperation.h"
#include "ResultTable.h"

using namespace std;

class Uses : public Clause {
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

	//vector<int> getUseStmtListOfVar();
	//vector<int> getUseProcListOfVar();
	//vector<int> getUseVarListOfStmt();

	//vector<int> getUseStmtListOfVar(PKB *pkb, unordered_set<int> stmtListSet);
	//vector<int> getUseProcListOfVar(PKB *pkb, unordered_set<int> procListSet);
	//vector<int> getUseVarListOfStmt(PKB *pkb, unordered_set<int> varListSet);

	unordered_set<int> getUseStmtListOfVar(PKB *pkb, unordered_set<int> stmtListSet);
	unordered_set<int> getUseProcListOfVar(PKB *pkb, unordered_set<int> procListSet);
	unordered_set<int> getUseVarListOfStmt(PKB *pkb, unordered_set<int> varListSet);

	//vector<int> convertSetToVector(unordered_set<int> unorderedSet);
	//unordered_set<int> convertVectorToSet(vector<int> vectorList);

	unordered_set<int> mergeSet(unordered_set<int> s1, unordered_set<int> s2);

	//vector<int> getRestrictedList(Type synType);
	unordered_set<int> getRestrictedSet(PKB *pkb, Type synType);
	

public:

	Uses(Parameter lc, Parameter rc);
	Parameter getLeftChild();
	Parameter getRightChild();
	ResultTable evaluate(PKB *pkb, ResultTable intResultTable);
	void insertSynList(Parameter p);
	vector<Parameter> getSynList();
	ClauseType getClauseType();

	//testing
	//void setPKB(PKB* pkbInput);

	//bool hasRel(PKB *pkb);
	//vector<int> getWithRelToLeft(PKB *pkb);
	//vector<int> getWithRelToRight(PKB *pkb);

	//ResultTable evaluate(PKB *pkb, vector<Parameter> paramList, vector<vector<int>> valueList);

	

	
};
#endif
