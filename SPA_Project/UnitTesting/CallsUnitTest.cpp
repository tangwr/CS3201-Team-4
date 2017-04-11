#include "stdafx.h"
#include "CppUnitTest.h"

#include "CallsPKBStub.h"
#include "ResultTable.h"
#include "Parameter.h"
#include "Calls.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(CallsObjectTest)
	{
	public:
		TEST_METHOD(UnitTest_Calls_Proc_Proc)
		{
			CallsPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter proc1, proc2;
			vector<vector<int>> expectedResult, actualResult;
			string p1 = "p1", p2 = "p2";

			proc1 = Parameter(p1, PROCEDURE);
			proc2 = Parameter(p2, PROCEDURE);


			Calls callsClause(proc1, proc2);
			queryResult = callsClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 0,1 },{ 0,2 },{ 1,2 }};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Calls_Proc_Anything) {
			CallsPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter proc, anything;
			vector<vector<int>> expectedResult, actualResult;
			string p = "p", any = "_";

			proc = Parameter(p, PROCEDURE);
			anything = Parameter(any, ANYTHING);


			Calls callsClause(proc, anything);
			queryResult = callsClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 0},{ 1 } };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Calls_Proc_ProcName) {
			CallsPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter proc, procName;
			vector<vector<int>> expectedResult, actualResult;
			string p = "p", pN = "p";

			proc = Parameter(p, PROCEDURE);
			procName = Parameter(pN, STRINGVARIABLE);


			Calls callsClause(proc, procName);
			queryResult = callsClause.evaluate(&pkbStub, intResult);

			expectedResult = { {0} };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Calls_Anything_Proc) {
			CallsPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter anything, proc;
			vector<vector<int>> expectedResult, actualResult;
			string  any = "_", p = "p";

			anything = Parameter(any, ANYTHING);
			proc = Parameter(p, PROCEDURE);
			


			Calls callsClause(anything, proc);
			queryResult = callsClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1 },{ 2 } };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Calls_ProcName_Proc) {
			CallsPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter procName, proc;
			vector<vector<int>> expectedResult, actualResult;
			string pN = "p", p = "p";

			procName = Parameter(pN, STRINGVARIABLE);
			proc = Parameter(p, PROCEDURE);
			
			Calls callsClause(procName, proc);
			queryResult = callsClause.evaluate(&pkbStub, intResult);

			expectedResult = {{2}};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Calls_ProcName_ProcName) {
			CallsPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter procName1, procName2;
			vector<vector<int>> expectedResult, actualResult;
			string pN1 = "p", pN2 = "q";

			procName1 = Parameter(pN1, STRINGVARIABLE);
			procName2 = Parameter(pN2, STRINGVARIABLE);


			Calls callsClause(procName1, procName2);
			queryResult = callsClause.evaluate(&pkbStub, intResult);

			expectedResult = {};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Calls_Anything_Anything)
		{
			CallsPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter anything1, anything2;
			vector<vector<int>> expectedResult, actualResult;
			string any1 = "_", any2 = "_";

			anything1 = Parameter(any1, ANYTHING);
			anything2 = Parameter(any2, ANYTHING);


			Calls callsClause(anything1, anything2);
			queryResult = callsClause.evaluate(&pkbStub, intResult);

			expectedResult = { };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsTrue(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Calls_One_Restricted_List_Proc) {
			CallsPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter proc, anything;
			vector<vector<int>> expectedResult, actualResult;
			string p = "p", any = "_";

			proc = Parameter(p, PROCEDURE);
			anything = Parameter(any, ANYTHING);

			vector<Parameter> pList;
			pList.push_back(Parameter("p", PROCEDURE));
			intResult.setSynList(pList);

			intResult.insertTuple({ 1 });

			Calls callsClause(proc, anything);
			queryResult = callsClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1 } };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Calls_Two_Restricted_List_Proc_Proc) {
			CallsPKBStub pkbStub;

			ResultTable intResult, queryResult;
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
		

			Calls callsClause(proc1, proc2);
			queryResult = callsClause.evaluate(&pkbStub, intResult);

			expectedResult = { {1,2 } };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		
		TEST_METHOD(UnitTest_Calls_Invalid_Paramters) {
			CallsPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter procName1, procName2;
			vector<vector<int>> expectedResult, actualResult;
			string pN1 = "q", pN2 = "p1";

			procName1 = Parameter(pN1, STRINGVARIABLE);
			procName2 = Parameter(pN2, STRINGVARIABLE);


			Calls callsClause(procName1, procName2);
			queryResult = callsClause.evaluate(&pkbStub, intResult);

			expectedResult = {};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Calls_No_Results) {
			CallsPKBStub pkbStub;

			ResultTable intResult, queryResult;
			Parameter procName1, procName2;
			vector<vector<int>> expectedResult, actualResult;
			string pN1 = "q", pN2 = "p";

			procName1 = Parameter(pN1, STRINGVARIABLE);
			procName2 = Parameter(pN2, STRINGVARIABLE);


			Calls callsClause(procName1, procName2);
			queryResult = callsClause.evaluate(&pkbStub, intResult);

			expectedResult = {};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
	};
}