#include "ClauseType.h"
#include "Type.h"
#include "Follow.h"
#include "Clause.h"


void Follow::setLeftChild(string left){
	leftChild = left;
}

void Follow::setRightChild(string right) {
	rightChild = right;
}

void Follow::setLeftChildType(Type leftType) {
	leftChildType = leftType;
}

void Follow::setRightChildType(Type rightType) {
	rightChildType = rightType;
}
string Follow::getLeftChild() {
	return leftChild;
}
string Follow::getRightChild() {
	return rightChild;
}
Type Follow::getLeftChildType() {
	return leftChildType;
}
Type Follow::getRightChildType() {
	return rightChildType;
}
