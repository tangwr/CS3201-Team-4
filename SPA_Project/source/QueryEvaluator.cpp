#include "QueryEvaluator.h"
#include "ClauseType.h"
#include "Follow.h"
#include "FollowStar.h"
#include "Modifies.h"
#include "Parent.h"
#include "ParentStar.h"
#include "Pattern.h"
#include "Uses.h"

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
	vector<Clause*> rawUnLimitList = qt.getUnLimits();
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

	string selectString;
	Type selectType;
	for (auto select : selectMap) {
		selectString = select.first;
		selectType = select.second;
	}
	returnResults.setResultType(selectType);

	vector<int> list1;
	vector<int> list2;
	vector<int> list3;
	vector<int> list4;

	if (allList.size() > 1) {
		if (isCommon) {
			string commonString;
			Type commonType;
			for (auto select : commonVarMap) {
				commonString = select.first;
				commonType = select.second;
			}

			if (selectType == commonType && selectString.compare(commonString) == 0) {
				vector<int> intersect1;
				if (allList[0]->getLeftChildType() == selectType && allList[0]->getLeftChild().compare(selectString) == 0) {
					intersect1 = allList[0]->getWithRelToLeft(pkb);
				}
				else {
					intersect1 = allList[0]->getWithRelToRight(pkb);
				}

				vector<int> intersect2;
				if (allList[1]->getLeftChildType() == selectType && allList[1]->getLeftChild().compare(selectString) == 0) {
					intersect2 = allList[1]->getWithRelToLeft(pkb);
				}
				else {
					intersect2 = allList[1]->getWithRelToRight(pkb);
				}

				returnResults.setResultVector(VectorSetOperation<int>::setIntersection(intersect1, intersect2));
			}
			else {
				vector<int> intersect1;
				int selectPos = 0;

				if (allList[1]->getLeftChildType() == selectType && allList[1]->getLeftChild().compare(selectString) == 0) {
					selectPos = 1;
				}
				else if (allList[1]->getRightChildType() == selectType && allList[1]->getRightChild().compare(selectString) == 0) {
					selectPos = 1;
				}

				if (allList[0]->getLeftChildType() == commonType && allList[0]->getLeftChild().compare(commonString) == 0) {
					intersect1 = allList[0]->getWithRelToLeft(pkb);
				}
				else {
					intersect1 = allList[0]->getWithRelToRight(pkb);
				}

				vector<int> intersect2;
				if (allList[1]->getLeftChildType() == commonType && allList[1]->getLeftChild().compare(commonString) == 0) {
					intersect2 = allList[1]->getWithRelToLeft(pkb);
				}
				else {
					intersect2 = allList[1]->getWithRelToRight(pkb);
				}

				vector<int> intersect3 = VectorSetOperation<int>::setIntersection(intersect1, intersect2);

				for (int i = 0; i < intersect3.size(); i++) {
					vector<int> temp;
					Pattern *p;
					switch (allList[selectPos]->getClauseType()) {
					case FOLLOW:
						if (allList[selectPos]->getLeftChildType() == selectType && allList[selectPos]->getLeftChild().compare(selectString) == 0) {
							Follow q(string(), selectType, to_string(intersect3[i]), INTEGER);
							temp = q.getWithRelToLeft(pkb);
						}
						else {
							Follow q(to_string(intersect3[i]), INTEGER, string(), selectType);
							temp = q.getWithRelToRight(pkb);
						}
						break;
					case FOLLOWSTAR:
						if (allList[selectPos]->getLeftChildType() == selectType && allList[selectPos]->getLeftChild().compare(selectString) == 0) {
							FollowStar q(string(), selectType, to_string(intersect3[i]), INTEGER);
							temp = q.getWithRelToLeft(pkb);
						}
						else {
							FollowStar q(to_string(intersect3[i]), INTEGER, string(), selectType);
							temp = q.getWithRelToRight(pkb);
						}
						break;
					case MODIFIES:
						if (allList[selectPos]->getLeftChildType() == selectType && allList[selectPos]->getLeftChild().compare(selectString) == 0) {
							Modifies q(string(), selectType, to_string(intersect3[i]), INTEGER);
							temp = q.getWithRelToLeft(pkb);
						}
						else {
							Modifies q(to_string(intersect3[i]), INTEGER, string(), selectType);
							temp = q.getWithRelToRight(pkb);
						}
						break;
					case PARENT:
						if (allList[selectPos]->getLeftChildType() == selectType && allList[selectPos]->getLeftChild().compare(selectString) == 0) {
							Parent q(string(), selectType, to_string(intersect3[i]), INTEGER);
							temp = q.getWithRelToLeft(pkb);
						}
						else {
							Parent q(to_string(intersect3[i]), INTEGER, string(), selectType);
							temp = q.getWithRelToRight(pkb);
						}
						break;
					case PARENTSTAR:
						if (allList[selectPos]->getLeftChildType() == selectType && allList[selectPos]->getLeftChild().compare(selectString) == 0) {
							ParentStar q(string(), selectType, to_string(intersect3[i]), INTEGER);
							temp = q.getWithRelToLeft(pkb);
						}
						else {
							ParentStar q(to_string(intersect3[i]), INTEGER, string(), selectType);
							temp = q.getWithRelToRight(pkb);
						}
						break;
					case PATTERN:
						p = (Pattern*)allList[selectPos];
						if (allList[selectPos]->getLeftChildType() == selectType && allList[selectPos]->getLeftChild().compare(selectString) == 0) {
							Pattern q(string(), selectType, to_string(intersect3[i]), INTEGER, p->getUnderScore(), p->getFactor(), p->getFactorType());
							temp = q.getWithRelToLeft(pkb);
						}
						else {
							Pattern q(to_string(intersect3[i]), INTEGER, string(), selectType, p->getUnderScore(), p->getFactor(), p->getFactorType());
							temp = q.getWithRelToRight(pkb);
						}
						break;
					case USES:
						if (allList[selectPos]->getLeftChildType() == selectType && allList[selectPos]->getLeftChild().compare(selectString) == 0) {
							Uses q(string(), selectType, to_string(intersect3[i]), INTEGER);
							temp = q.getWithRelToLeft(pkb);
						}
						else {
							Uses q(to_string(intersect3[i]), INTEGER, string(), selectType);
							temp = q.getWithRelToRight(pkb);
						}
						break;
					}
					returnResults.setResultVector(VectorSetOperation<int>::setUnion(returnResults.getResultVector(), temp));
				}
			}
		}
		else {
			vector<int> intersect1;
			if (allList[0]->getLeftChildType() == selectType && allList[0]->getLeftChild().compare(selectString) == 0) {
				intersect1 = allList[0]->getWithRelToLeft(pkb);
			}
			else if (allList[0]->getRightChildType() == selectType && allList[0]->getRightChild().compare(selectString) == 0) {
				intersect1 = allList[0]->getWithRelToRight(pkb);
			}
			else {
				if (allList[0]->hasRel(pkb)) {
					intersect1 = getAllSelectResults(selectType);
					returnResults.setResultBool(true);
				}
				else {
					intersect1 = vector<int>();
					returnResults.setResultBool(false);
				}
			}

			vector<int> intersect2;
			if (allList[1]->getLeftChildType() == selectType && allList[1]->getLeftChild().compare(selectString) == 0) {
				intersect2 = allList[0]->getWithRelToLeft(pkb);
			}
			else if (allList[1]->getRightChildType() == selectType && allList[1]->getRightChild().compare(selectString) == 0) {
				intersect2 = allList[0]->getWithRelToRight(pkb);
			}
			else {
				if (allList[1]->hasRel(pkb)) {
					intersect2 = getAllSelectResults(selectType);
					returnResults.setResultBool(true);
				}
				else {
					intersect2 = vector<int>();
					returnResults.setResultBool(false);
				}
			}

			returnResults.setResultVector(VectorSetOperation<int>::setIntersection(intersect1, intersect2));
		}
	}
	else if (allList.size() == 1){
		if (allList[0]->getLeftChildType() == selectType && allList[0]->getLeftChild().compare(selectString) == 0) {
			returnResults.setResultVector(allList[0]->getWithRelToLeft(pkb));
		}
		else if (allList[0]->getRightChildType() == selectType && allList[0]->getRightChild().compare(selectString) == 0) {
			returnResults.setResultVector(allList[0]->getWithRelToRight(pkb));
		}
		else {
			if (allList[0]->hasRel(pkb)) {
				returnResults.setResultVector(getAllSelectResults(selectType));
				returnResults.setResultBool(true);
			}
			else {
				returnResults.setResultVector(vector<int>());
				returnResults.setResultBool(false);
			}
		}
	}
	else {
		returnResults.setResultVector(getAllSelectResults(selectType));
	}

	//Remove clause allList object
	for (int i = 0; i < allList.size(); i++) {
		delete allList[i];
	}
	allList.clear();

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

vector<int> QueryEvaluator::evaluateLimitList(vector<Clause*> limitList, Type selectType, string selectStr) {
	
	vector<int> evaluateResults, oldEvaluateResults;

	for (int i = 0; i < (int)limitList.size(); i++) {
		Clause* c = limitList[i];
		Type leftChildType = c->getLeftChildType();
		Type rightChildType = c->getRightChildType();
		string leftChildStr = c->getLeftChild();
		string rightChildStr = c->getRightChild();

		if (leftChildType != selectType && rightChildType != selectType) {
			evaluateResults = c->getWithRelToLeft(pkb);
		}
		
		if (selectType == leftChildType) {
			if (selectStr == leftChildStr) {
				evaluateResults = c->getWithRelToLeft(pkb);
			}
		}
		if (selectType == rightChildType) {
			if (selectStr == rightChildStr) {
				evaluateResults = c->getWithRelToRight(pkb);
			}
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
		result = pkb->getAllAssignStmt(); 
		break;
	
	case WHILES:
		result = pkb->getAllWhileStmt();
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




