#include "Controller.h"
#include "Parser.h"
#include "PKB.h"
#include "DesignExtractor.h"

Controller::Controller() {}

void Controller::processSource(string source) {
	PKB pkb;
	
	Parser parser(&pkb, source);
	parser.parse();

	DesignExtractor extractor(&pkb);
	extractor.extractStarRelations();

	pkb.printAllTables();

	cout << "finish parsing" << endl;
}

string Controller::processQuery(string source) {
	return "";
}