#ifndef ParameterH
#define ParameterH

#include <string>
#include "Type.h"

using namespace std;

class Parameter {
private:
	string paraName;
	Type paraType;

public:
	Parameter();
	Parameter(string, Type);
	string getParaName();
	Type getParaType();

};
#endif
