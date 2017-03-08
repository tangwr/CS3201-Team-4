#include "Type.h"
#include "Parameter.h"

using namespace std;

Parameter::Parameter() {
}

Parameter::Parameter(string name, Type type) {
	paraName = name;
	paraType = type;

	if (paraType != CONSTANT && paraType != BOOLEAN && paraType != ANYTHING
		&& paraType != STRINGVARIABLE && paraType != INTEGER) {
		isSyn = true;
	}
	else {
		isSyn = false;
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
}

bool Parameter::isSynonym() {
	return isSyn;
}

bool Parameter::isSame(Parameter paraObj) {
	if (paraName.compare(paraObj.getParaName()) != 0) {
		return false;
	}
	if (paraType != paraObj.getParaType) {
		return false;
	}
	return true;
}
