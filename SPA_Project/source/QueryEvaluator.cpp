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

	
	//vector<Clause*> allList = qt.getAllList();
	bool isCommon = qt.getIsComonVar();
	unordered_map<string, Type> selectMap = qt.getSelect();
	unordered_map<string, Type> commonVarMap = qt.getComonVar();

	vector<Clause*> limitList;// = qt.getLimits();
	vector<Clause*> unlimitList;// = qt.getUnLimits();
	vector<Clause*> rawLimitList = qt.getLimits();
	vector<Clause*> rawUnLimitList= qt.getUnLimits();
	vector<int> evaluateResults, oldEvaluateResults;
	Result returnResults;
	bool firstMap = true;

	vector<Clause*> allList;

	for (auto c : rawLimitList) {
		allList.push_back(c);
	}
	for (auto c : rawUnLimitList) {
		allList.push_back(c);
	}
	

	for (auto select : selectMap) {
		string selectString = select.first;
		Type selectType = select.second;
		
		for (int i = 0; i < (int)allList.size(); i++) {
			Clause* c = allList[i];
			Type leftChildType = c->getLeftChildType();
			Type rightChildType = c->getRightChildType();
			string leftChild = c->getLeftChild();
			string rightChild = c->getRightChild();

			if (isCommon == true) {
				for (auto common : commonVarMap) {
					string commonVar = common.first;
					Type commonType = common.second;

					if (commonVar == leftChild || commonVar == rightChild) {
						limitList.push_back(c);
					}
					else {
						unlimitList.push_back(c);
					}		
				}
			}
			else {
				if (selectType == leftChildType || selectType == rightChildType) {
					limitList.push_back(c);
				}
				else {
					unlimitList.push_back(c);
				}
			}
		}
		

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
		
		//for 2 or more select type
		if (firstMap == true) {
			oldEvaluateResults = evaluateResults;
		}
		else {
			evaluateResults = VectorSetOperation<int>::setIntersection(oldEvaluateResults, evaluateResults);
		}

		returnResults.setResultVector(evaluateResults);
		returnResults.setResultType(selectType);
		returnResults.setResultBool(true);
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

		if (leftChildType != selectType && rightChildType != selectType) {
			evaluateResults = c->getWithRelToLeft(pkb);
		}

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




