#include "stdafx.h"
#include "CppUnitTest.h"

#include "PKBStubNextStar.h"
#include "ResultTable.h"
#include "Parameter.h"
#include "NextStar.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(NextStarObjectTest)
	{
	public:

		TEST_METHOD(UnitTest_NextStar_Num_Num)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("1", INTEGER);
			stmt2 = Parameter("8", INTEGER);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());

			Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Num_Num2)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("18", INTEGER);
			stmt2 = Parameter("20", INTEGER);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Stmt_Num)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("14", INTEGER);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 13 },{ 14 }, {15}, {16}, {17} };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Assign_Num)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("a1", ASSIGN);
			stmt2 = Parameter("14", INTEGER);

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { {15}, { 17 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			//Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Assign_Num2)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("a1", ASSIGN);
			stmt2 = Parameter("5", INTEGER);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { {1}, {2}, {3}, { 5 }, {7}, {8}, {9}, {11} };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Call_Num)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", CALL);
			stmt2 = Parameter("11", INTEGER);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 10 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Call_Num2)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", CALL);
			stmt2 = Parameter("2", INTEGER);

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			//expectedResult = { { 10 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_ProgLine_Num)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", PROG_LINE);
			stmt2 = Parameter("2", INTEGER);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Underscore_Num)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", ANYTHING);
			stmt2 = Parameter("2", INTEGER);

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

		//	expectedResult = { { 1 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(0, queryResult.getSynCount());

			Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Num_Underscore)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("6", INTEGER);
			stmt2 = Parameter("c1", ANYTHING);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			//expectedResult = { { 7 },{ 8 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(0, queryResult.getSynCount());

			Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Num_While)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("2", INTEGER);
			stmt2 = Parameter("c1", WHILE);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 4 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Num_While2)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("8", INTEGER);
			stmt2 = Parameter("c1", WHILE);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 4 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}
		/*
		TEST_METHOD(UnitTest_NextStar_Stmt_Stmt)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("s1", STMT);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 4,4 }, {5,5}, {6,6}, {7,7}, {8,8}, {9,9}, {10,10}, {11,11}, {14,14}, {15,15},
			{16,16}, {17,17} };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}
		/*

		TEST_METHOD(UnitTest_NextStar_Stmt_Stmt2)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("s2", STMT);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1,2 },{ 2,3 },{ 3,4 },{ 4,5 },{ 4,12 },{ 5,6 },{ 6,7 },{ 6,8 },{ 7,9 },{ 8,9 },{ 9,10 },{ 10,11 }
				,{ 11, 4 },{ 13, 14 },{ 13,20 },{ 14,15 },{ 14,18 },{ 15,16 },{ 16,17 },{ 17, 14 },{ 18,19 },{ 19, 21 },{ 20, 21 },
				{ 22, 23 },{ 22, 24 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}
		/*

		TEST_METHOD(UnitTest_NextStar_Call_Stmt)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", CALL);
			stmt2 = Parameter("s2", STMT);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 10, 11 },{ 16,17 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}
		/*

		TEST_METHOD(UnitTest_NextStar_Restricted_Stmt_Num)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("14", INTEGER);

			intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));

			intResult.insertTuple({ 1 });
			intResult.insertTuple({ 13 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 13 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			//Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}
		/*

		TEST_METHOD(UnitTest_NextStar_Restricted_Stmt_Num2)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("2", INTEGER);

			intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
			intResult.insertTuple({ 2 });
			intResult.insertTuple({ 12 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			//expectedResult = { { 1 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}
		/*

		TEST_METHOD(UnitTest_NextStar_Restricted_Num_Stmt)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("4", INTEGER);
			stmt2 = Parameter("s1", STMT);

			intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
			intResult.insertTuple({ 4 });
			intResult.insertTuple({ 5 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 5 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}
		/*

		TEST_METHOD(UnitTest_NextStar_Restricted_Num_Stmt2)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("2", INTEGER);
			stmt2 = Parameter("s1", STMT);

			intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
			intResult.insertTuple({ 4 });
			intResult.insertTuple({ 12 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			//expectedResult = { { 3 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}
		/*

		TEST_METHOD(UnitTest_NextStar_Restricted_Stmt_Stmt)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("s2", STMT);

			intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
			intResult.insertTuple({ 3 });
			intResult.insertTuple({ 13 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 3,4 },{ 13, 14 },{ 13, 20 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}
		/*

		TEST_METHOD(UnitTest_NextStar_Restricted_While_Stmt)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", WHILE);
			stmt2 = Parameter("s2", STMT);

			intResult.setSynList(vector<Parameter>(1, Parameter("s1", WHILE)));
			intResult.insertTuple({ 14 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 14, 15 } ,{ 14,18 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}
		/*

		TEST_METHOD(UnitTest_NextStar_Restricted_Stmt_Stmt2)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("s2", STMT);

			intResult.setSynList(vector<Parameter>(1, Parameter("s2", STMT)));
			intResult.insertTuple({ 15 });
			intResult.insertTuple({ 14 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 13,14 },{ 17,14 },{ 14,15 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}
		/*

		TEST_METHOD(UnitTest_NextStar_Restricted_While_Stmt2)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", WHILE);
			stmt2 = Parameter("s2", STMT);

			intResult.setSynList(vector<Parameter>(1, Parameter("s2", STMT)));
			intResult.insertTuple({ 15 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 14, 15 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}
		/*

		TEST_METHOD(UnitTest_NextStar_Restricted_Stmt_Stmt_Tuple)
		{
			PKBStubNextStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("s2", STMT);

			vector<Parameter> pList;
			pList.push_back(Parameter("s1", STMT));
			pList.push_back(Parameter("s2", STMT));
			intResult.setSynList(pList);

			intResult.insertTuple({ 1,2 });
			intResult.insertTuple({ 2, 3 });
			intResult.insertTuple({ 4, 6 });
			intResult.insertTuple({ 4, 8 });
			intResult.insertTuple({ 13, 14 });
			intResult.insertTuple({ 13,15 });
			intResult.insertTuple({ 13,20 });
			intResult.insertTuple({ 13,21 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1,2 },{ 2,3 },{ 13,14 },{ 13,20 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}
		*/
	};
}
