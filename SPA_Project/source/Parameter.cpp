#include "Type.h"
#include "Parameter.h"

using namespace std;

Parameter::Parameter() {
	isAttributeProc = false;
}

Parameter::Parameter(string name, Type type) {
	paraName = name;
	paraType = type;
	isAttributeProc = false;

	if (paraType != BOOLEAN && paraType != ANYTHING
		&& paraType != STRINGVARIABLE && paraType != INTEGER) {
		isSyn = true;
	}
	else {
		isSyn = false;
	}

	if (paraType == INTEGER) {
		isInt = true;
	}
	else {
		isInt = false;
	}
	if (paraType == STRINGVARIABLE) {
		isStr = true;
	}
	else {
		isStr = false;
	}
}

string Parameter::getParaName() {
	return paraName;
}

Type Parameter::getParaType() {
	return paraType;
}

void Parameter::setParaName(string name) {
	paraName = name;
}

void Parameter::setParaType(Type type) {
	paraType = type;


	if (paraType != BOOLEAN && paraType != ANYTHING
		&& paraType != STRINGVARIABLE && paraType != INTEGER) {
		isSyn = true;
	}
	else {
		isSyn = false;
	}

	if (paraType == INTEGER) {
		isInt = true;
	}
	else {
		isInt = false;
	}
	if (paraType == STRINGVARIABLE) {
		isStr = true;
	}
	else {
		isStr = false;
	}

}

bool Parameter::isSynonym() {
	return isSyn;
}

bool Parameter::isInteger() {
	return isInt;
}

bool Parameter::isString() {
	return isStr;
}

bool Parameter::isSame(Parameter paraObj) {
	if (paraName.compare(paraObj.getParaName()) != 0) {
		return false;
	}
	if (paraType != paraObj.getParaType()) {
		return false;
	}
	return true;
}

void Parameter::setAttributeProc(bool value) {
	isAttributeProc = value;
}

bool Parameter::getAttributeProc() {
	return isAttributeProc;
}
