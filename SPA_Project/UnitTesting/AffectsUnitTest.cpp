#include "stdafx.h"
#include "CppUnitTest.h"

#include "PKBAffectsStub.h"
#include "Affects.h"
#include "ResultTable.h"
#include "Parameter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_Affects_Object
{
	TEST_CLASS(AffectsObjectTest)
	{
	public:

		TEST_METHOD(UnitTest_Affects_Integer_And_Integer_Valid)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;

			affectorStmt = Parameter("1", INTEGER);
			affectedStmt = Parameter("5", INTEGER);

			Affects affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());
			Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Affects_Integer_And_Integer_Invalid)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;

			affectorStmt = Parameter("2", INTEGER);
			affectedStmt = Parameter("11", INTEGER);

			Affects affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Affects_Integer_And_Anything_Valid)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;

			affectorStmt = Parameter("3", INTEGER);
			affectedStmt = Parameter("_", ANYTHING);

			Affects affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());
			Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Affects_Integer_And_Anything_Invalid)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;

			affectorStmt = Parameter("8", INTEGER);
			affectedStmt = Parameter("_", ANYTHING);

			Affects affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Affects_Anything_And_Integer_Invalid)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;

			affectorStmt = Parameter("_", ANYTHING);
			affectedStmt = Parameter("15", INTEGER);

			Affects affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Affects_Anything_And_Anything_Valid)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;

			affectorStmt = Parameter("_", ANYTHING);
			affectedStmt = Parameter("_", ANYTHING);

			Affects affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());
			Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Affects_Integer_And_Assign)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;
			vector<vector<int>> expectedResult, tupleResult;

			affectorStmt = Parameter("2", INTEGER);
			affectedStmt = Parameter("s2", ASSIGN);

			Affects affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(affectedStmt));
			Assert::AreEqual(0, queryResult.getSynIndex(affectedStmt));

			expectedResult = { { 8 }, { 9 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Affects_Stmt_And_Integer)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;
			vector<vector<int>> expectedResult, tupleResult;

			affectorStmt = Parameter("s1", STMT);
			affectedStmt = Parameter("21", INTEGER);

			Affects affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(affectorStmt));
			Assert::AreEqual(0, queryResult.getSynIndex(affectorStmt));

			expectedResult = { { 17 },{ 18 },{ 19 },{ 20 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Affects_Integer_And_Anyhting)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;
			vector<vector<int>> expectedResult, tupleResult;

			affectorStmt = Parameter("a1", ASSIGN);
			affectedStmt = Parameter("_", ANYTHING);

			Affects affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(affectorStmt));
			Assert::AreEqual(0, queryResult.getSynIndex(affectorStmt));

			expectedResult = { { 1 },{ 2 },{ 3 },{ 5 },{ 7 },{ 11 },{ 17 },{ 18 },{ 19 },{ 20 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Affects_Anything_And_Stmt)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;
			vector<vector<int>> expectedResult, tupleResult;

			affectorStmt = Parameter("_", ANYTHING);
			affectedStmt = Parameter("s2", STMT);

			Affects affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(affectedStmt));
			Assert::AreEqual(0, queryResult.getSynIndex(affectedStmt));

			expectedResult = { { 5 },{ 7 },{ 8 },{ 9 },{ 11 },{ 17 },{ 19 },{ 21 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Affects_ProgLine_And_ProgLine)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;
			vector<vector<int>> expectedResult, tupleResult;

			affectorStmt = Parameter("s1", PROG_LINE);
			affectedStmt = Parameter("s2", PROG_LINE);

			Affects affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(affectorStmt));
			Assert::IsTrue(queryResult.isSynInTable(affectedStmt));
			Assert::AreEqual(0, queryResult.getSynIndex(affectorStmt));
			Assert::AreEqual(1, queryResult.getSynIndex(affectedStmt));

			expectedResult = { { 1,5 },{ 2,8 },{ 2,9 },{ 3,9 },{ 3,11 },{ 5,7 },{ 5,8 },{ 5,9 },{ 7,9 },{ 11,9 },
								{ 11,11 },{ 17,17 },{ 17,21 },{ 18,19 },{ 18,21 },{ 19,21 },{ 20,21 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Affects_Stmt_And_Stmt_Identical_Synonym)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;
			vector<vector<int>> expectedResult, tupleResult;

			affectorStmt = Parameter("s1", STMT);
			affectedStmt = Parameter("s1", STMT);

			Affects affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(affectorStmt));
			Assert::IsTrue(queryResult.isSynInTable(affectedStmt));
			Assert::AreEqual(0, queryResult.getSynIndex(affectorStmt));
			Assert::AreEqual(0, queryResult.getSynIndex(affectedStmt));

			expectedResult = { { 11 },{ 17 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Affects_Stmt_And_Assign_With_LeftIntermediateList)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;
			vector<vector<int>> expectedResult, tupleResult;

			affectorStmt = Parameter("s1", STMT);
			affectedStmt = Parameter("s2", ASSIGN);

			Affects affectsObj(affectorStmt, affectedStmt);
			intResult.setSynList({ affectorStmt });
			intResult.insertTuple({ 3 });
			intResult.insertTuple({ 4 });
			intResult.insertTuple({ 5 });
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(affectorStmt));
			Assert::IsTrue(queryResult.isSynInTable(affectedStmt));
			Assert::AreEqual(0, queryResult.getSynIndex(affectorStmt));
			Assert::AreEqual(1, queryResult.getSynIndex(affectedStmt));

			expectedResult = { { 3,9 },{ 3,11 },{ 5,7 },{ 5,8 },{ 5,9 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Affects_Assign_And_Stmt_With_RightIntermediateList)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;
			vector<vector<int>> expectedResult, tupleResult;

			affectorStmt = Parameter("s1", STMT);
			affectedStmt = Parameter("s2", ASSIGN);

			Affects affectsObj(affectorStmt, affectedStmt);
			intResult.setSynList({ affectedStmt });
			intResult.insertTuple({ 11 });
			intResult.insertTuple({ 16 });
			intResult.insertTuple({ 21 });
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(affectorStmt));
			Assert::IsTrue(queryResult.isSynInTable(affectedStmt));
			Assert::AreEqual(0, queryResult.getSynIndex(affectorStmt));
			Assert::AreEqual(1, queryResult.getSynIndex(affectedStmt));

			expectedResult = { { 3,11 },{ 11,11 },{ 17,21 },{ 18,21 },{ 19,21 },{ 20,21 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Affects_Assign_And_Assign_With_BothIntermediateList)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;
			vector<vector<int>> expectedResult, tupleResult;

			affectorStmt = Parameter("s1", ASSIGN);
			affectedStmt = Parameter("s2", ASSIGN);

			Affects affectsObj(affectorStmt, affectedStmt);
			intResult.setSynList({ affectorStmt,affectedStmt });
			intResult.insertTuple({ 3,9 });
			intResult.insertTuple({ 9,11 });
			intResult.insertTuple({ 18,21 });
			queryResult = affectsObj.evaluate(&pkbStub, intResult).join(intResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(affectorStmt));
			Assert::IsTrue(queryResult.isSynInTable(affectedStmt));
			Assert::AreEqual(0, queryResult.getSynIndex(affectorStmt));
			Assert::AreEqual(1, queryResult.getSynIndex(affectedStmt));

			expectedResult = { { 3,9 },{ 18,21 }};
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());	
			Assert::IsTrue(expectedResult == tupleResult);
		}
	};
}
