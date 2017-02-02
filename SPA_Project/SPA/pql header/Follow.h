#ifndef FollowH
#define FollowH

#include <string>
#include "Clause.h"
#include "ClauseType.h"

using namespace std;


class Follow : public Clause {
private:

	ClauseType type;
	string leftChild;
	string rightChild;
	Type leftChildType;
	Type rightChildType;
public:
	void setLeftChild(string);
	void setRightChild(string);
	void setLeftChildType(Type);
	void setRightChildType(Type);
	string getLeftChild();
	string getRightChild();
	Type getLeftChildType();
	Type getRightChildType();
};
#endif