#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <unordered_map>

enum CHILD {
	LEFT_CHILD,
	RIGHT_CHILD
};


using namespace std;

class QueryEvaluator {
private:
	bool checkCondition();
	
	vector<int> getDeclareTypeList(Type);
	vector<int> getClauseTypeList(ClauseType, int, CHILD);
	bool isSubsetList(vector<int>, vector<int>);
	bool checkClauseCondition(ClauseType, string, string, Type, Type);

	vector<int> getEntRefList(string, Type);
	vector<int> QueryEvaluator::get_stmt_ent_list(ClauseType, int);
	bool QueryEvaluator::check_stmt_ent_condition(ClauseType, string, string, Type, Type);

	bool checkFollow(string, string, Type, Type);
	bool checkFollowStar();
	bool checkParent();
	bool checkParentStar();
	bool checkPattern();
	bool checkModifies(string, string, Type, Type);
	bool checkUses();

	vector<string> getAssignResult();
	vector<string> getStatementResult();
	vector<string> getVariableResult();
	vector<string> getWhileResult();
	vector<string> getConstantResult();
	vector<string> getProgLineResult();
	vector<string> getBooleanResult();

public:
	QueryEvaluator();
	vector<string> evaluate(QueryTree*);
};