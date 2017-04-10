#include "stdafx.h"
#include "CppUnitTest.h"

#include "PKBStubNextBip.h"
#include "ResultTable.h"
#include "Parameter.h"
#include "NextBip.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(NextBipObjectTest)
	{
	public:


		TEST_METHOD(UnitTest_NextBip_Num_Num)
		{
			PKBStubNextBip pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("15", INTEGER);
			stmt2 = Parameter("11", INTEGER);

			NextBip nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			//expectedResult = { { 12 },{ 13 },{ 14 },{ 16 },{ 17 },{ 18 },{ 19 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(0, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}


		TEST_METHOD(UnitTest_NextBip_Num_Num2)
		{
			PKBStubNextBip pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("14", INTEGER);
			stmt2 = Parameter("17", INTEGER);

			NextBip nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			//expectedResult = { { 12 },{ 13 },{ 14 },{ 16 },{ 17 },{ 18 },{ 19 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(0, queryResult.getSynCount());

			Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextBip_Num_Stmt)
		{
			PKBStubNextBip pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("14", INTEGER);
			stmt2 = Parameter("c1", STMT);

			NextBip nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { {11}, {17} };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextBip_Num_Stmt2)
		{
			PKBStubNextBip pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("19", INTEGER);
			stmt2 = Parameter("c1", STMT);

			NextBip nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 16 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextBip_Stmt_Num)
		{
			PKBStubNextBip pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", STMT);
			stmt2 = Parameter("12", INTEGER);

			NextBip nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 10 }, {16} };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextBip_Stmt_Stmt)
		{
			PKBStubNextBip pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", STMT);
			stmt2 = Parameter("c2", STMT);

			NextBip nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = {{1,2}, {2,3},{3,4}, {4,5},{5,6},{6,7}, {6,8}, {7,9}, {8,9}, {9,10}, {10,12},{11,4}, {12,13}, {12,14},
			{13,11}, {14,11}, {15,18}, {18,19}, {19,16}, {16,12}, {13,17}, {14,17} };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}
	};
}
