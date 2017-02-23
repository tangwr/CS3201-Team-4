#ifndef UsesH
#define UsesH

#include <string>
#include <unordered_map>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "VectorSetOperation.h"

using namespace std;

class Uses : public Clause {
private:
	//ClauseType cltype;
	string leftChild;
	string rightChild;
	Type leftChildType;
	Type rightChildType;
	PKB *pkb;
	bool isRel;
	vector<int> getStmtListOfVarIdList(vector<int> varIdList);
	vector<int> getParentOfStmt(vector<int> stmtList);

	vector<int> getUsesCallStmt(vector<int> stmtList, vector<int> varStmtList);
	vector<int> getStmtOfCallStmt(vector<int> stmtList, int varStmtId, int callStmtId);

	vector<int> getUsesVarStmt(vector<int> stmtList, vector<int> varStmtList);
	vector<int> getStmtOfVarStmt(vector<int> stmtList, int varStmtId, int callStmtId);

	vector<int> getUsesProcId(vector<int> procIdList, vector<int> varStmtList);
	vector<int> getUsesProcStmt(vector<int> procIdList, vector<int> varStmtList);

public:

	Uses(string, Type, string, Type);	
	bool hasRel(PKB *pkb);
	vector<int> getWithRelToLeft(PKB *pkb, vector<int> synList);
	vector<int> getWithRelToRight(PKB *pkb, vector<int> synList);
	vector<int> getReverseRelToLeft(PKB *pkb, vector<int> synList);
	vector<int> getReverseRelToRight(PKB *pkb, vector<int> synList);
	string getLeftChild();
	string getRightChild();
	Type getLeftChildType();
	Type getRightChildType();
	ClauseType getClauseType();

};
#endif