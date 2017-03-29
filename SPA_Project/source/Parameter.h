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
	bool isAttributeProc;
public:
	Parameter();
	Parameter(string, Type);
	string getParaName();
	Type getParaType();
	void setParaName(string);
	void setAttributeProc(bool);
	void setParaType(Type);
	bool isSynonym();
	bool isSame(Parameter);
	bool isInteger();
	bool isString();
	bool getAttributeProc();
};
#endif
