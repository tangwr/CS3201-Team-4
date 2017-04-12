#include "stdafx.h"
#include "PKB.h"
#include "QueryTree.h"
#include "QueryEvaluatorStub.h"
#include "Modifies.h"
#include "Uses.h"
#include "With.h"
#include "Follow.h"
#include "AffectsStar.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace IntegrationTesting
{
	TEST_CLASS(UnitTest1)
	{

	public:

		TEST_METHOD(IntegrationTest_QEPKB_Simple)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select s1 such that modifies(s1, v)
			Parameter p1, p2;
			p1 = Parameter("s1", STMT);
			p2 = Parameter("v", VARIABLE);
			qt.insertUsed(p1);
			qt.insertUsed(p2);
			qt.insertSelect(p1);
			Modifies *m = new Modifies(p1, p2);
			qt.insertResult(m);

			// code: procedure A{ a=1; b=2;}
			pkb->insertVar("a");
			pkb->insertVar("b");
			pkb->setExpToAssignStmt(1, "1");
			pkb->setExpToAssignStmt(2, "2");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtModifyVarRel(2, 1);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			vector<vector<int>> expect;
			expect = { {1}, {2} };
			Assert::AreEqual(1, rt->getSynCount());
			Assert::AreEqual(2, rt->getTupleSize());
			Assert::IsTrue(expect == rt->getTupleList());
		}
		TEST_METHOD(IntegrationTest_QEPKB_SelectBoolean)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select Boolean such that modifies(s1, v)
			Parameter p1, p2, p3;
			p1 = Parameter("s1", STMT);
			p2 = Parameter("v", VARIABLE);
			p3 = Parameter("BOOLEAN", BOOLEAN);
			qt.insertUsed(p1);
			qt.insertUsed(p2);
			qt.insertSelect(p3);
			Modifies *m = new Modifies(p1, p2);
			qt.insertResult(m);

			// code: procedure A{ a=1; b=2;}
			pkb->insertVar("a");
			pkb->insertVar("b");
			pkb->setExpToAssignStmt(1, "1");
			pkb->setExpToAssignStmt(2, "2");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtModifyVarRel(2, 1);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			Assert::AreEqual(0, rt->getSynCount());
			Assert::AreEqual(0, rt->getTupleSize());
			Assert::IsTrue(true == rt->getBoolean());
		}

		TEST_METHOD(IntegrationTest_QEPKB_SelectBoolean2)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select Boolean such that modifies(1, "a")
			Parameter p1, p2, p3;
			p1 = Parameter("1", INTEGER);
			p2 = Parameter("a", STRINGVARIABLE);
			p3 = Parameter("BOOLEAN", BOOLEAN);
			qt.insertSelect(p3);
			Modifies *m = new Modifies(p1, p2);
			qt.insertResult(m);

			// code: procedure A{ a=1; b=2;}
			pkb->insertVar("a");
			pkb->insertVar("b");
			pkb->setExpToAssignStmt(1, "1");
			pkb->setExpToAssignStmt(2, "2");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtModifyVarRel(2, 1);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			Assert::AreEqual(0, rt->getSynCount());
			Assert::AreEqual(0, rt->getTupleSize());
			Assert::IsTrue(true == rt->getBoolean());
		}

		TEST_METHOD(IntegrationTest_QEPKB_SelectBoolean3)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select Boolean such that modifies(2, "a")
			Parameter p1, p2, p3;
			p1 = Parameter("2", INTEGER);
			p2 = Parameter("a", STRINGVARIABLE);
			p3 = Parameter("BOOLEAN", BOOLEAN);
			qt.insertSelect(p3);
			Modifies *m = new Modifies(p1, p2);
			qt.insertResult(m);

			// code: procedure A{ a=1; b=2;}
			pkb->insertVar("a");
			pkb->insertVar("b");
			pkb->setExpToAssignStmt(1, "1");
			pkb->setExpToAssignStmt(2, "2");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtModifyVarRel(2, 1);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			Assert::AreEqual(0, rt->getSynCount());
			Assert::AreEqual(0, rt->getTupleSize());
			Assert::IsTrue(false == rt->getBoolean());
		}

		TEST_METHOD(IntegrationTest_QEPKB_SelectBoolean4)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select Boolean such that modifies(s1, "a") and modifies(s1, "b")
			Parameter p1, p2, p3, p4, p5;
			p1 = Parameter("s1", STMT);
			p2 = Parameter("s2", STMT);

			p3 = Parameter("a", STRINGVARIABLE);
			p4 = Parameter("b", STRINGVARIABLE);
			p5 = Parameter("BOOLEAN", BOOLEAN);
			qt.insertUsed(p1);
			qt.insertSelect(p5);
			Modifies *m = new Modifies(p1, p3);
			qt.insertResult(m);
			m = new Modifies(p1, p4);
			qt.insertResult(m);

			// code: procedure A{ a=1; b=2;}
			pkb->insertVar("a");
			pkb->insertVar("b");
			pkb->setExpToAssignStmt(1, "1");
			pkb->setExpToAssignStmt(2, "2");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtModifyVarRel(2, 1);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			Assert::AreEqual(0, rt->getSynCount());
			Assert::AreEqual(0, rt->getTupleSize());
			Assert::IsTrue(false == rt->getBoolean());
		}

		TEST_METHOD(IntegrationTest_QEPKB_MultipleSynGroup)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select <s1, s2> such that modifies(s1, v1) and modifies(s2, v2)
			Parameter p1, p2 ,p3, p4;
			p1 = Parameter("s1", STMT);
			p2 = Parameter("v1", VARIABLE);
			p3 = Parameter("s2", STMT);
			p4 = Parameter("v2", VARIABLE);
			qt.insertUsed(p1);
			qt.insertUsed(p2);
			qt.insertUsed(p3);
			qt.insertUsed(p4);
			qt.insertSelect(p1);
			qt.insertSelect(p3);
			Modifies *m = new Modifies(p1, p2);
			qt.insertResult(m);
			m = new Modifies(p3, p4);
			qt.insertResult(m);

			// code: procedure A{ a=1; b=2;}
			pkb->insertVar("a");
			pkb->insertVar("b");
			pkb->setExpToAssignStmt(1, "1");
			pkb->setExpToAssignStmt(2, "2");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtModifyVarRel(2, 1);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			vector<vector<int>> expect;
			expect = { { 1, 1 },{ 1, 2 }, {2, 1}, {2, 2} };
			Assert::AreEqual(2, rt->getSynCount());
			Assert::AreEqual(4, rt->getTupleSize());
			Assert::IsTrue(expect == rt->getTupleList());
		}

		TEST_METHOD(IntegrationTest_QEPKB_EarlyTermination)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select <s1, s2> such that modifies(s1, v1) and modifies(s2, v2) and uses(s2, v1)
			Parameter p1, p2, p3, p4;
			p1 = Parameter("s1", STMT);
			p2 = Parameter("v1", VARIABLE);
			p3 = Parameter("s2", STMT);
			p4 = Parameter("v2", VARIABLE);
			qt.insertUsed(p1);
			qt.insertUsed(p2);
			qt.insertUsed(p3);
			qt.insertUsed(p4);
			qt.insertSelect(p1);
			qt.insertSelect(p3);
			Modifies *m = new Modifies(p1, p2);
			qt.insertResult(m);
			m = new Modifies(p3, p4);
			qt.insertResult(m);
			Uses *u = new Uses(p3, p2);
			qt.insertResult(u);

			// code: procedure A{ a=1; b=2;}
			pkb->insertVar("a");
			pkb->insertVar("b");
			pkb->setExpToAssignStmt(1, "1");
			pkb->setExpToAssignStmt(2, "2");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtModifyVarRel(2, 1);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			vector<vector<int>> expect;
			expect = { };
			Assert::AreEqual(2, rt->getSynCount());
			Assert::AreEqual(0, rt->getTupleSize());
			Assert::IsTrue(expect == rt->getTupleList());
		}

		TEST_METHOD(IntegrationTest_QEPKB_NonSynClause)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select s1 such that modifies(1, "a")
			Parameter p1, p2, p3;
			p1 = Parameter("1", INTEGER);
			p2 = Parameter("a", STRINGVARIABLE);
			p3 = Parameter("s1", STMT);
			qt.insertSelect(p3);
			Modifies *m = new Modifies(p1, p2);
			qt.insertResult(m);

			// code: procedure A{ a=1; b=2;}
			pkb->insertVar("a");
			pkb->insertVar("b");
			pkb->setExpToAssignStmt(1, "1");
			pkb->setExpToAssignStmt(2, "2");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtModifyVarRel(2, 1);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			vector<vector<int>> expect;
			expect = { { 1 } , { 2 } };
			Assert::AreEqual(1, rt->getSynCount());
			Assert::AreEqual(2, rt->getTupleSize());
			Assert::IsTrue(expect == rt->getTupleList());
		}

		TEST_METHOD(IntegrationTest_QEPKB_NonSynClauseNoResult)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select s1 such that modifies(1, "a")
			Parameter p1, p2, p3, p4;
			p1 = Parameter("1", INTEGER);
			p2 = Parameter("b", STRINGVARIABLE);
			p3 = Parameter("s1", STMT);
			qt.insertSelect(p3);
			Modifies *m = new Modifies(p1, p2);
			qt.insertResult(m);

			// code: procedure A{ a=1; b=2;}
			pkb->insertVar("a");
			pkb->insertVar("b");
			pkb->setExpToAssignStmt(1, "1");
			pkb->setExpToAssignStmt(2, "2");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtModifyVarRel(2, 1);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			vector<vector<int>> expect;
			expect = { };
			Assert::AreEqual(1, rt->getSynCount());
			Assert::AreEqual(0, rt->getTupleSize());
			Assert::IsTrue(expect == rt->getTupleList());
		}

		TEST_METHOD(IntegrationTest_QEPKB_OneSynClause)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select s1 such that modifies(1, v)
			Parameter p1, p2, p3;
			p1 = Parameter("1", INTEGER);
			p2 = Parameter("v", VARIABLE);
			p3 = Parameter("s1", STMT);
			qt.insertSelect(p3);
			Modifies *m = new Modifies(p1, p2);
			qt.insertResult(m);

			// code: procedure A{ a=1; b=2;}
			pkb->insertVar("a");
			pkb->insertVar("b");
			pkb->setExpToAssignStmt(1, "1");
			pkb->setExpToAssignStmt(2, "2");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtModifyVarRel(2, 1);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			vector<vector<int>> expect;
			expect = { { 1 } ,{ 2 } };
			Assert::AreEqual(1, rt->getSynCount());
			Assert::AreEqual(2, rt->getTupleSize());
			Assert::IsTrue(expect == rt->getTupleList());
		}

		TEST_METHOD(IntegrationTest_QEPKB_OneSynClauseNoResult)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select s1 such that modifies(4, v)
			Parameter p1, p2, p3;
			p1 = Parameter("4", INTEGER);
			p2 = Parameter("v", VARIABLE);
			p3 = Parameter("s1", STMT);
			qt.insertSelect(p3);
			Modifies *m = new Modifies(p1, p2);
			qt.insertResult(m);

			// code: procedure A{ a=1; b=2;}
			pkb->insertVar("a");
			pkb->insertVar("b");
			pkb->setExpToAssignStmt(1, "1");
			pkb->setExpToAssignStmt(2, "2");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtModifyVarRel(2, 1);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			vector<vector<int>> expect;
			expect = {};
			Assert::AreEqual(1, rt->getSynCount());
			Assert::AreEqual(0, rt->getTupleSize());
			Assert::IsTrue(expect == rt->getTupleList());
		}

		TEST_METHOD(IntegrationTest_QEPKB_With)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select s1 with s1.stmt# = 1
			Parameter p1, p2, p3;
			
			p1 = Parameter("s1", STMT);
			p2 = Parameter("1", INTEGER);
			qt.insertUsed(p1);
			qt.insertSelect(p1);
			With *w = new With(p1, p2);
			qt.insertResult(w);

			// code: procedure A{ a=1; b=2;}
			pkb->insertVar("a");
			pkb->insertVar("b");
			pkb->setExpToAssignStmt(1, "1");
			pkb->setExpToAssignStmt(2, "2");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtModifyVarRel(2, 1);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			vector<vector<int>> expect;
			expect = { { 1 } };
			Assert::AreEqual(1, rt->getSynCount());
			Assert::AreEqual(1, rt->getTupleSize());
			Assert::IsTrue(expect == rt->getTupleList());
		}

		TEST_METHOD(IntegrationTest_QEPKB_IntroduceNewOneSynClause)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select s1 with s1.stmt# = 1 such that Modifies(s2, "b")
			//                      such that Follows(s1, s2) with s2.stmt# = 2;
			Parameter p1, p2, p3, p4, p5;

			p1 = Parameter("s1", STMT);
			p2 = Parameter("1", INTEGER);
			p3 = Parameter("s2", STMT);
			p4 = Parameter("b", STRINGVARIABLE);
			p5 = Parameter("2", INTEGER);
			qt.insertUsed(p1);
			qt.insertUsed(p3);
			qt.insertSelect(p1);
			With *w = new With(p1, p2);
			qt.insertResult(w);
			w = new With(p3, p5);
			qt.insertResult(w);
			Modifies *m = new Modifies(p3, p4);
			qt.insertResult(m);
			Follow *f = new Follow(p1, p3);
			qt.insertResult(f);
			// code: procedure A{ a=1; b=2;}
			pkb->insertVar("a");
			pkb->insertVar("b");
			pkb->setExpToAssignStmt(1, "1");
			pkb->setExpToAssignStmt(2, "2");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtModifyVarRel(2, 1);
			pkb->setStmtFollowStmtRel(1, 2);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			vector<vector<int>> expect;
			expect = { { 1 } };
			Assert::AreEqual(1, rt->getSynCount());
			Assert::AreEqual(1, rt->getTupleSize());
			Assert::IsTrue(expect == rt->getTupleList());
		}

		TEST_METHOD(IntegrationTest_QEPKB_NonSelectGroupSyn)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select s2 such that modifies(s1, "a")
			Parameter p1, p2, p3;
			p1 = Parameter("s1", STMT);
			p2 = Parameter("a", STRINGVARIABLE);
			p3 = Parameter("s2", STMT);
			qt.insertUsed(p1);
			qt.insertSelect(p3);
			Modifies *m = new Modifies(p1, p2);
			qt.insertResult(m);

			// code: procedure A{ a=1; b=2;}
			pkb->insertVar("a");
			pkb->insertVar("b");
			pkb->setExpToAssignStmt(1, "1");
			pkb->setExpToAssignStmt(2, "2");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtModifyVarRel(2, 1);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			vector<vector<int>> expect;
			expect = { { 1 } ,{ 2 } };
			Assert::AreEqual(1, rt->getSynCount());
			Assert::AreEqual(2, rt->getTupleSize());
			Assert::IsTrue(expect == rt->getTupleList());
		}

		TEST_METHOD(IntegrationTest_QEPKB_IntroduceWithNewOneSynClause)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select s1 with s1.stmt# = 2 such that Modifies(s2, "b")
			//                      such that Follows(1, s2) with s2.stmt# = s1.stmt#;
			Parameter p1, p2, p3, p4, p5, p6;

			p1 = Parameter("s1", STMT);
			p2 = Parameter("2", INTEGER);
			p3 = Parameter("s2", STMT);
			p4 = Parameter("b", STRINGVARIABLE);
			p5 = Parameter("2", INTEGER);
			p6 = Parameter("1", INTEGER);
			qt.insertUsed(p1);
			qt.insertUsed(p3);
			qt.insertSelect(p1);
			With *w = new With(p1, p2);
			qt.insertResult(w);
			w = new With(p3, p1);
			qt.insertResult(w);
			Modifies *m = new Modifies(p3, p4);
			qt.insertResult(m);
			Follow *f = new Follow(p6, p3);
			qt.insertResult(f);
			// code: procedure A{ a=1; b=2;}
			pkb->insertVar("a");
			pkb->insertVar("b");
			pkb->setExpToAssignStmt(1, "1");
			pkb->setExpToAssignStmt(2, "2");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtModifyVarRel(2, 1);
			pkb->setStmtFollowStmtRel(1, 2);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			vector<vector<int>> expect;
			expect = { { 2 } };
			Assert::AreEqual(1, rt->getSynCount());
			Assert::AreEqual(1, rt->getTupleSize());
			Assert::IsTrue(expect == rt->getTupleList());
		}

		TEST_METHOD(IntegrationTest_QEPKB_EarlyTermination1)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select s1 with s1.stmt# = 2 and s1.stmt# = 1 and Follows(s2, s1)
			Parameter p1, p2, p3, p4, p5, p6;

			p1 = Parameter("s1", STMT);
			p2 = Parameter("2", INTEGER);
			p3 = Parameter("s2", STMT);
			p5 = Parameter("1", INTEGER);
			qt.insertUsed(p1);
			qt.insertUsed(p3);
			qt.insertSelect(p1);
			With *w = new With(p1, p2);
			qt.insertResult(w);
			w = new With(p1, p4);
			qt.insertResult(w);
			Follow *f = new Follow(p3, p1);
			qt.insertResult(f);
			// code: procedure A{ a=1; b=2;}
			pkb->insertVar("a");
			pkb->insertVar("b");
			pkb->setExpToAssignStmt(1, "1");
			pkb->setExpToAssignStmt(2, "2");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtModifyVarRel(2, 1);
			pkb->setStmtFollowStmtRel(1, 2);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			vector<vector<int>> expect;
			expect = { };
			Assert::AreEqual(1, rt->getSynCount());
			Assert::AreEqual(0, rt->getTupleSize());
			Assert::IsTrue(expect == rt->getTupleList());
		}

		TEST_METHOD(IntegrationTest_QEPKB_EarlyTermination2)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select s1 such that Modifies(s1, "a") and Modifies (s1, "b")
			Parameter p1, p2, p3, p4, p5, p6;

			p1 = Parameter("s1", STMT);
			p2 = Parameter("a", STRINGVARIABLE);
			p4 = Parameter("b", STRINGVARIABLE);
			qt.insertUsed(p1);
			qt.insertSelect(p1);
			Modifies *m = new Modifies(p1, p2);
			qt.insertResult(m);
			m = new Modifies(p1, p4);
			qt.insertResult(m);
			// code: procedure A{ a=1; b=2;}
			pkb->insertVar("a");
			pkb->insertVar("b");
			pkb->setExpToAssignStmt(1, "1");
			pkb->setExpToAssignStmt(2, "2");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtModifyVarRel(2, 1);
			pkb->setStmtFollowStmtRel(1, 2);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			vector<vector<int>> expect;
			expect = { };
			Assert::AreEqual(1, rt->getSynCount());
			Assert::AreEqual(0, rt->getTupleSize());
			Assert::IsTrue(expect == rt->getTupleList());
		}

		TEST_METHOD(IntegrationTest_QEPKB_EarlyTermination3)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select s1 with s1.stmt# = 2 (*3) and with s1 = s2
			//          and Modifies(s2, "a") and Modifies(s2, "b")
			Parameter p1, p2, p3, p4, p5, p6;

			p1 = Parameter("s1", STMT);
			p2 = Parameter("2", INTEGER);
			p3 = Parameter("s2", STMT);
			p4 = Parameter("a", STRINGVARIABLE);
			p5 = Parameter("b", STRINGVARIABLE);
			qt.insertUsed(p1);
			qt.insertUsed(p3);
			qt.insertSelect(p1);
			With *w = new With(p1, p2);
			qt.insertResult(w);
			w = new With(p1, p2);
			qt.insertResult(w);
			w = new With(p1, p2);
			qt.insertResult(w);
			w = new With(p1, p3);
			qt.insertResult(w);
			Modifies *m = new Modifies(p3, p4);
			qt.insertResult(m);
			m = new Modifies(p3, p5);
			qt.insertResult(m);
			// code: procedure A{ a=1; b=2;}
			pkb->insertVar("a");
			pkb->insertVar("b");
			pkb->setExpToAssignStmt(1, "1");
			pkb->setExpToAssignStmt(2, "2");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtModifyVarRel(2, 1);
			pkb->setStmtFollowStmtRel(1, 2);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			vector<vector<int>> expect;
			expect = {};
			Assert::AreEqual(1, rt->getSynCount());
			Assert::AreEqual(0, rt->getTupleSize());
			Assert::IsTrue(expect == rt->getTupleList());
		}

		TEST_METHOD(IntegrationTest_QEPKB_EarlyTermination4)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select s1 with s1.stmt# = 2 (*3) and Follows(s2, s1)
			//          and Modifies(s2, "a") and Modifies(s2, "b")
			Parameter p1, p2, p3, p4, p5, p6;

			p1 = Parameter("s1", STMT);
			p2 = Parameter("2", INTEGER);
			p3 = Parameter("s2", STMT);
			p4 = Parameter("a", STRINGVARIABLE);
			p5 = Parameter("b", STRINGVARIABLE);
			qt.insertUsed(p1);
			qt.insertUsed(p3);
			qt.insertSelect(p1);
			With *w = new With(p1, p2);
			qt.insertResult(w);
			w = new With(p1, p2);
			qt.insertResult(w);
			w = new With(p1, p2);
			qt.insertResult(w);
			Follow *f = new Follow(p3, p1);
			qt.insertResult(f);
			Modifies *m = new Modifies(p3, p4);
			qt.insertResult(m);
			m = new Modifies(p3, p5);
			qt.insertResult(m);
			// code: procedure A{ a=1; b=2;}
			pkb->insertVar("a");
			pkb->insertVar("b");
			pkb->setExpToAssignStmt(1, "1");
			pkb->setExpToAssignStmt(2, "2");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtModifyVarRel(2, 1);
			pkb->setStmtFollowStmtRel(1, 2);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			vector<vector<int>> expect;
			expect = {};
			Assert::AreEqual(1, rt->getSynCount());
			Assert::AreEqual(0, rt->getTupleSize());
			Assert::IsTrue(expect == rt->getTupleList());
		}

		TEST_METHOD(IntegrationTest_QEPKB_Depriortization)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select s1 such that affect*(s1, s2)  with s1.stmt# = s2.stmt# 
			Parameter p1, p2, p3, p4, p5, p6;

			p1 = Parameter("s1", STMT);
			p3 = Parameter("s2", STMT);
			qt.insertUsed(p1);
			qt.insertUsed(p3);
			qt.insertSelect(p1);
			With *w = new With(p1, p3);
			qt.insertResult(w);
			AffectsStar *a = new AffectsStar(p1, p3);
			qt.insertResult(a);


			// code: procedure A{ a=1; b=2;}
			pkb->insertVar("a");
			pkb->insertVar("b");
			pkb->setExpToAssignStmt(1, "1");
			pkb->setExpToAssignStmt(2, "2");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtModifyVarRel(2, 1);
			pkb->setStmtFollowStmtRel(1, 2);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			vector<vector<int>> expect;
			expect = {};
			Assert::AreEqual(1, rt->getSynCount());
			Assert::AreEqual(0, rt->getTupleSize());
			Assert::IsTrue(expect == rt->getTupleList());
		}

		TEST_METHOD(IntegrationTest_QEPKB_UnusedSelect)
		{

			PKB *pkb = new PKB();
			QueryTree qt;
			QueryEvaluatorStub* qe;
			// query: select s1 ....
			Parameter p1, p2, p3, p4, p5, p6, p7, p8, p9, p10;

			p1 = Parameter("s", STMT);
			p2 = Parameter("pl", PROG_LINE);
			p3 = Parameter("a", ASSIGN);
			p4 = Parameter("c", CALL);
			p5 = Parameter("w", WHILE);
			p6 = Parameter("if", IF);
			p7 = Parameter("sl", STMTLST);
			p8 = Parameter("p", PROCEDURE);
			p9 = Parameter("v", VARIABLE);
			p10 = Parameter("const", CONSTANT);

			qt.insertSelect(p1);  qt.insertSelect(p2);
			qt.insertSelect(p3);  qt.insertSelect(p4);
			qt.insertSelect(p5);  qt.insertSelect(p6);
			qt.insertSelect(p7);  qt.insertSelect(p8);
			qt.insertSelect(p9);  qt.insertSelect(p10);

			pkb->insertVar("a");
			pkb->insertProc("proc");
			pkb->insertConst(100);
			pkb->setProcStmtLstContainsStmtRel(0, 1);
			pkb->setExpToAssignStmt(1, "1");
			pkb->setStmtModifyVarRel(1, 0);
			pkb->setStmtCallProcRel(1, 0);
			pkb->setVarToIfStmt(1, 1);
			pkb->setVarToWhileStmt(1, 1);

			qe = new QueryEvaluatorStub(pkb);
			ResultTable* rt = qe->evaluate(qt);
			vector<vector<int>> expect;
			expect = { };
			Assert::AreEqual(10, rt->getSynCount());
			Assert::AreEqual(0, rt->getTupleSize());
			Assert::IsTrue(expect == rt->getTupleList());
		}
	};
}