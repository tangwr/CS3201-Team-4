#include "QueryParser.h"
#include "QueryTree.h"
#include "Clause.h"
#include "Follow.h"
#include "FollowStar.h"
#include "Modifies.h"
#include "Parent.h"
#include "ParentStar.h"
#include "Pattern.h"
#include "Uses.h"
#include "ExpOperation.h"

#include <regex>



const vector<string> TYPES = { "variable", "constant", "stmt", "assign", "while","prog_line" };

const string TYPE_STRING = "string";
const string TYPE_CONSTANT = "constant";
const string TYPE_ASSIGN = "assign";
const string TYPE_WHILE = "while";
const string TYPE_VARNAME = "varName";
const string TYPE_PROG_LINE = "prog_line";
const string TYPE_ALL = "all";
const string TYPE_BOOLEAN = "BOOLEAN";
const string TYPE_VARIABLE = "variable";
const string TYPE_PATTERN = "pattern";
const string TYPE_SUCH = "such";


const regex variableNameRegex("(^[[:alpha:]])([[:alnum:]]+)*$");
const regex identifierNameRegex("([a-zA-Z][a-zA-Z0-9#]*)");

const char SYMBOL_SEMICOLON = ';';
const char SYMBOL_SPACE = ' ';
const char SYMBOL_COMMA = ',';
const char SYMBOL_QUOTE = '\"';
const char SYMBOL_UNDERSCORE = '_';
const char SYMBOL_OPEN_BRACKET = '(';
const char SYMBOL_CLOSE_BRACKET = ')';
const char SYMBOL_EQUALS = '=';
const char SYMBOL_FULL_STOP = '.';

const vector<string> KEYS = { "Pattern", "and", "such", "that", "call", "prog_line", "Select", "constant", "stmt", "stmtLst", "assign", "while",
	"if", "procedure", "Calls", "Calls*", "Modifies", "Uses", "Affects", "Affects*", "Parent",
	"Parent*", "Follows", "Follows*","Next","Next*", "with" };

const vector<string> RELATIONS = { "Modifies", "Uses", "Parent" , "Parent*", "Follows", "Follows*" };
const vector<string> CHILDREN = { "Parent" , "Parent*", "Follows", "Follows*" };

string checkFirstLeftChild = "";
string checkFirstRightChild = "";
string checkSecondLeftChild = "";
string checkSecondRightChild = "";
int counter1 = 0;
int counter2 = 0;
bool isSuchThanBeforePattern = false;



QueryParser::QueryParser() {

}
bool QueryParser::isValid(string query) {
	queryTree = new QueryTree();
	string q = trim(query);
	cout<< "the trim query is: " <<q;
	queryTree->setIsComonVar(false);
	varMap.clear(); // clear the varMap
	vector<string> resultStr = splitTheString(q, ';');
	int size = resultStr.size();

	int i;
	string feedback = "";
	for (i = 0; i < size - 1; i++) {
		string firstPart = resultStr.at(0);
		cout<< "\n first Part: " << firstPart;

		if (!isValidDeclaration(resultStr.at(i))) {
			feedback =  "\n Invalid Query Declaration: ";
			return false;
		}
		//here is the OKay!
	}
	//subQuery is 
	cout <<"\n"<< "the subQuery is: " << resultStr.at(i);
	if (!isValidQuery(resultStr.at(i))) {
		feedback = "\n Invalid Query: ";
		queryTree->getSelect().clear();
		queryTree->getLimits().clear();
		queryTree->getUnLimits().clear();
		return false;
	}

	feedback = "\n Valid Query: ";

	std::cout << feedback << std::endl;

	return true;
}

QueryTree QueryParser::getQuery() {
	QueryTree qt = *queryTree;
	delete queryTree;
	return qt;
}

bool QueryParser::isValidDeclaration(string input) {
	vector<string> arrDec = splitTheStringIntoParts(input, ' ', 2);
	cout << "\n" << "1: " << arrDec.at(0) << "2: " << arrDec.at(1);
	if (arrDec.size() < 2 || find(TYPES.begin(), TYPES.end(), arrDec.at(0)) == TYPES.end()) {
		return false;
	}

	vector<string> synonyms = splitTheString(arrDec.at(1), ',');

	if (synonyms.size() < 1) {
		return false;
	}

	for (int i = 0; i < synonyms.size(); i++) {
		if (!isValidVarName(synonyms.at(i)) || isVarNameExists(synonyms.at(i))) {
			return false;
		}
		else {
			cout <<"\n"<< "key:" << synonyms.at(i) << "value: " << arrDec.at(0);
				varMap[synonyms.at(i)] = arrDec.at(0);// insert to the VarMap

		}
	}
	return true;
}

