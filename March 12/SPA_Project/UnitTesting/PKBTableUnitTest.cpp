#include "stdafx.h"
#include "CppUnitTest.h"
#include "VarTable.h"
#include "ConstTable.h"
#include "ProcTable.h"
#include "FollowsTable.h"
#include "ParentsTable.h"
#include "IfTable.h"
#include "WhileTable.h"
#include "AssignTable.h"
#include "CallTable.h"
#include "UsesTable.h"
#include "ModifiesTable.h"	

#include <unordered_map>
#include <vector>
#include <iostream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
	/*
	TEST_CLASS(TestAST)
	{
	public:

		TEST_METHOD(UnitTest_VarTable)
		{
			VarTable vt;
			Assert::AreEqual(0,vt.getSize());

			int a = vt.insertVar("ABC");
			Assert::AreEqual(0, a);
			Assert::AreEqual(1, vt.getSize());
			Assert::AreEqual((string)"ABC", vt.getVarNameById(0));
			Assert::AreEqual(0, vt.getVarIndex("ABC"));

			vt.insertVar("ABCD");
			vt.insertVar("ABCDE");
			vt.insertVar("ABCDEF");
			Assert::AreEqual(4, vt.getSize());
			Assert::AreEqual((string)"ABCDE", vt.getVarNameById(2));
			Assert::AreEqual(3, vt.getVarIndex("ABCDEF"));

			Assert::AreEqual(false, vt.checkVarExistById(6));
			Assert::AreEqual(true, vt.checkVarExistById(3));
			Assert::AreEqual(false, vt.checkVarExistByName("AB"));
			Assert::AreEqual(false, vt.checkVarExistByName("ABc"));
			Assert::AreEqual(true, vt.checkVarExistByName("ABCD"));
		}

		TEST_METHOD(UnitTest_ProcTable)
		{
			ProcTable vt;
			Assert::AreEqual(0, vt.getSize());

			int a = vt.insertProc("ABC");
			Assert::AreEqual(0, a);
			Assert::AreEqual(1, vt.getSize());
			Assert::AreEqual((string)"ABC", vt.getProcName(0));
			Assert::AreEqual(0, vt.getProcIndex("ABC"));

			vt.insertProc("ABCD");
			vt.insertProc("ABCDE");
			vt.insertProc("ABCDEF");
			Assert::AreEqual(4, vt.getSize());
			Assert::AreEqual((string)"ABCDE", vt.getProcName(2));
			Assert::AreEqual(3, vt.getProcIndex("ABCDEF"));

			Assert::AreEqual(false, vt.checkProcExistById(6));
			Assert::AreEqual(true, vt.checkProcExistById(3));
			Assert::AreEqual(false, vt.checkProcExistByName("AB"));
			Assert::AreEqual(false, vt.checkProcExistByName("ABc"));
			Assert::AreEqual(true, vt.checkProcExistByName("ABCD"));
		}

		TEST_METHOD(UnitTest_ConstTable)
		{
			ConstTable ct;
			Assert::AreEqual(0, ct.getSize());
			
			int a = ct.insertConst(10);
			Assert::AreEqual(0, a);
			Assert::AreEqual(1, ct.getSize());
			Assert::AreEqual(0, ct.getConstIndex(10));
			Assert::AreEqual(10, ct.getConstName(0));
			Assert::AreEqual(10, ct.getValueById(0));

			
			ct.insertConst(20);
			ct.insertConst(30);
			ct.insertConst(40);

			Assert::AreEqual(4, ct.getSize());
			Assert::AreEqual(3, ct.getConstIndex(40));
			Assert::AreEqual(2, ct.getConstIndex(30));
			Assert::AreEqual(30, ct.getConstName(2));
			Assert::AreEqual(30, ct.getValueById(2));
			Assert::AreEqual(true, ct.checkConstExist(30));
			Assert::AreEqual(false, ct.checkConstExist(50));
		}

		TEST_METHOD(UnitTest_FollowsTable)
		{
			/*
				Sample: 1,2,3,4-while{5,6}
			*/
	/*
			FollowsTable ft;
			ft.setStmtFollowStmtRel(1, 2);
			ft.setStmtFollowStmtRel(2, 3);
			ft.setStmtFollowStmtRel(3, 4);
			ft.insertStmtFollowStmtRel(1, 3);
			ft.insertStmtFollowStmtRel(1, 4);
			ft.insertStmtFollowStmtRel(2, 4);
			ft.insertStmtFollowStmtRel(5, 6);
			Assert::AreEqual(2, ft.getDirectFollow(1));
			Assert::AreEqual(1, ft.getDirectFollowedBy(2));
			Assert::IsTrue(vector<int>({2,3,4}) == ft.getStmtFollowStarStmt(1));
			Assert::AreEqual(2, (int)ft.getStmtFollowedByStarStmt(3).size());
			Assert::IsTrue(vector<int>({ 2,1 }) == ft.getStmtFollowedByStarStmt(3));
			Assert::IsTrue(vector<int>({ 6 }) == ft.getStmtFollowStarStmt(5));
			Assert::IsTrue(vector<int>() == ft.getStmtFollowStarStmt(6));
			Assert::IsTrue(vector<int>() == ft.getStmtFollowedByStarStmt(1));
		}

		TEST_METHOD(UnitTest_ParentsTable)
		{
			/*
				Sample 1, 2_while{3,4-if{5,6}, 7} 
			*/
