#include "stdafx.h"
#include "CppUnitTest.h"

#include "UsesPKBStub.h"
#include "ResultTable.h"
#include "Parameter.h"
#include "Uses.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(UsesObjectTest)
	{
	public:
		TEST_METHOD(UnitTest_Uses_Stmt_Var)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt, var;
			vector<vector<int>> expectedResult, actualResult;
			string s = "s", v = "v";

			stmt = Parameter(s, STMT);
			var = Parameter(v, VARIABLE);


			Uses usesClause(stmt, var);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 4,0 },{ 4,1 },{ 4,2 },{ 5,0 }, {6,0}, { 6,1 },
			{ 7,0 },{8,0}, { 8,1 },{9,0},{9,1}, { 9,2 },{ 10,0 },{ 10,1 },{ 11,2 },{ 12,0 },{ 12,1 },{ 12,2 },{12,3},
			{ 13,0 },{ 13,1 },{ 13,2 },{13,3}, { 14,1 },{ 14,2 },{ 14,3 },{ 15,1 },{15,3}, { 16,0 },{ 16,1 },
			{ 17,2 },{ 18,0 },{19,0}, { 19,1 } ,{ 21,0 },{ 21,1 },{21,2}, { 22,0 },{ 22,1 },{ 23,0 },{ 24,0 }, {24,1} };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		
		}
		TEST_METHOD(UnitTest_Uses_Stmt_Anything)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt, anything;
			vector<vector<int>> expectedResult, actualResult;
			string s = "s", any = "_";

			stmt = Parameter(s, STMT);
			anything = Parameter(any, ANYTHING);


			Uses usesClause(stmt, anything);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 4 },{ 5 },{ 6 },{ 7 },{ 8 },{ 9 },{ 10 },{ 11 },{ 12 },
			{ 13 },{ 14 },{ 15 },{ 16 },{ 17 },{ 18 },{ 19 },{ 21 },{ 22 },{ 23 },{ 24 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			for (int i = 0; i < expectedResult.size(); i++) {
				vector<int> expectedTuple = expectedResult.at(i);
				vector<int> actualTuple = actualResult.at(i);
				Assert::AreEqual(expectedTuple.at(0), actualTuple.at(0));
			}

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_Stmt_StrVar)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt, stringVar;
			vector<vector<int>> expectedResult, actualResult;
			string s = "s", strVar = "x";

			stmt = Parameter(s, STMT);
			stringVar = Parameter(strVar, STRINGVARIABLE);


			Uses usesClause(stmt, stringVar);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 4 },{ 5 },{6},{7}, {8},{9}, { 10 },{ 12 },{ 13 },{ 14 },{ 16 },{ 18 },{19},{21}, { 22 },{23}, { 24 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());


			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_Uses_Assign_Var)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter assign, var;
			vector<vector<int>> expectedResult, actualResult;
			string a = "a", v = "v";

			assign = Parameter(a, ASSIGN);
			var = Parameter(v, VARIABLE);

			Uses usesClause(assign, var);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 5,0 },{ 7,0 },{ 8,0 },{ 8,1 },{ 9,0 },{ 9,1 },{ 9,2 },{ 11,2 },
			{ 15,1 },{ 15,3 },{ 17,2 },{ 18,0 },{ 19,0 },{ 19,1 } ,{ 21,0 },{ 21,1 },{ 21,2 },{ 23,0 },{ 24,0 },{ 24,1 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_Assign_Anything)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter assign, anything;
			vector<vector<int>> expectedResult, actualResult;
			string a = "a", any = "_";

			assign = Parameter(a, ASSIGN);
			anything = Parameter(any, ANYTHING);


			Uses usesClause(assign, anything);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 5 },{ 7 },{ 8 },{ 9 },{ 11 },{ 15 },{ 17 },{ 18 },
			{ 19 },{ 21 },{ 23 },{ 24 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_Assign_StrVar)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter assign, stringVar;
			vector<vector<int>> expectedResult, actualResult;
			string a = "a", strVar = "x";

			assign = Parameter(a, ASSIGN);
			stringVar = Parameter(strVar, STRINGVARIABLE);


			Uses usesClause(assign, stringVar);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 5 },{ 7 },{8}, {9}, {18}, { 19 },{ 21 },{23}, { 24 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_Uses_While_Var)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter whiles, var;
			vector<vector<int>> expectedResult, actualResult;
			string w = "w", v = "v";

			whiles = Parameter(w, WHILE);
			var = Parameter(v, VARIABLE);

			Uses usesClause(whiles, var);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 4,0 },{ 4,1 },{ 4,2 },{ 14,1},{ 14,2 },{ 14,3 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_While_Anything)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter whiles, anything;
			vector<vector<int>> expectedResult, actualResult;
			string w = "w", any = "_";

			whiles = Parameter(w, WHILE);
			anything = Parameter(any, ANYTHING);


			Uses usesClause(whiles, anything);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 4 },{ 14 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			for (int i = 0; i < expectedResult.size(); i++) {
				vector<int> expectedTuple = expectedResult.at(i);
				vector<int> actualTuple = actualResult.at(i);
				Assert::AreEqual(expectedTuple.at(0), actualTuple.at(0));
			}

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_While_StrVar)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter whiles, stringVar;
			vector<vector<int>> expectedResult, actualResult;
			string w = "w", strVar = "x";

			whiles = Parameter(w, WHILE);
			stringVar = Parameter(strVar, STRINGVARIABLE);

			Uses usesClause(whiles, stringVar);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 4 },{ 14 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_Uses_If_Var)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter ifs, var;
			vector<vector<int>> expectedResult, actualResult;
			string i = "i", v = "v";

			ifs = Parameter(i, IF);
			var = Parameter(v, VARIABLE);

			Uses usesClause(ifs, var);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 6,0 },{ 6,1 },{ 13,0 },{ 13,1 },{ 13,2 },{13,3}, { 22,0 },{ 22,1 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_If_Anything)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter ifs, anything;
			vector<vector<int>> expectedResult, actualResult;
			string i = "i", any = "_";

			ifs = Parameter(i, IF);
			anything = Parameter(any, ANYTHING);


			Uses usesClause(ifs, anything);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 6 },{ 13 },{ 22 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			for (int i = 0; i < expectedResult.size(); i++) {
				vector<int> expectedTuple = expectedResult.at(i);
				vector<int> actualTuple = actualResult.at(i);
				Assert::AreEqual(expectedTuple.at(0), actualTuple.at(0));
			}

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_If_StrVar)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter ifs, stringVar;
			vector<vector<int>> expectedResult, actualResult;
			string i = "i", strVar = "x";

			ifs = Parameter(i, IF);
			stringVar = Parameter(strVar, STRINGVARIABLE);

			Uses usesClause(ifs, stringVar);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { {6}, { 13 },{ 22 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_Uses_Call_Var)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter call, var;
			vector<vector<int>> expectedResult, actualResult;
			string c = "c", v = "v";

			call = Parameter(c, CALL);
			var = Parameter(v, VARIABLE);

			Uses usesClause(call, var);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 10,0 },{ 10,1 },{ 12,0 },{ 12,1 },{ 12,2 },{12,3}, { 16,0 },{ 16,1 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_Call_Anything)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter call, anything;
			vector<vector<int>> expectedResult, actualResult;
			string c = "c", any = "_";

			call = Parameter(c, CALL);
			anything = Parameter(any, ANYTHING);


			Uses usesClause(call, anything);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 10 },{ 12 },{ 16 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			for (int i = 0; i < expectedResult.size(); i++) {
				vector<int> expectedTuple = expectedResult.at(i);
				vector<int> actualTuple = actualResult.at(i);
				Assert::AreEqual(expectedTuple.at(0), actualTuple.at(0));
			}

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_Call_StrVar)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter call, stringVar;
			vector<vector<int>> expectedResult, actualResult;
			string c = "c", strVar = "i";

			call = Parameter(c, CALL);
			stringVar = Parameter(strVar, STRINGVARIABLE);


			Uses usesClause(call, stringVar);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 12 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());


			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_Uses_ProgLine_Var)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter prog_line, var;
			vector<vector<int>> expectedResult, actualResult;
			string n = "n", v = "v";

			prog_line = Parameter(n, PROG_LINE);
			var = Parameter(v, VARIABLE);


			Uses usesClause(prog_line, var);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 4,0 },{ 4,1 },{ 4,2 },{ 5,0 },{ 6,0 },{ 6,1 },
			{ 7,0 },{ 8,0 },{ 8,1 },{ 9,0 },{ 9,1 },{ 9,2 },{ 10,0 },{ 10,1 },{ 11,2 },{ 12,0 },{ 12,1 },{ 12,2 },{ 12,3 },
			{ 13,0 },{ 13,1 },{ 13,2 },{ 13,3 },{ 14,1 },{ 14,2 },{ 14,3 },{ 15,1 },{ 15,3 },{ 16,0 },{ 16,1 },
			{ 17,2 },{ 18,0 },{ 19,0 },{ 19,1 } ,{ 21,0 },{ 21,1 },{ 21,2 },{ 22,0 },{ 22,1 },{ 23,0 },{ 24,0 },{ 24,1 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_ProgLine_Anything)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter prog_line, anything;
			vector<vector<int>> expectedResult, actualResult;
			string n = "n", any = "_";

			prog_line = Parameter(n, PROG_LINE);
			anything = Parameter(any, ANYTHING);


			Uses usesClause(prog_line, anything);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 4 },{ 5 },{ 6 },{ 7 },{ 8 },{ 9 },{ 10 },{ 11 },{ 12 },
			{ 13 },{ 14 },{ 15 },{ 16 },{ 17 },{ 18 },{ 19 },{ 21 },{ 22 },{ 23 },{ 24 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			for (int i = 0; i < expectedResult.size(); i++) {
				vector<int> expectedTuple = expectedResult.at(i);
				vector<int> actualTuple = actualResult.at(i);
				Assert::AreEqual(expectedTuple.at(0), actualTuple.at(0));
			}

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_ProgLine_StrVar)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter prog_line, stringVar;
			vector<vector<int>> expectedResult, actualResult;
			string n = "n", strVar = "y";

			prog_line = Parameter(n, PROG_LINE);
			stringVar = Parameter(strVar, STRINGVARIABLE);


			Uses usesClause(prog_line, stringVar);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 12 },{ 13 },{ 14 },{ 15 }};
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());


			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_Uses_Proc_Var)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter proc, var;
			vector<vector<int>> expectedResult, actualResult;
			string p = "p", v = "v";

			proc = Parameter(p, PROCEDURE);
			var = Parameter(v, VARIABLE);


			Uses usesClause(proc, var);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 0,0 },{ 0,1 },{ 0,2 },{ 0,3 },{ 1,0 },{ 1,1 },{ 1,2 },{1,3}, { 2,0 },{ 2,1 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_Proc_Anything)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter proc, anything;
			vector<vector<int>> expectedResult, actualResult;
			string p = "p", any = "v";

			proc = Parameter(p, PROCEDURE);
			anything = Parameter(any, ANYTHING);


			Uses usesClause(proc, anything);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 0 },{ 1 },{ 2 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_Proc_StrVar)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter proc, stringVar;
			vector<vector<int>> expectedResult, actualResult;
			string p = "p", strVar = "i";

			proc = Parameter(p, PROCEDURE);
			stringVar = Parameter(strVar, STRINGVARIABLE);

			Uses usesClause(proc, stringVar);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 0 },{ 1 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_Uses_StmtNum_Var)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmtNum, var;
			vector<vector<int>> expectedResult, actualResult;
			string sn = "13", v = "v";

			stmtNum = Parameter(sn, INTEGER);
			var = Parameter(v, VARIABLE);

			Uses usesClause(stmtNum, var);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 0 },{ 1 },{ 2 } ,{3} };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_StmtNum_Anything)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmtNum, anything;
			vector<vector<int>> expectedResult, actualResult;
			string sn = "13", any = "_";

			stmtNum = Parameter(sn, INTEGER);
			anything = Parameter(any, ANYTHING);

			Uses usesClause(stmtNum, anything);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = {};
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsTrue(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_StmtNum_StrVar)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmtNum, stringVar;
			vector<vector<int>> expectedResult, actualResult;
			string sn = "13", strVar = "y";

			stmtNum = Parameter(sn, INTEGER);
			stringVar = Parameter(strVar, STRINGVARIABLE);

			Uses usesClause(stmtNum, stringVar);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = {};
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsTrue(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_Uses_ProcName_Var)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter procName, var;
			vector<vector<int>> expectedResult, actualResult;
			string pn = "p", v = "v";

			procName = Parameter(pn, STRINGVARIABLE);
			var = Parameter(v, VARIABLE);

			Uses usesClause(procName, var);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 0 },{ 1 },{ 2 }, {3} };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_ProcName_Anything)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter procName, anything;
			vector<vector<int>> expectedResult, actualResult;
			string pn = "q", any = "_";

			procName = Parameter(pn, STRINGVARIABLE);
			anything = Parameter(any, ANYTHING);

			Uses usesClause(procName, anything);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = {};
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsTrue(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_ProcName_StrVar)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter procName, stringVar;
			vector<vector<int>> expectedResult, actualResult;
			string pn = "y", strVar = "y";

			procName = Parameter(pn, STRINGVARIABLE);
			stringVar = Parameter(strVar, STRINGVARIABLE);

			Uses usesClause(procName, stringVar);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = {};
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_Uses_Invalid_Paramters) {
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter procName, stringVar;
			vector<vector<int>> expectedResult, actualResult;
			string pn = "p1", strVar = "y";

			procName = Parameter(pn, STRINGVARIABLE);
			stringVar = Parameter(strVar, STRINGVARIABLE);

			Uses usesClause(procName, stringVar);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = {};
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_Uses_Two_Restricted_List_Stmt_Variable)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter stmt, var;
			vector<vector<int>> expectedResult, actualResult;
			string s = "n", v = "v";

			stmt = Parameter(s, STMT);
			var = Parameter(v, VARIABLE);

			vector<Parameter> pList;
			pList.push_back(Parameter("s", STMT));
			pList.push_back(Parameter("v", VARIABLE));
			intResult.setSynList(pList);

			intResult.insertTuple({ 22,0 });
			intResult.insertTuple({ 23, 0 });
			intResult.insertTuple({ 24, 0 });
			intResult.insertTuple({ 24, 1 });

			Uses usesClause(stmt, var);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 22,0 },{22,1}, { 23,0 },{ 24,0 }, {24,1} };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_Two_Restricted_List_Stmt_Procedure)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter proc, var;
			vector<vector<int>> expectedResult, actualResult;
			string p = "p", v = "v";

			proc = Parameter(p, PROCEDURE);
			var = Parameter(v, VARIABLE);

			vector<Parameter> pList;
			pList.push_back(Parameter("p", PROCEDURE));
			pList.push_back(Parameter("v", VARIABLE));
			intResult.setSynList(pList);

			intResult.insertTuple({ 0,0 });
			intResult.insertTuple({ 0, 1 });
			intResult.insertTuple({ 0, 2 });

			Uses usesClause(proc, var);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 0,0 },{ 0,1 },{ 0,2 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}

		TEST_METHOD(UnitTest_Uses_One_Restricted_List_Assign)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter assign, anything;
			vector<vector<int>> expectedResult, actualResult;
			string a = "a", any = "_";

			assign = Parameter(a, ASSIGN);
			anything = Parameter(any, ANYTHING);

			vector<Parameter> pList;
			pList.push_back(Parameter("a", ASSIGN));
			intResult.setSynList(pList);

			intResult.insertTuple({ 7 });
			intResult.insertTuple({ 8 });


			Uses usesClause(assign, anything);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 7},{ 8 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_One_Restricted_List_While)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter whiles, anything;
			vector<vector<int>> expectedResult, actualResult;
			string w = "w", any = "_";

			whiles = Parameter(w, WHILE);
			anything = Parameter(any, ANYTHING);

			vector<Parameter> pList;
			pList.push_back(Parameter("w", WHILE));
			intResult.setSynList(pList);

			intResult.insertTuple({ 4 });

			Uses usesClause(whiles, anything);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 4 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			for (int i = 0; i < expectedResult.size(); i++) {
				vector<int> expectedTuple = expectedResult.at(i);
				vector<int> actualTuple = actualResult.at(i);
				Assert::AreEqual(expectedTuple.at(0), actualTuple.at(0));
			}

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_One_Restricted_List_If)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter ifs, anything;
			vector<vector<int>> expectedResult, actualResult;
			string i = "i", any = "_";

			ifs = Parameter(i, IF);
			anything = Parameter(any, ANYTHING);

			vector<Parameter> pList;
			pList.push_back(Parameter("i", IF));
			intResult.setSynList(pList);

			intResult.insertTuple({ 13 });
			intResult.insertTuple({ 22 });

			Uses usesClause(ifs, anything);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 13 },{ 22 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			for (int i = 0; i < expectedResult.size(); i++) {
				vector<int> expectedTuple = expectedResult.at(i);
				vector<int> actualTuple = actualResult.at(i);
				Assert::AreEqual(expectedTuple.at(0), actualTuple.at(0));
			}

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_One_Restricted_List_Call)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter call, anything;
			vector<vector<int>> expectedResult, actualResult;
			string c = "c", any = "_";

			call = Parameter(c, CALL);
			anything = Parameter(any, ANYTHING);

			vector<Parameter> pList;
			pList.push_back(Parameter("c", CALL));
			intResult.setSynList(pList);

			intResult.insertTuple({ 10 });
			intResult.insertTuple({ 16 });

			Uses usesClause(call, anything);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 10 },{ 16 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			for (int i = 0; i < expectedResult.size(); i++) {
				vector<int> expectedTuple = expectedResult.at(i);
				vector<int> actualTuple = actualResult.at(i);
				Assert::AreEqual(expectedTuple.at(0), actualTuple.at(0));
			}

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
		TEST_METHOD(UnitTest_Uses_One_Restricted_List_Procedure)
		{
			UsesPKBStub pkbStub;

			ResultTable intResult, *queryResult;
			Parameter proc, anything;
			vector<vector<int>> expectedResult, actualResult;
			string p = "p", any = "v";

			proc = Parameter(p, PROCEDURE);
			anything = Parameter(any, ANYTHING);

			vector<Parameter> pList;
			pList.push_back(Parameter("p", PROCEDURE));
			intResult.setSynList(pList);

			intResult.insertTuple({ 0 });
			intResult.insertTuple({ 2 });

			Uses usesClause(proc, anything);
			queryResult = usesClause.evaluate(&pkbStub, &intResult);

			expectedResult = { { 0 },{ 2 } };
			actualResult = queryResult->getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult->getBoolean());
		}
	};
}
