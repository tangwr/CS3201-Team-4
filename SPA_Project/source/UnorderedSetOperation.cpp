#include "UnorderedSetOperation.h"

template <class T>
unordered_set<T> UnorderedSetOperation<T>::setIntersection(unordered_set<T> s1, unordered_set<T> s2) {
	unordered_set<T> elementMap;
	unordered_set<T>* useList;
	unordered_set<T>* matchList;
	
	if (s1.size() < s2.size()) {
		useList = &s1;
		matchList = &s2;
	} else {
		useList = &s2;
		matchList = &s1;
	}

	for (auto element : *useList) {
		if (matchList->find(element) != matchList->end()) {
			elementMap.insert(element);
		}
	}
	return elementMap;
}

template <class T>
unordered_set<T> UnorderedSetOperation<T>::setUnion(unordered_set<T> s1, unordered_set<T> s2) {
	unordered_set<T> elementMap;
	elementMap.insert(s1.begin(), s1.end());
	elementMap.insert(s2.begin(), s2.end());
	return elementMap;
}