#include "Controller.h"
#include "Parser.h"
#include "DesignExtractor.h"
#include "QueryEvaluator.h"
#include "Modifies.h"

Controller::Controller() {
	pkb = new PKB();
}

void Controller::processSource(string source) {	
	Parser parser(pkb, source);
	parser.parse();

	DesignExtractor extractor(pkb);
	extractor.extractStarRelations();

	//pkb->printAllTables();

	cout << "finish parsing" << endl;
}

string Controller::processQuery(string source) {
	cout << "\n PQL" << endl;
	/*
	QueryEvaluator qe;
	qe.setPKB(pkb);
	

	vector<string> selectStr = { "s", "s", "s", "s", "s", "v" };
	vector<Type> selectType = { STMT, STMT, STMT, STMT, STMT, VARIABLE };
	//vector<Type> selectType = { ASSIGN, ASSIGN, ASSIGN, ASSIGN, ASSIGN, VARIABLE };
	//vector<Type> selectType = {WHILES, WHILES, WHILES, WHILES, WHILES, VARIABLE };
	//vector<Type> selectType = { BOOLEAN, BOOLEAN, BOOLEAN, VARIABLE, VARIABLE, VARIABLE };


	vector<string> leftChild = { "s", "s", "s", "s", "s", "s" };
	vector<Type> leftChildType = { STMT, STMT, STMT, STMT, STMT, STMT };
	//vector<Type> leftChildType = { ASSIGN, ASSIGN, ASSIGN, ASSIGN, ASSIGN, ASSIGN };
	//vector<Type> leftChildType = { WHILES, WHILES, WHILES, WHILES, WHILES, WHILES };
	//vector<string> leftChild = { "1", "1", "1", "1", "2", "3" };
	//vector<string> leftChild = { "13", "13", "13", "14", "12", "13" };
	//vector<Type> leftChildType = { INTEGER, INTEGER, INTEGER, INTEGER, INTEGER, INTEGER};

	vector<string> rightChild = { "x", "y", "z", "_", "v", "v" };
	vector<Type> rightChildType = { STRINGVARIABLE, STRINGVARIABLE, STRINGVARIABLE, ANYTHING, VARIABLE, VARIABLE };

	//vector<string> rightChild = { "x", "y", "z", "v", "v", "_" };
	//vector<Type> rightChildType = { STRINGVARIABLE, STRINGVARIABLE, STRINGVARIABLE, VARIABLE, VARIABLE, ANYTHING };
	


	for (int i = 0; i < 6; i++) {
		QueryTree qt;
			
		qt.insertSelect(selectStr[i], selectType[i]);
		Modifies* m = new Modifies(leftChild[i], leftChildType[i], rightChild[i], rightChildType[i]);
		
		//qt.insertUnLimits(m); //check boolean list
		qt.insertLimits(m); //get the results from seelct

		
		vector<int> result = qe.evaluate(qt);
		
		for (int v : result) {
			cout << v << " ";
		}
		cout << " " << endl;
		
	}
	*/
	
	QueryTree qt;
	QueryEvaluator qe;
	qe.setPKB(pkb);
	
	qt.insertSelect("a", ASSIGN);
	Modifies *m = new Modifies("a", ASSIGN, "x", STRINGVARIABLE);
	
	qt.insertLimits(m); //for select results
	//qt.insertUnLimits(m); //for true / false results
	vector<int> result = qe.evaluate(qt);
	
	for (int i : result) {
		cout << i << " ";
	}
	
	
 	return "";
}