#pragma once

#include <unordered_set>

using namespace std;

template <class T>
class UnorderedSetOperation {
public:
	static unordered_set<T> setIntersection(unordered_set<T> v1, unordered_set<T> v2);
	static unordered_set<T> setUnion(unordered_set<T> v1, unordered_set<T> v2);
};

template class UnorderedSetOperation<int>;
