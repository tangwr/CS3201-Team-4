#ifndef ClauseH
#define ClauseH

#include "ClauseType.h"
#include "Type.h"
#include <string>

using namespace std;

class Clause {
	
public:
    virtual void setLeftChild(string) = 0;

};

#endif