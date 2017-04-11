#include "stdafx.h"
#include "CppUnitTest.h"

#include "WithPKBStub.h"
#include "With.h"
#include "ResultTable.h"
#include "Parameter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_With_Object
{
	TEST_CLASS(WithObjectTest)
	{
	public:

		TEST_METHOD(UnitTest_With_INTEGER_Equal_INTEGER_Valid)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;

			left = Parameter("11", INTEGER);
			right = Parameter("11", INTEGER);

			With withObj(left, right);
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());
			Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_With_INTEGER_Equal_INTEGER_Invalid)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;

			left = Parameter("5", INTEGER);
			right = Parameter("11", INTEGER);

			With withObj(left, right);
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_With_ASSIGN_Equal_INTEGER)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("a", ASSIGN);
			right = Parameter("11", INTEGER);

			With withObj(left, right);
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(left));
			Assert::AreEqual(0, queryResult.getSynIndex(left));

			expectedResult = { { 11 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_INTEGER_Equal_Assign)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("11", INTEGER);
			right = Parameter("a", ASSIGN);

			With withObj(left, right);
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(right));
			Assert::AreEqual(0, queryResult.getSynIndex(right));

			expectedResult = { { 11 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_Proc_Equal_NAME)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("p", PROCEDURE);
			right = Parameter("Example", STRINGVARIABLE);

			With withObj(left, right);
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(left));
			Assert::AreEqual(0, queryResult.getSynIndex(left));

			expectedResult = { { 0 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_NAME_Equal_Proc)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("Example", STRINGVARIABLE);
			right = Parameter("p", PROCEDURE);

			With withObj(left, right);
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(right));
			Assert::AreEqual(0, queryResult.getSynIndex(right));

			expectedResult = { { 0 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_Call_Equal_NAME)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("cl", CALL);
			right = Parameter("q", STRINGVARIABLE);
			left.setAttributeProc(true);

			With withObj(left, right);
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(left));
			Assert::AreEqual(0, queryResult.getSynIndex(left));

			expectedResult = { { 10 },{ 16 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_NAME_Equal_Call)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("q", STRINGVARIABLE);
			right = Parameter("cl", CALL);
			right.setAttributeProc(true);

			With withObj(left, right);
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(right));
			Assert::AreEqual(0, queryResult.getSynIndex(right));

			expectedResult = { { 10 },{ 16 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_Var_Equal_NAME)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("v", VARIABLE);
			right = Parameter("y", STRINGVARIABLE);

			With withObj(left, right);
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(left));
			Assert::AreEqual(0, queryResult.getSynIndex(left));

			expectedResult = { { 3 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_NAME_Equal_Var)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("y", STRINGVARIABLE);
			right = Parameter("v", VARIABLE);
		
			With withObj(left, right);
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(right));
			Assert::AreEqual(0, queryResult.getSynIndex(right));

			expectedResult = { { 3 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_ASSIGN_Equal_INTEGER_With_LeftIntermediateList)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("a", ASSIGN);
			right = Parameter("11", INTEGER);

			With withObj(left, right);
			intResult.setSynList({ left });
			intResult.insertTuple({ 5 });
			intResult.insertTuple({ 9 });
			intResult.insertTuple({ 11 });
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(left));
			Assert::AreEqual(0, queryResult.getSynIndex(left));

			expectedResult = { { 11 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_Proc_Equal_NAME_With_LeftIntermediateList)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("p", PROCEDURE);
			right = Parameter("Example", STRINGVARIABLE);

			With withObj(left, right);
			intResult.setSynList({ left });
			intResult.insertTuple({ 1 });
			intResult.insertTuple({ 2 });
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(left));
			Assert::AreEqual(0, queryResult.getSynIndex(left));

			expectedResult = {};
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_Var_Equal_NAME_With_LeftIntermediateList)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("v", VARIABLE);
			right = Parameter("x", STRINGVARIABLE);

			With withObj(left, right);
			intResult.setSynList({ left });
			intResult.insertTuple({ 0 });
			intResult.insertTuple({ 1 });
			intResult.insertTuple({ 2 });
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(left));
			Assert::AreEqual(0, queryResult.getSynIndex(left));

			expectedResult = { { 0 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_Assign_Equal_Constant)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("a", ASSIGN);
			right = Parameter("c", CONSTANT);

			With withObj(left, right);
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(left));
			Assert::IsTrue(queryResult.isSynInTable(right));
			Assert::AreEqual(0, queryResult.getSynIndex(left));
			Assert::AreEqual(1, queryResult.getSynIndex(right));

			expectedResult = { { 1, 1 },{ 2, 2 },{ 3, 3 },{ 5, 5 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_While_Equal_Stmt)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("w", WHILE);
			right = Parameter("s", STMT);

			With withObj(left, right);
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(left));
			Assert::IsTrue(queryResult.isSynInTable(right));
			Assert::AreEqual(0, queryResult.getSynIndex(left));
			Assert::AreEqual(1, queryResult.getSynIndex(right));

			expectedResult = { { 4, 4 },{ 14, 14 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_If_Equal_ProgLine)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("i", IF);
			right = Parameter("pl", PROG_LINE);

			With withObj(left, right);
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(left));
			Assert::IsTrue(queryResult.isSynInTable(right));
			Assert::AreEqual(0, queryResult.getSynIndex(left));
			Assert::AreEqual(1, queryResult.getSynIndex(right));

			expectedResult = { { 6, 6 },{ 13, 13 },{ 22, 22 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_Call_Equal_Stmt)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("cl", CALL);
			right = Parameter("s", STMT);
			left.setAttributeProc(false);

			With withObj(left, right);
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(left));
			Assert::IsTrue(queryResult.isSynInTable(right));
			Assert::AreEqual(0, queryResult.getSynIndex(left));
			Assert::AreEqual(1, queryResult.getSynIndex(right));

			expectedResult = { { 10, 10 },{ 12, 12 },{ 16, 16 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_CallStmt_Equal_CallStmt)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("cl1", CALL);
			right = Parameter("cl2", CALL);
			left.setAttributeProc(false);
			right.setAttributeProc(false);

			With withObj(left, right);
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(left));
			Assert::IsTrue(queryResult.isSynInTable(right));
			Assert::AreEqual(0, queryResult.getSynIndex(left));
			Assert::AreEqual(1, queryResult.getSynIndex(right));

			expectedResult = { { 10, 10 },{ 12, 12 },{ 16, 16 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_CallProc_Equal_CallProc)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("cl1", CALL);
			right = Parameter("cl2", CALL);
			left.setAttributeProc(true);
			right.setAttributeProc(true);

			With withObj(left, right);
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(left));
			Assert::IsTrue(queryResult.isSynInTable(right));
			Assert::AreEqual(0, queryResult.getSynIndex(left));
			Assert::AreEqual(1, queryResult.getSynIndex(right));

			expectedResult = { { 10, 10 },{ 12, 12 },{ 16, 16 },{ 10, 16 },{ 16, 10 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_Var_Equal_Call)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("v", VARIABLE);
			right = Parameter("cl", CALL);
			right.setAttributeProc(true);

			With withObj(left, right);
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(left));
			Assert::IsTrue(queryResult.isSynInTable(right));
			Assert::AreEqual(0, queryResult.getSynIndex(left));
			Assert::AreEqual(1, queryResult.getSynIndex(right));

			expectedResult = {};
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_Proc_Equal_Call)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("p", PROCEDURE);
			right = Parameter("cl", CALL);
			right.setAttributeProc(true);

			With withObj(left, right);
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(left));
			Assert::IsTrue(queryResult.isSynInTable(right));
			Assert::AreEqual(0, queryResult.getSynIndex(left));
			Assert::AreEqual(1, queryResult.getSynIndex(right));

			expectedResult = { { 2,10 },{ 1,12 },{ 2,16 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_Proc_Equal_Var)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("p", PROCEDURE);
			right = Parameter("v", VARIABLE);

			With withObj(left, right);
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(left));
			Assert::IsTrue(queryResult.isSynInTable(right));
			Assert::AreEqual(0, queryResult.getSynIndex(left));
			Assert::AreEqual(1, queryResult.getSynIndex(right));

			expectedResult = {};
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_While_Equal_While_Identical_Synonym)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("w", WHILE);
			right = Parameter("w", WHILE);

			With withObj(left, right);
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(left));
			Assert::IsTrue(queryResult.isSynInTable(right));
			Assert::AreEqual(0, queryResult.getSynIndex(left));
			Assert::AreEqual(0, queryResult.getSynIndex(right));

			expectedResult = { { 4 },{ 14 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_Proc_Equal_Call_With_RightIntermediateList)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("p", PROCEDURE);
			right = Parameter("cl", CALL);

			With withObj(left, right);
			intResult.setSynList({ right });
			intResult.insertTuple({ 10 });
			intResult.insertTuple({ 16 });
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(left));
			Assert::IsTrue(queryResult.isSynInTable(right));
			Assert::AreEqual(0, queryResult.getSynIndex(left));
			Assert::AreEqual(1, queryResult.getSynIndex(right));

			expectedResult = { { 2, 10 },{ 2, 16 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_Call_Equal_Proc_With_LeftIntermediateLsit)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("cl", CALL);
			right = Parameter("p", PROCEDURE);
			left.setAttributeProc(true);

			With withObj(left, right);
			intResult.setSynList({ left });
			intResult.insertTuple({ 10 });
			intResult.insertTuple({ 16 });
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(left));
			Assert::IsTrue(queryResult.isSynInTable(right));
			Assert::AreEqual(0, queryResult.getSynIndex(left));
			Assert::AreEqual(1, queryResult.getSynIndex(right));

			expectedResult = { { 10, 2 },{ 16, 2 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_With_Constant_Equal_Stmt_With_BothIntermediateLsit)
		{
			WithPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("c", CONSTANT);
			right = Parameter("s", STMT);

			With withObj(left, right);
			intResult.setSynList({ left, right });
			intResult.insertTuple({ { 1, 1 } });
			intResult.insertTuple({ { 1, 2 } });
			intResult.insertTuple({ { 1, 5 } });
			intResult.insertTuple({ { 2, 1 } });
			intResult.insertTuple({ { 2, 2 } });
			intResult.insertTuple({ { 2, 5 } });
			queryResult = withObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(left));
			Assert::IsTrue(queryResult.isSynInTable(right));
			Assert::AreEqual(0, queryResult.getSynIndex(left));
			Assert::AreEqual(1, queryResult.getSynIndex(right));

			expectedResult = { { 1, 1 } , { 2, 2 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}
	};
}
