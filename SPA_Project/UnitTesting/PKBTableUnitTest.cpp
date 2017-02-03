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
			Assert::AreEqual((string)"ABC", vt.getVarName(0));
			Assert::AreEqual(0, vt.getVarIndex("ABC"));

			vt.insertVar("ABCD");
			vt.insertVar("ABCDE");
			vt.insertVar("ABCDEF");
			Assert::AreEqual(4, vt.getSize());
			Assert::AreEqual((string)"ABCDE", vt.getVarName(2));
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
			FollowsTable ft;
			ft.setFollowDirectRel(1, 2);
			ft.setFollowDirectRel(2, 3);
			ft.setFollowDirectRel(3, 4);
			ft.insertFollowRel(1, 3);
			ft.insertFollowRel(1, 4);
			ft.insertFollowRel(2, 4);
			ft.setFollowDirectRel(5, 6);
			Assert::AreEqual(2, ft.getDirectFollow(1));
			Assert::AreEqual(1, ft.getDirectFollowedBy(2));
			Assert::IsTrue(vector<int>({2,3,4}) == ft.getFollowStar(1));
			Assert::AreEqual(2, (int)ft.getFollowedByStar(3).size());
			Assert::IsTrue(vector<int>({ 2,1 }) == ft.getFollowedByStar(3));
			Assert::IsTrue(vector<int>({ 6 }) == ft.getFollowStar(5));
			Assert::IsTrue(vector<int>() == ft.getFollowStar(6));
			Assert::IsTrue(vector<int>() == ft.getFollowedByStar(1));
		}

		TEST_METHOD(UnitTest_ParentsTable)
		{
			/*
				Sample 1, 2_while{3,4-if{5,6}, 7} 
			*/
			ParentsTable pt;
			pt.setParentDirectRel(2, 3);
			pt.setParentDirectRel(2, 4);
			pt.setParentDirectRel(4, 5);
			pt.setParentDirectRel(4, 6);
			pt.setParentDirectRel(2, 7);
			pt.insertParentRel(2, 5);
			pt.insertParentRel(2, 6);
			Assert::AreEqual(2, pt.getParent(3));
			Assert::AreEqual(4, pt.getParent(6));
			Assert::AreEqual(3, (int)pt.getChildren(2).size());
			Assert::IsTrue(vector<int>({ 3,4,7 }) == pt.getChildren(2));
			Assert::IsTrue(vector<int>({ 5,6 }) == pt.getChildren(4));
			Assert::IsTrue(vector<int>() == pt.getChildren(5));
			Assert::AreEqual(2, (int)pt.getParentStar(5).size());
			Assert::IsTrue(vector<int>({ 4,2}) == pt.getParentStar(5));
			Assert::AreEqual(5, (int)pt.getChildrenStar(2).size());
			Assert::IsTrue(vector<int>({ 3,4,7,5,6 }) == pt.getChildrenStar(2));
			Assert::IsTrue(vector<int>({ 5,6 }) == pt.getChildrenStar(4));
		}
		TEST_METHOD(UnitTest_IfTable)
		{
			IfTable it;
			Assert::AreEqual(0, it.getSize());
			it.setIfCtrlVar(2, 5);
			it.setIfCtrlVar(3, 6);
			Assert::AreEqual(5, it.getIfCtrlVar(2));
			Assert::AreEqual(2, it.getSize());
		}
		TEST_METHOD(UnitTest_WhileTable)
		{
			WhileTable wt;
			Assert::AreEqual(0, wt.getSize());
			wt.setWhileCtrlVar(2, 5);
			wt.setWhileCtrlVar(3, 6);
			Assert::AreEqual(5, wt.getWhileCtrlVar(2));
			Assert::AreEqual(2, wt.getSize());
		}
		TEST_METHOD(UnitTest_AssignTable)
		{
			AssignTable at;
			Assert::AreEqual(0, at.getSize());
			at.setAssignExp(2, "a+b");
			at.setAssignExp(3, "c*d");
			Assert::IsTrue("a+b" == at.getAssignExp(2));
			Assert::AreEqual(2, at.getSize());
		}
		TEST_METHOD(UnitTest_CallTable)
		{
			CallTable ct;
			Assert::AreEqual(0, ct.getSize());
			ct.setCallProc(2, 5);
			ct.setCallProc(3, 6);
			Assert::AreEqual(5, ct.getCallProc(2));
			Assert::AreEqual(2, ct.getSize());
		}
		TEST_METHOD(UnitTest_UsesTable)
		{
			UsesTable ut;
			ut.setStmtUseRel(2, 11);
			ut.setStmtUseRel(2, 12);
			ut.setStmtUseRel(2, 13);
			ut.setStmtUseRel(3, 11);
			Assert::AreEqual(3, (int)ut.getVarUsedByStmt(2).size());
			Assert::IsTrue(vector<int>({ 11,12,13 }) == ut.getVarUsedByStmt(2));
			Assert::AreEqual(1, (int)ut.getVarUsedByStmt(3).size());
			Assert::IsTrue(vector<int>({ 11 }) == ut.getVarUsedByStmt(3));
			Assert::AreEqual(2, (int)ut.getStmtUsesVar(11).size());
			Assert::IsTrue(vector<int>({ 2,3 }) == ut.getStmtUsesVar(11));
			Assert::AreEqual(1, (int)ut.getStmtUsesVar(13).size());
			Assert::IsTrue(vector<int>({ 2 }) == ut.getStmtUsesVar(13));
			Assert::AreEqual(0, (int)ut.getStmtUsesVar(100).size());
			Assert::IsTrue(vector<int>({}) == ut.getStmtUsesVar(100));

			ut.setStmtUseRelConst(2, 11);
			ut.setStmtUseRelConst(2, 12);
			ut.setStmtUseRelConst(2, 13);
			ut.setStmtUseRelConst(3, 11);
			Assert::AreEqual(3, (int)ut.getConstUsedByStmt(2).size());
			Assert::IsTrue(vector<int>({ 11,12,13 }) == ut.getConstUsedByStmt(2));
			Assert::AreEqual(1, (int)ut.getConstUsedByStmt(3).size());
			Assert::IsTrue(vector<int>({ 11 }) == ut.getConstUsedByStmt(3));
			Assert::AreEqual(2, (int)ut.getStmtUsesConst(11).size());
			Assert::IsTrue(vector<int>({ 2,3 }) == ut.getStmtUsesConst(11));
			Assert::AreEqual(1, (int)ut.getStmtUsesConst(13).size());
			Assert::IsTrue(vector<int>({ 2 }) == ut.getStmtUsesConst(13));
			Assert::AreEqual(0, (int)ut.getStmtUsesConst(100).size());
			Assert::IsTrue(vector<int>({}) == ut.getStmtUsesConst(100));

			ut.setProcUseRel(2, 11);
			ut.setProcUseRel(2, 12);
			ut.setProcUseRel(2, 13);
			ut.setProcUseRel(3, 11);
			Assert::AreEqual(3, (int)ut.getVarUsedByProc(2).size());
			Assert::IsTrue(vector<int>({ 11,12,13 }) == ut.getVarUsedByProc(2));
			Assert::AreEqual(1, (int)ut.getVarUsedByProc(3).size());
			Assert::IsTrue(vector<int>({ 11 }) == ut.getVarUsedByProc(3));
			Assert::AreEqual(2, (int)ut.getProcUsesVar(11).size());
			Assert::IsTrue(vector<int>({ 2,3 }) == ut.getProcUsesVar(11));
			Assert::AreEqual(1, (int)ut.getProcUsesVar(13).size());
			Assert::IsTrue(vector<int>({ 2 }) == ut.getProcUsesVar(13));
			Assert::AreEqual(0, (int)ut.getProcUsesVar(100).size());
			Assert::IsTrue(vector<int>({}) == ut.getProcUsesVar(100));

			ut.setProcUseRelConst(2, 11);
			ut.setProcUseRelConst(2, 12);
			ut.setProcUseRelConst(2, 13);
			ut.setProcUseRelConst(3, 11);
			Assert::AreEqual(3, (int)ut.getConstUsedByProc(2).size());
			Assert::IsTrue(vector<int>({ 11,12,13 }) == ut.getConstUsedByProc(2));
			Assert::AreEqual(1, (int)ut.getConstUsedByProc(3).size());
			Assert::IsTrue(vector<int>({ 11 }) == ut.getConstUsedByProc(3));
			Assert::AreEqual(2, (int)ut.getProcUsesConst(11).size());
			Assert::IsTrue(vector<int>({ 2,3 }) == ut.getProcUsesConst(11));
			Assert::AreEqual(1, (int)ut.getProcUsesConst(13).size());
			Assert::IsTrue(vector<int>({ 2 }) == ut.getProcUsesConst(13));
			Assert::AreEqual(0, (int)ut.getProcUsesConst(100).size());
			Assert::IsTrue(vector<int>({}) == ut.getProcUsesConst(100));
		}

		TEST_METHOD(UnitTest_ModifiesTable)
		{
			ModifiesTable mt;
			mt.setStmtModifyRel(2, 4);
			mt.setStmtModifyRel(2, 5);  // this is not executed due to duplicate key
			mt.setStmtModifyRel(3, 5);
			mt.setStmtModifyRel(4, 5);

			mt.setProcModifyRel(2, 4);
			mt.setProcModifyRel(2, 5);  // this is not executed due to duplicate key
			mt.setProcModifyRel(3, 5);
			mt.setProcModifyRel(4, 5);

			Assert::IsTrue(vector<int>({ 4 }) == mt.getStmtModify(2));
			Assert::IsTrue(vector<int>({ 2 }) == mt.getModifiedByStmt(4));
			Assert::IsTrue(vector<int>({ 3,4 }) == mt.getModifiedByStmt(5));

			Assert::IsTrue(vector<int>({ 4 }) == mt.getProcModify(2));
			Assert::IsTrue(vector<int>({ 2 }) == mt.getModifiedByProc(4));
			Assert::IsTrue(vector<int>({ 3,4 }) == mt.getModifiedByProc(5));
		}
	};
}