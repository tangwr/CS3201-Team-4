#include "stdafx.h"
#include "CppUnitTest.h"
#include "QueryParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(queryParserTest)
	{
	public:

		TEST_METHOD(isValid)
		{
			vector<string> queries;
			vector<bool> queryResults;

			queries.push_back("assign a;variable b; Select a such that Uses(a, \"x\")");
			queryResults.push_back(true);
			queries.push_back("while w; assign a; Select w such that Follows(w, a)");
			queryResults.push_back(true);
			queries.push_back("while w; Select w");
			queryResults.push_back(true);
			queries.push_back("assign a; stmt s; Select a pattern a(_,_) such that Parent*(1,s)");
			queryResults.push_back(true);
			queries.push_back("stmt s; Select s such that Follows(_,_)");
			queryResults.push_back(true);
			queries.push_back("stmt s; prog_line p; assign a; variable v; Select v such that Follows(s,p)");
			queryResults.push_back(true);
			queries.push_back("variable v;Select v such that Follows(3, 4)");
			queryResults.push_back(true);
			queries.push_back("variable v; assign a; Select a such that Follows*(a, 9)");
			queryResults.push_back(true);
			queries.push_back("prog_line p; assign a5; Select a5 such that Parent*(p, 8)");
			queryResults.push_back(true);
			queries.push_back("prog_line p; Select BOOLEAN such that Parent(p, 8)");
			queryResults.push_back(true);
			

			queries.push_back("assign a; variable v; Select a pattern a(v, _) such that Follows(a,v)");
			queryResults.push_back(false);
			queries.push_back("assign a,a1; stms s; Select a pattern a1(\"uio\",\"-1235\")");
			queryResults.push_back(false);
			queries.push_back("assign a,a1; stms s; Select a pattern a1(\"uio\", _\"-1\"_)");
			queryResults.push_back(false);
			queries.push_back("assign a7,a1,a3; stms s; Select a7 pattern a3(_, _\"+xyz\"_)");
			queryResults.push_back(false);
			queries.push_back("assign a,a1,a3; stms s; Select a1 such that Follows(1, a3) d u m");
			queryResults.push_back(false);
			queries.push_back("assign a; stms s; Select s1 such that Follows(1, a)");
			queryResults.push_back(false);
			queries.push_back("while w; assign a; Select w such that Follows(1, a) pattern a(a, _\"x\"_)");
			queryResults.push_back(false);
			queries.push_back("assign a; stmt s; Select a pattern a(a,_) such that Parent*(a,s)"); // checking for one comon syn
			queryResults.push_back(false);
			queries.push_back("assign a; stmt s; Select a pattern a(s,_) such that Parent*(a,s)"); // checking for two comon syns
			queryResults.push_back(false);
			queries.push_back("stmt s; Select s such that Modifies(_,_)");
			queryResults.push_back(false);
			queries.push_back("stmt s; Select s such that Modifies(_,s)");
			queryResults.push_back(false);
			queries.push_back("stmt s; Select s such that Uses(_,s)");
			queryResults.push_back(false);
			for (int i = 0; i < queries.size(); i++) {
				QueryParser qp;
				Assert::AreEqual((bool)queryResults.at(i), qp.isValid(queries.at(i)));
			}
		}
	};
}