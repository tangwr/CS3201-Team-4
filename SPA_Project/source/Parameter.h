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

public:
	Parameter();
	Parameter(string, Type);
	string getParaName();
	Type getParaType();
	void setParaName(string);
	void setParaType(Type);
	bool isSynonym();
	bool isSame(Parameter);
};
#endif