bool QueryParser::isValidQuery(string query) {
	vector<string> arrClauses = splitTheStringIntoParts(query, ' ', 2); //split the query into 2 parts.

	cout << "\n"<< "1: " << arrClauses.at(0) << " 2: " << arrClauses.at(1);
	if (arrClauses.at(0).compare("Select") != 0 || arrClauses.size() != 2) {
		return false;
	}

	if (arrClauses.at(1).at(0) == '<') {
		return false; // can only select one 
	}
	else {
		cout << "\n can reach here";
		if (trim(arrClauses.at(1)).size() == 1 && isVarNameExists(arrClauses.at(1))) {
			cout << "\n reach!";
			//for just select s cases;
			string key = arrClauses.at(1);
			cout << "\n" << "the selecMap's key: " << key;
			string variableType = getVarType(key);
			cout << "\n" << "the selectMap's value: " << variableType;
			Type value = getTypeOfChild(variableType);
			queryTree->insertSelect(key, value);
			if (queryTree->getSelect().size() < 1) {
				cout << "\n" << "the Select Map is empty";
			}
			else {
				cout << "\n" << "insert selectmap successfully for only select s";
				string dummy = "";
			}
			return true;
		}
		arrClauses = splitTheStringIntoParts(arrClauses.at(1), ' ', 2);//a and such that...
		cout << "\n";
		cout << "syn : " << arrClauses.at(0) << "  that:  " << arrClauses.at(1);
		if ((!isVarNameExists(arrClauses.at(0)) && arrClauses.at(0).compare(TYPE_BOOLEAN) != 0)) {// select a (here is the a)
			return false;
		}
		cout << "\n";
		cout << "the sys name is valid";

		if (isVarNameExists(arrClauses.at(0))) {
			//here to insert a select Map 
			string key = arrClauses.at(0);
			cout << "\n" << "the selecMap's key: " << key;
			string variableType = getVarType(arrClauses.at(0));
			Type value = getTypeOfChild(variableType);
			cout << "\n" << "the selectMap's value: " << variableType;
			queryTree->insertSelect(key, value);
			if (queryTree->getSelect().size() < 1) {
				cout << "\n" << "the Select Map is empty";
				string dummy = "";
			}
			else {
				cout << "\n" << "insert selectmap successfully";
				string dummy = "";
			}
		}
		else {
			// here to insert Select BOOLEAN
			string key = stringToLower(TYPE_BOOLEAN);
			Type b = BOOLEAN;
			queryTree->insertSelect(key, b);
			if (queryTree->getSelect().size() < 1) {
				cout << "\n" << "the Select Map is empty";
				string dummy = "";
			}
		}
	}
	/*
	if (arrClauses.size() == 1) {
		cout << "\n" << "reach unkowwn";
		return true;
	}*/


	bool isRelationValid;
	string previous = "";

		arrClauses = splitTheStringIntoParts(arrClauses.at(1), ' ', 2);// such and that...
		cout << "\n" << "Arr(0): " << arrClauses.at(0) << " Arr(1): " << arrClauses.at(1);
		if (arrClauses.size() != 2) {
			return false;
		}

		if (arrClauses.at(0).compare("such") == 0) {
			arrClauses = splitTheStringIntoParts(arrClauses.at(1), ' ', 2);

			if (arrClauses.size() != 2 || arrClauses.at(0).compare("that") != 0) {
				return false;
			}
			//here is for the Follow(1,s) pattern a(v, _)
			isSuchThanBeforePattern = true;
			counter1 = 0;// reset the counters
			counter2 = 0;
			isRelationValid = checkRelation(arrClauses.at(1));
			previous = "such that";

		}
		else if (arrClauses.at(0).compare("pattern") == 0) {
			//here is for the pattern checking after the selecting
			isSuchThanBeforePattern = false;
			counter1 = 0;// reset the counters
			counter2 = 0;
			isRelationValid = checkPattern2(arrClauses.at(1));
			previous = "pattern";

		}
		else {
			isRelationValid = false;
		}

	    return isRelationValid;
}

