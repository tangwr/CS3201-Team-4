#include "Type.h"
#include "Parameter.h"

using namespace std;

Parameter::Parameter(string name, Type type) {
	paraName = name;
	paraType = type;
}

string Parameter::getParaName() {
	return paraName;
}

Type Parameter::getParaType() {
	return paraType;
}