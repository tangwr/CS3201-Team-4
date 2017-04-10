#include "stdafx.h"
#include "CppUnitTest.h"

#include "PKBStubNextBipStar.h"
#include "ResultTable.h"
#include "Parameter.h"
#include "NextBipStar.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(NextBipStarObjectTest)
	{
	public:
		

		TEST_METHOD(UnitTest_NextBipStar_Num_Num)
		{
			PKBStubNextBipStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("15", INTEGER);
			stmt2 = Parameter("11", INTEGER);

			NextBipStar nextStarClause(stmt1, stmt2);
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


		TEST_METHOD(UnitTest_NextBipStar_Num_Num2)
		{
			PKBStubNextBipStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("14", INTEGER);
			stmt2 = Parameter("17", INTEGER);

			NextBipStar nextStarClause(stmt1, stmt2);
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

		TEST_METHOD(UnitTest_NextBipStar_Num_Stmt)
		{
			PKBStubNextBipStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("15", INTEGER);
			stmt2 = Parameter("c1", STMT);

			NextBipStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 12 },{ 13 },{ 14 },{ 16 },{ 17 },{ 18 },{ 19 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextBipStar_Num_Stmt2)
		{
			PKBStubNextBipStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("13", INTEGER);
			stmt2 = Parameter("c1", STMT);

			NextBipStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 4 },{ 5 },{ 6 },{ 7 },{ 8 },{ 9 },{ 10 },{ 11 },{ 12 },{ 13 },{ 14 },{ 17 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextBipStar_Stmt_Num)
		{
			PKBStubNextBipStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", STMT);
			stmt2 = Parameter("13", INTEGER);

			NextBipStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1 },{ 2 },{ 3 },{ 4 },{ 5 },{ 6 },{ 7 },{ 8 },{ 9 },{ 10 },
			{ 11 },{ 12 },{ 13 },{ 14 } ,{ 15 },{ 16 },{ 18 },{ 19 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextBipStar_Num_Stmt41)
		{
			PKBStubNextBipStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("18", INTEGER);
			stmt2 = Parameter("c1", STMT);

			NextBipStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 12 },{ 13 },{ 14 },{ 16 },{ 17 },{ 19 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}
		/*
		TEST_METHOD(UnitTest_NextBipStar_Stmt_Stmt)
		{
			PKBStubNextBipStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", STMT);
			stmt2 = Parameter("c2", STMT);

			NextBipStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1 },{ 2 },{ 3 },{ 4 },{ 5 },{ 6 },{ 7 },{ 8 },{ 9 },{ 10 },
			{ 11 },{ 12 },{ 13 },{ 14 } ,{ 15 },{ 16 },{ 18 },{ 19 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}
		
		TEST_METHOD(UnitTest_NextBipStar_Call_Stmt)
		{
			PKBStubNextBipStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", CALL);
			stmt2 = Parameter("c2", STMT);

			NextBipStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1 },{ 2 },{ 3 },{ 4 },{ 5 },{ 6 },{ 7 },{ 8 },{ 9 },{ 10 },
			{ 11 },{ 12 },{ 13 },{ 14 } ,{ 15 },{ 16 },{ 18 },{ 19 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextBipStar_If_Stmt)
		{
			PKBStubNextBipStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", IF);
			stmt2 = Parameter("c2", STMT);

			NextBipStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1 },{ 2 },{ 3 },{ 4 },{ 5 },{ 6 },{ 7 },{ 8 },{ 9 },{ 10 },
			{ 11 },{ 12 },{ 13 },{ 14 } ,{ 15 },{ 16 },{ 18 },{ 19 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextBipStar_While_Stmt)
		{
			PKBStubNextBipStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", WHILE);
			stmt2 = Parameter("c2", STMT);

			NextBipStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1 },{ 2 },{ 3 },{ 4 },{ 5 },{ 6 },{ 7 },{ 8 },{ 9 },{ 10 },
			{ 11 },{ 12 },{ 13 },{ 14 } ,{ 15 },{ 16 },{ 18 },{ 19 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextBipStar_Assign_Stmt)
		{
			PKBStubNextBipStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", ASSIGN);
			stmt2 = Parameter("c2", STMT);

			NextBipStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1 },{ 2 },{ 3 },{ 4 },{ 5 },{ 6 },{ 7 },{ 8 },{ 9 },{ 10 },
			{ 11 },{ 12 },{ 13 },{ 14 } ,{ 15 },{ 16 },{ 18 },{ 19 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}*/
	};
}
