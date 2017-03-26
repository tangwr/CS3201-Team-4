#include "stdafx.h"
#include "CppUnitTest.h"

#include "PKBWithStub.h"
#include "With.h"
#include "ResultTable.h"
#include "Parameter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_With_Object
{
	TEST_CLASS(WithObjectTest)
	{
	public:

		TEST_METHOD(UnitTest_With_ASSIGN_Equal_INTEGER)
		{
			PKBWithStub pkbStub;

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

		TEST_METHOD(UnitTest_With_Proc_Equal_NAME)
		{
			PKBWithStub pkbStub;

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

		TEST_METHOD(UnitTest_With_Call_Equal_NAME)
		{
			PKBWithStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("cl", CALL);
			right = Parameter("q", STRINGVARIABLE);

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

		TEST_METHOD(UnitTest_With_Var_Equal_NAME)
		{
			PKBWithStub pkbStub;

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

		TEST_METHOD(UnitTest_With_ASSIGN_Equal_INTEGER_With_LeftIntermediateList)
		{
			PKBWithStub pkbStub;

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
			PKBWithStub pkbStub;

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
			PKBWithStub pkbStub;

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
			PKBWithStub pkbStub;

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
			PKBWithStub pkbStub;

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
			PKBWithStub pkbStub;

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

		TEST_METHOD(UnitTest_With_Proc_Equal_Var)
		{
			PKBWithStub pkbStub;

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

		TEST_METHOD(UnitTest_With_Proc_Equal_Call_With_RightIntermediateList)
		{
			PKBWithStub pkbStub;

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
			PKBWithStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter left, right;
			vector<vector<int>> expectedResult, tupleResult;

			left = Parameter("cl", CALL);
			right = Parameter("p", PROCEDURE);

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
			PKBWithStub pkbStub;

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

			expectedResult = { { 2, 2 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::AreEqual(expectedResult[0][0], tupleResult[0][0]);
			Assert::IsTrue(expectedResult == tupleResult);
		}
	};
}
