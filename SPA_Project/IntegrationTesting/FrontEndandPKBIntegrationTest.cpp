#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"
#include "Parser.h"
#include "DesignExtractor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTest_FrontEnd_PKB
{		
	TEST_CLASS(FrontEnd_PKB_Test)
	{
	public:

		TEST_METHOD(IntegrationTest_Assign)
		{
			string source = "procedure ABC {x = 1;y = x * y;z = (x + y) * z;}";

			PKB pkb;
			Parser parser(&pkb, source);
			parser.parse();
			DesignExtractor designExtractor(&pkb);
			designExtractor.extractStarRelations();

			int expectedAns, acutualAns;
			string expectedStr, actualStr;
			unordered_set<int> expectedResults, actualResults;

			//Statement Table
			expectedResults = { 1, 2, 3 };
			actualResults = pkb.getAllStmtId();
			Assert::IsTrue(expectedResults == actualResults);

			//Procedure Table
			expectedResults = { 0 };
			actualResults = pkb.getAllProcId();
			Assert::IsTrue(expectedResults == actualResults);

			//Variable Table
			expectedResults = { 0, 1, 2 };
			actualResults = pkb.getAllVarId();
			Assert::IsTrue(expectedResults == actualResults);

			//Constant Table
			expectedResults = { 1 };
			actualResults = pkb.getAllConst();
			Assert::IsTrue(expectedResults == actualResults);

			//Parent Table
			expectedResults = {};
			actualResults = pkb.getStmtParentStarStmt(3);
			Assert::IsTrue(expectedResults == actualResults);

			//Follow Table
			expectedResults = { 2,3 };
			actualResults = pkb.getStmtFollowStarStmt(1);
			Assert::IsTrue(expectedResults == actualResults);

			//Modifies Table
			expectedResults = { 2 };
			actualResults = pkb.getVarModifiedInStmt(3);
			Assert::IsTrue(expectedResults == actualResults);

			//Uses Table
			expectedResults = { 0,1,2 };
			actualResults = pkb.getVarUsedByStmt(3);
			Assert::IsTrue(expectedResults == actualResults);

			//Assign Table
			expectedResults = { 1, 2, 3 };
			actualResults = pkb.getAllAssignStmt();
			Assert::IsTrue(expectedResults == actualResults);

			expectedStr = "|*|+|x|y|z|";
			actualStr = pkb.getExpInAssignStmt(3);
			Assert::IsTrue(expectedStr == actualStr);

			//While Table
			expectedResults = {};
			actualResults = pkb.getAllWhileStmt();
			Assert::IsTrue(expectedResults == actualResults);

			//If Table
			expectedResults = {};
			actualResults = pkb.getAllIfId();
			Assert::IsTrue(expectedResults == actualResults);

			//Call Table
			expectedResults = {};
			actualResults = pkb.getAllCallId();
			Assert::IsTrue(expectedResults == actualResults);

			//Next Table
			expectedResults = { 2 };
			actualResults = pkb.getNextStmt(1);
			Assert::IsTrue(expectedResults == actualResults);

			//StmtLst Table
			expectedResults = { 1 };
			actualResults = pkb.getAllStmtLst();
			Assert::IsTrue(expectedResults == actualResults);
		}


		TEST_METHOD(IntegrationTest_While)
		{
			string source = "procedure ABC {while x {while y {while z {z = (x + y) * z;}}}x=1;}";

			PKB pkb;
			Parser parser(&pkb, source);
			parser.parse();
			DesignExtractor designExtractor(&pkb);
			designExtractor.extractStarRelations();

			int expectedAns, acutualAns;
			string expectedStr, actualStr;
			unordered_set<int> expectedResults, actualResults;

			//Statement Table
			expectedResults = { 1, 2, 3, 4, 5 };
			actualResults = pkb.getAllStmtId();
			Assert::IsTrue(expectedResults == actualResults);

			//Procedure Table
			expectedResults = { 0 };
			actualResults = pkb.getAllProcId();
			Assert::IsTrue(expectedResults == actualResults);

			//Variable Table
			expectedResults = { 0, 1, 2 };
			actualResults = pkb.getAllVarId();
			Assert::IsTrue(expectedResults == actualResults);

			//Constant Table
			expectedResults = { 1 };
			actualResults = pkb.getAllConst();
			Assert::IsTrue(expectedResults == actualResults);

			//Parent Table
			expectedResults = { 1, 2, 3 };
			actualResults = pkb.getStmtParentStarStmt(4);
			Assert::IsTrue(expectedResults == actualResults);

			//Follow Table
			expectedResults = { 5 };
			actualResults = pkb.getStmtFollowStarStmt(1);
			Assert::IsTrue(expectedResults == actualResults);

			//Modifies Table
			expectedResults = { 2 };
			actualResults = pkb.getVarModifiedInStmt(4);
			Assert::IsTrue(expectedResults == actualResults);

			//Uses Table
			expectedResults = { 0,1,2 };
			actualResults = pkb.getVarUsedByStmt(4);
			Assert::IsTrue(expectedResults == actualResults);

			//Assign Table
			expectedResults = { 4,5 };
			actualResults = pkb.getAllAssignStmt();
			Assert::IsTrue(expectedResults == actualResults);

			expectedStr = "|*|+|x|y|z|";
			actualStr = pkb.getExpInAssignStmt(4);
			Assert::IsTrue(expectedStr == actualStr);

			//While Table
			expectedResults = { 1, 2, 3 };
			actualResults = pkb.getAllWhileStmt();
			Assert::IsTrue(expectedResults == actualResults);

			//If Table
			expectedResults = {};
			actualResults = pkb.getAllIfId();
			Assert::IsTrue(expectedResults == actualResults);

			//Call Table
			expectedResults = {};
			actualResults = pkb.getAllCallId();
			Assert::IsTrue(expectedResults == actualResults);

			//Next Table
			expectedResults = { 2,5 };
			actualResults = pkb.getNextStmt(1);
			Assert::IsTrue(expectedResults == actualResults);

			//StmtLst Table
			expectedResults = { 1, 2, 3, 4 };
			actualResults = pkb.getAllStmtLst();
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(IntegrationTest_If)
		{
			string source = "procedure ABC {if x then {if y then {y = x;} else {i = z;}} else {if z then {z = (x + y) * z;} else {y = 2;}}x = 1;}";

			PKB pkb;
			Parser parser(&pkb, source);
			parser.parse();
			DesignExtractor designExtractor(&pkb);
			designExtractor.extractStarRelations();

			int expectedAns, acutualAns;
			string expectedStr, actualStr;
			unordered_set<int> expectedResults, actualResults;

			//Statement Table
			expectedResults = { 1, 2, 3, 4, 5, 6, 7, 8 };
			actualResults = pkb.getAllStmtId();
			Assert::IsTrue(expectedResults == actualResults);

			//Procedure Table
			expectedResults = { 0 };
			actualResults = pkb.getAllProcId();
			Assert::IsTrue(expectedResults == actualResults);

			//Variable Table
			expectedResults = { 0, 1, 2, 3 };
			actualResults = pkb.getAllVarId();
			Assert::IsTrue(expectedResults == actualResults);

			//Constant Table
			expectedResults = { 1, 2 };
			actualResults = pkb.getAllConst();
			Assert::IsTrue(expectedResults == actualResults);

			//Parent Table
			expectedResults = { 1, 5 };
			actualResults = pkb.getStmtParentStarStmt(6);
			Assert::IsTrue(expectedResults == actualResults);

			//Follow Table
			expectedResults = { 8 };
			actualResults = pkb.getStmtFollowStarStmt(1);
			Assert::IsTrue(expectedResults == actualResults);

			//Modifies Table
			expectedResults = { 3 };
			actualResults = pkb.getVarModifiedInStmt(6);
			Assert::IsTrue(expectedResults == actualResults);

			//Uses Table
			expectedResults = { 0, 1, 3 };
			actualResults = pkb.getVarUsedByStmt(6);
			Assert::IsTrue(expectedResults == actualResults);

			//Assign Table
			expectedResults = { 3, 4, 6, 7, 8 };
			actualResults = pkb.getAllAssignStmt();
			Assert::IsTrue(expectedResults == actualResults);

			expectedStr = "|*|+|x|y|z|";
			actualStr = pkb.getExpInAssignStmt(6);
			Assert::IsTrue(expectedStr == actualStr);

			//While Table
			expectedResults = {};
			actualResults = pkb.getAllWhileStmt();
			Assert::IsTrue(expectedResults == actualResults);

			//If Table
			expectedResults = { 1, 2, 5 };
			actualResults = pkb.getAllIfId();
			Assert::IsTrue(expectedResults == actualResults);

			//Call Table
			expectedResults = {};
			actualResults = pkb.getAllCallId();
			Assert::IsTrue(expectedResults == actualResults);

			//Next Table
			expectedResults = { 2,5 };
			actualResults = pkb.getNextStmt(1);
			Assert::IsTrue(expectedResults == actualResults);

			//StmtLst Table
			expectedResults = { 1, 2, 3, 4, 5, 6, 7 };
			actualResults = pkb.getAllStmtLst();
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(IntegrationTest_Call)
		{
			string source = "procedure ABC {x = 100;call BCD;}procedure BCD {call CDE;y = 3201;}procedure CDE {z = (x + y) * z;}";

			PKB pkb;
			Parser parser(&pkb, source);
			parser.parse();
			DesignExtractor designExtractor(&pkb);
			designExtractor.extractStarRelations();

			int expectedAns, acutualAns;
			string expectedStr, actualStr;
			unordered_set<int> expectedResults, actualResults;

			//Statement Table
			expectedResults = { 1, 2, 3, 4, 5 };
			actualResults = pkb.getAllStmtId();
			Assert::IsTrue(expectedResults == actualResults);

			//Procedure Table
			expectedResults = { 0, 1, 2 };
			actualResults = pkb.getAllProcId();
			Assert::IsTrue(expectedResults == actualResults);

			//Variable Table
			expectedResults = { 0, 1, 2 };
			actualResults = pkb.getAllVarId();
			Assert::IsTrue(expectedResults == actualResults);

			//Constant Table
			expectedResults = { 100, 3201 };
			actualResults = pkb.getAllConst();
			Assert::IsTrue(expectedResults == actualResults);

			//Parent Table
			expectedResults = {};
			actualResults = pkb.getStmtParentStarStmt(5);
			Assert::IsTrue(expectedResults == actualResults);

			//Follow Table
			expectedResults = { 4 };
			actualResults = pkb.getStmtFollowStarStmt(3);
			Assert::IsTrue(expectedResults == actualResults);

			//Modifies Table
			expectedResults = { 2 };
			actualResults = pkb.getVarModifiedInStmt(5);
			Assert::IsTrue(expectedResults == actualResults);

			//Uses Table
			expectedResults = { 0, 1, 2 };
			actualResults = pkb.getVarUsedByStmt(5);
			Assert::IsTrue(expectedResults == actualResults);

			//Assign Table
			expectedResults = { 1, 4, 5 };
			actualResults = pkb.getAllAssignStmt();
			Assert::IsTrue(expectedResults == actualResults);

			expectedStr = "|*|+|x|y|z|";
			actualStr = pkb.getExpInAssignStmt(5);
			Assert::IsTrue(expectedStr == actualStr);

			//While Table
			expectedResults = {};
			actualResults = pkb.getAllWhileStmt();
			Assert::IsTrue(expectedResults == actualResults);

			//If Table
			expectedResults = {};
			actualResults = pkb.getAllIfId();
			Assert::IsTrue(expectedResults == actualResults);

			//Call Table
			expectedResults = { 2, 3 };
			actualResults = pkb.getAllCallId();
			Assert::IsTrue(expectedResults == actualResults);

			//Next Table
			expectedResults = { 4 };
			actualResults = pkb.getNextStmt(3);
			Assert::IsTrue(expectedResults == actualResults);

			//StmtLst Table
			expectedResults = { 1, 3, 5 };
			actualResults = pkb.getAllStmtLst();
			Assert::IsTrue(expectedResults == actualResults);
		}

		TEST_METHOD(IntegrationTest_Mix)
		{
			string source = "procedure ABC {if y then {x = 100;} else {call BCD;}}procedure BCD {while z {call CDE;}y = 3201;}procedure CDE {while x {if y then {z = y - x;} else {z = (x + y) * z;}}y = z * x;}";

			PKB pkb;
			Parser parser(&pkb, source);
			parser.parse();
			DesignExtractor designExtractor(&pkb);
			designExtractor.extractStarRelations();

			int expectedAns, acutualAns;
			string expectedStr, actualStr;
			unordered_set<int> expectedResults, actualResults;

			//Statement Table
			expectedResults = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
			actualResults = pkb.getAllStmtId();
			Assert::IsTrue(expectedResults == actualResults);

			//Procedure Table
			expectedResults = { 0, 1, 2 };
			actualResults = pkb.getAllProcId();
			Assert::IsTrue(expectedResults == actualResults);

			//Variable Table
			expectedResults = { 0, 1, 2 };
			actualResults = pkb.getAllVarId();
			Assert::IsTrue(expectedResults == actualResults);

			//Constant Table
			expectedResults = { 100, 3201 };
			actualResults = pkb.getAllConst();
			Assert::IsTrue(expectedResults == actualResults);

			//Parent Table
			expectedResults = { 7,8 };
			actualResults = pkb.getStmtParentStarStmt(9);
			Assert::IsTrue(expectedResults == actualResults);

			//Follow Table
			expectedResults = { 11 };
			actualResults = pkb.getStmtFollowStarStmt(7);
			Assert::IsTrue(expectedResults == actualResults);

			//Modifies Table
			expectedResults = { 2 };
			actualResults = pkb.getVarModifiedInStmt(10);
			Assert::IsTrue(expectedResults == actualResults);

			//Uses Table
			expectedResults = { 0, 1, 2 };
			actualResults = pkb.getVarUsedByStmt(10);
			Assert::IsTrue(expectedResults == actualResults);

			//Assign Table
			expectedResults = { 2, 6, 9, 10, 11 };
			actualResults = pkb.getAllAssignStmt();
			Assert::IsTrue(expectedResults == actualResults);

			expectedStr = "|*|+|x|y|z|";
			actualStr = pkb.getExpInAssignStmt(10);
			Assert::IsTrue(expectedStr == actualStr);

			//While Table
			expectedResults = { 4,7 };
			actualResults = pkb.getAllWhileStmt();
			Assert::IsTrue(expectedResults == actualResults);

			//If Table
			expectedResults = { 1,8 };
			actualResults = pkb.getAllIfId();
			Assert::IsTrue(expectedResults == actualResults);

			//Call Table
			expectedResults = { 3,5 };
			actualResults = pkb.getAllCallId();
			Assert::IsTrue(expectedResults == actualResults);

			//Next Table
			expectedResults = { -2 };
			actualResults = pkb.getNextStmt(9);
			Assert::IsTrue(expectedResults == actualResults);

			//StmtLst Table
			expectedResults = { 1, 2, 3, 4, 5, 7, 8, 9, 10 };
			actualResults = pkb.getAllStmtLst();
			Assert::IsTrue(expectedResults == actualResults);
		}
	};
}