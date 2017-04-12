#include "stdafx.h"
#include "CppUnitTest.h"

#include "CallsStarPKBStub.h"
#include "ResultTable.h"
#include "Parameter.h"
#include "CallsStar.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(CallsStarObjectTest)
	{
	public:
		TEST_METHOD(UnitTest_CallsStar_Proc_Proc)
		{
			CallsStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter proc1, proc2;
			vector<vector<int>> expectedResult, actualResult;
			string p1 = "p1", p2 = "p2";

			proc1 = Parameter(p1, PROCEDURE);
			proc2 = Parameter(p2, PROCEDURE);


			CallsStar callsStarClause(proc1, proc2);
			queryResult = callsStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 0,1 },{ 0,2 },{ 1,2 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_CallsStar_Proc_Anything) {
			CallsStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter proc, anything;
			vector<vector<int>> expectedResult, actualResult;
			string p = "p", any = "_";

			proc = Parameter(p, PROCEDURE);
			anything = Parameter(any, ANYTHING);


			CallsStar callsStarClause(proc, anything);
			queryResult = callsStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 0 },{ 1 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_CallsStar_Proc_ProcName) {
			CallsStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter proc, procName;
			vector<vector<int>> expectedResult, actualResult;
			string p = "p", pN = "p";

			proc = Parameter(p, PROCEDURE);
			procName = Parameter(pN, STRINGVARIABLE);


			CallsStar callsStarClause(proc, procName);
			queryResult = callsStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 0 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_CallsStar_Anything_Proc) {
			CallsStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter anything, proc;
			vector<vector<int>> expectedResult, actualResult;
			string  any = "_", p = "p";

			anything = Parameter(any, ANYTHING);
			proc = Parameter(p, PROCEDURE);



			CallsStar callsStarClause(anything, proc);
			queryResult = callsStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 1 },{ 2 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_CallsStar_ProcName_Proc) {
			CallsStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter procName, proc;
			vector<vector<int>> expectedResult, actualResult;
			string pN = "p", p = "p";

			procName = Parameter(pN, STRINGVARIABLE);
			proc = Parameter(p, PROCEDURE);

			CallsStar callsStarClause(procName, proc);
			queryResult = callsStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 2 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_CallsStar_ProcName_ProcName) {
			CallsStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter procName1, procName2;
			vector<vector<int>> expectedResult, actualResult;
			string pN1 = "p", pN2 = "q";

			procName1 = Parameter(pN1, STRINGVARIABLE);
			procName2 = Parameter(pN2, STRINGVARIABLE);


			CallsStar callsStarClause(procName1, procName2);
			queryResult = callsStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = {};
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsTrue(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_CallsStar_Anything_Anything)
		{
			CallsStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter anything1, anything2;
			vector<vector<int>> expectedResult, actualResult;
			string any1 = "_", any2 = "_";

			anything1 = Parameter(any1, ANYTHING);
			anything2 = Parameter(any2, ANYTHING);


			CallsStar callsStarClause(anything1, anything2);
			queryResult = callsStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = {};
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsTrue(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_CallsStar_One_Restricted_List_Proc) {
			CallsStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter proc, anything;
			vector<vector<int>> expectedResult, actualResult;
			string p = "p", any = "_";

			proc = Parameter(p, PROCEDURE);
			anything = Parameter(any, ANYTHING);

			vector<Parameter> pList;
			pList.push_back(Parameter("p", PROCEDURE));
			intResult.setSynList(pList);

			intResult.insertTuple({ 1 });

			CallsStar callsStarClause(proc, anything);
			queryResult = callsStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 1 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_CallsStar_Two_Restricted_List_Proc_Proc) {
			CallsStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter proc1, proc2;
			vector<vector<int>> expectedResult, actualResult;
			string p1 = "p1", p2 = "p2";

			proc1 = Parameter(p1, PROCEDURE);
			proc2 = Parameter(p2, PROCEDURE);

			vector<Parameter> pList;
			pList.push_back(Parameter("p1", PROCEDURE));
			pList.push_back(Parameter("p2", PROCEDURE));
			intResult.setSynList(pList);

			intResult.insertTuple({ 1, 2 });


			CallsStar callsStarClause(proc1, proc2);
			queryResult = callsStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 1,2 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_CallsStar_Invalid_Paramters) {
			CallsStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter procName1, procName2;
			vector<vector<int>> expectedResult, actualResult;
			string pN1 = "q", pN2 = "p1";

			procName1 = Parameter(pN1, STRINGVARIABLE);
			procName2 = Parameter(pN2, STRINGVARIABLE);


			CallsStar callsStarClause(procName1, procName2);
			queryResult = callsStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = {};
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_CallsStar_No_Results) {
			CallsStarPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter procName1, procName2;
			vector<vector<int>> expectedResult, actualResult;
			string pN1 = "q", pN2 = "p";

			procName1 = Parameter(pN1, STRINGVARIABLE);
			procName2 = Parameter(pN2, STRINGVARIABLE);


			CallsStar callsStarClause(procName1, procName2);
			queryResult = callsStarClause.evaluate(&pkbStub, &intResult);

			expectedResult = {};
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
	};
}