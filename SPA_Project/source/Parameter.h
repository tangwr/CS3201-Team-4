#ifndef ParameterH
#define ParameterH

#include <string>
#include "Type.h"

using namespace std;

class Parameter {
private:
	string paraName;
	Type paraType;
	bool isSyn;
	bool isInt;
	bool isStr;
	bool hasAttributeValue;
public:
	Parameter();
	Parameter(string, Type);
	string getParaName();
	Type getParaType();
	void setParaName(string);
	void setAttributeValue(bool);
	void setParaType(Type);
	bool isSynonym();
	bool isSame(Parameter);
	bool isInteger();
	bool isString();
	bool getAttributeValue();
};
#endif
