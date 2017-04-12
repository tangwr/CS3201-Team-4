#include "stdafx.h"
#include "CppUnitTest.h"
#include "TableOperations.h"

#include <unordered_map>
#include <vector>
#include <iostream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
	TEST_CLASS(TestTableOperation)
	{
	public:

		TEST_METHOD(UnitTest_TableOperation)
		{
			unordered_set<int> testSetOne = unordered_set<int>({});
			testSetOne.insert(1);
			testSetOne.insert(330);
			testSetOne.insert(2000);
			unordered_set<int> testSetTwo = unordered_set<int>({ 1, 2000, 330 });
			unordered_set<int> testSetThree = unordered_set<int>({ 2, 2000, 330 });
			Assert::AreEqual(TableOperations::isEqualUnorderedSet(testSetOne, testSetTwo), testSetOne == testSetTwo);
			Assert::IsFalse(TableOperations::isEqualUnorderedSet(testSetOne, testSetThree));
		}
	};
}