/*
			ParentsTable pt;
			pt.setStmtParentStmtRel(2, 3);
			pt.setStmtParentStmtRel(2, 4);
			pt.setStmtParentStmtRel(4, 5);
			pt.setStmtParentStmtRel(4, 6);
			pt.setStmtParentStmtRel(2, 7);
			pt.insertStmtParentStmtRel(2, 5);
			pt.insertStmtParentStmtRel(2, 6);
			Assert::AreEqual(2, pt.getParent(3));
			Assert::AreEqual(4, pt.getParent(6));
			Assert::AreEqual(3, (int)pt.getStmtChildrenStmt(2).size());
			Assert::IsTrue(vector<int>({ 3,4,7 }) == pt.getStmtChildrenStmt(2));
			Assert::IsTrue(vector<int>({ 5,6 }) == pt.getStmtChildrenStmt(4));
			Assert::IsTrue(vector<int>() == pt.getStmtChildrenStmt(5));
			Assert::AreEqual(2, (int)pt.getStmtParentStarStmt(5).size());
			Assert::IsTrue(vector<int>({ 4,2}) == pt.getStmtParentStarStmt(5));
			Assert::AreEqual(5, (int)pt.getStmtChildrenStarStmt(2).size());
			Assert::IsTrue(vector<int>({ 3,4,7,5,6 }) == pt.getStmtChildrenStarStmt(2));
			Assert::IsTrue(vector<int>({ 5,6 }) == pt.getStmtChildrenStarStmt(4));
		}
		TEST_METHOD(UnitTest_IfTable)
		{
			IfTable it;
			Assert::AreEqual(0, it.getSize());
			it.setVarToIfStmt(2, 5);
			it.setVarToIfStmt(3, 6);
			Assert::AreEqual(5, it.getVarInIfStmt(2));
			Assert::AreEqual(2, it.getSize());
		}
		TEST_METHOD(UnitTest_WhileTable)
		{
			WhileTable wt;
			Assert::AreEqual(0, wt.getSize());
			wt.setVarToWhileStmt(2, 5);
			wt.setVarToWhileStmt(3, 6);
			Assert::AreEqual(5, wt.getVarInWhileStmt(2));
			Assert::AreEqual(2, wt.getSize());
		}
		TEST_METHOD(UnitTest_AssignTable)
		{
			AssignTable at;
			Assert::AreEqual(0, at.getSize());
			at.setExpToAssignStmt(2, "a+b");
			at.setExpToAssignStmt(3, "c*d");
			Assert::IsTrue("a+b" == at.getExpInAssignStmt(2));
			Assert::AreEqual(2, at.getSize());
		}
		TEST_METHOD(UnitTest_CallTable)
		{
			CallTable ct;
			Assert::AreEqual(0, ct.getSize());
			ct.setStmtCallProc(2, 5);
			ct.setStmtCallProc(3, 6);
			Assert::AreEqual(5, ct.getCallProc(2));
			Assert::AreEqual(2, ct.getSize());
		}
		TEST_METHOD(UnitTest_UsesTable)
		{
			UsesTable ut;
			ut.setStmtUseVarRel(2, 11);
			ut.setStmtUseVarRel(2, 12);
			ut.setStmtUseVarRel(2, 13);
			ut.setStmtUseVarRel(3, 11);
			Assert::AreEqual(3, (int)ut.getVarUsedByStmt(2).size());
			Assert::IsTrue(vector<int>({ 11,12,13 }) == ut.getVarUsedByStmt(2));
			Assert::AreEqual(1, (int)ut.getVarUsedByStmt(3).size());
			Assert::IsTrue(vector<int>({ 11 }) == ut.getVarUsedByStmt(3));
			Assert::AreEqual(2, (int)ut.getStmtUseVar(11).size());
			Assert::IsTrue(vector<int>({ 2,3 }) == ut.getStmtUseVar(11));
			Assert::AreEqual(1, (int)ut.getStmtUseVar(13).size());
			Assert::IsTrue(vector<int>({ 2 }) == ut.getStmtUseVar(13));
			Assert::AreEqual(0, (int)ut.getStmtUseVar(100).size());
			Assert::IsTrue(vector<int>({}) == ut.getStmtUseVar(100));

			ut.setStmtUseConstRel(2, 11);
			ut.setStmtUseConstRel(2, 12);
			ut.setStmtUseConstRel(2, 13);
			ut.setStmtUseConstRel(3, 11);
			Assert::AreEqual(3, (int)ut.getConstUsedByStmt(2).size());
			Assert::IsTrue(vector<int>({ 11,12,13 }) == ut.getConstUsedByStmt(2));
			Assert::AreEqual(1, (int)ut.getConstUsedByStmt(3).size());
			Assert::IsTrue(vector<int>({ 11 }) == ut.getConstUsedByStmt(3));
			Assert::AreEqual(2, (int)ut.getStmtUseConst(11).size());
			Assert::IsTrue(vector<int>({ 2,3 }) == ut.getStmtUseConst(11));
			Assert::AreEqual(1, (int)ut.getStmtUseConst(13).size());
			Assert::IsTrue(vector<int>({ 2 }) == ut.getStmtUseConst(13));
			Assert::AreEqual(0, (int)ut.getStmtUseConst(100).size());
			Assert::IsTrue(vector<int>({}) == ut.getStmtUseConst(100));

			ut.setProcUseVarRel(2, 11);
			ut.setProcUseVarRel(2, 12);
			ut.setProcUseVarRel(2, 13);
			ut.setProcUseVarRel(3, 11);
			Assert::AreEqual(3, (int)ut.getVarUsedByProc(2).size());
			Assert::IsTrue(vector<int>({ 11,12,13 }) == ut.getVarUsedByProc(2));
			Assert::AreEqual(1, (int)ut.getVarUsedByProc(3).size());
			Assert::IsTrue(vector<int>({ 11 }) == ut.getVarUsedByProc(3));
			Assert::AreEqual(2, (int)ut.getProcUseVar(11).size());
			Assert::IsTrue(vector<int>({ 2,3 }) == ut.getProcUseVar(11));
			Assert::AreEqual(1, (int)ut.getProcUseVar(13).size());
			Assert::IsTrue(vector<int>({ 2 }) == ut.getProcUseVar(13));
			Assert::AreEqual(0, (int)ut.getProcUseVar(100).size());
			Assert::IsTrue(vector<int>({}) == ut.getProcUseVar(100));

			ut.setProcUseConstRel(2, 11);
			ut.setProcUseConstRel(2, 12);
			ut.setProcUseConstRel(2, 13);
			ut.setProcUseConstRel(3, 11);
			Assert::AreEqual(3, (int)ut.getConstUsedByProc(2).size());
			Assert::IsTrue(vector<int>({ 11,12,13 }) == ut.getConstUsedByProc(2));
			Assert::AreEqual(1, (int)ut.getConstUsedByProc(3).size());
			Assert::IsTrue(vector<int>({ 11 }) == ut.getConstUsedByProc(3));
			Assert::AreEqual(2, (int)ut.getProcUseConst(11).size());
			Assert::IsTrue(vector<int>({ 2,3 }) == ut.getProcUseConst(11));
			Assert::AreEqual(1, (int)ut.getProcUseConst(13).size());
			Assert::IsTrue(vector<int>({ 2 }) == ut.getProcUseConst(13));
			Assert::AreEqual(0, (int)ut.getProcUseConst(100).size());
			Assert::IsTrue(vector<int>({}) == ut.getProcUseConst(100));
		}

		TEST_METHOD(UnitTest_ModifiesTable)
		{
			ModifiesTable mt;
			mt.setStmtModifyVarRel(2, 4);
			mt.setStmtModifyVarRel(2, 5);  // this is not executed due to duplicate key
			mt.setStmtModifyVarRel(3, 5);
			mt.setStmtModifyVarRel(4, 5);

			mt.setProcModifyVarRel(2, 4);
			mt.setProcModifyVarRel(2, 5);  // this is not executed due to duplicate key
			mt.setProcModifyVarRel(3, 5);
			mt.setProcModifyVarRel(4, 5);

			Assert::IsTrue(vector<int>({ 4 }) == mt.getVarModifiedInStmt(2));
			Assert::IsTrue(vector<int>({ 2 }) == mt.getStmtModifyVar(4));
			Assert::IsTrue(vector<int>({ 3,4 }) == mt.getStmtModifyVar(5));

			Assert::IsTrue(vector<int>({ 4 }) == mt.getVarModifiedInProc(2));
			Assert::IsTrue(vector<int>({ 2 }) == mt.getProcModifyVar(4));
			Assert::IsTrue(vector<int>({ 3,4 }) == mt.getProcModifyVar(5));
		}
	};
	*/
}