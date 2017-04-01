#include "stdafx.h"
#include "CppUnitTest.h"

#include "PKBStubParent.h"
#include "ResultTable.h"
#include "Parameter.h"
#include "Parent.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(ParentObjectTest)
	{
	public:

		TEST_METHOD(UnitTest_Parent_Num_Num)
		{
			PKBStubParent pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("1", INTEGER);
			stmt2 = Parameter("2", INTEGER);


			Parent parentClause(stmt1, stmt2);
			queryResult = parentClause.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());

			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Parent_Num_Num2)
		{
			PKBStubParent pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt1, stmt2;
			vector<vector<int>> expectedResult, tupleResult;

			stmt1 = Parameter("6", INTEGER);
			stmt2 = Parameter("8", INTEGER);


			Parent parentClause(stmt1, stmt2);
			queryResult = parentClause.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());

			Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Parent_Stmt_Num)
		{
		PKBStubParent pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", STMT);
		stmt2 = Parameter("6", INTEGER);


		Parent parentClause(stmt1, stmt2);
		queryResult = parentClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 4 } };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Parent_While_Num)
		{
		PKBStubParent pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("a1", WHILE);
		stmt2 = Parameter("16", INTEGER);


		Parent parentClause(stmt1, stmt2);
		queryResult = parentClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 14 } };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Parent_While_Num2)
		{
		PKBStubParent pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("a1", WHILE);
		stmt2 = Parameter("2", INTEGER);


		Parent parentClause(stmt1, stmt2);
		queryResult = parentClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 7 } };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Parent_Call_Num)
		{
		PKBStubParent pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("c1", CALL);
		stmt2 = Parameter("11", INTEGER);


		Parent parentClause(stmt1, stmt2);
		queryResult = parentClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 10 } };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Parent_ProgLine_Num)
		{
		PKBStubParent pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("c1", PROG_LINE);
		stmt2 = Parameter("20", INTEGER);


		Parent parentClause(stmt1, stmt2);
		queryResult = parentClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 13 } };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Parent_Underscore_Num)
		{
		PKBStubParent pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("c1", ANYTHING);
		stmt2 = Parameter("11", INTEGER);


		Parent parentClause(stmt1, stmt2);
		queryResult = parentClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 4 } };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(0, queryResult.getSynCount());

		Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Parent_Num_Underscore)
		{
		PKBStubParent pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("14", INTEGER);
		stmt2 = Parameter("c1", ANYTHING);


		Parent parentClause(stmt1, stmt2);
		queryResult = parentClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 15 }, {16}, {17} };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(0, queryResult.getSynCount());

		Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Parent_Num_While)
		{
		PKBStubParent pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("13", INTEGER);
		stmt2 = Parameter("c1", WHILE);


		Parent parentClause(stmt1, stmt2);
		queryResult = parentClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 14 } };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Parent_Num_While2)
		{
		PKBStubParent pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("4", INTEGER);
		stmt2 = Parameter("c1", WHILE);


		Parent parentClause(stmt1, stmt2);
		queryResult = parentClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 4 } };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Parent_Stmt_Stmt)
		{
		PKBStubParent pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", STMT);
		stmt2 = Parameter("s1", STMT);


		Parent parentClause(stmt1, stmt2);
		queryResult = parentClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 4 } };
		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Parent_Stmt_Stmt2)
		{
		PKBStubParent pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", STMT);
		stmt2 = Parameter("s2", STMT);


		Parent parentClause(stmt1, stmt2);
		queryResult = parentClause.evaluate(&pkbStub, intResult);

		expectedResult = { {4,5}, {4,6}, {4,9}, {4,10}, {4,11}, {6,7}, {6,8},
		{13,14}, {13,18}, {13,19}, {13,20}, {14,15}, {14,16}, {14,17}, {22,23}, {22,24} };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(2, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Parent_Call_Stmt)
		{
		PKBStubParent pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", CALL);
		stmt2 = Parameter("s2", STMT);


		Parent parentClause(stmt1, stmt2);
		queryResult = parentClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 10, 11 },{ 16,17 } };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(2, queryResult.getSynCount());

		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Parent_Restricted_Stmt_Num)
		{
		PKBStubParent pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", STMT);
		stmt2 = Parameter("6", INTEGER);

		intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));

		intResult.insertTuple({ 1 });
		intResult.insertTuple({ 2 });
		intResult.insertTuple({ 3 });
		intResult.insertTuple({ 4 });

		Parent parentClause(stmt1, stmt2);
		queryResult = parentClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 4 } };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());
		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Parent_Restricted_Stmt_Num2)
		{
		PKBStubParent pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", STMT);
		stmt2 = Parameter("5", INTEGER);

		intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
		intResult.insertTuple({ 2 });
		intResult.insertTuple({ 12 });

		Parent parentClause(stmt1, stmt2);
		queryResult = parentClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 1 } };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());
		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Parent_Restricted_Num_Stmt)
		{
		PKBStubParent pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("13", INTEGER);
		stmt2 = Parameter("s1", STMT);

		intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
		intResult.insertTuple({ 2 });
		intResult.insertTuple({ 12 });

		Parent parentClause(stmt1, stmt2);
		queryResult = parentClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 14 }, {18}, {19}, {20} };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());
		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Parent_Restricted_Num_Stmt2)
		{
		PKBStubParent pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("2", INTEGER);
		stmt2 = Parameter("s1", STMT);

		intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
		intResult.insertTuple({ 3 });
		intResult.insertTuple({ 12 });

		Parent parentClause(stmt1, stmt2);
		queryResult = parentClause.evaluate(&pkbStub, intResult);

		//expectedResult = { { 3 } };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(1, queryResult.getSynCount());
		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Parent_Restricted_Stmt_Stmt)
		{
		PKBStubParent pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", STMT);
		stmt2 = Parameter("s2", STMT);

		intResult.setSynList(vector<Parameter>(1, Parameter("s1", STMT)));
		intResult.insertTuple({ 3 });
		intResult.insertTuple({ 6 });

		Parent parentClause(stmt1, stmt2);
		queryResult = parentClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 6,7 },{ 6,8} };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(2, queryResult.getSynCount());
		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Parent_Restricted_While_Stmt)
		{
		PKBStubParent pkbStub;

		ResultTable intResult, queryResult;
		Parameter stmt1, stmt2;
		vector<vector<int>> expectedResult, tupleResult;

		stmt1 = Parameter("s1", WHILE);
		stmt2 = Parameter("s2", STMT);

		intResult.setSynList(vector<Parameter>(1, Parameter("s1", WHILE)));
		intResult.insertTuple({ 14 });

		Parent parentClause(stmt1, stmt2);
		queryResult = parentClause.evaluate(&pkbStub, intResult);

		expectedResult = { { 14, 15 }, {14, 16}, {14, 17} };

		sort(expectedResult.begin(), expectedResult.end());
		tupleResult = queryResult.getTupleList();
		sort(tupleResult.begin(), tupleResult.end());

		Assert::AreEqual(expectedResult.size(), tupleResult.size());
		Assert::IsTrue(expectedResult == tupleResult);

		Assert::AreEqual(2, queryResult.getSynCount());
		Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Parent_Restricted_Stmt_Stmt_Tuple)
		{
			PKBStubParent pkbStub;

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

			Parent parentClause(stmt1, stmt2);
			queryResult = parentClause.evaluate(&pkbStub, intResult);

			expectedResult = { {4,6 }, {13,14}, {13,20} };

			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Parent_Restricted_Stmt_Stmt_Tuple2)
		{
			PKBStubParent pkbStub;

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

			Parent parentClause(stmt1, stmt2);
			queryResult = parentClause.evaluate(&pkbStub, intResult);

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
