#include "stdafx.h"
#include "CppUnitTest.h"

#include "PatternPKBStub.h"
#include "Pattern.h"
#include "ResultTable.h"
#include "Parameter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_Pattern_Object
{
	TEST_CLASS(PatternObjectTest)
	{
	public:
		
		TEST_METHOD(UnitTest_Pattern_WhileSynonym_With_VariableSynonym)
		{
			PatternPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt, var, factor;
			vector<vector<int>> expectedResult, tupleResult;

			stmt = Parameter("w", WHILE);
			var = Parameter("v", VARIABLE);
			factor = Parameter("_", ANYTHING);

			Pattern patternObj(stmt, var, factor, false);
			queryResult = patternObj.evaluate(&pkbStub, &intResult);

			Assert::AreEqual(2, queryResult->getSynCount());

			Assert::IsTrue(queryResult->isSynInTable(stmt));
			Assert::IsTrue(queryResult->isSynInTable(var));

			Assert::AreEqual(0, queryResult->getSynIndex(stmt));
			Assert::AreEqual(1, queryResult->getSynIndex(var));

			expectedResult = { { 4, 2 },{ 14, 2 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Pattern_WhileSynonym_With_IDENT)
		{
			PatternPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt, var, factor;
			vector<vector<int>> expectedResult, tupleResult;

			stmt = Parameter("w", WHILE);
			var = Parameter("i", STRINGVARIABLE);
			factor = Parameter("_", ANYTHING);

			Pattern patternObj(stmt, var, factor, false);
			queryResult = patternObj.evaluate(&pkbStub, &intResult);

			Assert::AreEqual(1, queryResult->getSynCount());
			Assert::IsTrue(queryResult->isSynInTable(stmt));
			Assert::AreEqual(0, queryResult->getSynIndex(stmt));

			expectedResult = { { 4 },{ 14 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Pattern_IfSynonym_VariableSynonym)
		{
			PatternPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt, var, factor;
			vector<vector<int>> expectedResult, tupleResult;

			stmt = Parameter("i", IF);
			var = Parameter("v", VARIABLE);
			factor = Parameter("_", ANYTHING);

			Pattern patternObj(stmt, var, factor, false);
			queryResult = patternObj.evaluate(&pkbStub, &intResult);

			Assert::AreEqual(2, queryResult->getSynCount());

			Assert::IsTrue(queryResult->isSynInTable(stmt));
			Assert::IsTrue(queryResult->isSynInTable(var));

			Assert::AreEqual(0, queryResult->getSynIndex(stmt));
			Assert::AreEqual(1, queryResult->getSynIndex(var));

			expectedResult = { { 6, 0 },{ 13, 0 },{ 22, 0 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Pattern_IfSynonym_With_IDENT)
		{
			PatternPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt, var, factor;
			vector<vector<int>> expectedResult, tupleResult;

			stmt = Parameter("i", IF);
			var = Parameter("x", STRINGVARIABLE);
			factor = Parameter("_", ANYTHING);

			Pattern patternObj(stmt, var, factor, false);
			queryResult = patternObj.evaluate(&pkbStub, &intResult);

			Assert::AreEqual(1, queryResult->getSynCount());
			Assert::IsTrue(queryResult->isSynInTable(stmt));
			Assert::AreEqual(0, queryResult->getSynIndex(stmt));

			expectedResult = { { 6 },{ 13 },{ 22 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Pattern_AssignSynonym_With_VariableSynonym_And_SubExpression)
		{
			PatternPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt, var, factor;
			vector<vector<int>> expectedResult, tupleResult;

			stmt = Parameter("a", ASSIGN);
			var = Parameter("v", VARIABLE); 
			factor = Parameter("z+x", STRINGVARIABLE);

			Pattern patternObj(stmt, var, factor, true);
			queryResult = patternObj.evaluate(&pkbStub, &intResult);

			Assert::AreEqual(2, queryResult->getSynCount());

			Assert::IsTrue(queryResult->isSynInTable(stmt));
			Assert::IsTrue(queryResult->isSynInTable(var));

			Assert::AreEqual(0, queryResult->getSynIndex(stmt));
			Assert::AreEqual(1, queryResult->getSynIndex(var));

			expectedResult = { {8, 3},{9, 1},{21, 1},{24, 0} };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Pattern_AssignSynonym_With_VariableSynonym_And_FullExpression)
		{
			PatternPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt, var, factor;
			vector<vector<int>> expectedResult, tupleResult;

			stmt = Parameter("a", ASSIGN);
			var = Parameter("v", VARIABLE);
			factor = Parameter("z+x", STRINGVARIABLE);

			Pattern patternObj(stmt, var, factor, false);
			queryResult = patternObj.evaluate(&pkbStub, &intResult);

			Assert::AreEqual(2, queryResult->getSynCount());

			Assert::IsTrue(queryResult->isSynInTable(stmt));
			Assert::IsTrue(queryResult->isSynInTable(var));

			Assert::AreEqual(0, queryResult->getSynIndex(stmt));
			Assert::AreEqual(1, queryResult->getSynIndex(var));

			expectedResult = { { 8, 3 },{ 24, 0 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Pattern_AssignSynonym_With_VariableSynonym_And_NoExpression)
		{
			PatternPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt, var, factor;
			vector<vector<int>> expectedResult, tupleResult;

			stmt = Parameter("a", ASSIGN);
			var = Parameter("v", VARIABLE);
			factor = Parameter("_", ANYTHING);

			Pattern patternObj(stmt, var, factor, false);
			queryResult = patternObj.evaluate(&pkbStub, &intResult);

			Assert::AreEqual(2, queryResult->getSynCount());

			Assert::IsTrue(queryResult->isSynInTable(stmt));
			Assert::IsTrue(queryResult->isSynInTable(var));

			Assert::AreEqual(0, queryResult->getSynIndex(stmt));
			Assert::AreEqual(1, queryResult->getSynIndex(var));

			expectedResult = { { 1, 0 },{ 2, 1 },{ 3, 2 },{ 5, 0 },{ 7, 1 },{ 8, 3 },{ 9, 1 },
								{ 11, 2 },{ 15, 0 },{ 17, 2 },{ 18, 0 },{ 19, 1 },{ 20, 1 },
								{ 21, 1 },{ 23, 1 },{ 24, 0 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Pattern_AssignSynonym_With_AnyVariable_And_SubExpression)
		{
			PatternPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt, var, factor;
			vector<vector<int>> expectedResult, tupleResult;

			stmt = Parameter("a", ASSIGN);
			var = Parameter("_", ANYTHING);
			factor = Parameter("x + 1", STRINGVARIABLE);

			Pattern patternObj(stmt, var, factor, true);
			queryResult = patternObj.evaluate(&pkbStub, &intResult);

			Assert::AreEqual(1, queryResult->getSynCount());

			Assert::IsTrue(queryResult->isSynInTable(stmt));

			Assert::AreEqual(0, queryResult->getSynIndex(stmt));

			expectedResult = { { 7 },{ 18 },{ 23 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Pattern_AssignSynonym_With_IDENT_And_SubExpression)
		{
			PatternPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt, var, factor;
			vector<vector<int>> expectedResult, tupleResult;

			stmt = Parameter("a", ASSIGN);
			var = Parameter("x", STRINGVARIABLE);
			factor = Parameter("2", STRINGVARIABLE);

			Pattern patternObj(stmt, var, factor, true);
			queryResult = patternObj.evaluate(&pkbStub, &intResult);

			Assert::AreEqual(1, queryResult->getSynCount());

			Assert::IsTrue(queryResult->isSynInTable(stmt));

			Assert::AreEqual(0, queryResult->getSynIndex(stmt));

			expectedResult = { { 1 }, { 15 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Pattern_AssignSynonym_With_StmtIntermediateResult)
		{
			PatternPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt, var, factor;
			vector<vector<int>> expectedResult, tupleResult;

			stmt = Parameter("a", ASSIGN);
			var = Parameter("v", VARIABLE);
			factor = Parameter("_", ANYTHING);

			Pattern patternObj(stmt, var, factor, false);
			intResult.setSynList({ stmt });
			intResult.insertTuple({ 1 });
			intResult.insertTuple({ 15 });
			intResult.insertTuple({ 24 });
			queryResult = patternObj.evaluate(&pkbStub, &intResult);

			Assert::AreEqual(2, queryResult->getSynCount());

			Assert::IsTrue(queryResult->isSynInTable(stmt));
			Assert::IsTrue(queryResult->isSynInTable(var));

			Assert::AreEqual(0, queryResult->getSynIndex(stmt));
			Assert::AreEqual(1, queryResult->getSynIndex(var));

			expectedResult = { { 1, 0 },{ 15, 0 },{ 24, 0 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Pattern_WhileSynonym_With_StmtIntermediateResult)
		{
			PatternPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt, var, factor;
			vector<vector<int>> expectedResult, tupleResult;

			stmt = Parameter("w", WHILE);
			var = Parameter("i", VARIABLE);
			factor = Parameter("_", ANYTHING);

			Pattern patternObj(stmt, var, factor, false);
			intResult.setSynList({ stmt });
			intResult.insertTuple({ 1 });
			intResult.insertTuple({ 6 });
			intResult.insertTuple({ 14 });
			queryResult = patternObj.evaluate(&pkbStub, &intResult);

			Assert::AreEqual(2, queryResult->getSynCount());

			Assert::IsTrue(queryResult->isSynInTable(stmt));
			Assert::IsTrue(queryResult->isSynInTable(var));

			Assert::AreEqual(0, queryResult->getSynIndex(stmt));
			Assert::AreEqual(1, queryResult->getSynIndex(var));

			expectedResult = { { 14, 2 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Pattern_IfSynonym_With_StmtIntermediateResult)
		{
			PatternPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt, var, factor;
			vector<vector<int>> expectedResult, tupleResult;

			stmt = Parameter("i", IF);
			var = Parameter("x", STRINGVARIABLE);
			factor = Parameter("_", ANYTHING);

			Pattern patternObj(stmt, var, factor, false);
			intResult.setSynList({ stmt });
			intResult.insertTuple({ 1 });
			intResult.insertTuple({ 6 });
			intResult.insertTuple({ 13 });
			queryResult = patternObj.evaluate(&pkbStub, &intResult);

			Assert::AreEqual(1, queryResult->getSynCount());
			Assert::IsTrue(queryResult->isSynInTable(stmt));
			Assert::AreEqual(0, queryResult->getSynIndex(stmt));

			expectedResult = { { 6 },{ 13 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Pattern_AssignSynonym_With_VarIntermediateResult)
		{
			PatternPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt, var, factor;
			vector<vector<int>> expectedResult, tupleResult;

			stmt = Parameter("a", ASSIGN);
			var = Parameter("v", VARIABLE);
			factor = Parameter("_", ANYTHING);

			Pattern patternObj(stmt, var, factor, false);
			intResult.setSynList({ var });
			intResult.insertTuple({ 0 });
			intResult.insertTuple({ 3 });
			queryResult = patternObj.evaluate(&pkbStub, &intResult);

			Assert::AreEqual(2, queryResult->getSynCount());

			Assert::IsTrue(queryResult->isSynInTable(stmt));
			Assert::IsTrue(queryResult->isSynInTable(var));

			Assert::AreEqual(0, queryResult->getSynIndex(stmt));
			Assert::AreEqual(1, queryResult->getSynIndex(var));

			expectedResult = { { 1, 0 },{ 5, 0 },{ 8, 3 },{ 15, 0 },{ 18, 0 },{ 24, 0 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Pattern_AssignSynonym_With_StmtIntermediateResult_And_VarIntermediateResult)
		{
			PatternPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt, var, factor;
			vector<vector<int>> expectedResult, tupleResult;

			stmt = Parameter("a", ASSIGN);
			var = Parameter("v", VARIABLE);
			factor = Parameter("_", ANYTHING);

			Pattern patternObj(stmt, var, factor, false);
			intResult.setSynList({ stmt, var });
			intResult.insertTuple({ 1, 0 });
			intResult.insertTuple({ 3, 1 });
			intResult.insertTuple({ 3, 2 });
			intResult.insertTuple({ 8, 3 });
			intResult.insertTuple({ 18, 3 });
			intResult.insertTuple({ 23, 1 });
			queryResult = patternObj.evaluate(&pkbStub, &intResult);

			Assert::AreEqual(2, queryResult->getSynCount());

			Assert::IsTrue(queryResult->isSynInTable(stmt));
			Assert::IsTrue(queryResult->isSynInTable(var));

			Assert::AreEqual(0, queryResult->getSynIndex(stmt));
			Assert::AreEqual(1, queryResult->getSynIndex(var));

			expectedResult = { { 1, 0 },{ 3, 2 },{ 8, 3 },{ 23, 1 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Pattern_WhileSynonym_With_StmtIntermediateResult_And_VarIntermediateResult)
		{
			PatternPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt, var, factor;
			vector<vector<int>> expectedResult, tupleResult;

			stmt = Parameter("w", WHILE);
			var = Parameter("v", VARIABLE);
			factor = Parameter("_", ANYTHING);

			Pattern patternObj(stmt, var, factor, false);
			intResult.setSynList({ stmt, var });
			intResult.insertTuple({ 1, 0 });
			intResult.insertTuple({ 3, 1 });
			intResult.insertTuple({ 3, 2 });
			intResult.insertTuple({ 4, 2 });
			intResult.insertTuple({ 14, 2 });
			intResult.insertTuple({ 23, 1 });
			queryResult = patternObj.evaluate(&pkbStub, &intResult);

			Assert::AreEqual(2, queryResult->getSynCount());

			Assert::IsTrue(queryResult->isSynInTable(stmt));
			Assert::IsTrue(queryResult->isSynInTable(var));

			Assert::AreEqual(0, queryResult->getSynIndex(stmt));
			Assert::AreEqual(1, queryResult->getSynIndex(var));

			expectedResult = { { 4, 2 }, { 14, 2 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}

		TEST_METHOD(UnitTest_Pattern_IfSynonym_With_StmtIntermediateResult_And_VarIntermediateResult)
		{
			PatternPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt, var, factor;
			vector<vector<int>> expectedResult, tupleResult;

			stmt = Parameter("w", WHILE);
			var = Parameter("v", VARIABLE);
			factor = Parameter("_", ANYTHING);

			Pattern patternObj(stmt, var, factor, false);
			intResult.setSynList({ stmt, var });
			intResult.insertTuple({ 1, 0 });
			intResult.insertTuple({ 3, 1 });
			intResult.insertTuple({ 6, 0 });
			intResult.insertTuple({ 22, 0 });
			intResult.insertTuple({ 22, 2 });
			intResult.insertTuple({ 23, 1 });
			queryResult = patternObj.evaluate(&pkbStub, &intResult);

			Assert::AreEqual(2, queryResult->getSynCount());

			Assert::IsTrue(queryResult->isSynInTable(stmt));
			Assert::IsTrue(queryResult->isSynInTable(var));

			Assert::AreEqual(0, queryResult->getSynIndex(stmt));
			Assert::AreEqual(1, queryResult->getSynIndex(var));

			expectedResult = { { 6, 0 },{ 22, 0 } };
			sort(expectedResult.begin(), expectedResult.end());
			tupleResult = queryResult->getTupleList();
			sort(tupleResult.begin(), tupleResult.end());

			Assert::AreEqual(expectedResult.size(), tupleResult.size());
			Assert::IsTrue(expectedResult == tupleResult);
		}
	};
}
