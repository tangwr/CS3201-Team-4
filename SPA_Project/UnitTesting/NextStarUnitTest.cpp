#include "stdafx.h"
#include "CppUnitTest.h"

#include "NextStarPKBStub.h"
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
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("1", INTEGER);
			stmt2 = Parameter("8", INTEGER);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			Assert::AreEqual(0, queryResult->getSynCount());

			Assert::IsTrue(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Num_Num2)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("18", INTEGER);
			stmt2 = Parameter("20", INTEGER);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			Assert::AreEqual(0, queryResult->getSynCount());

			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Stmt_Num)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("14", INTEGER);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 13 },{ 14 },{ 15 },{ 16 },{ 17 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult->getSynCount());

			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Assign_Num)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("a1", ASSIGN);
			stmt2 = Parameter("14", INTEGER);

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 15 },{ 17 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			//Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult->getSynCount());

			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Assign_Num2)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("a1", ASSIGN);
			stmt2 = Parameter("5", INTEGER);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 1 },{ 2 },{ 3 },{ 5 },{ 7 },{ 8 },{ 9 },{ 11 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult->getSynCount());

			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Call_Num)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", CALL);
			stmt2 = Parameter("11", INTEGER);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 10 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult->getSynCount());

			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Call_Num2)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", CALL);
			stmt2 = Parameter("2", INTEGER);

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			//expectedResult = { { 10 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult->getSynCount());

			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_ProgLine_Num)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", PROG_LINE);
			stmt2 = Parameter("2", INTEGER);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 1 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult->getSynCount());

			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Underscore_Num)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", ANYTHING);
			stmt2 = Parameter("2", INTEGER);

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			//	expectedResult = { { 1 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(0, queryResult->getSynCount());

			Assert::IsTrue(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Num_Underscore)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("6", INTEGER);
			stmt2 = Parameter("c1", ANYTHING);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			//expectedResult = { { 7 },{ 8 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(0, queryResult->getSynCount());

			Assert::IsTrue(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Num_While)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("2", INTEGER);
			stmt2 = Parameter("c1", WHILE);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 4 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult->getSynCount());

			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Num_While2)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("8", INTEGER);
			stmt2 = Parameter("c1", WHILE);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 4 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult->getSynCount());

			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Stmt_Stmt)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("s1", STMT);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 4 },{ 5 },{ 6 },{ 7 },{ 8 },{ 9 },{ 10 },{ 11 },{ 14 },{ 15 },
			{ 16 },{ 17 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult->getSynCount());

			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Call_Stmt)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", CALL);
			stmt2 = Parameter("s2", STMT);


			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 10, 4 },{ 10, 5 },{ 10, 6 },{ 10, 7 },{ 10, 8 },{ 10, 9 },{ 10, 10 },{ 10, 11 },{ 10, 12 },
			{ 16,14 },{ 16,15 },{ 16,16 },{ 16,17 },{ 16,18 },{ 16,19 }, };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult->getSynCount());

			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Restricted_Stmt_Num)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("14", INTEGER);

			intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));

			intResult.insertTuple({ 1 });
			intResult.insertTuple({ 13 });
			intResult.insertTuple({ 16 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 13 },{ 16 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			//Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult->getSynCount());
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Restricted_Stmt_Num2)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("2", INTEGER);

			intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
			intResult.insertTuple({ 2 });
			intResult.insertTuple({ 12 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			//expectedResult = { { 1 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult->getSynCount());
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Restricted_Num_Stmt)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("4", INTEGER);
			stmt2 = Parameter("s1", STMT);

			intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
			intResult.insertTuple({ 2 });
			intResult.insertTuple({ 4 });
			intResult.insertTuple({ 5 });
			intResult.insertTuple({ 13 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 4 },{ 5 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult->getSynCount());
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Restricted_Num_Stmt2)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("2", INTEGER);
			stmt2 = Parameter("s1", STMT);

			intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
			intResult.insertTuple({ 1 });
			intResult.insertTuple({ 2 });
			intResult.insertTuple({ 22 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			//expectedResult = { { 3 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult->getSynCount());
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Restricted_Stmt_Stmt)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("s2", STMT);

			intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
			intResult.insertTuple({ 12 });
			intResult.insertTuple({ 22 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 22,23 },{ 22, 24 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult->getSynCount());
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Restricted_While_Stmt)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", WHILE);
			stmt2 = Parameter("s2", STMT);

			intResult.setSynList(vector<Parameter>(1, Parameter("s1", WHILE)));
			intResult.insertTuple({ 14 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 14, 14 } ,{ 14, 15 } ,{ 14, 16 } ,{ 14, 17 } ,{ 14,18 },{ 14, 19 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult->getSynCount());
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Restricted_Stmt_Stmt2)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("s2", STMT);

			intResult.setSynList(vector<Parameter>(1, Parameter("s2", STMT)));
			intResult.insertTuple({ 15 });
			intResult.insertTuple({ 14 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 13,14 },{ 14,14 },{ 15,14 },{ 16,14 },{ 17,14 },{ 13,15 } ,{ 14,15 } ,{ 15,15 },{ 16,15 } ,{ 17,15 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult->getSynCount());
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Restricted_While_Stmt2)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", WHILE);
			stmt2 = Parameter("s2", STMT);

			intResult.setSynList(vector<Parameter>(1, Parameter("s2", STMT)));
			intResult.insertTuple({ 15 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 14, 15 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult->getSynCount());
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Restricted_Stmt_Stmt_Tuple)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("s2", STMT);

			vector<Parameter> pList;
			pList.push_back(Parameter("s1", STMT));
			pList.push_back(Parameter("s2", STMT));
			intResult.setSynList(pList);

			intResult.insertTuple({ 1,2 });
			intResult.insertTuple({ 1,22 });
			intResult.insertTuple({ 2, 3 });
			intResult.insertTuple({ 4, 6 });
			intResult.insertTuple({ 4, 8 });
			intResult.insertTuple({ 13, 14 });
			intResult.insertTuple({ 13,15 });
			intResult.insertTuple({ 13,20 });
			intResult.insertTuple({ 13,21 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 1,2 },{ 2,3 },{ 4,6 },{ 4,8 },{ 13, 14 },{ 13,15 },{ 13,20 },{ 13,21 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult->getSynCount());
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Restricted_Stmt_Stmt_Tuple2)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("s2", STMT);

			vector<Parameter> pList;
			pList.push_back(Parameter("s1", STMT));
			pList.push_back(Parameter("s2", STMT));
			intResult.setSynList(pList);

			intResult.insertTuple({ 1,9 });
			intResult.insertTuple({ 2,9 });
			intResult.insertTuple({ 5,9 });
			intResult.insertTuple({ 11,9 });
			intResult.insertTuple({ 10,9 });
			intResult.insertTuple({ 11,8 });
			intResult.insertTuple({ 12,8 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 1,9 },{ 2,9 },{ 5,9 }, {11,9}, {10,9}, {11,8} };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult->getSynCount());
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Restricted_Stmt_Stmt_Tuple3)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("s2", STMT);

			vector<Parameter> pList;
			pList.push_back(Parameter("s2", STMT));
			pList.push_back(Parameter("s1", STMT));
			intResult.setSynList(pList);

			intResult.insertTuple({ 1,22 });
			intResult.insertTuple({ 22, 1 });
			intResult.insertTuple({ 2, 3 });
			intResult.insertTuple({ 3, 2 });
			intResult.insertTuple({ 12, 4 });
			intResult.insertTuple({ 8, 4 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 2,3 },{ 4,8 },{ 4, 12 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult->getSynCount());
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_NextStar_Restricted_Stmt_Stmt_Tuple4)
		{
			NextStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("s2", STMT);

			vector<Parameter> pList;
			pList.push_back(Parameter("s2", STMT));
			pList.push_back(Parameter("s1", STMT));
			intResult.setSynList(pList);

			intResult.insertTuple({ 1,22 });
			intResult.insertTuple({ 22, 1 });
			intResult.insertTuple({ 2, 3 });
			intResult.insertTuple({ 3, 2 });
			intResult.insertTuple({ 12, 4 });
			intResult.insertTuple({ 12, 5 });

			NextStar nextStarClause(stmt1, stmt2);
			queryResult = nextStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { {2,3}, {4,12}, {5,12} };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult->getSynCount());
			Assert::IsFalse(queryResult->getBoolean());
		}

	};
}
