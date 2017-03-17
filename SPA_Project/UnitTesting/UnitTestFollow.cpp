#include "stdafx.h"
#include "CppUnitTest.h"

#include "PKBStubFollow.h"
#include "ResultTable.h"
#include "Parameter.h"
#include "Follow.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(FollowObjectTest)
	{
	public:
		
		TEST_METHOD(UnitTest_Follow_Num_Num)
		{
			PKBStubFollow pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("1", INTEGER);
			stmt2 = Parameter("2", INTEGER);


			Follow followClause(stmt1, stmt2);
			queryResult = followClause.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());

			Assert::IsTrue(queryResult.getBoolean());
		}
		
		TEST_METHOD(UnitTest_Follow_Stmt_Num)
		{
			PKBStubFollow pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("2", INTEGER);


			Follow followClause(stmt1, stmt2);
			queryResult = followClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end()); 

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Follow_Assign_Num)
		{
			PKBStubFollow pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("a1", ASSIGN);
			stmt2 = Parameter("14", INTEGER);


			Follow followClause(stmt1, stmt2);
			queryResult = followClause.evaluate(&pkbStub, intResult);

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Follow_Assign_Num2)
		{
			PKBStubFollow pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("a1", ASSIGN);
			stmt2 = Parameter("2", INTEGER);


			Follow followClause(stmt1, stmt2);
			queryResult = followClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Follow_Call_Num)
		{
			PKBStubFollow pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", CALL);
			stmt2 = Parameter("11", INTEGER);


			Follow followClause(stmt1, stmt2);
			queryResult = followClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 10 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Follow_Call_Num2)
		{
			PKBStubFollow pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", CALL);
			stmt2 = Parameter("2", INTEGER);


			Follow followClause(stmt1, stmt2);
			queryResult = followClause.evaluate(&pkbStub, intResult);

			//expectedResult = { { 10 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Follow_ProgLine_Num)
		{
			PKBStubFollow pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", PROG_LINE);
			stmt2 = Parameter("2", INTEGER);


			Follow followClause(stmt1, stmt2);
			queryResult = followClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Follow_Underscore_Num)
		{
			PKBStubFollow pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", ANYTHING);
			stmt2 = Parameter("2", INTEGER);


			Follow followClause(stmt1, stmt2);
			queryResult = followClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Follow_Num_Underscore)
		{
			PKBStubFollow pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("2", INTEGER);
			stmt2 = Parameter("c1", ANYTHING);


			Follow followClause(stmt1, stmt2);
			queryResult = followClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 3 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Follow_Num_While)
		{
			PKBStubFollow pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("2", INTEGER);
			stmt2 = Parameter("c1", WHILE);


			Follow followClause(stmt1, stmt2);
			queryResult = followClause.evaluate(&pkbStub, intResult);

			//expectedResult = { { 3 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Follow_Num_While2)
		{
			PKBStubFollow pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("3", INTEGER);
			stmt2 = Parameter("c1", WHILE);


			Follow followClause(stmt1, stmt2);
			queryResult = followClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 4 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Follow_Stmt_Stmt)
		{
			PKBStubFollow pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("s1", STMT);


			Follow followClause(stmt1, stmt2);
			queryResult = followClause.evaluate(&pkbStub, intResult);

			//expectedResult = { { 4 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Follow_Stmt_Stmt2)
		{
			PKBStubFollow pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("s2", STMT);


			Follow followClause(stmt1, stmt2);
			queryResult = followClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1,2 },{ 2,3 },{ 3,4 },{ 4,12 },{ 5,6 },{ 6,9 },{ 9,10 },{ 10,11 }
			,{ 13,21 },{ 14,18 },{ 15,16 },{ 16,17 },{ 18,19 } };
			
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Follow_Call_Stmt)
		{
			PKBStubFollow pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", CALL);
			stmt2 = Parameter("s2", STMT);


			Follow followClause(stmt1, stmt2);
			queryResult = followClause.evaluate(&pkbStub, intResult);

			expectedResult = { {10, 11}, {16,17} };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Follow_Restricted_Stmt_Num)
		{
			PKBStubFollow pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("2", INTEGER);

			intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));

			intResult.insertTuple({ 1 });
			intResult.insertTuple({ 12 });

			Follow followClause(stmt1, stmt2);
			queryResult = followClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			//Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Follow_Restricted_Stmt_Num2)
		{
			PKBStubFollow pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("2", INTEGER);

			intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
			intResult.insertTuple({ 2 });
			intResult.insertTuple({ 12 });

			Follow followClause(stmt1, stmt2);
			queryResult = followClause.evaluate(&pkbStub, intResult);

			//expectedResult = { { 1 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Follow_Restricted_Num_Stmt)
		{
			PKBStubFollow pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("2", INTEGER);
			stmt2 = Parameter("s1", STMT);

			intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
			intResult.insertTuple({ 2 });
			intResult.insertTuple({ 12 });

			Follow followClause(stmt1, stmt2);
			queryResult = followClause.evaluate(&pkbStub, intResult);

			//expectedResult = { { 1 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Follow_Restricted_Num_Stmt2)
		{
			PKBStubFollow pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("2", INTEGER);
			stmt2 = Parameter("s1", STMT);

			intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
			intResult.insertTuple({ 3 });
			intResult.insertTuple({ 12 });

			Follow followClause(stmt1, stmt2);
			queryResult = followClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 3 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Follow_Restricted_Stmt_Stmt)
		{
			PKBStubFollow pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("s2", STMT);

			intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
			intResult.insertTuple({ 3 });
			intResult.insertTuple({ 13 });

			Follow followClause(stmt1, stmt2);
			queryResult = followClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 3,4 }, { 13, 21} };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Follow_Restricted_While_Stmt)
		{
			PKBStubFollow pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", WHILE);
			stmt2 = Parameter("s2", STMT);

			intResult.setSynList(vector<Parameter>(1, Parameter("s1", WHILE)));
			intResult.insertTuple({ 14 });

			Follow followClause(stmt1, stmt2);
			queryResult = followClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 14,18 } };

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
