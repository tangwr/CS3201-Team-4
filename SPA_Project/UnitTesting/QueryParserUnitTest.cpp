#include "stdafx.h"
#include "CppUnitTest.h"
#include "Parameter.h"
#include "QueryParser.h"
#include "Parameter.h"
#include "QueryTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(queryParserTest)
	{
	public:

		TEST_METHOD(UnitTest_Parse) {
			vector<string> queries;
			queries.push_back("assign a; variable b; Select <a, b> such that Uses(a, \"x\") and Follows(a, 6)");
			queries.push_back("procedure p1; assign a2; variable v3; stmt s; while w; if ifs; Select a2 such that Next*(a2, w) and Modifies(a2, v3)");
			queries.push_back("stmt s1,s2; call c1,c2; procedure p4; assign a6, a7; if i; Select <i,c1,s1,p4,a7> such that Follows(a7, 8) and Calls*(_, p4) and Uses(p4, \"index\") and Next(c1, c2) and Parent(i, s2) and Follows*(s1, s2)");
			queries.push_back("while w6; if i3; variable v5, v2; stmt s9; assign a4, a6; call c3, c9; Select c9 pattern a6(v2, _\"node * 5\"_) and a4(\"y\", _) such that Next*(c3, w6) and Uses(i3, v5) and Parent*(c9, s9)");
			queries.push_back("assign a1; if i1, i2; call c1, c2, c3; constant cos; variable v1, v2; procedure p1, p2, p3; Select BOOLEAN with v1.varName = \"x\" and p1.procName = c1.procName and cos.value = 12 pattern i1(\"y\", _, _) with a1.stmt# = c2.stmt# pattern i2(_, _, _) with p1.procName = p3.procName");
			queries.push_back("if i1, i2; assign a3, a4; variable v4; Select <a3, i1> pattern i1(v4, _, _) and a3(v4, _\"x + y\"_) and a4(\"test\", \"g * h - v\")");
			queries.push_back("stmt s1, s2; variable v; procedure p4, p5; Select <s1, v, p4> such that Calls(p4, p5) and Calls(p5, \"First\") and Calls*(\"second\", p4) and Calls*(_ , _) and Modifies(1, v) and Modifies(s2, _)");
			queries.push_back("procedure p7, p8; Select p7 such that Calls*(p8, \"XYZ\") and Calls(\"P1\", _) and Calls(_, _) and Parent(_ , _) and Parent(1, 6) and Parent*(5, _) and Parent*(_, 6)");
			queries.push_back("variable v; stmtLst ls; prog_line n1, n2; assign a1; call c; procedure p; constant cos; Select <p.procName, c.stmt#, c.procName, cos.value, a1.stmt#, v.varName> such that Modifies(\"p2\" , _) and Modifies(6, \"z\") and Uses(1, _) and Uses(\"P3\", v)");
			queries.push_back("stmt s1, s2; Select s1.stmt# such that Parent(1, s1) and Parent(_, _) and Follows(5, s2) and Follows(_, _) and Follows*(_, _) and Follows*(6, 9)");
			queries.push_back("call c1,c2; procedure p1,p2; stmt s2, s3; Select c1.stmt# such that Next(3, 4) and Next(_ , _) and Next*(_, 6) and Next*(7, _)");
			queries.push_back("assign a1, a2; stmt s1, s2;call c; Select c.procName such that Affects(a1 , a2) and Affects(1, 3) and Affects(_, _) and Affects*(s1, s2) and Affects*(9, 6) and Affects*(_ ,_)");
			queries.push_back("while w1, w2; assign a2, a3; if i4,i5; constant con; Select con.value pattern a3(_, _) and w2(_, _)");
			queries.push_back("assign a1, a2; call c1, c2; variable v4, v5; procedure p1, p2; constant cos; Select v4.varName with c1.stmt# = a2.stmt# and 6 = a1.stmt# and \"h\" = v5.varName and c2.procName = \"test\" and 45 = cos.value");
			queries.push_back("assign a1, a2; stmt s1, s2; Select <a1, s2> such that AffectsBip(a1, a2) and AffectsBip(_, _) and AffectsBip(6, 4) and AffectsBip*(_, _) and AffectsBip*(8, 9) and AffectsBip*(s2, a2)");
			queries.push_back("if ifs; while w; assign a; Select <w, a, ifs> such that NextBip(_, _) and NextBip(ifs, w) and NextBip(5, 6) and NextBip*(_, _) and NextBip*(2, 9) and NextBip*(a, ifs)");
			QueryParser *qp = new QueryParser();

			//test the first query
			QueryTree qt = qp->parse(queries.at(0));

			Assert::AreEqual(2, (int)qt.getClauseSize());
			Assert::IsTrue("a" == qt.getClause(0)->getLeftChild().getParaName());
			Assert::IsTrue("x" == qt.getClause(0)->getRightChild().getParaName());
			Assert::IsTrue(ASSIGN == qt.getClause(0)->getLeftChild().getParaType());
			Assert::IsTrue(STRINGVARIABLE == qt.getClause(0)->getRightChild().getParaType());
			Assert::IsTrue("a" == qt.getClause(1)->getLeftChild().getParaName());
			Assert::IsTrue("6" == qt.getClause(1)->getRightChild().getParaName());
			Assert::IsTrue(ASSIGN == qt.getClause(1)->getLeftChild().getParaType());
			Assert::IsTrue(INTEGER == qt.getClause(1)->getRightChild().getParaType());
			Assert::AreEqual(2, (int)qt.getSelectParameter().size());
			Assert::AreEqual(1, (int)qt.getUsedParameter().size());

			//test the second query
			QueryTree qt2 = qp->parse(queries.at(1));

			Assert::AreEqual(2, (int)qt2.getClauseSize());
			Assert::IsTrue("a2" == qt2.getClause(0)->getLeftChild().getParaName());
			Assert::IsTrue("w" == qt2.getClause(0)->getRightChild().getParaName());
			Assert::IsTrue(ASSIGN == qt2.getClause(0)->getLeftChild().getParaType());
			Assert::IsTrue(WHILE == qt2.getClause(0)->getRightChild().getParaType());
			Assert::IsTrue("a2" == qt2.getClause(1)->getLeftChild().getParaName());
			Assert::IsTrue("v3" == qt2.getClause(1)->getRightChild().getParaName());
			Assert::IsTrue(ASSIGN == qt2.getClause(1)->getLeftChild().getParaType());
			Assert::IsTrue(VARIABLE == qt2.getClause(1)->getRightChild().getParaType());
			Assert::AreEqual(1, (int)qt2.getSelectParameter().size());
			Assert::AreEqual(3, (int)qt2.getUsedParameter().size());

			//test the third query
			QueryTree qt3 = qp->parse(queries.at(2));
			Assert::AreEqual(6, (int)qt3.getClauseSize());
			Assert::IsTrue("a7" == qt3.getClause(0)->getLeftChild().getParaName());
			Assert::IsTrue("8" == qt3.getClause(0)->getRightChild().getParaName());
			Assert::IsTrue(ASSIGN == qt3.getClause(0)->getLeftChild().getParaType());
			Assert::IsTrue(INTEGER == qt3.getClause(0)->getRightChild().getParaType());
			Assert::IsTrue("_" == qt3.getClause(1)->getLeftChild().getParaName());
			Assert::IsTrue("p4" == qt3.getClause(1)->getRightChild().getParaName());
			Assert::IsTrue(ANYTHING == qt3.getClause(1)->getLeftChild().getParaType());
			Assert::IsTrue(PROCEDURE == qt3.getClause(1)->getRightChild().getParaType());
			Assert::IsTrue("p4" == qt3.getClause(2)->getLeftChild().getParaName());
			Assert::IsTrue("index" == qt3.getClause(2)->getRightChild().getParaName());
			Assert::IsTrue(PROCEDURE == qt3.getClause(2)->getLeftChild().getParaType());
			Assert::IsTrue(STRINGVARIABLE == qt3.getClause(2)->getRightChild().getParaType());
			Assert::IsTrue("c1" == qt3.getClause(3)->getLeftChild().getParaName());
			Assert::IsTrue("c2" == qt3.getClause(3)->getRightChild().getParaName());
			Assert::IsTrue(CALL == qt3.getClause(3)->getLeftChild().getParaType());
			Assert::IsTrue(CALL == qt3.getClause(3)->getRightChild().getParaType());
			Assert::IsTrue("i" == qt3.getClause(4)->getLeftChild().getParaName());
			Assert::IsTrue("s2" == qt3.getClause(4)->getRightChild().getParaName());
			Assert::IsTrue(IF == qt3.getClause(4)->getLeftChild().getParaType());
			Assert::IsTrue(STMT == qt3.getClause(4)->getRightChild().getParaType());
			Assert::IsTrue("s1" == qt3.getClause(5)->getLeftChild().getParaName());
			Assert::IsTrue("s2" == qt3.getClause(5)->getRightChild().getParaName());
			Assert::IsTrue(STMT == qt3.getClause(5)->getLeftChild().getParaType());
			Assert::IsTrue(STMT == qt3.getClause(5)->getRightChild().getParaType());
			Assert::AreEqual(5, (int)qt3.getSelectParameter().size());
			Assert::AreEqual(7, (int)qt3.getUsedParameter().size());

			//test the fourth query 
			QueryTree qt4 = qp->parse(queries.at(3));
			Assert::AreEqual(5, (int)qt4.getClauseSize());
			Assert::IsTrue("a6" == qt4.getClause(0)->getLeftChild().getParaName());
			Assert::IsTrue("v2" == qt4.getClause(0)->getRightChild().getParaName());
			Assert::IsTrue(ASSIGN == qt4.getClause(0)->getLeftChild().getParaType());
			Assert::IsTrue(VARIABLE == qt4.getClause(0)->getRightChild().getParaType());
			Assert::IsTrue("a4" == qt4.getClause(1)->getLeftChild().getParaName());
			Assert::IsTrue("y" == qt4.getClause(1)->getRightChild().getParaName());
			Assert::IsTrue(ASSIGN == qt4.getClause(1)->getLeftChild().getParaType());
			Assert::IsTrue(STRINGVARIABLE == qt4.getClause(1)->getRightChild().getParaType());
			Assert::IsTrue("c3" == qt4.getClause(2)->getLeftChild().getParaName());
			Assert::IsTrue("w6" == qt4.getClause(2)->getRightChild().getParaName());
			Assert::IsTrue(CALL == qt4.getClause(2)->getLeftChild().getParaType());
			Assert::IsTrue(WHILE == qt4.getClause(2)->getRightChild().getParaType());
			Assert::IsTrue("i3" == qt4.getClause(3)->getLeftChild().getParaName());
			Assert::IsTrue("v5" == qt4.getClause(3)->getRightChild().getParaName());
			Assert::IsTrue(IF == qt4.getClause(3)->getLeftChild().getParaType());
			Assert::IsTrue(VARIABLE == qt4.getClause(3)->getRightChild().getParaType());
			Assert::IsTrue("c9" == qt4.getClause(4)->getLeftChild().getParaName());
			Assert::IsTrue("s9" == qt4.getClause(4)->getRightChild().getParaName());
			Assert::IsTrue(CALL == qt4.getClause(4)->getLeftChild().getParaType());
			Assert::IsTrue(STMT == qt4.getClause(4)->getRightChild().getParaType());
			Assert::AreEqual(1, (int)qt4.getSelectParameter().size());
			Assert::AreEqual(9, (int)qt4.getUsedParameter().size());
			
			//test fifth query
			QueryTree qt5 = qp->parse(queries.at(4));
			Assert::AreEqual(7, (int)qt5.getClauseSize());
			Assert::IsTrue("v1" == qt5.getClause(0)->getLeftChild().getParaName());
			Assert::IsTrue("x" == qt5.getClause(0)->getRightChild().getParaName());
			Assert::IsTrue(VARIABLE == qt5.getClause(0)->getLeftChild().getParaType());
			Assert::IsTrue(STRINGVARIABLE == qt5.getClause(0)->getRightChild().getParaType());
			Assert::IsTrue("p1" == qt5.getClause(1)->getLeftChild().getParaName());
			Assert::IsTrue("c1" == qt5.getClause(1)->getRightChild().getParaName());
			Assert::IsTrue(PROCEDURE == qt5.getClause(1)->getLeftChild().getParaType());
			Assert::IsTrue(CALL == qt5.getClause(1)->getRightChild().getParaType());
			Assert::IsTrue("cos" == qt5.getClause(2)->getLeftChild().getParaName());
			Assert::IsTrue("12" == qt5.getClause(2)->getRightChild().getParaName());
			Assert::IsTrue(CONSTANT == qt5.getClause(2)->getLeftChild().getParaType());
			Assert::IsTrue(INTEGER == qt5.getClause(2)->getRightChild().getParaType());
			Assert::IsTrue("i1" == qt5.getClause(3)->getLeftChild().getParaName());
			Assert::IsTrue("y" == qt5.getClause(3)->getRightChild().getParaName());
			Assert::IsTrue(IF == qt5.getClause(3)->getLeftChild().getParaType());
			Assert::IsTrue(STRINGVARIABLE == qt5.getClause(3)->getRightChild().getParaType());
			Assert::IsTrue("a1" == qt5.getClause(4)->getLeftChild().getParaName());
			Assert::IsTrue("c2" == qt5.getClause(4)->getRightChild().getParaName());
			Assert::IsTrue(ASSIGN == qt5.getClause(4)->getLeftChild().getParaType());
			Assert::IsTrue(CALL == qt5.getClause(4)->getRightChild().getParaType());
			Assert::IsTrue("i2" == qt5.getClause(5)->getLeftChild().getParaName());
			Assert::IsTrue("_" == qt5.getClause(5)->getRightChild().getParaName());
			Assert::IsTrue(IF == qt5.getClause(5)->getLeftChild().getParaType());
			Assert::IsTrue(ANYTHING == qt5.getClause(5)->getRightChild().getParaType());
			Assert::IsTrue("p1" == qt5.getClause(6)->getLeftChild().getParaName());
			Assert::IsTrue("p3" == qt5.getClause(6)->getRightChild().getParaName());
			Assert::IsTrue(PROCEDURE == qt5.getClause(6)->getLeftChild().getParaType());
			Assert::IsTrue(PROCEDURE == qt5.getClause(6)->getRightChild().getParaType());
			Assert::AreEqual(1, (int)qt5.getSelectParameter().size());
			Assert::AreEqual(9, (int)qt5.getUsedParameter().size());

			//test sixth query
			QueryTree qt6 = qp->parse(queries.at(5));
			Assert::AreEqual(3, (int)qt6.getClauseSize());
			Assert::IsTrue("i1" == qt6.getClause(0)->getLeftChild().getParaName());
			Assert::IsTrue("v4" == qt6.getClause(0)->getRightChild().getParaName());
			Assert::IsTrue(IF == qt6.getClause(0)->getLeftChild().getParaType());
			Assert::IsTrue(VARIABLE == qt6.getClause(0)->getRightChild().getParaType());
			Assert::IsTrue("a3" == qt6.getClause(1)->getLeftChild().getParaName());
			Assert::IsTrue("v4" == qt6.getClause(1)->getRightChild().getParaName());
			Assert::IsTrue(ASSIGN == qt6.getClause(1)->getLeftChild().getParaType());
			Assert::IsTrue(VARIABLE == qt6.getClause(1)->getRightChild().getParaType());
			Assert::IsTrue("a4" == qt6.getClause(2)->getLeftChild().getParaName());
			Assert::IsTrue("test" == qt6.getClause(2)->getRightChild().getParaName());
			Assert::IsTrue(ASSIGN == qt6.getClause(2)->getLeftChild().getParaType());
			Assert::IsTrue(STRINGVARIABLE == qt6.getClause(2)->getRightChild().getParaType());
			Assert::AreEqual(2, (int)qt6.getSelectParameter().size());
			Assert::AreEqual(4, (int)qt6.getUsedParameter().size());

			//test seventh query
			QueryTree qt7 = qp->parse(queries.at(6));
			Assert::AreEqual(6, (int)qt7.getClauseSize());
			Assert::IsTrue("p4" == qt7.getClause(0)->getLeftChild().getParaName());
			Assert::IsTrue("p5" == qt7.getClause(0)->getRightChild().getParaName());
			Assert::IsTrue(PROCEDURE == qt7.getClause(0)->getLeftChild().getParaType());
			Assert::IsTrue(PROCEDURE == qt7.getClause(0)->getRightChild().getParaType());
			Assert::IsTrue("p5" == qt7.getClause(1)->getLeftChild().getParaName());
			Assert::IsTrue("First" == qt7.getClause(1)->getRightChild().getParaName());
			Assert::IsTrue(PROCEDURE == qt7.getClause(1)->getLeftChild().getParaType());
			Assert::IsTrue(STRINGVARIABLE == qt7.getClause(1)->getRightChild().getParaType());
			Assert::IsTrue("second" == qt7.getClause(2)->getLeftChild().getParaName());
			Assert::IsTrue("p4" == qt7.getClause(2)->getRightChild().getParaName());
			Assert::IsTrue(STRINGVARIABLE == qt7.getClause(2)->getLeftChild().getParaType());
			Assert::IsTrue(PROCEDURE == qt7.getClause(2)->getRightChild().getParaType());
			Assert::IsTrue("_" == qt7.getClause(3)->getLeftChild().getParaName());
			Assert::IsTrue("_" == qt7.getClause(3)->getRightChild().getParaName());
			Assert::IsTrue(ANYTHING == qt7.getClause(3)->getLeftChild().getParaType());
			Assert::IsTrue(ANYTHING == qt7.getClause(3)->getRightChild().getParaType());
			Assert::IsTrue("1" == qt7.getClause(4)->getLeftChild().getParaName());
			Assert::IsTrue("v" == qt7.getClause(4)->getRightChild().getParaName());
			Assert::IsTrue(INTEGER == qt7.getClause(4)->getLeftChild().getParaType());
			Assert::IsTrue(VARIABLE == qt7.getClause(4)->getRightChild().getParaType());
			Assert::IsTrue("s2" == qt7.getClause(5)->getLeftChild().getParaName());
			Assert::IsTrue("_" == qt7.getClause(5)->getRightChild().getParaName());
			Assert::IsTrue(STMT == qt7.getClause(5)->getLeftChild().getParaType());
			Assert::IsTrue(ANYTHING == qt7.getClause(5)->getRightChild().getParaType());
			Assert::AreEqual(3, (int)qt7.getSelectParameter().size());
			Assert::AreEqual(4, (int)qt7.getUsedParameter().size());

			//test eighth query
			QueryTree qt8 = qp->parse(queries.at(7));
			Assert::AreEqual(7, (int)qt8.getClauseSize());
			Assert::IsTrue("p8" == qt8.getClause(0)->getLeftChild().getParaName());
			Assert::IsTrue("XYZ" == qt8.getClause(0)->getRightChild().getParaName());
			Assert::IsTrue(PROCEDURE == qt8.getClause(0)->getLeftChild().getParaType());
			Assert::IsTrue(STRINGVARIABLE == qt8.getClause(0)->getRightChild().getParaType());
			Assert::IsTrue("P1" == qt8.getClause(1)->getLeftChild().getParaName());
			Assert::IsTrue("_" == qt8.getClause(1)->getRightChild().getParaName());
			Assert::IsTrue(STRINGVARIABLE == qt8.getClause(1)->getLeftChild().getParaType());
			Assert::IsTrue(ANYTHING == qt8.getClause(1)->getRightChild().getParaType());
			Assert::IsTrue("_" == qt8.getClause(2)->getLeftChild().getParaName());
			Assert::IsTrue("_" == qt8.getClause(2)->getRightChild().getParaName());
			Assert::IsTrue(ANYTHING == qt8.getClause(2)->getLeftChild().getParaType());
			Assert::IsTrue(ANYTHING == qt8.getClause(2)->getRightChild().getParaType());
			Assert::IsTrue("_" == qt8.getClause(3)->getLeftChild().getParaName());
			Assert::IsTrue("_" == qt8.getClause(3)->getRightChild().getParaName());
			Assert::IsTrue(ANYTHING == qt8.getClause(3)->getLeftChild().getParaType());
			Assert::IsTrue(ANYTHING == qt8.getClause(3)->getRightChild().getParaType());
			Assert::IsTrue("1" == qt8.getClause(4)->getLeftChild().getParaName());
			Assert::IsTrue("6" == qt8.getClause(4)->getRightChild().getParaName());
			Assert::IsTrue(INTEGER == qt8.getClause(4)->getLeftChild().getParaType());
			Assert::IsTrue(INTEGER == qt8.getClause(4)->getRightChild().getParaType());
			Assert::IsTrue("5" == qt8.getClause(5)->getLeftChild().getParaName());
			Assert::IsTrue("_" == qt8.getClause(5)->getRightChild().getParaName());
			Assert::IsTrue(INTEGER == qt8.getClause(5)->getLeftChild().getParaType());
			Assert::IsTrue(ANYTHING == qt8.getClause(5)->getRightChild().getParaType());
			Assert::IsTrue("_" == qt8.getClause(6)->getLeftChild().getParaName());
			Assert::IsTrue("6" == qt8.getClause(6)->getRightChild().getParaName());
			Assert::IsTrue(ANYTHING == qt8.getClause(6)->getLeftChild().getParaType());
			Assert::IsTrue(INTEGER == qt8.getClause(6)->getRightChild().getParaType());
			Assert::AreEqual(1, (int)qt8.getSelectParameter().size());
			Assert::AreEqual(1, (int)qt8.getUsedParameter().size());

			//test nineth query
			QueryTree qt9 = qp->parse(queries.at(8));
			Assert::AreEqual(4, (int)qt9.getClauseSize());

			//test tenth query
			QueryTree qt10 = qp->parse(queries.at(9));
			Assert::AreEqual(6, (int)qt10.getClauseSize());

			//test eleventh query
			QueryTree qt11 = qp->parse(queries.at(10));
			Assert::AreEqual(4, (int)qt11.getClauseSize());

			//test twelfth query
			QueryTree qt12 = qp->parse(queries.at(11));
			Assert::AreEqual(6, (int)qt12.getClauseSize());

			//test thirteenth query
			QueryTree qt13 = qp->parse(queries.at(12));
			Assert::AreEqual(2, (int)qt13.getClauseSize());

			//test fourteenth query
			QueryTree qt14 = qp->parse(queries.at(13));
			Assert::AreEqual(5, (int)qt14.getClauseSize());

			//test fifteenth query
			QueryTree qt15 = qp->parse(queries.at(14));
			Assert::AreEqual(6, (int)qt15.getClauseSize());

			//test sixteenth query
			QueryTree qt16 = qp->parse(queries.at(15));
			Assert::AreEqual(6, (int)qt16.getClauseSize());
		}
	};
}
