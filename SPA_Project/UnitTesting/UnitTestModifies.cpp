#include "stdafx.h"
#include "CppUnitTest.h"

#include "PKBStubModifies.h"
#include "ResultTable.h"
#include "Parameter.h"
#include "Modifies.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(ModifiesObjectTest)
	{
	public:
		TEST_METHOD(UnitTest_Modifies_Stmt_Var)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt, var;
			vector<vector<int>> expectedResult, actualResult;
			string s = "s", v = "v";

			stmt = Parameter(s, STMT);
			var = Parameter(v, VARIABLE);


			Modifies modifiesClause(stmt, var);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);
			
			expectedResult = { {1,0}, {2,1},{3,2},{4,0}, {4,1}, {4,2}, {4,3}, {5,0}, {6,1}, {6,3},
								{7,1}, {8,3}, {9,1}, {10,0}, {10,1}, {11,2}, {12,0}, {12,1}, {12,2},
								{13,0}, {13,1}, {13,2}, {14,0}, {14,1}, {14,2}, {15,0}, {16,0}, {16,1},
								{17,2}, {18,0}, {19,1} ,{ 20,1 }, { 21,1 }, { 22,0 }, { 22,1 }, { 23,1 }, { 24,0 }};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			for (int i = 0; i < expectedResult.size(); i++) {
				vector<int> expectedTuple = expectedResult.at(i);
				vector<int> actualTuple = actualResult.at(i);

				Assert::AreEqual(expectedTuple.at(0), actualTuple.at(0));
				Assert::AreEqual(expectedTuple.at(1), actualTuple.at(1));
			}
			
			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
			Assert::AreEqual(s, queryResult.getSynList().at(0).getParaName());
			Assert::AreEqual(v, queryResult.getSynList().at(1).getParaName());
			Assert::IsTrue(STMT == queryResult.getSynList().at(0).getParaType());
			Assert::IsTrue(VARIABLE == queryResult.getSynList().at(1).getParaType());
			
		}
		TEST_METHOD(UnitTest_Modifies_Stmt_Anything)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt, anything;
			vector<vector<int>> expectedResult, actualResult;
			string s = "s", any = "_";

			stmt = Parameter(s, STMT);
			anything = Parameter(any, ANYTHING);


			Modifies modifiesClause(stmt, anything);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { {1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11},{12},
						{13},{14},{15},{16},{17},{18},{19},{20},{21},{22},{23}, {24} };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());
			
			for (int i = 0; i < expectedResult.size(); i++) {
				vector<int> expectedTuple = expectedResult.at(i);
				vector<int> actualTuple = actualResult.at(i);
				Assert::AreEqual(expectedTuple.at(0), actualTuple.at(0));
			}
			
			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
			Assert::AreEqual(s, queryResult.getSynList().at(0).getParaName());
			Assert::IsTrue(STMT == queryResult.getSynList().at(0).getParaType());
		}
		TEST_METHOD(UnitTest_Modifies_Stmt_StrVar)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt, stringVar;
			vector<vector<int>> expectedResult, actualResult;
			string s = "s", strVar = "x";

			stmt = Parameter(s, STMT);
			stringVar = Parameter(strVar, STRINGVARIABLE);


			Modifies modifiesClause(stmt, stringVar);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1 }, { 4 },{ 5 },{ 10 },{ 12 },{ 13 },{ 14 },{ 15 },{ 16 },{ 18 },{ 22 },{ 24 } };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());


			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
			Assert::AreEqual(s, queryResult.getSynList().at(0).getParaName());
			Assert::IsTrue(STMT == queryResult.getSynList().at(0).getParaType());
		}

		TEST_METHOD(UnitTest_Modifies_Assign_Var)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter assign, var;
			vector<vector<int>> expectedResult, actualResult;
			string a = "a", v = "v";

			assign = Parameter(a, ASSIGN);
			var = Parameter(v, VARIABLE);

			Modifies modifiesClause(assign, var);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1,0 },{ 2,1 },{ 3,2 },{ 5,0 },
			{ 7,1 },{ 8,3 },{ 9,1 },{ 11,2 },{ 15,0 },
			{ 17,2 },{ 18,0 },{ 19,1 } ,{ 20,1 },{ 21,1 },{ 23,1 },{ 24,0 } };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_Assign_Anything)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter assign, anything;
			vector<vector<int>> expectedResult, actualResult;
			string a = "a", any = "_";

			assign = Parameter(a, ASSIGN);
			anything = Parameter(any, ANYTHING);


			Modifies modifiesClause(assign, anything);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1 },{ 2 },{ 3 },{ 5 },{ 7 },{ 8 },{ 9 },{ 11 },
			{ 15 },{ 17 },{ 18 },{ 19 },{ 20 },{ 21 },{ 23 },{ 24 } };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_Assign_StrVar)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter assign, stringVar;
			vector<vector<int>> expectedResult, actualResult;
			string a = "a", strVar = "x";

			assign = Parameter(a, ASSIGN);
			stringVar = Parameter(strVar, STRINGVARIABLE);


			Modifies modifiesClause(assign, stringVar);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1 },{ 5 },{ 15 },{ 18 },{ 24 } };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Modifies_While_Var)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter whiles, var;
			vector<vector<int>> expectedResult, actualResult;
			string w = "w", v = "v";

			whiles = Parameter(w, WHILE);
			var = Parameter(v, VARIABLE);

			Modifies modifiesClause(whiles, var);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 4,0 },{ 4,1 },{ 4,2 },{ 4,3 },{ 14,0 },{ 14,1 },{ 14,2 }};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_While_Anything)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter whiles, anything;
			vector<vector<int>> expectedResult, actualResult;
			string w = "w", any = "_";

			whiles = Parameter(w, WHILE);
			anything = Parameter(any, ANYTHING);


			Modifies modifiesClause(whiles, anything);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 4 },{ 14 }};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			for (int i = 0; i < expectedResult.size(); i++) {
				vector<int> expectedTuple = expectedResult.at(i);
				vector<int> actualTuple = actualResult.at(i);
				Assert::AreEqual(expectedTuple.at(0), actualTuple.at(0));
			}

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_While_StrVar)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter whiles, stringVar;
			vector<vector<int>> expectedResult, actualResult;
			string w = "w", strVar = "x";

			whiles = Parameter(w, WHILE);
			stringVar = Parameter(strVar, STRINGVARIABLE);

			Modifies modifiesClause(whiles, stringVar);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 4 },{ 14 } };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Modifies_If_Var)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter ifs, var;
			vector<vector<int>> expectedResult, actualResult;
			string i = "i", v = "v";

			ifs = Parameter(i, IF);
			var = Parameter(v, VARIABLE);

			Modifies modifiesClause(ifs, var);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { {6,1}, {6,3}, { 13,0 },{ 13,1 },{ 13,2 },{ 22,0 },{ 22,1 }};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_If_Anything)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter ifs, anything;
			vector<vector<int>> expectedResult, actualResult;
			string i = "i", any = "_";

			ifs = Parameter(i, IF);
			anything = Parameter(any, ANYTHING);


			Modifies modifiesClause(ifs, anything);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 6 },{ 13 }, {22 } };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			for (int i = 0; i < expectedResult.size(); i++) {
				vector<int> expectedTuple = expectedResult.at(i);
				vector<int> actualTuple = actualResult.at(i);
				Assert::AreEqual(expectedTuple.at(0), actualTuple.at(0));
			}

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_If_StrVar)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter ifs, stringVar;
			vector<vector<int>> expectedResult, actualResult;
			string i = "i", strVar = "x";

			ifs = Parameter(i, IF);
			stringVar = Parameter(strVar, STRINGVARIABLE);

			Modifies modifiesClause(ifs, stringVar);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 13 },{ 22 } };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Modifies_Call_Var)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter call, var;
			vector<vector<int>> expectedResult, actualResult;
			string c = "c", v = "v";

			call = Parameter(c, CALL);
			var = Parameter(v, VARIABLE);

			Modifies modifiesClause(call, var);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 10,0 },{ 10,1 },{ 12,0 },{ 12,1 },{ 12,2 },{ 16,0 },{ 16,1 }};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_Call_Anything)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter call, anything;
			vector<vector<int>> expectedResult, actualResult;
			string c = "c", any = "_";

			call = Parameter(c, CALL);
			anything = Parameter(any, ANYTHING);


			Modifies modifiesClause(call, anything);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { {10}, {12}, {16} };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			for (int i = 0; i < expectedResult.size(); i++) {
				vector<int> expectedTuple = expectedResult.at(i);
				vector<int> actualTuple = actualResult.at(i);
				Assert::AreEqual(expectedTuple.at(0), actualTuple.at(0));
			}

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_Call_StrVar)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter call, stringVar;
			vector<vector<int>> expectedResult, actualResult;
			string c = "c", strVar = "i";

			call = Parameter(c, CALL);
			stringVar = Parameter(strVar, STRINGVARIABLE);


			Modifies modifiesClause(call, stringVar);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 12 } };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());


			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Modifies_ProgLine_Var)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter prog_line, var;
			vector<vector<int>> expectedResult, actualResult;
			string n = "n", v = "v";

			prog_line = Parameter(n, PROG_LINE);
			var = Parameter(v, VARIABLE);


			Modifies modifiesClause(prog_line, var);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1,0 },{ 2,1 },{ 3,2 },{ 4,0 },{ 4,1 },{ 4,2 },{ 4,3 },{ 5,0 },{ 6,1 },{ 6,3 },
			{ 7,1 },{ 8,3 },{ 9,1 },{ 10,0 },{ 10,1 },{ 11,2 },{ 12,0 },{ 12,1 },{ 12,2 },
			{ 13,0 },{ 13,1 },{ 13,2 },{ 14,0 },{ 14,1 },{ 14,2 },{ 15,0 },{ 16,0 },{ 16,1 },
			{ 17,2 },{ 18,0 },{ 19,1 } ,{ 20,1 },{ 21,1 },{ 22,0 },{ 22,1 },{ 23,1 },{ 24,0 } };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_ProgLine_Anything)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter prog_line, anything;
			vector<vector<int>> expectedResult, actualResult;
			string n = "n", any = "_";

			prog_line = Parameter(n, PROG_LINE);
			anything = Parameter(any, ANYTHING);


			Modifies modifiesClause(prog_line, anything);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1 },{ 2 },{ 3 },{ 4 },{ 5 },{ 6 },{ 7 },{ 8 },{ 9 },{ 10 },{ 11 },{ 12 },
			{ 13 },{ 14 },{ 15 },{ 16 },{ 17 },{ 18 },{ 19 },{ 20 },{ 21 },{ 22 },{ 23 },{ 24 } };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			for (int i = 0; i < expectedResult.size(); i++) {
				vector<int> expectedTuple = expectedResult.at(i);
				vector<int> actualTuple = actualResult.at(i);
				Assert::AreEqual(expectedTuple.at(0), actualTuple.at(0));
			}

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_ProgLine_StrVar)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter prog_line, stringVar;
			vector<vector<int>> expectedResult, actualResult;
			string n = "n", strVar = "y";

			prog_line = Parameter(n, PROG_LINE);
			stringVar = Parameter(strVar, STRINGVARIABLE);


			Modifies modifiesClause(prog_line, stringVar);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = {{ 4 },{ 6 },{ 8 }};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());


			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Modifies_Proc_Var)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter proc, var;
			vector<vector<int>> expectedResult, actualResult;
			string p = "p", v = "v";

			proc = Parameter(p, PROCEDURE);
			var = Parameter(v, VARIABLE);


			Modifies modifiesClause(proc, var);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { {0,0}, {0,1}, {0,2}, {0,3}, {1,0}, {1,1}, {1,2}, {2,0},{2,1} };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_Proc_Anything)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter proc, anything;
			vector<vector<int>> expectedResult, actualResult;
			string p = "p", any = "v";

			proc = Parameter(p, PROCEDURE);
			anything = Parameter(any, ANYTHING);


			Modifies modifiesClause(proc, anything);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { {0}, {1}, {2} };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_Proc_StrVar)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter proc, stringVar;
			vector<vector<int>> expectedResult, actualResult;
			string p = "p", strVar = "i";

			proc = Parameter(p, PROCEDURE);
			stringVar = Parameter(strVar, STRINGVARIABLE);

			Modifies modifiesClause(proc, stringVar);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 0 },{ 1 }};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Modifies_StmtNum_Var)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmtNum, var;
			vector<vector<int>> expectedResult, actualResult;
			string sn = "13", v = "v";

			stmtNum = Parameter(sn, INTEGER);
			var = Parameter(v, VARIABLE);

			Modifies modifiesClause(stmtNum, var);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { {0},{ 1 },{ 2 } };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_StmtNum_Anything)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmtNum, anything;
			vector<vector<int>> expectedResult, actualResult;
			string sn = "13", any = "_";

			stmtNum = Parameter(sn, INTEGER);
			anything = Parameter(any, ANYTHING);

			Modifies modifiesClause(stmtNum, anything);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = {};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsTrue(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_StmtNum_StrVar)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmtNum, stringVar;
			vector<vector<int>> expectedResult, actualResult;
			string sn = "13", strVar = "y";

			stmtNum = Parameter(sn, INTEGER);
			stringVar = Parameter(strVar, STRINGVARIABLE);

			Modifies modifiesClause(stmtNum, stringVar);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = {};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Modifies_ProcName_Var)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter procName, var;
			vector<vector<int>> expectedResult, actualResult;
			string pn = "p", v = "v";

			procName = Parameter(pn, STRINGVARIABLE);
			var = Parameter(v, VARIABLE);

			Modifies modifiesClause(procName, var);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 0 },{ 1 },{ 2 } };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_ProcName_Anything)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter procName, anything;
			vector<vector<int>> expectedResult, actualResult;
			string pn = "q", any = "_";

			procName = Parameter(pn, STRINGVARIABLE);
			anything = Parameter(any, ANYTHING);

			Modifies modifiesClause(procName, anything);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = {};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsTrue(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_ProcName_StrVar)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter procName, stringVar;
			vector<vector<int>> expectedResult, actualResult;
			string pn = "y", strVar = "y";

			procName = Parameter(pn, STRINGVARIABLE);
			stringVar = Parameter(strVar, STRINGVARIABLE);

			Modifies modifiesClause(procName, stringVar);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = {};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Modifies_Invalid_Paramters) {
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter procName, stringVar;
			vector<vector<int>> expectedResult, actualResult;
			string pn = "p1", strVar = "y";

			procName = Parameter(pn, STRINGVARIABLE);
			stringVar = Parameter(strVar, STRINGVARIABLE);

			Modifies modifiesClause(procName, stringVar);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = {};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Modifies_Two_Restricted_List_Stmt_Variable)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter stmt, var;
			vector<vector<int>> expectedResult, actualResult;
			string s = "n", v = "v";

			stmt = Parameter(s, STMT);
			var = Parameter(v, VARIABLE);

			vector<Parameter> pList;
			pList.push_back(Parameter("s", STMT));
			pList.push_back(Parameter("v", VARIABLE));
			intResult.setSynList(pList);

			intResult.insertTuple({ 1,0 });
			intResult.insertTuple({ 2, 1 });
			intResult.insertTuple({ 3, 2 });
			
			Modifies modifiesClause(stmt, var);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1,0 },{ 2,1 },{ 3,2 }};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_Two_Restricted_List_Stmt_Procedure)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
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

			Modifies modifiesClause(proc, var);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 0,0 },{ 0,1 },{ 0,2 }};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}

		TEST_METHOD(UnitTest_Modifies_One_Restricted_List_Assign)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter assign, anything;
			vector<vector<int>> expectedResult, actualResult;
			string a = "a", any = "_";

			assign = Parameter(a, ASSIGN);
			anything = Parameter(any, ANYTHING);

			vector<Parameter> pList;
			pList.push_back(Parameter("a", ASSIGN));
			intResult.setSynList(pList);

			intResult.insertTuple({ 1});
			intResult.insertTuple({ 2 });
			intResult.insertTuple({ 3});


			Modifies modifiesClause(assign, anything);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 1 },{ 2 },{ 3 }};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_One_Restricted_List_While)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
			Parameter whiles, anything;
			vector<vector<int>> expectedResult, actualResult;
			string w = "w", any = "_";

			whiles = Parameter(w, WHILE);
			anything = Parameter(any, ANYTHING);

			vector<Parameter> pList;
			pList.push_back(Parameter("w", WHILE));
			intResult.setSynList(pList);

			intResult.insertTuple({ 4 });

			Modifies modifiesClause(whiles, anything);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 4 }};
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			for (int i = 0; i < expectedResult.size(); i++) {
				vector<int> expectedTuple = expectedResult.at(i);
				vector<int> actualTuple = actualResult.at(i);
				Assert::AreEqual(expectedTuple.at(0), actualTuple.at(0));
			}

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_One_Restricted_List_If)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
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

			Modifies modifiesClause(ifs, anything);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 13 },{ 22 } };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			for (int i = 0; i < expectedResult.size(); i++) {
				vector<int> expectedTuple = expectedResult.at(i);
				vector<int> actualTuple = actualResult.at(i);
				Assert::AreEqual(expectedTuple.at(0), actualTuple.at(0));
			}

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_One_Restricted_List_Call)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
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

			Modifies modifiesClause(call, anything);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 10 },{ 16 } };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			for (int i = 0; i < expectedResult.size(); i++) {
				vector<int> expectedTuple = expectedResult.at(i);
				vector<int> actualTuple = actualResult.at(i);
				Assert::AreEqual(expectedTuple.at(0), actualTuple.at(0));
			}

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
		TEST_METHOD(UnitTest_Modifies_One_Restricted_List_Procedure)
		{
			PKBStubModifies pkbStub;

			ResultTable intResult, queryResult;
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

			Modifies modifiesClause(proc, anything);
			queryResult = modifiesClause.evaluate(&pkbStub, intResult);

			expectedResult = { { 0 },{ 2 } };
			actualResult = queryResult.getTupleList();

			sort(expectedResult.begin(), expectedResult.end());
			sort(actualResult.begin(), actualResult.end());

			Assert::AreEqual(expectedResult.size(), actualResult.size());
			Assert::IsTrue(expectedResult == actualResult);
			Assert::IsFalse(queryResult.getBoolean());
		}
	};
}
