#include "Controller.h"
#include "Parser.h"
#include "DesignExtractor.h"

Controller::Controller() {
	pkb = new PKB();
	pql = new PQL(pkb);
}

Controller::~Controller() {
	delete pkb;
	delete pql;
}

void Controller::processSource(string source) {	
	Parser parser(pkb, source);
	DesignExtractor designExtractor(pkb);
	
	try {
		parser.parse();
		//pkb->printAllTables();
		designExtractor.extractStarRelations();
	} catch (string msg) {
		cerr << msg << endl;
		exit(1);
	}

	pkb->printAllTables();

	cout << "finish parsing" << endl;
}

list<string> Controller::processQuery(string source) {
	return pql->evaluateQuery(source);
}