#include "Controller.h"
#include "Parser.h"
#include "DesignExtractor.h"
#include "Pattern.h"
#include "Type.h"

Controller::Controller() {
	pkb = new PKB();
}

Controller::~Controller() {
	delete pkb;
}

void Controller::processSource(string source) {	
	Parser parser(pkb, source);
	parser.parse();

	DesignExtractor extractor(pkb);
	extractor.extractStarRelations();

	pkb->printAllTables();

	cout << "finish parsing" << endl;
}

string Controller::processQuery(string source) {
	Pattern pat("a", Type::ASSIGN, "_", Type::ANYTHING, true, "x+i", Type::STRINGVARIABLE);
	pat.setUnderScore(true);

	/*
	vector<int> result = pat.getResultRelwithLeft(pkb);

	cout << endl << "result of pattern: ";
	for (int i = 0; i < (int)result.size(); i++) {
		cout << result[i] << " ";
	}
	cout << endl;
	*/

	if (pat.hasRel(pkb)) {
		cout << "Have Relation" << endl;
	}
	else {
		cout << "No Relation" << endl;
	}

	return "";
}