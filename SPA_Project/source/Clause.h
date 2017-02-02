#ifndef ClauseH
#define ClauseH

#include <string>
#include "ClauseType.h"
#include "Type.h"

using namespace std;


class Clause {
protected:
    ClauseType cltype;
	string leftChild;
	string rightChild;
	Type leftChildType;
	Type rightChildType;
public:
	Clause();
	virtual void setLeftChild(string);
	virtual void setRightChild(string);
	virtual void setLeftChildType(Type);
	virtual void setRightChildType(Type);
	virtual string getLeftChild();
	virtual string getRightChild();
	virtual Type getLeftChildType();
	virtual Type getRightChildType();
};
#endif