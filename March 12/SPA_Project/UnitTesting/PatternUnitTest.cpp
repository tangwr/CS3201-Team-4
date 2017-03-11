#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKBStub.h"
#include "Pattern.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	/*
	TEST_CLASS(PatternObjectTest)
	{
	public:
		
		TEST_METHOD(UnitTest_AssignPattern_With_Variable_Synonym)
		{
			PKBStub *pkbStub = new PKBStub();
			Pattern *patternObj;
			vector<int> expectedAns, results;

			patternObj = new Pattern("a", ASSIGN, "v", VARIABLE, "z + x", STRINGVARIABLE, true);
			results = patternObj->getWithRelToLeft(pkbStub);
			sort(results.begin(), results.end());
			expectedAns = { 8, 9, 21, 24 };

			Assert::AreEqual(expectedAns.size(), results.size());
			Assert::IsTrue(expectedAns == results);

			results = patternObj->getWithRelToRight(pkbStub);
			sort(results.begin(), results.end());
			expectedAns = { 0, 1, 3 };

			Assert::AreEqual(expectedAns.size(), results.size());
			Assert::IsTrue(expectedAns == results);
			delete patternObj;


			patternObj = new Pattern("a", ASSIGN, "v", VARIABLE, "z + x", STRINGVARIABLE, false);
			results = patternObj->getWithRelToLeft(pkbStub);
			sort(results.begin(), results.end());
			expectedAns = { 8, 24 };

			Assert::AreEqual(expectedAns.size(), results.size());
			Assert::IsTrue(expectedAns == results);

			results = patternObj->getWithRelToRight(pkbStub);
			sort(results.begin(), results.end());
			expectedAns = { 0, 3 };

			Assert::AreEqual(expectedAns.size(), results.size());
			Assert::IsTrue(expectedAns == results);
			delete patternObj;

			patternObj = new Pattern("a", ASSIGN, "v", VARIABLE, "_", ANYTHING, false);
			results = patternObj->getWithRelToLeft(pkbStub);
			sort(results.begin(), results.end());
			expectedAns = { 1, 2, 3, 5, 7, 8, 9, 11, 15, 17, 18, 19, 20, 21, 23, 24 };

			Assert::AreEqual(expectedAns.size(), results.size());
			Assert::IsTrue(expectedAns == results);

			results = patternObj->getWithRelToRight(pkbStub);
			sort(results.begin(), results.end());
			expectedAns = { 0, 1, 2, 3 };

			Assert::AreEqual(expectedAns.size(), results.size());
			Assert::IsTrue(expectedAns == results);
			delete patternObj;

			delete pkbStub;
		}

		TEST_METHOD(UnitTest_AssignPattern_With_Variable_Name)
		{
			PKBStub *pkbStub = new PKBStub();
			Pattern *patternObj;
			vector<int> expectedAns, results;

			patternObj = new Pattern("a", ASSIGN, "i", STRINGVARIABLE, "i", STRINGVARIABLE, true);
			results = patternObj->getWithRelToLeft(pkbStub);
			sort(results.begin(), results.end());
			expectedAns = { 11, 17 };

			Assert::AreEqual(expectedAns.size(), results.size());
			Assert::IsTrue(expectedAns == results);
			delete patternObj;


			patternObj = new Pattern("a", ASSIGN, "i", STRINGVARIABLE, "i", STRINGVARIABLE, false);
			results = patternObj->getWithRelToLeft(pkbStub);
			sort(results.begin(), results.end());
			expectedAns = {};

			Assert::AreEqual(expectedAns.size(), results.size());
			Assert::IsTrue(expectedAns == results);
			delete patternObj;

			patternObj = new Pattern("a", ASSIGN, "i", STRINGVARIABLE, "_", ANYTHING, false);
			results = patternObj->getWithRelToLeft(pkbStub);
			sort(results.begin(), results.end());
			expectedAns = { 11, 17 };

			Assert::AreEqual(expectedAns.size(), results.size());
			Assert::IsTrue(expectedAns == results);
			delete patternObj;

			delete pkbStub;
		}
	};
	*/
}
