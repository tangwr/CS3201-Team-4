#include "Controller.h"
#include "Parser.h"
#include "DesignExtractor.h"

//to delete=========================
#include "Pattern.h"
#include "Type.h"
#include "Result.h"
#include "PostProcessor.h"
//==================================

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

list<string> Controller::processQuery(string source) {

	return list<string>();
}