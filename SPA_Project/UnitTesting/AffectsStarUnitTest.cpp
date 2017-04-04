#include "stdafx.h"
#include "CppUnitTest.h"

#include "PKBAffectsStub.h"
#include "AffectsStar.h"
#include "ResultTable.h"
#include "Parameter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_AffectsStar_Object
{
	TEST_CLASS(AffectsStarObjectTest)
	{
	public:

		TEST_METHOD(UnitTest_AffectsStar_Integer_And_Integer_Valid)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;

			affectorStmt = Parameter("1", INTEGER);
			affectedStmt = Parameter("9", INTEGER);

			AffectsStar affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());
			Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_AffectsStar_Integer_And_Integer_Invalid)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;

			affectorStmt = Parameter("7", INTEGER);
			affectedStmt = Parameter("8", INTEGER);

			AffectsStar affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_AffectsStar_Integer_And_Anything_Valid)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;

			affectorStmt = Parameter("17", INTEGER);
			affectedStmt = Parameter("_", ANYTHING);

			AffectsStar affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());
			Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_AffectsStar_Integer_And_Anything_Invalid)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;

			affectorStmt = Parameter("23", INTEGER);
			affectedStmt = Parameter("_", ANYTHING);

			AffectsStar affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_AffectsStar_Anything_And_Integer_Valid)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;

			affectorStmt = Parameter("_", ANYTHING);
			affectedStmt = Parameter("9", INTEGER);

			AffectsStar affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());
			Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_AffectsStar_Anything_And_Integer_Invalid)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;

			affectorStmt = Parameter("_", ANYTHING);
			affectedStmt = Parameter("20", INTEGER);

			AffectsStar affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_AffectsStar_Anything_And_Anything_Valid)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;

			affectorStmt = Parameter("_", ANYTHING);
			affectedStmt = Parameter("_", ANYTHING);

			AffectsStar affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(0, queryResult.getSynCount());
			Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_AffectsStar_Integer_And_Assign)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;
			vector<vector<int>> expectedResult, tupleResult;

			affectorStmt = Parameter("1", INTEGER);
			affectedStmt = Parameter("s2", ASSIGN);

			AffectsStar affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(affectedStmt));
			Assert::AreEqual(0, queryResult.getSynIndex(affectedStmt));

			expectedResult = { { 5 },{ 7 },{ 8 },{ 9 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_AffectsStar_Stmt_And_Integer)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;
			vector<vector<int>> expectedResult, tupleResult;

			affectorStmt = Parameter("s1", STMT);
			affectedStmt = Parameter("9", INTEGER);

			AffectsStar affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(1, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(affectorStmt));
			Assert::AreEqual(0, queryResult.getSynIndex(affectorStmt));

			expectedResult = { { 1 },{ 2 },{ 3 },{ 5 },{ 7 },{ 11 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_AffectsStar_Integer_And_Anyhting)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;
			vector<vector<int>> expectedResult, tupleResult;

			affectorStmt = Parameter("a1", ASSIGN);
			affectedStmt = Parameter("_", ANYTHING);

			AffectsStar affectsObj(affectorStmt, affectedStmt);
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

		TEST_METHOD(UnitTest_AffectsStar_Anything_And_Stmt)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;
			vector<vector<int>> expectedResult, tupleResult;

			affectorStmt = Parameter("_", ANYTHING);
			affectedStmt = Parameter("s2", STMT);

			AffectsStar affectsObj(affectorStmt, affectedStmt);
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

		TEST_METHOD(UnitTest_AffectsStar_ProgLine_And_ProgLine)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;
			vector<vector<int>> expectedResult, tupleResult;

			affectorStmt = Parameter("s1", PROG_LINE);
			affectedStmt = Parameter("s2", PROG_LINE);

			AffectsStar affectsObj(affectorStmt, affectedStmt);
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(affectorStmt));
			Assert::IsTrue(queryResult.isSynInTable(affectedStmt));
			Assert::AreEqual(0, queryResult.getSynIndex(affectorStmt));
			Assert::AreEqual(1, queryResult.getSynIndex(affectedStmt));

			expectedResult = { { 1,5 },{ 1,7 },{ 1,8 },{ 1,9 },{ 2,8 },{ 2,9 },{ 3,9 },{ 3,11 },{ 5,7 },{ 5,8 },{ 5,9 },
								{ 7,9 },{ 11,9 },{ 11,11 },{ 17,17 },{ 17,21 },{ 18,19 },{ 18,21 },{ 19,21 },{ 20,21 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_AffectsStar_Stmt_And_Stmt_Identical_Synonym)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;
			vector<vector<int>> expectedResult, tupleResult;

			affectorStmt = Parameter("s1", STMT);
			affectedStmt = Parameter("s1", STMT);

			AffectsStar affectsObj(affectorStmt, affectedStmt);
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

		TEST_METHOD(UnitTest_AffectsStar_Stmt_And_Assign_With_LeftIntermediateList)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;
			vector<vector<int>> expectedResult, tupleResult;

			affectorStmt = Parameter("s1", STMT);
			affectedStmt = Parameter("s2", ASSIGN);

			AffectsStar affectsObj(affectorStmt, affectedStmt);
			intResult.setSynList({ affectorStmt });
			intResult.insertTuple({ 1 });
			intResult.insertTuple({ 2 });
			intResult.insertTuple({ 3 });
			intResult.insertTuple({ 4 });
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(affectorStmt));
			Assert::IsTrue(queryResult.isSynInTable(affectedStmt));
			Assert::AreEqual(0, queryResult.getSynIndex(affectorStmt));
			Assert::AreEqual(1, queryResult.getSynIndex(affectedStmt));

			expectedResult = { { 1,5 },{ 1,7 },{ 1,8 },{ 1,9 },{ 2,8 },{ 2,9 },{ 3,9 },{ 3,11 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_AffectsStar_Assign_And_Stmt_With_RightIntermediateList)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;
			vector<vector<int>> expectedResult, tupleResult;

			affectorStmt = Parameter("s1", STMT);
			affectedStmt = Parameter("s2", ASSIGN);

			AffectsStar affectsObj(affectorStmt, affectedStmt);
			intResult.setSynList({ affectedStmt });
			intResult.insertTuple({ 7 });
			intResult.insertTuple({ 16 });
			intResult.insertTuple({ 21 });
			queryResult = affectsObj.evaluate(&pkbStub, intResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(affectorStmt));
			Assert::IsTrue(queryResult.isSynInTable(affectedStmt));
			Assert::AreEqual(0, queryResult.getSynIndex(affectorStmt));
			Assert::AreEqual(1, queryResult.getSynIndex(affectedStmt));

			expectedResult = { { 1,7 },{ 5,7 },{ 17,21 },{ 18,21 },{ 19,21 },{ 20,21 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_AffectsStar_Assign_And_Assign_With_BothIntermediateList)
		{
			PKBAffectsStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter affectorStmt, affectedStmt;
			vector<vector<int>> expectedResult, tupleResult;

			affectorStmt = Parameter("s1", ASSIGN);
			affectedStmt = Parameter("s2", ASSIGN);

			AffectsStar affectsObj(affectorStmt, affectedStmt);
			intResult.setSynList({ affectorStmt,affectedStmt });
			intResult.insertTuple({ 1,8 });
			intResult.insertTuple({ 9,11 });
			intResult.insertTuple({ 17,21 });
			queryResult = affectsObj.evaluate(&pkbStub, intResult);
			queryResult.join(intResult);

			Assert::AreEqual(2, queryResult.getSynCount());
			Assert::IsTrue(queryResult.isSynInTable(affectorStmt));
			Assert::IsTrue(queryResult.isSynInTable(affectedStmt));
			Assert::AreEqual(0, queryResult.getSynIndex(affectorStmt));
			Assert::AreEqual(1, queryResult.getSynIndex(affectedStmt));

			expectedResult = { { 1,8 },{ 17,21 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult.getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}
	};
}
