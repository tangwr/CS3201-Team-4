
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

		TEST_METHOD(IntegrationTest_WhileIfProcedure)
		{
			// TODO: Your test code here
			Controller *c = new Controller();
			Assert::AreEqual(0, (int)(c->pkb->getProcCount()));

			Assert::AreEqual(0, (int)(c->pkb->getVarCount()));


			Assert::AreEqual(4, (int)(c->pkb->getAllVarId().size()));

			Assert::AreEqual(3, (int)(c->pkb->getAllVarId().at(0)));
			Assert::AreEqual(0, (int)(c->pkb->getAllVarId().at(1)));
			Assert::AreEqual(1, (int)(c->pkb->getAllVarId().at(2)));
			Assert::AreEqual(2, (int)(c->pkb->getAllVarId().at(3)));

			//Assert::AreEqual((string)"c", c->pkb->getVarName(0));
			//string str = "procedure abc{a=0;while b{c=3;if c{d=4;}else {d=5}e = 6;}f = 7;}";

			string str = "procedure ABC {  i=1;	 b=200  ;c= a +b ;}";
			//ct.processSource(str);

			Assert::AreEqual(0, (int)(c->pkb->getProcCount()));
			Assert::AreEqual(4, (int)(c->pkb->getAllVarId().size()));
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


	};
}