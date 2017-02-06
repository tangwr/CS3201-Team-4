#include <algorithm>
#include <iterator> 
#include <unordered_set>

#include "VectorSetOperation.h"

template <class T>
vector<T> VectorSetOperation<T>::setIntersection(vector<T> v1, vector<T> v2) {
	unordered_set<T> elementMap;
	vector<T> results; 
	for (int i = INITIAL_INDEX; i < v1.size(); i++) {
		elementMap.insert(v1[i]);
	}
	for (int i = INITIAL_INDEX; i < v2.size(); i++) {
		if (elementMap.find(v2[i]) != elementMap.end()) {
			results.push_back(v2[i]);
		}
	}
	return results;
}

template <class T>
vector<T> VectorSetOperation<T>::setUnion(vector<T> v1, vector<T> v2) {
	unordered_set<T> elementMap;
	for (int i = INITIAL_INDEX; i < v1.size(); i++) {
		elementMap.insert(v1[i]);
	}
	for (int i = INITIAL_INDEX; i < v2.size(); i++) {
		elementMap.insert(v2[i]);
	}
	vector<T> results(elementMap.size());
	for (auto& it: elementMap) {
		results.push_back(it);
	}
	return results;
}