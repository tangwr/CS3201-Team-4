#include "QueryEvaluator.h"

/*Public */

QueryEvaluator::QueryEvaluator() {

}
QueryEvaluator::QueryEvaluator(PKB* pkbSource){
	pkb = pkbSource;
}

void QueryEvaluator::setPKB(PKB* pkbInput) {
	this->pkb = pkbInput;
}


vector<int> QueryEvaluator::evaluate(QueryTree qt) {

	vector<Clause*> limitList = qt.getLimits();
	vector<Clause*> unlimitList = qt.getUnLimits();
	unordered_map<string, Type> selectMap = qt.getSelect();
	vector<int> evaluateResults;
	
	

	for (auto select : selectMap) {
		string selectString = select.first;
		Type selectType = select.second;
		
		
		if (evaluateUnlimitList(unlimitList) == false) {
			return evaluateResults;
		}
		
		if (limitList.size() == 0) {
			evaluateResults = getAllSelectResults(selectType);

			return evaluateResults;
		}

		evaluateResults = evaluateLimitList(limitList, selectType);
	
		return evaluateResults;
	}
	return evaluateResults;
}

/*Private methods*/

bool QueryEvaluator::evaluateUnlimitList(vector<Clause*> unlimitList) {

	for (int i = 0; i < (int)unlimitList.size(); i++) {
		Clause* c = unlimitList[i];
		
		//Temp
		bool hasRelation = c->hasRel(pkb);
		if (hasRelation == false) {
			return false;
		}
	}
	return true;

}

vector<int> QueryEvaluator::evaluateLimitList(vector<Clause*> limitList, Type selectType) {
	
	vector<int> evaluateResults, oldEvaluateResults;

	for (int i = 0; i < (int)limitList.size(); i++) {
		Clause* c = limitList[i];
		Type leftChildType = c->getLeftChildType();
		Type rightChildType = c->getRightChildType();

		if (selectType == leftChildType) {
			evaluateResults = c->getWithRelToLeft(pkb);
		}
		if (selectType == rightChildType) {
			evaluateResults = c->getWithRelToRight(pkb);
		}
		
		//Return if there is only 1 item in the limit list
		if (limitList.size() == 1) {
			return evaluateResults;
		}

		//Get the intersection of "x" number of result list
		if (i != 0) {
			evaluateResults = getIntersection(oldEvaluateResults, evaluateResults);
		}
		oldEvaluateResults = evaluateResults;
	}
	return evaluateResults;
}

vector<int> QueryEvaluator::getAllSelectResults(Type selectType) {

	vector<int> result;
	list<string> strResults;


	switch (selectType) {
	case STMT:
		//need to deal with more condition
		result = pkb->getAllStmtId();
		break;
	case ASSIGN:
		result = pkb->getAllAssignStmtId();
		break;
	
	case WHILES:
		result = pkb->getAllWhileStmtId();
		break;
	case VARIABLE:
		result = pkb->getAllVarId();
		break;
	}

	return result;
}

vector<int> QueryEvaluator::getIntersection(vector<int> v1, vector<int> v2) {
	vector<int> v3;
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));

	return v3;
}

vector<int> QueryEvaluator::getUnion(vector<int> v1, vector<int> v2) {
	vector<int> v3;
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));

	return v3;
}



////////////////////////////////////////////////////////////


//using list instead of vector
list<int> QueryEvaluator::getUnionList(list<int> s1, list<int> s2) {
	list<int> s3;
	s1.sort();
	s2.sort();

	set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(s3));

	return s3;
}

