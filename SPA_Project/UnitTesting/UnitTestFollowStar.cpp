#include "stdafx.h"
#include "CppUnitTest.h"

#include "PKBStubFollowStar.h"
#include "ResultTable.h"
#include "Parameter.h"
#include "FollowStar.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(FollowStarStarObjectTest)
	{
	public:

		TEST_METHOD(UnitTest_FollowStarStar_Num_Num)
		{
			PKBStubFollowStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("1", INTEGER);
			stmt2 = Parameter("3", INTEGER);


			FollowStar followStarClause(stmt1, stmt2);
			queryResult = followStarClause.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());

			Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_FollowStar_Stmt_Num)
		{
			PKBStubFollowStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("11", INTEGER);


			FollowStar followStarClause(stmt1, stmt2);
			queryResult = followStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 5 },{ 6 },{ 9 },{ 10 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_FollowStar_Assign_Num)
		{
			PKBStubFollowStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("a1", ASSIGN);
			stmt2 = Parameter("14", INTEGER);


			FollowStar followStarClause(stmt1, stmt2);
			queryResult = followStarClause.evaluate(&pkbStub, intResult);

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_FollowStar_Assign_Num2)
		{
			PKBStubFollowStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("a1", ASSIGN);
			stmt2 = Parameter("11", INTEGER);


			FollowStar followStarClause(stmt1, stmt2);
			queryResult = followStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 5 },{ 9 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}
		
		TEST_METHOD(UnitTest_FollowStar_Call_Num)
		{
		PKBStubFollowStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("c1", CALL);
		stmt2 = Parameter("11", INTEGER);


		FollowStar followStarClause(stmt1, stmt2);
		queryResult = followStarClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 10 } };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}
		
		TEST_METHOD(UnitTest_FollowStar_Call_Num2)
		{
		PKBStubFollowStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("c1", CALL);
		stmt2 = Parameter("4", INTEGER);


		FollowStar followStarClause(stmt1, stmt2);
		queryResult = followStarClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 10 } };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}
		
		TEST_METHOD(UnitTest_FollowStar_ProgLine_Num)
		{
		PKBStubFollowStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("c1", PROG_LINE);
		stmt2 = Parameter("3", INTEGER);


		FollowStar followStarClause(stmt1, stmt2);
		queryResult = followStarClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 1 },{ 2 } };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}
		
		TEST_METHOD(UnitTest_FollowStar_Underscore_Num)
		{
		PKBStubFollowStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("c1", ANYTHING);
		stmt2 = Parameter("19", INTEGER);


		FollowStar followStarClause(stmt1, stmt2);
		queryResult = followStarClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 14 }, {18} };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(0, queryResult.getSynCount());

		Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_FollowStar_If_Num)
		{
			PKBStubFollowStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", IF);
			stmt2 = Parameter("11", INTEGER);


			FollowStar followStarClause(stmt1, stmt2);
			queryResult = followStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { {6} };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}
		
		TEST_METHOD(UnitTest_FollowStar_Num_Underscore)
		{
		PKBStubFollowStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("2", INTEGER);
		stmt2 = Parameter("c1", ANYTHING);


		FollowStar followStarClause(stmt1, stmt2);
		queryResult = followStarClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 3 }, {4}, {12} };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(0, queryResult.getSynCount());

		Assert::IsTrue(queryResult.getBoolean());
		}
		
		TEST_METHOD(UnitTest_FollowStar_Num_While)
		{
		PKBStubFollowStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("2", INTEGER);
		stmt2 = Parameter("c1", WHILE);


		FollowStar followStarClause(stmt1, stmt2);
		queryResult = followStarClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 4 } };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}
		
		TEST_METHOD(UnitTest_FollowStar_Num_While2)
		{
		PKBStubFollowStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("9", INTEGER);
		stmt2 = Parameter("c1", WHILE);


		FollowStar followStarClause(stmt1, stmt2);
		queryResult = followStarClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 4 } };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_FollowStar_Underscore_Underscore)
		{
			PKBStubFollowStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", ANYTHING);
			stmt2 = Parameter("s2", ANYTHING);


			FollowStar followStarClause(stmt1, stmt2);
			queryResult = followStarClause.evaluate(&pkbStub, intResult);

			//expectedResult = { { 4 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(0, queryResult.getSynCount());

			Assert::IsTrue(queryResult.getBoolean());
		}
	
		TEST_METHOD(UnitTest_FollowStar_Stmt_Stmt)
		{
		PKBStubFollowStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", STMT);
		stmt2 = Parameter("s1", STMT);


		FollowStar followStarClause(stmt1, stmt2);
		queryResult = followStarClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 4 } };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_FollowStar_While_Call)
		{
		PKBStubFollowStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", WHILE);
		stmt2 = Parameter("s2", CALL);


		FollowStar followStarClause(stmt1, stmt2);
		queryResult = followStarClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 4,12 } };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(2, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_FollowStar_Stmt_Call)
		{
		PKBStubFollowStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", STMT);
		stmt2 = Parameter("s2", CALL);


		FollowStar followStarClause(stmt1, stmt2);
		queryResult = followStarClause.evaluate(&pkbStub, intResult);

		expectedResult = { {1,12},{ 2,12 },{ 3,12 },{ 4,12 }, {5,10},{ 6,10 } ,{ 9,10 },{ 15,16 } };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(2, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}
		
		TEST_METHOD(UnitTest_FollowStar_Restricted_Stmt_Num)
		{
		PKBStubFollowStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", STMT);
		stmt2 = Parameter("4", INTEGER);

		intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));

		intResult.insertTuple({ 1 });
		intResult.insertTuple({ 12 });

		FollowStar followStarClause(stmt1, stmt2);
		queryResult = followStarClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 1 } };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		//Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());
		Assert::IsFalse(queryResult.getBoolean());
		}
		
		TEST_METHOD(UnitTest_FollowStar_Restricted_Stmt_Num2)
		{
		PKBStubFollowStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", STMT);
		stmt2 = Parameter("2", INTEGER);

		intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
		intResult.insertTuple({ 2 });
		intResult.insertTuple({ 12 });

		FollowStar followStarClause(stmt1, stmt2);
		queryResult = followStarClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 1 } };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());
		Assert::IsFalse(queryResult.getBoolean());
		}
		
		TEST_METHOD(UnitTest_FollowStar_Restricted_Num_Stmt)
		{
		PKBStubFollowStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("2", INTEGER);
		stmt2 = Parameter("s1", STMT);

		intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
		intResult.insertTuple({ 2 });
		intResult.insertTuple({ 12 });

		FollowStar followStarClause(stmt1, stmt2);
		queryResult = followStarClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 12 } };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());
		Assert::IsFalse(queryResult.getBoolean());
		}
		
		TEST_METHOD(UnitTest_FollowStar_Restricted_Num_Stmt2)
		{
		PKBStubFollowStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("2", INTEGER);
		stmt2 = Parameter("s1", STMT);

		intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
		intResult.insertTuple({ 33 });
		intResult.insertTuple({ 212 });

		FollowStar followStarClause(stmt1, stmt2);
		queryResult = followStarClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 3 } };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());
		Assert::IsFalse(queryResult.getBoolean());
		}
		
		TEST_METHOD(UnitTest_FollowStar_Restricted_Stmt_Stmt)
		{
		PKBStubFollowStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", STMT);
		stmt2 = Parameter("s2", STMT);

		intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
		intResult.insertTuple({ 3 });
		intResult.insertTuple({ 13 });

		FollowStar followStarClause(stmt1, stmt2);
		queryResult = followStarClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 3,4 },{ 3,12 },{ 13, 21 } };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(2, queryResult.getSynCount());
		Assert::IsFalse(queryResult.getBoolean());
		}
		
		TEST_METHOD(UnitTest_FollowStar_Restricted_While_Stmt)
		{
		PKBStubFollowStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", WHILE);
		stmt2 = Parameter("s2", STMT);

		intResult.setSynList(vector<Parameter>(1, Parameter("s2", STMT)));
		intResult.insertTuple({ 12 });

		FollowStar followStarClause(stmt1, stmt2);
		queryResult = followStarClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 4,12 } };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(2, queryResult.getSynCount());
		Assert::IsFalse(queryResult.getBoolean());
		}
		
		TEST_METHOD(UnitTest_FollowStar_Restricted_Stmt_Stmt_Tuple)
		{
			PKBStubFollowStar pkbStub;

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
			intResult.insertTuple({ 2, 4 });
			intResult.insertTuple({ 4, 6 });
			intResult.insertTuple({ 4, 8 });
			intResult.insertTuple({ 13, 14 });
			intResult.insertTuple({ 13,15 });
			intResult.insertTuple({ 13,20 });
			intResult.insertTuple({ 13,21 });

			FollowStar followStarClause(stmt1, stmt2);
			queryResult = followStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1,2 },{ 2,4 },{ 13,21 } };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_FollowStar_Restricted_Stmt_Stmt_Tuple2)
		{
			PKBStubFollowStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("s2", STMT);

			vector<Parameter> pList;
			pList.push_back(Parameter("s2", STMT));
			pList.push_back(Parameter("s1", STMT));
			intResult.setSynList(pList);

			intResult.insertTuple({ 2, 1 });
			intResult.insertTuple({ 4, 2 });
			intResult.insertTuple({ 1, 2 });
			intResult.insertTuple({ 4, 8 });
			intResult.insertTuple({ 13, 14 });
			intResult.insertTuple({ 13,15 });
			intResult.insertTuple({ 13,20 });
			intResult.insertTuple({ 21, 13 });

			FollowStar followStarClause(stmt1, stmt2);
			queryResult = followStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1,2 },{ 2,4 },{ 13,21 } };

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
