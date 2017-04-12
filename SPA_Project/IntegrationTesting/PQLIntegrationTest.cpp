#include "stdafx.h"
#include "CppUnitTest.h"
#include "PQLStub.h"
#include "PKBStub.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace IntegrationTesting
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(IntegrationTest_Evaluate_Select_Type_No_Clauses)
		{
			string declaration = "stmt s; assign a; while w; if i; call c; prog_line n; stmtLst sl; procedure p; variable v; constant ct; ";
			//Select all stmt
			string query = declaration + "Select s";
			PKBStub pkbStub;
			PQLStub pql(&pkbStub);
			list<string> actualResult;
			list<string> expectedResult;

			actualResult = pql.evaluateQuery(query);


			for (int i = 1; i < 25; i++) {
				expectedResult.push_back(to_string(i));
			}
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			//Select all assign stmt
			query = declaration + "Select a";
			expectedResult = { "1","2","3","5", "7", "8","9","11", "15", "17", "18", "19", "20", "21", "23", "24" };
			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			//Select all while stmt
			query = declaration + "Select w";
			expectedResult = { "4","14" };
			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			//Select all if stmt
			query = declaration + "Select i";
			expectedResult = { "6","13", "22" };
			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			//Select all call stmt
			query = declaration + "Select c";
			expectedResult = { "10", "12", "16" };
			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			// Select all prog_line stmt
			query = declaration + "Select n";
			expectedResult = {};
			for (int i = 1; i < 25; i++) {
				expectedResult.push_back(to_string(i));
			}
			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			// Select all  stmtLst
			query = declaration + "Select sl";
			expectedResult = { "1", "13", "22" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			// Select all procedure
			query = declaration + "Select p";
			expectedResult = { "Example", "p", "q" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			// Select all variable
			query = declaration + "Select v";
			expectedResult = { "x", "z", "y", "i" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			// Select all variable
			query = declaration + "Select ct";
			expectedResult = { "1", "2", "3", "5" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);



		}

		TEST_METHOD(IntegrationTest_Evaluate_Select_Tuple)
		{
			string declaration = "stmt s; assign a; while w; if i; call c; prog_line n; stmtLst sl; procedure p; variable v; constant ct;";
			//Select tuple stmtlst & variable
			string query = declaration + "Select <sl,v>";
			PKBStub pkbStub;
			PQLStub pql(&pkbStub);
			list<string> actualResult;
			list<string> expectedResult;

			actualResult = pql.evaluateQuery(query);

			expectedResult = { "1 x", "1 z", "1 y", "1 i", "13 x", "13 z", "13 y", "13 i", "22 x", "22 z", "22 y", "22 i" };
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			// Select tuple procdure,while, call with procName = "q"
			query = declaration + "Select <p.procName,w.stmt#,c.stmt#> with p.procName=\"q\" with 1=1";

			expectedResult = { "q 4 10", "q 4 12", "q 4 16", "q 14 10", "q 14 12", "q 14 16" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			// Select tuple procdure,while, call with procName = "q"
			query = declaration + "Select <p,w,c> with p.procName=\"q\" with 1=1";

			expectedResult = { "q 4 10", "q 4 12", "q 4 16", "q 14 10", "q 14 12", "q 14 16" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			// Select v.varanme
			query = declaration + "Select <v.varName>";

			expectedResult = { "x", "z", "y", "i" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			// Select ct.value
			query = declaration + "Select <ct.value>";

			expectedResult = { "1", "2", "3", "5" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			// Select v.varName
			query = declaration + "Select v.varName";

			expectedResult = { "x", "z", "y", "i" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			// Select p.procName
			query = declaration + "Select p.procName";

			expectedResult = { "Example", "p", "q" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			// Select ct.value
			query = declaration + "Select ct.value";

			expectedResult = { "1", "2", "3", "5" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			// Select i.stmt#
			query = declaration + "Select i.stmt#";

			expectedResult = { "6","13", "22" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			// Select c.stmt#
			query = declaration + "Select c.stmt#";

			expectedResult = { "10", "12", "16" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);


		}

		TEST_METHOD(IntegrationTest_Evaluate_Multiple_Clause_Modifies_Uses)
		{
			string declaration = "stmt s,s1,s2; assign a; while w; if i; call c; prog_line n; stmtLst sl; procedure p; variable v; ";
			string query;
			PKBStub pkbStub;
			PQLStub pql(&pkbStub);
			list<string> actualResult;
			list<string> expectedResult;

			query = declaration + "Select a such that Modifies(a,\"x\") and Uses(a,\"x\") and Modifies(5,\"x\") and Uses(5,\"x\") and Modifies(\"p\", \"x\") and Uses(\"p\", \"x\") and Modifies(a,_) and Uses (a,_) and Modifies(a,v) and Uses (a,v) with a.stmt#=5";

			expectedResult = { "5" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

		}

		TEST_METHOD(IntegrationTest_Evaluate_Multiple_Clause_Calls_CallsStar)
		{
			string declaration = "stmt s,s1,s2; assign a; while w; if i; call c; prog_line n; stmtLst sl; procedure p, p1, p2; variable v; ";
			string query;
			PKBStub pkbStub;
			PQLStub pql(&pkbStub);
			list<string> actualResult;
			list<string> expectedResult;

			query = declaration + "Select p1 such that Calls(p1,p2) and Calls*(p1,p2) and Calls(\"p\",\"q\") and Calls*(\"p\",\"q\") and Calls(_,_) and Calls*(_,_) with p1.procName=\"p\"";

			expectedResult = { "p" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

		}

		TEST_METHOD(IntegrationTest_Evaluate_Multiple_Clause_Parent_ParentStar)
		{
			string declaration = "stmt s,s1,s2; assign a; while w; if i; call c; prog_line n; stmtLst sl; procedure p, p1, p2; variable v; ";
			string query;
			PKBStub pkbStub;
			PQLStub pql(&pkbStub);
			list<string> actualResult;
			list<string> expectedResult;

			query = declaration + "Select <s1,s2> such that Parent(s1,s2) and Parent*(s1,s2) and Parent(4,5) and Parent*(4,5) and Parent(_,_) and Parent*(_,_) with s1.stmt#=4 and s2.stmt#=5";

			expectedResult = { "4 5" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

		}

		TEST_METHOD(IntegrationTest_Evaluate_Multiple_Clause_Follows_FollowsStar)
		{
			string declaration = "stmt s,s1,s2; assign a; while w; if i; call c; prog_line n; stmtLst sl; procedure p, p1, p2; variable v; ";
			string query;
			PKBStub pkbStub;
			PQLStub pql(&pkbStub);
			list<string> actualResult;
			list<string> expectedResult;

			query = declaration + "Select <s1,s2> such that Follows(s1,s2) and Follows*(s1,s2) and Follows(1,2) and Follows*(1,2) and Follows(_,_) and Follows*(_,_) with s1.stmt#=1 and s2.stmt#=2";

			expectedResult = { "1 2" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

		}

		TEST_METHOD(IntegrationTest_Evaluate_Multiple_Clause_Next_NextStar)
		{
			string declaration = "stmt s,s1,s2; assign a; while w; if i; call c; prog_line n; stmtLst sl; procedure p, p1, p2; variable v; ";
			string query;
			PKBStub pkbStub;
			PQLStub pql(&pkbStub);
			list<string> actualResult;
			list<string> expectedResult;

			query = declaration + "Select <s1,s2> such that Next(s1,s2) and Next*(s1,s2) and Next(1,2) and Next*(1,2) and Next(_,_) and Next*(_,_) with s1.stmt#=1 and s2.stmt#=2";

			expectedResult = { "1 2" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

		}

		TEST_METHOD(IntegrationTest_Evaluate_Multiple_Clause_NextBip)
		{
			string declaration = "stmt s,s1,s2; assign a, a1, a2; while w; if i; call c; prog_line n; stmtLst sl; procedure p, p1, p2; variable v; ";
			string query;
			PKBStub pkbStub;
			PQLStub pql(&pkbStub);
			list<string> actualResult;
			list<string> expectedResult;

			query = declaration + "Select BOOLEAN such that NextBip(s1,s2) and NextBip(1, 2) and NextBip(_, _) with s1.stmt# = 1 and s2.stmt# = 2 ";

			expectedResult = { "TRUE" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

		}

		TEST_METHOD(IntegrationTest_Evaluate_Multiple_Clause_NextBipStar)
		{
			/*
			string declaration = "stmt s,s1,s2; assign a, a1, a2; while w; if i; call c; prog_line n; stmtLst sl; procedure p, p1, p2; variable v; ";
			string query;
			PKBStub pkbStub;
			PQLStub pql(&pkbStub);
			list<string> actualResult;
			list<string> expectedResult;

			query = declaration + "Select BOOLEAN such that NextBip*(1, 2)";

			expectedResult = { "TRUE" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);
			*/
		}

		TEST_METHOD(IntegrationTest_Evaluate_Multiple_Clause_Affects_AffectsStar)
		{
			string declaration = "stmt s,s1,s2; assign a, a1, a2; while w; if i; call c; prog_line n; stmtLst sl; procedure p, p1, p2; variable v; ";
			string query;
			PKBStub pkbStub;
			PQLStub pql(&pkbStub);
			list<string> actualResult;
			list<string> expectedResult;

			query = declaration + "Select <a1,a2> such that Affects(a1,a2) and Affects*(a1,a2) and Affects(18,19) and Affects*(18,19) and Affects(_,_) and Affects*(_,_) with a1.stmt#=18 and a2.stmt#=19";

			expectedResult = { "18 19" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

		}

		TEST_METHOD(IntegrationTest_Evaluate_Multiple_Clause_AffectsBip_AffectsBipStar)
		{
			string declaration = "stmt s,s1,s2; assign a, a1, a2; while w; if i; call c; prog_line n; stmtLst sl; procedure p, p1, p2; variable v; ";
			string query;
			PKBStub pkbStub;
			PQLStub pql(&pkbStub);
			list<string> actualResult;
			list<string> expectedResult;

			query = declaration + "Select BOOLEAN such that AffectsBip(a1,a2) and AffectsBip*(a1,a2) and AffectsBip(18,19) and AffectsBip*(18,19) and AffectsBip(_,_) and AffectsBip*(_,_) with a1.stmt#=18 and a2.stmt#=19";

			expectedResult = { "TRUE" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

		}


		TEST_METHOD(IntegrationTest_Evaluate_Multiple_With)
		{

			string declaration = "stmt s,s1,s2; assign a, a1, a2; while w; if i; call c; prog_line n; stmtLst sl; procedure p, p1, p2; variable v; constant ct;";
			string query;
			PKBStub pkbStub;
			PQLStub pql(&pkbStub);
			list<string> actualResult;
			list<string> expectedResult;

			query = declaration + "Select BOOLEAN with c.stmt#=10 and c.procName = \"q\" and p.procName=\"q\" and v.varName=\"x\" and ct.value=1 and s.stmt#=1 and ct.value = s.stmt# and s.stmt# = ct.value and \"a\" = \"a\" and c.stmt# = c.stmt# and p.procName = p.procName and v.varName = v.varName";

			expectedResult = { "TRUE" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			query = declaration + "Select BOOLEAN with c.procName = p.procName";

			expectedResult = { "TRUE" };

			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);
		}

		TEST_METHOD(IntegrationTest_Evaluate_Multiple_Pattern)
		{

			string declaration = "stmt s,s1,s2; assign a, a1, a2; while w; if i, i1, i2; call c; prog_line n; stmtLst sl; procedure p, p1, p2; variable v, v1, v2; constant ct;";
			string query;
			PKBStub pkbStub;
			PQLStub pql(&pkbStub);
			list<string> actualResult;
			list<string> expectedResult;


			//pattern if stmt
			query = declaration + "Select i pattern i2(v, _, _) and i(\"x\",_,_) and i(v, _, _)";

			expectedResult = { "6", "13", "22" };
			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			//pattern while stmt
			query = declaration + "Select w pattern  w(_, _) and w(v1, _) and w(\"i\",_) ";

			expectedResult = { "4", "14" };
			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);

			//pattern assign stmt
			query = declaration + "Select a pattern  a(_, _) and a(v1, _) and a(\"x\",_) and a(\"x\",\"x-1\") and a(\"x\",_\"x\"_) ";

			expectedResult = { "5" };
			actualResult = pql.evaluateQuery(query);
			expectedResult.sort();
			actualResult.sort();
			Assert::IsTrue(actualResult == expectedResult);


		}

	};
}

