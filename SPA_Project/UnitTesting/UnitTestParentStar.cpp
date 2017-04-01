#include "stdafx.h"
#include "CppUnitTest.h"

#include "PKBStubParentStar.h"
#include "ResultTable.h"
#include "Parameter.h"
#include "ParentStar.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(ParentStarObjectTest)
	{
	public:

		TEST_METHOD(UnitTest_ParentStar_Num_Num)
		{
			PKBStubParentStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("1", INTEGER);
			stmt2 = Parameter("2", INTEGER);


			ParentStar parentStarClause(stmt1, stmt2);
			queryResult = parentStarClause.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_ParentStar_Num_Num2)
		{
			PKBStubParentStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("4", INTEGER);
			stmt2 = Parameter("7", INTEGER);


			ParentStar parentStarClause(stmt1, stmt2);
			queryResult = parentStarClause.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());

			Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_ParentStar_Stmt_Num)
		{
			PKBStubParentStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("s1", STMT);
			stmt2 = Parameter("7", INTEGER);


			ParentStar parentStarClause(stmt1, stmt2);
			queryResult = parentStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 4 }, {6} };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_ParentStar_While_Num)
		{
			PKBStubParentStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("a1", WHILE);
			stmt2 = Parameter("8", INTEGER);


			ParentStar parentStarClause(stmt1, stmt2);
			queryResult = parentStarClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 4 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_ParentStar_While_Num2)
		{
			PKBStubParentStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("a1", WHILE);
			stmt2 = Parameter("14", INTEGER);


			ParentStar parentStarClause(stmt1, stmt2);
			queryResult = parentStarClause.evaluate(&pkbStub, intResult);

			//expectedResult = { { 7 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_ParentStar_Call_Num)
		{
			PKBStubParentStar pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("c1", CALL);
			stmt2 = Parameter("11", INTEGER);


			ParentStar parentStarClause(stmt1, stmt2);
			queryResult = parentStarClause.evaluate(&pkbStub, intResult);

			//expectedResult = { { 10 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(1, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_ParentStar_ProgLine_Num)
		{
		PKBStubParentStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("c1", PROG_LINE);
		stmt2 = Parameter("17", INTEGER);


		ParentStar parentStarClause(stmt1, stmt2);
		queryResult = parentStarClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 13 }, {14} };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_ParentStar_Underscore_Num)
		{
		PKBStubParentStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("c1", ANYTHING);
		stmt2 = Parameter("11", INTEGER);


		ParentStar parentStarClause(stmt1, stmt2);
		queryResult = parentStarClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 4 } };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(0, queryResult.getSynCount());

		Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_ParentStar_Num_Underscore)
		{
		PKBStubParentStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("14", INTEGER);
		stmt2 = Parameter("c1", ANYTHING);


		ParentStar parentStarClause(stmt1, stmt2);
		queryResult = parentStarClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 15 }, {16}, {17} };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(0, queryResult.getSynCount());

		Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_ParentStar_Num_Call)
		{
		PKBStubParentStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("13", INTEGER);
		stmt2 = Parameter("c1", CALL);


		ParentStar parentStarClause(stmt1, stmt2);
		queryResult = parentStarClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 16 } };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_ParentStar_Num_IF)
		{
		PKBStubParentStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("13", INTEGER);
		stmt2 = Parameter("c1", IF);


		ParentStar parentStarClause(stmt1, stmt2);
		queryResult = parentStarClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 4 } };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_ParentStar_Stmt_Stmt)
		{
		PKBStubParentStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", STMT);
		stmt2 = Parameter("s1", STMT);


		ParentStar parentStarClause(stmt1, stmt2);
		queryResult = parentStarClause.evaluate(&pkbStub, intResult);

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_ParentStar_If_Call)
		{
		PKBStubParentStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", IF);
		stmt2 = Parameter("s2", CALL);


		ParentStar parentStarClause(stmt1, stmt2);
		queryResult = parentStarClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 13, 16 }};

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(2, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_ParentStar_Restricted_Stmt_Num)
		{
		PKBStubParentStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", STMT);
		stmt2 = Parameter("8", INTEGER);

		intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));

		intResult.insertTuple({ 1 });
		intResult.insertTuple({ 2 });
		intResult.insertTuple({ 3 });
		intResult.insertTuple({ 4 });

		ParentStar parentStarClause(stmt1, stmt2);
		queryResult = parentStarClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 4 } };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());
		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_ParentStar_Restricted_Stmt_Num2)
		{
		PKBStubParentStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", STMT);
		stmt2 = Parameter("5", INTEGER);

		intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
		intResult.insertTuple({ 2 });
		intResult.insertTuple({ 12 });

		ParentStar parentStarClause(stmt1, stmt2);
		queryResult = parentStarClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 1 } };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());
		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_ParentStar_Restricted_Num_Stmt)
		{
		PKBStubParentStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("13", INTEGER);
		stmt2 = Parameter("s1", STMT);

		intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
		intResult.insertTuple({ 2 });
		intResult.insertTuple({ 12 });

		ParentStar parentStarClause(stmt1, stmt2);
		queryResult = parentStarClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 14 }, {18}, {19}, {20} };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());
		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_ParentStar_Restricted_Num_Stmt2)
		{
		PKBStubParentStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("2", INTEGER);
		stmt2 = Parameter("s1", STMT);

		intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
		intResult.insertTuple({ 3 });
		intResult.insertTuple({ 12 });

		ParentStar parentStarClause(stmt1, stmt2);
		queryResult = parentStarClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 3 } };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());
		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_ParentStar_Restricted_Stmt_Stmt)
		{
		PKBStubParentStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", STMT);
		stmt2 = Parameter("s2", STMT);

		intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
		intResult.insertTuple({ 3 });
		intResult.insertTuple({ 6 });

		ParentStar parentStarClause(stmt1, stmt2);
		queryResult = parentStarClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 6,7 },{ 6,8 } };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(2, queryResult.getSynCount());
		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_ParentStar_Restricted_While_IF)
		{
		PKBStubParentStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", WHILE);
		stmt2 = Parameter("s2", IF);

		intResult.setSynList(vector<Parameter>(1, Parameter("s2", IF)));
		intResult.insertTuple({ 6 });

		ParentStar parentStarClause(stmt1, stmt2);
		queryResult = parentStarClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 4, 6 } };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(2, queryResult.getSynCount());
		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_ParentStar_Restricted_Stmt_Stmt_Tuple)
		{
		PKBStubParentStar pkbStub;

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

		ParentStar parentStarClause(stmt1, stmt2);
		queryResult = parentStarClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 4,6 },{ 4,8 },{ 13,14 },{ 13,15 },{ 13,20 } };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(2, queryResult.getSynCount());
		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_ParentStar_Restricted_Stmt_Stmt_Tuple2)
		{
		PKBStubParentStar pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", STMT);
		stmt2 = Parameter("s2", STMT);

		vector<Parameter> pList;
		pList.push_back(Parameter("s2", STMT));
		pList.push_back(Parameter("s1", STMT));
		intResult.setSynList(pList);

		intResult.insertTuple({ 1,2 });
		intResult.insertTuple({ 2, 3 });
		intResult.insertTuple({ 4, 6 });
		intResult.insertTuple({ 6,4 });
		intResult.insertTuple({ 13, 14 });
		intResult.insertTuple({ 13,15 });
		intResult.insertTuple({ 20, 13 });

		ParentStar parentStarClause(stmt1, stmt2);
		queryResult = parentStarClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 4,6 },{ 13,20 } };

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
