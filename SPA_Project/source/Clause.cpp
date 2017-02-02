#include "ClauseType.h"
#include "Type.h"
#include "Clause.h"

Clause::Clause() {

}

void Clause::setLeftChild(string left) {
	leftChild = left;
}

void Clause::setRightChild(string right) {
	rightChild = right;
}

void Clause::setLeftChildType(Type leftType) {
	leftChildType = leftType;
}

void Clause::setRightChildType(Type rightType) {
	rightChildType = rightType;
}
string Clause::getLeftChild() {
	return leftChild;
}
string Clause::getRightChild() {
	return rightChild;
}
Type Clause::getLeftChildType() {
	return leftChildType;
}
Type Clause::getRightChildType() {
	return rightChildType;
}
