#pragma once

#include <vector>

using namespace std;

template <class T>
class VectorSetOperation {
public:
	static vector<T> setIntersection(vector<T> v1, vector<T> v2);
	static vector<T> setUnion(vector<T> v1, vector<T> v2);
	static vector<T> setDifference(vector<T> v1, vector<T> v2);
};

template class VectorSetOperation<int>;