#pragma once

#include <vector>

using namespace std;

const int INITIAL_INDEX = 0;

template <class T>
class VectorSetOperation {
public:
	static vector<T> setIntersection(vector<T> v1, vector<T> v2);
	static vector<T> setUnion(vector<T> v1, vector<T> v2);
};

template class VectorSetOperation<int>;