bool QueryParser::checkRelation(string checkingStr) {
	vector<string> arrClauses;

	if (checkingStr.find(TYPE_PATTERN) != std::string::npos) {
		arrClauses = splitTheString(checkingStr, '(');
	}
	else {
		arrClauses = splitTheStringIntoParts(checkingStr, '(', 2);
	}

	if (arrClauses.size() < 2 || find(RELATIONS.begin(), RELATIONS.end(), arrClauses.at(0)) == RELATIONS.end() || arrClauses.size() > 3) {
		return false;
	}
	//is the type of Follows
	string relType = arrClauses.at(0);

	if (arrClauses.at(1).find(")") == string::npos) {
		return false;
	}

	vector<string> arrClauseTemp = splitTheStringIntoParts(arrClauses.at(1), ')', 2);//a,v and pattern a

	if (arrClauseTemp.size() != 2) {
		return false;
	}
	vector<string> arrVariables = splitTheString(arrClauseTemp.at(0), ',');// a,v

	if (arrVariables.size() != 2) {
		return false;
	}
	// now process to check Children method!!
	if (!checkChildren(relType, arrVariables)) {
		return false;
	}

	//for only such that clauses
	if (!strcmp(arrClauseTemp.at(1).c_str(), "")) {
		return true;
	}
	
	//checkingStr = trim(arrClauses.at(1));
	if(arrClauses.at(1).size() > 0) {
	//if((arrClauses.at(1).compare("pattern a")) == 0) {
		vector<string> patternClauses = splitTheStringIntoParts(arrClauseTemp.at(1), ' ', 2);// check the pattern after such that clause
		if (patternClauses.at(0).compare("pattern") == 0) {
			if (patternClauses.size() < 2) {
				return false;
			}
			string origin = patternClauses.at(1);
			string originSub = patternClauses.at(1).substr(0, patternClauses.at(1).size() - 1);
			if (isVarNameExists(originSub)) {
				origin = originSub;
			}
			if (getVarType(origin).compare("assign")== 0) { // only for the pattern a(....) For iteration 1;
				string relType = "pattern";
				string syn = origin;
				Type synType = ASSIGN;
				string passStr = arrClauses.at(2);

				bool isPattern = checkPattern(relType, syn, synType, passStr);
				return isPattern;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

	return true;
}
// parse the "4,a" inside the Follows
bool QueryParser::checkChildren(string relType, vector<string> variable) {
	string leftChild = "";
	string rightChild = "";
	string lcType = "";
	string rcType = "";
	Type leftChildType;
	Type rightChildType;
	bool isLimit = false;

	if (find(CHILDREN.begin(), CHILDREN.end(), relType) != CHILDREN.end() ||
		find(CHILDREN.begin(), CHILDREN.end(), relType.substr(0, relType.size() - 1)) != CHILDREN.end()) {

		for (int i = 0; i < variable.size(); i++) {
			if (i == 0) {

				if (isVarNameExists(variable.at(0))) {
					leftChild = variable.at(0);
					lcType = getVarType(leftChild);
					leftChildType = getTypeOfChild(lcType);
					if (queryTree->getSelect().count(leftChild)) {
						isLimit = true;
					}
					if (isSuchThanBeforePattern) {
						checkFirstLeftChild = leftChild;// set the first left child to check
					}
					else {
						cout << "\n" << "the result comes here";
						if (leftChild.compare(checkFirstLeftChild) == 0 && !checkFirstLeftChild.empty()) {
							counter1++;
							cout << "\n" << "counter1 = " << counter1;
							string dummy = "";
						}
						else if (leftChild.compare(checkFirstRightChild) == 0 && !checkFirstRightChild.empty()) {
							counter1++;
				
						}
					}
					//---------	
 
				}
				else if (variable.at(0).compare("_") == 0) {
					leftChild = variable.at(0);
					leftChildType = getTypeOfChild(leftChild);
				}
				else if (isPositiveInteger(variable.at(0))) {// for the follows and Parent
					leftChild = variable.at(0);

					leftChildType = getTypeOfChild(leftChild);
				}
				else {
					return false;
				}
			}
			else {
				if (isVarNameExists(variable.at(1))) {
					rightChild = variable.at(1);
					rcType = getVarType(rightChild);
					rightChildType = getTypeOfChild(rcType);

					if (queryTree->getSelect().count(rightChild)) {
						isLimit = true;

					}
					if (isSuchThanBeforePattern) {
						checkFirstRightChild = rightChild;// set the first right child to check
					}
					else {
						if (rightChild.compare(checkFirstLeftChild) == 0 && !checkFirstLeftChild.empty() && rightChild.compare(leftChild) != 0) {
							counter2++;
						}
						else if (rightChild.compare(checkFirstRightChild) == 0 && !checkFirstRightChild.empty() && rightChild.compare(leftChild) != 0) {
							counter2++;
							string dummy = "";
						}
					}

				}
				else if (isVarNameExists(variable.at(1).substr(0, variable.at(1).size() - 1))) {// check for the null pointer
					rightChild = variable.at(1).substr(0, variable.at(1).size() - 1);
					rcType = getVarType(rightChild);
					rightChildType = getTypeOfChild(rcType);

					if (queryTree->getSelect().count(rightChild)) {
						isLimit = true;

					}
					if (isSuchThanBeforePattern) {
						checkFirstRightChild = rightChild;// set the first right child to check
					}
					else {
						if (rightChild.compare(checkFirstLeftChild) == 0 && !checkFirstLeftChild.empty() && rightChild.compare(leftChild) != 0) {
							counter2++;
						}
						else if (rightChild.compare(checkFirstRightChild) == 0 && !checkFirstRightChild.empty() && rightChild.compare(leftChild) != 0) {
							counter2++;
							string dummy = "";
						}
					}
				}
				else if (variable.at(1).compare("_") == 0) {
					rightChild = variable.at(1);
					rightChildType = getTypeOfChild(rightChild);
				}
				else if (variable.at(1).substr(0, variable.at(1).size() - 1).compare("_") == 0) {
					rightChild = variable.at(1).substr(0, variable.at(1).size() - 1);
					rightChildType = getTypeOfChild(rightChild);
				}
				else if (isPositiveInteger(variable.at(1))) {
					rcType = "integer";
					rightChild = variable.at(1);
					rightChildType = getTypeOfChild(rightChild);
				}
				else if (isPositiveInteger(variable.at(1).substr(0, variable.at(1).size() - 1))) {
					rcType = "integer";
					rightChild = variable.at(1).substr(0, variable.at(1).size() - 1);
					rightChildType = getTypeOfChild(rightChild);
				}
				else {
					return false;
				}
			}
		}
	}
	else {
		cout << "\n" << "come for the Uses";
		//for the Modifies and Uses objects
		for (int i = 0; i < variable.size(); i++) {
			if (i == 0) {
				if (isVarNameExists(variable.at(0))) {
					leftChild = variable.at(0);
					lcType = getVarType(leftChild);
					leftChildType = getTypeOfChild(lcType);
					if (isSuchThanBeforePattern) {
						checkFirstLeftChild = leftChild;
					}
					if (queryTree->getSelect().count(leftChild)) {
						isLimit = true;
					}
					else {
						if (leftChild.compare(checkFirstLeftChild) == 0 && !checkFirstLeftChild.empty()) {
							counter1++;
						}
					}
				}
				else if (isPositiveInteger(variable.at(0))) {
					leftChild = variable.at(0);
					leftChildType = getTypeOfChild(leftChild);
				}
				else {
					return false;
				}
			}
			else {
				if (isVarNameExists(variable.at(1))) {
					rightChild = variable.at(1);
					rcType = getVarType(rightChild);
					rightChildType = getTypeOfChild(rcType);
					if (isSuchThanBeforePattern) {
						checkFirstRightChild = rightChild;// for Modifies and Uses
					}
					if (queryTree->getSelect().count(leftChild)) {
						isLimit = true;
					}
					else {
						if (rightChild.compare(checkFirstRightChild) == 0 && !checkFirstRightChild.empty()) {
							counter2++;
						}
					}
				}
				else if (isVarNameExists(variable.at(1).substr(0, variable.at(1).size() - 1))) {// for the null poninter checking
					rightChild = variable.at(1).substr(0, variable.at(1).size() - 1);
					rcType = getVarType(rightChild);
					rightChildType = getTypeOfChild(rcType);
					if (isSuchThanBeforePattern) {
						checkFirstRightChild = rightChild;// for Modifies and Uses
					}
					if (queryTree->getSelect().count(leftChild)) {
						isLimit = true;
					}
					else {
						if (rightChild.compare(checkFirstRightChild) == 0 && !checkFirstRightChild.empty()) {
							counter2++;
						}
					}
				}
				else if (variable.at(1).compare("_") == 0) {
					rightChild = variable.at(1);
					rightChildType = getTypeOfChild(rightChild);
				}
				else if (variable.at(1).substr(0, variable.at(1).size() - 1).compare("_") == 0) {
					rightChild = variable.at(1).substr(0, variable.at(1).size() - 1);
					rightChildType = getTypeOfChild(rightChild);
				}
				//indentifier checking 
				else if (isStringVar(variable.at(1))) {
					rightChild = variable.at(1);
					string strVar = rightChild.substr(1, rightChild.size() - 2);
					if (regex_match(strVar, identifierNameRegex)) {
						rightChild = strVar;
					}
					else {
						return false;
					}
					rightChildType = STRINGVARIABLE;
				}
				else if (isStringVar(variable.at(1).substr(0, variable.at(1).size() - 1))) {// for the null pointer checking 
					rightChild = variable.at(1).substr(0, variable.at(1).size() - 1);
					string strVar = rightChild.substr(1, rightChild.size() - 2);
			
					if (regex_match(strVar, identifierNameRegex)) {
						rightChild = strVar;
					}
					else {
						return false;
					}
					rightChildType = STRINGVARIABLE;
				}
				else {
					return false;
				}
			}
		}
	}
	if (counter1 == 1 && counter2 == 1) { // has two Common Variables
		return false;
	}
	else if (counter1 >= 1) {
		string key = leftChild;
		string sType = getVarType(key);
		Type comType = getTypeOfChild(sType);
		queryTree->insertComonVar(key, comType);
		//for inserting to the ComonVar Map 
		queryTree->setIsComonVar(true);
	}
	else if (counter2 >= 1) {
		string key = rightChild;
		string sType = getVarType(key);
		Type comType = getTypeOfChild(sType);
		queryTree->insertComonVar(key, comType);
		//for inserting to the ComonVar Map 
		queryTree->setIsComonVar(true);
	}
	//counter checking 
	if (relType.compare("Follows") == 0) {
		//create Follow
		cout << "\n" << "insert into the Follows Object here";
		Follow *f = new Follow(leftChild, leftChildType, rightChild, rightChildType);
		if (isLimit) {
			queryTree->insertLimits(f);
		}
		else {
			queryTree->insertUnLimits(f);

		}
	}
	else if (relType.compare("Follows*") == 0) {
		//create FollowStar
		FollowStar *fs = new FollowStar(leftChild, leftChildType, rightChild, rightChildType);
		if (isLimit) {
			queryTree->insertLimits(fs);
		}
		else {
			queryTree->insertUnLimits(fs);

		}

	}
	else if (relType.compare("Parent") == 0) {
		cout << "\n" << "insert Parent";
		cout << "\n" << leftChild;
		cout << "\n" << lcType;
		cout << "\n" << rightChild;
		cout << "\n" << rcType;
		cout << "\n" << "isCommonVar : " <<queryTree->getIsComonVar();
		Parent *p = new Parent(leftChild, leftChildType, rightChild, rightChildType);
		if (isLimit) {
			queryTree->insertLimits(p);
		}
		else {
			queryTree->insertUnLimits(p);

		}
		if (queryTree->getLimits().size() < 1) {
			cout << "\n" << "nothing inside the limit";
			string dummy = "";
		}
		else {
			cout << "\n" << "stored succesfully";
			string dummy = "";
		}
		if (queryTree->getUnLimits().size() < 1) {
			cout << "\n" << "nothing inside the unLimt";
			string dummy = "";
		}
		else {
			cout << "\n" << "stored succesfully for unLimits";
			string dummy = "";
		}
	}
	else if (relType.compare("Parent*") == 0) {
		ParentStar *ps = new ParentStar(leftChild, leftChildType, rightChild, rightChildType);
		if (isLimit) {
			queryTree->insertLimits(ps);
		}
		else {
			queryTree->insertUnLimits(ps);

		}
	}
	else if (relType.compare("Modifies") == 0) {
		Modifies *m = new Modifies(leftChild, leftChildType, rightChild, rightChildType);
		if (isLimit) {
			queryTree->insertLimits(m);
		}
		else {
			queryTree->insertUnLimits(m);

		}
	}
	else if (relType.compare("Uses") == 0) {
		Uses *u = new Uses(leftChild, leftChildType, rightChild, rightChildType);
		if (isLimit) {
			queryTree->insertLimits(u);
		}
		else {
			queryTree->insertUnLimits(u);

		}
	}
	return true;
}
bool QueryParser::checkPattern(string relType, string syn, Type synType, string subquery) {
	string leftChild = "";
	string rightChild = "";
	string factor = "";
	Type factorType;
	string lcType = "";
	string rcType = "";
	Type leftChildType;
	Type rightChildType;
	bool isUnderscore = false;
	bool isLimit = false;

	if (queryTree->getSelect().count(syn)) {
		isLimit = true;
	}
	if (isSuchThanBeforePattern) {
		if (syn.compare(checkFirstLeftChild) == 0 && !checkFirstLeftChild.empty()) {
			counter1++;
		}
		else if (syn.compare(checkFirstRightChild) == 0 && !checkFirstRightChild.empty()) {
			counter1++;
		}
	}
	
	//set the left child of pattern
	leftChild = syn;
	lcType = getVarType(leftChild);
	cout << "\n" << "lcType = " << lcType;
	leftChildType = getTypeOfChild(lcType);



	vector<string> arrPatterns = splitTheStringIntoParts(subquery, ',', 2);
	if (arrPatterns.size() != 2) {
		return false;
	}


	for (int i = 0; i < arrPatterns.size(); i++) {
		if (i == 0) {
			if (isVarNameExists(arrPatterns.at(0))) {
				string var = arrPatterns.at(0);
				rightChild = var;
				rcType = getVarType(rightChild);
				if (rcType.compare("variable") != 0 && rcType.substr(0,rcType.size() - 1).compare("variable") != 0) {
					return false;
				}
				rightChildType = getTypeOfChild(rcType);
				if (queryTree->getSelect().count(var)) {
					isLimit = true;
				}
				if (isSuchThanBeforePattern) {
					if (var.compare(checkFirstLeftChild) == 0 && !checkFirstLeftChild.empty() && var.compare(syn) != 0) {
						counter2++;
					}
					else if (var.compare(checkFirstRightChild) == 0 && !checkFirstRightChild.empty() && var.compare(syn) != 0) {
						counter2++;
					}
				}
				
				//patterna(v,_), now v is the leftChild; 
			}
			else if (arrPatterns.at(0).compare("_") == 0) {
				rightChild = arrPatterns.at(0);	
				rightChildType = ANYTHING;
			}
			else if (isStringVar(arrPatterns.at(0))) {
				rightChild = arrPatterns.at(0).substr(1, arrPatterns.at(0).size() - 2);// for checing stringVar
				rightChildType = STRINGVARIABLE;
			}
			else {
				return false;
			}
		}
		else {
			//check the last part of the patterna(..., .....)
			if (arrPatterns.at(1).find(")") == string::npos) {
				return false;
			}
			vector<string> PatternChild = splitTheStringIntoParts(arrPatterns.at(1), SYMBOL_CLOSE_BRACKET, 2);
			if (PatternChild.size() < 1) {
				return false;
			}
			else {
				if (PatternChild.at(0).compare("_") == 0) {
					factor = PatternChild.at(0);
					factorType = ANYTHING;
				}
				else if (isBothUnderScore(PatternChild.at(0))) {
					isUnderscore = true;
					string strVar = PatternChild.at(0).substr(1, PatternChild.at(0).size() - 2);
					string factorValue = strVar.substr(1, strVar.size() - 2);
				
					factor = factorValue;
					factorType = STRINGVARIABLE;
				}
				else if (isStringExpression(PatternChild.at(0))) {
					factor = PatternChild.at(0).substr(1, PatternChild.at(0).size() - 2);
	
					if (!ExpOperation::isValidExp(factor)) {
						return false;
					}
					factorType = STRINGVARIABLE;
				}
				else {
					return false;
				}
			}
		}
	}
	//pattern is after such that clause
	if (counter1 == 1 && counter2 == 1) {
		return false;
	}
	else if (counter1 >= 1) {
		string key = syn;
		string sType = getVarType(key);
		Type comType = getTypeOfChild(sType);
		queryTree->insertComonVar(key, comType);
		//for inserting to the ComonVar Map 
		queryTree->setIsComonVar(true);
		if (queryTree->getComonVar().size() > 0) {
			cout << "\n" << "one CommonVar insert successfully";
			string dummy = "";
		}
	}
	else if (counter2 >= 1) {
		string key = rightChild;
		string sType = getVarType(key);
		Type comType = getTypeOfChild(sType);
		queryTree->insertComonVar(key, comType);
		queryTree->setIsComonVar(true);
	}
	//create a pattern obj

	Pattern *pt = new Pattern(leftChild, leftChildType, rightChild, rightChildType, isUnderscore, factor, factorType);
	if (isLimit) {
		queryTree->insertLimits(pt);
	}
	else {
		queryTree->insertUnLimits(pt);
	}
	return true;
}

bool QueryParser::checkPattern2(string checkingStr) {
	string leftChild = "";
	string rightChild = "";
	string factor = "";
	Type factorType;
	string lcType = "";
	string rcType = "";
	Type leftChildType;
	Type rightChildType;
	bool isUnderscore = false;
	bool isLimit = false;
	vector<string> arrWords;

	if (checkingStr.find(TYPE_SUCH) != std::string::npos) {
		arrWords = splitTheString(checkingStr, '(');
	}
	else {
		arrWords = splitTheStringIntoParts(checkingStr, '(', 2);
	}

	if (arrWords.size() < 2 || arrWords.size() > 3) {
		return false;
	}

	if (isVarNameExists(arrWords.at(0))) {
		if (getVarType(arrWords.at(0)).compare("assign") == 0) {
			leftChild = arrWords.at(0);
			leftChildType = ASSIGN;
			if (!isSuchThanBeforePattern) {
				checkFirstLeftChild = leftChild;
			}
			if (arrWords.at(1).find(")") == string::npos) {
				return false;
			}

			vector<string> arrWordsOne = splitTheStringIntoParts(arrWords.at(1), SYMBOL_CLOSE_BRACKET, 2);

			if (arrWordsOne.size() < 1) {
				return false;
			}
			vector<string> arrPatterns = splitTheStringIntoParts(arrWordsOne.at(0), ',', 2);
			if (arrPatterns.size() != 2) {
				return false;
			}

			for (int i = 0; i < arrPatterns.size(); i++) {
				if (i == 0) {
					if (isVarNameExists(arrPatterns.at(0))) {
						string var = arrPatterns.at(0);
						rightChild = var;
						rcType = getVarType(rightChild);
						if (rcType.compare("variable") != 0) {//only can be pattern a(v,_);
							return false;
						}
						rightChildType = getTypeOfChild(rcType);
						if (queryTree->getSelect().count(var)) {
							isLimit = true;
						}
						if (!isSuchThanBeforePattern) {
							checkFirstRightChild = rightChild;
						}
					}
					else if (arrPatterns.at(0).compare("_") == 0) {
						rightChild = arrPatterns.at(0);
						rightChildType = ANYTHING;
					}
					else if (isStringVar(arrPatterns.at(0))) {
						rightChild = arrPatterns.at(0).substr(1, arrPatterns.at(0).size() - 2);// for checing stringVar
						rightChildType = STRINGVARIABLE;
					}
					else {
						return false;
					}
				}
				else {
					//check the part of the patterna(..., here) (pattern before such that)
					if (arrPatterns.at(1).compare("_") == 0) {
						factor = arrPatterns.at(1);
						factorType = ANYTHING;
					}
					else if (arrPatterns.at(1).substr(0, arrPatterns.at(1).size() - 1).compare("_") == 0) {// solve the null pointer problem
						factor = arrPatterns.at(1).substr(0, arrPatterns.at(1).size() - 1);
						factorType = ANYTHING;
					}
					else if (isBothUnderScore(arrPatterns.at(1))) {
						isUnderscore = true;
						string strVar = arrPatterns.at(1).substr(1, arrPatterns.at(1).size() - 2);
						string factorValue = strVar.substr(1, strVar.size() - 2);

						factor = factorValue;
						if (!ExpOperation::isValidExp(factor)) {//check for valid expression
							return false;
						}

						factorType = STRINGVARIABLE;
					}
					else if (isBothUnderScore(arrPatterns.at(1).substr(0, arrPatterns.at(1).size() - 1))) {
						isUnderscore = true;
						string strVar = arrPatterns.at(1).substr(1, arrPatterns.at(1).size() - 2);

						string factorValue = strVar.substr(1, strVar.size() - 3);//for checking the both underScore with null char

						factor = factorValue;
						if (!ExpOperation::isValidExp(factor)) {
							return false;
						}
						factorType = STRINGVARIABLE;
					}
					else if (isStringExpression(arrPatterns.at(1))) {
						factor = arrPatterns.at(1).substr(1, arrPatterns.at(1).size() - 2);
						if (!ExpOperation::isValidExp(factor)) {
							return false;
						}
						factorType = STRINGVARIABLE;
					}
					else if (isStringExpression(arrPatterns.at(1).substr(0, arrPatterns.at(1).size() - 1))) {
						factor = arrPatterns.at(1).substr(1, arrPatterns.at(1).size() - 3);//coz got null char
						if (!ExpOperation::isValidExp(factor)) {
							return false;
						}
						factorType = STRINGVARIABLE;
					}
					else {
						return false;
					}

				}
			}
			// -----------------------
			Pattern *pt = new Pattern(leftChild, leftChildType, rightChild, rightChildType, isUnderscore, factor, factorType);
			if (isLimit) {
				queryTree->insertLimits(pt);
			}
			else {
				queryTree->insertUnLimits(pt);
			}
			string dummy = "";
			//check only have pattern clause
			if (!strcmp(arrWordsOne.at(1).c_str(), "")) {
				return true;
			}


			string word = arrWordsOne.at(1);//such that follows
			word = trim(word);

			//the pattern ... such that ends here!!
			vector<string> arrSuch = splitTheStringIntoParts(word, ' ', 2);
			if (arrSuch.at(0).compare("such") == 0) {
				arrSuch = splitTheStringIntoParts(arrSuch.at(1), ' ', 2);
				
			
				if (arrSuch.size() != 2 || arrSuch.at(0).compare("that") != 0) {
					return false;
				}

				string relType = arrSuch.at(1);//Follows
				if (relType.compare("Parent*") == 0 || relType.compare("Follows*") == 0) {
		        }
				else {
					if (find(RELATIONS.begin(), RELATIONS.end(), relType.substr(0, relType.size() - 1)) != RELATIONS.end()) {
						relType = relType.substr(0, relType.size() - 1);
					}
				}			

				if (find(RELATIONS.begin(), RELATIONS.end(), relType) == RELATIONS.end() && 
					find(RELATIONS.begin(), RELATIONS.end(), relType.substr(0,relType.size() - 1)) == RELATIONS.end()) {
					return false;
				}

				string info = arrWords.at(2);

				if (info.find(")") == string::npos) {
					return false;
				}
				info = info.substr(0, info.size() - 1);
				vector<string> arrInfo = splitTheStringIntoParts(info, ',', 2);
				bool isValidSuchThat = checkChildren(relType, arrInfo);
				return isValidSuchThat;
			}
			else {
				return false;
			}
		}

		else {
			return false;
		}
	}

	return true;// last edits
}
bool QueryParser::isValidVarName(string varName) {
	if (varName.length() == 0) {
		return false;
	}

	if (find(KEYS.begin(), KEYS.end(), varName) != KEYS.end()) {
		return false;
	}

	return regex_match(varName, variableNameRegex);
}

vector<string> QueryParser::splitTheString(string input, char c) {
	vector<string> result;

	const char *strC = input.c_str();

	do {
		const char *begin = strC;

		while (*strC != c && *strC) {
			strC++;
		}

		result.push_back(trim(string(begin, strC)));

	} while (0 != *strC++);

	return result;
}

vector<string> QueryParser::splitTheStringIntoParts(string input, char c, int number) {
	vector<string> result;
	const char *strC = input.c_str();
	int i = 1;

	do {
		const char *begin = strC;

		while (*strC != c && *strC) {
			strC++;
		}

		result.push_back(trim(string(begin, strC)));
	} while (0 != *strC++ && ++i < number);

	if (i == number) {
		const char *begin = strC;

		while (0 != *strC++  && *strC) {
			strC++;
		}

		result.push_back(trim(string(begin, strC)));
	}

	return result;
}

string QueryParser::trim(string input) {
	input.erase(0, input.find_first_not_of(SYMBOL_SPACE));
	input.erase(input.find_last_not_of(SYMBOL_SPACE) + 1);
	input.erase(remove(input.begin(), input.end(), '\n'), input.end());
	input.erase(remove(input.begin(), input.end(), '\t'), input.end());
	return regex_replace(input, regex("[' ']{2,}"), " ");
}

string QueryParser::removeSpaces(string line) {
	line.erase(0, line.find_first_not_of(SYMBOL_SPACE));
	line.erase(line.find_last_not_of(SYMBOL_SPACE) + 1);
	return line;
}


string QueryParser::stringToLower(string str) {
	transform(str.begin(), str.end(), str.begin(), tolower);
	return str;
}

bool QueryParser::isVarNameExists(string varName) {
	auto iter = varMap.find(varName);

	if (iter == varMap.end()) {
		return false;
	}

	return true;
}

string QueryParser::getVarType(string varName) {
	return varMap.find(varName)->second;
}
//like "a"
bool QueryParser::isStringVar(string str) {
	if (!(str.front() == SYMBOL_QUOTE && str.back() == SYMBOL_QUOTE)) {
		return false;
	}

	string varName = str.substr(1, str.size() - 2);

	return isValidVarName(varName);
}
bool QueryParser::isBothUnderScore(string str) {
	if ((str.front() == SYMBOL_UNDERSCORE && str.back() == SYMBOL_UNDERSCORE)) {
		return true;
	}
	return false;
}
bool QueryParser::isStringExpression(string str) {
	if (!(str.front() == SYMBOL_QUOTE && str.back() == SYMBOL_QUOTE)) {
		return false;
	}
	return true;
}
bool QueryParser::isInteger(string str) {
	if (str.empty() || ((!isdigit(str.at(0))) && (str.at(0) != '-') &&
		(str.at(0) != '+'))) {
		return false;
	}

	char *p;
	strtol(str.c_str(), &p, 10);

	return (*p == 0);
}

bool QueryParser::isPositiveInteger(string str) {
	if (str.empty() || !isdigit(str.at(0)) || str.at(0) == '0') {
		return false;
	}

	char *p;
	strtol(str.c_str(), &p, 10);

	return (*p == 0);
}

Type QueryParser::getTypeOfChild(string input) {
	Type result;
	if (input.compare("assign") == 0) {
		result = ASSIGN;
	}
	else if (input.compare("stmt") == 0) {
		result = STMT;
	}
	else if (input.compare("constant") == 0) {
		result = CONSTANT;
	}
	else if (input.compare("variable") == 0) {
		result = VARIABLE;
	}
	else if (input.compare("while") == 0) {
		result = WHILES;
	}
	else if (input.compare("prog_line") == 0) {
		result = PROG_LINE;
	}
	else if (input.compare("_") == 0) {
		result = ANYTHING;
	}
	else if (isInteger(input)) {
		result = INTEGER;
	}
	else if (isStringVar(input)) {
		result = STRINGVARIABLE;
	}
	return result;
}
