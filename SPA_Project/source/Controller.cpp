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

void Controller::processSource(string sourceCode) {	
	Parser parser(pkb, sourceCode);
	DesignExtractor designExtractor(pkb);
	
	try {
		parser.parse();
		designExtractor.extractStarRelations();
	} catch (string msg) {
		cerr << msg << endl;
		exit(1);
	}
}

list<string> Controller::processQuery(string querySource) {
	return pql->evaluateQuery(querySource);
}