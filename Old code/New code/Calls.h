#ifndef CallsH
#define CallsH

#include <string>
#include <unordered_map>
#include "Clause.h"
#include "Type.h"
#include "PKB.h"
#include "VectorSetOperation.h"

using namespace std;

class Calls : public Clause {
private:
	//ClauseType cltype;
	string leftChild;
	string rightChild;
	Type leftChildType;
	Type rightChildType;
	PKB *pkb;
	bool isRel;
	vector<int> getCallProc(vector<int> leftProcList, vector<int> rightProcList);
	bool hasDirectCall(int procId, vector<int> procList);
	
public:

	Calls(string, Type, string, Type);
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