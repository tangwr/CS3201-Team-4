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


//vector<int> QueryEvaluator::evaluate(QueryTree qt) {
Result QueryEvaluator::evaluate(QueryTree qt) {

	vector<Clause*> limitList = qt.getLimits();
	vector<Clause*> unlimitList = qt.getUnLimits();
	unordered_map<string, Type> selectMap = qt.getSelect();
	vector<int> evaluateResults;
	Result returnResults;

	

	for (auto select : selectMap) {
		string selectString = select.first;
		Type selectType = select.second;
		
		
		if (evaluateUnlimitList(unlimitList) == false) {
		
			returnResults.setResultVector(evaluateResults);
			returnResults.setResultType(selectType);
			returnResults.setResultBool(false);
			
			return returnResults;
		}
		
		if (limitList.size() == 0) {
			evaluateResults = getAllSelectResults(selectType);

			returnResults.setResultVector(evaluateResults);
			returnResults.setResultType(selectType);
			returnResults.setResultBool(true);
			
			return returnResults;
		}

		evaluateResults = evaluateLimitList(limitList, selectType);

		returnResults.setResultVector(evaluateResults);
		returnResults.setResultType(selectType);
		returnResults.setResultBool(true);
		
	
		return returnResults;
	}
	
	return returnResults;
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
			evaluateResults = VectorSetOperation<int>::setIntersection(oldEvaluateResults, evaluateResults);
		}
		oldEvaluateResults = evaluateResults;
	}
	return evaluateResults;
}

vector<int> QueryEvaluator::getAllSelectResults(Type selectType) {

	vector<int> result;
	list<string> strResults;


	switch (selectType) {
	case PROG_LINE:
	case STMT:
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
	case BOOLEAN:
		result = { 999 }; //non empty value
		break;
	case CONSTANT:
		result = pkb->getAllConstId();
		break;
	}

	return result;
}




