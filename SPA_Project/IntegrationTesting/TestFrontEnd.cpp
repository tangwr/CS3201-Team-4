
#include "stdafx.h"
#include "CppUnitTest.h"
#include "Parser.h"
#include "DesignExtractor.h"
#include "Controller.h"
#include "PKB.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace IntegrationTesting
{		
	TEST_CLASS(UnitTest1)
	{

	public:

		TEST_METHOD(IntegrationTest_SimpleProcedure)
		{
			// TODO: Your test code here
			Controller ct;
			string str = "procedure ABC {  i=1;	 b=200  ;c= a +b ;}";
			ct.processSource(str);

			//Assert::AreEqual(1, (int)(ct.pkb->getProcCount()));
			Assert::AreEqual(4, (int)(ct.pkb->getAllVarId().size()));
			Assert::AreEqual(3, (int)ct.pkb->getTotalStmtNum());
			Assert::AreEqual(1, (int)ct.pkb->getStmtModify(1).size());
			Assert::AreEqual(0, (int)ct.pkb->getStmtModify(1).at(0));
			Assert::AreEqual(1, (int)ct.pkb->getStmtModify(2).at(0));
			Assert::AreEqual(2, (int)ct.pkb->getStmtModify(3).at(0));
			Assert::AreEqual(2, (int)ct.pkb->getVarUsedByStmt(3).size());
			Assert::IsTrue(vector<int>({ 3,1 }) == ct.pkb->getVarUsedByStmt(3));

			Assert::AreEqual(3, ct.pkb->getFollowDirect(2));
			Assert::AreEqual(-1, ct.pkb->getFollowDirect(3));
			Assert::AreEqual(1, ct.pkb->getFollowedByDirect(2));

			//ct.pkb->insertFollowRel(1, 3);
			//ct.pkb->insertFollowRel(2, 3);

			Assert::AreEqual(3, ct.pkb->getTotalStmtNum());
			Assert::AreEqual(0, (int)ct.pkb->getFollowStar(3).size());
			Assert::AreEqual(2, (int)ct.pkb->getFollowedByStar(3).size());
			Assert::AreEqual(2, (int)ct.pkb->getFollowedByStar(3).at(0));
			Assert::AreEqual(1, (int)ct.pkb->getFollowedByStar(3).at(1));
			Assert::IsTrue(vector<int>({}) == ct.pkb->getFollowedByStar(1));
			Assert::IsTrue(vector<int>({2,3}) == ct.pkb->getFollowStar(1));
		}

		TEST_METHOD(IntegrationTest_WhileProcedure)
		{
			Controller ct;
			string str = "procedure Example {x = 2; z = 3; i = 5;while i {x = x - 1; z = x + 1;  y = z + x;  z = z + x + i; i = i - 1;}}";
			ct.processSource(str);

			//Assert::AreEqual(3, (int)ct.pkb->getTotalStmtNum());
			//Assert::AreEqual(1, (int)ct.pkb->getStmtModify(1).size());
			//Assert::AreEqual(0, (int)ct.pkb->getStmtModify(1).at(0));
			//Assert::AreEqual(1, (int)ct.pkb->getStmtModify(2).at(0));
			//Assert::AreEqual(2, (int)ct.pkb->getStmtModify(3).at(0));
			//Assert::AreEqual(2, (int)ct.pkb->getVarUsedByStmt(3).size());
			//Assert::IsTrue(vector<int>({ 3,1 }) == ct.pkb->getVarUsedByStmt(3));

			//Assert::AreEqual(3, ct.pkb->getFollowDirect(2));
			//Assert::AreEqual(-1, ct.pkb->getFollowDirect(3));
			//Assert::AreEqual(1, ct.pkb->getFollowedByDirect(2));

			//ct.pkb->insertFollowRel(1, 3);
			//ct.pkb->insertFollowRel(2, 3);
		}

		TEST_METHOD(IntegrationTest_NestedWhileProcedure)
		{
			Controller ct;
			string str = "procedure Example {x = 2;while y{z = 2; while c{a = x;}}}";
			ct.processSource(str);

			Assert::AreEqual(-1, ct.pkb->getParentDirect(2));
			Assert::AreEqual(2, ct.pkb->getParentDirect(3));
			Assert::AreEqual(2, ct.pkb->getParentDirect(4));
			Assert::AreEqual(4, ct.pkb->getParentDirect(5));
			Assert::AreEqual(0, (int)ct.pkb->getChildren(1).size());
			Assert::IsTrue(vector<int>({ 3,4 }) == ct.pkb->getChildren(2));
			Assert::IsTrue(vector<int>({}) == ct.pkb->getChildren(3));
			Assert::IsTrue(vector<int>({ 5 }) == ct.pkb->getChildren(4));

			//ct.pkb->insertParentRel(2, 5);
			Assert::AreEqual(3, (int)ct.pkb->getChildrenStar(2).size());
			Assert::IsTrue(vector<int>({ 3,4,5 }) == ct.pkb->getChildrenStar(2));
			Assert::IsTrue(vector<int>({ 5 }) == ct.pkb->getChildrenStar(4));
			Assert::IsTrue(vector<int>({}) == ct.pkb->getChildrenStar(5));

			Assert::IsTrue(vector<int>({ 4,2 }) == ct.pkb->getParentStar(5));
			Assert::IsTrue(vector<int>({ 2 }) == ct.pkb->getParentStar(4));

			// == test parent modify == //
			Assert::AreEqual(4, (int)ct.pkb->getStmtModify(5).at(0));
			Assert::IsTrue(true == ct.pkb->checkStmtVarModifiesRelExist(5, 4));
			Assert::AreEqual(1, (int)ct.pkb->getStmtModify(4).size());
			Assert::IsTrue(vector<int>({ 4 }) == ct.pkb->getStmtModify(4));
			Assert::AreEqual(2, (int)ct.pkb->getStmtModify(2).size());
			Assert::IsTrue(vector<int>({ 2,4 }) == ct.pkb->getStmtModify(2));

			// == test parent uses == //
			Assert::AreEqual(1, (int)ct.pkb->getVarUsedByStmt(5).size());
			Assert::AreEqual(0, (int)ct.pkb->getVarUsedByStmt(5).at(0));

			//Assert::IsTrue(true == ct.pkb->checkStmtVarUseRelExist(4, 4));

			Assert::AreEqual(2, (int)ct.pkb->getVarUsedByStmt(4).size());
			Assert::AreEqual(3, (int)ct.pkb->getVarUsedByStmt(4).at(0));
			Assert::AreEqual(0, (int)ct.pkb->getVarUsedByStmt(4).at(1));
			Assert::AreEqual(3, (int)ct.pkb->getVarUsedByStmt(2).size());



		}
	};
}