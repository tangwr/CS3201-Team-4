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
		}

	};
}
