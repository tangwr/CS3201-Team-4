#include <algorithm>
#include <iterator> 

#include "VectorSetOperation.h"

template <class T>
vector<T> VectorSetOperation<T>::setIntersection(vector<T> v1, vector<T> v2) {
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	vector<T> results;
	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(results));
	return results;
}

template <class T>
vector<T> VectorSetOperation<T>::setUnion(vector<T> v1, vector<T> v2) {
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	vector<T> results;
	set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(results));
	return results;
}

template <class T>
vector<T> VectorSetOperation<T>::setDifference(vector<T> v1, vector<T> v2) {
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	vector<T> results;
	set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(results));
	return results;
}