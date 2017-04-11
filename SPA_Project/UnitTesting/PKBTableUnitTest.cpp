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
#include "NextTable.h"
#include "StmtLstTable.h"
#include "CombinedStmtTable.h"
#include "TableOperations.h"

#include <unordered_map>
#include <vector>
#include <iostream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
	TEST_CLASS(TestTABLE)
	{
	public:

		TEST_METHOD(UnitTest_VarTable)
		{
			VarTable vt;
			Assert::AreEqual(0,vt.getSize());

			int a = vt.insertVar("ABC");
			Assert::AreEqual(vt.insertVar("ABC"), a);
			Assert::AreEqual(0, a);
			Assert::AreEqual(1, vt.getSize());
			Assert::AreEqual((string)"ABC", vt.getVarNameById(0));
			Assert::AreEqual(0, vt.getVarIndex("ABC"));
			Assert::AreEqual(-1, vt.getVarIndex("GGG"));

			Assert::AreEqual(vt.getVarNameById(9999), (string)"");

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

            Assert::IsTrue(vt.getAllVarId() == unordered_set<int>({ 0, 1, 2, 3 }));
			vt.printContents();
		}

		TEST_METHOD(UnitTest_ProcTable)
		{
			ProcTable pt;
			Assert::AreEqual(0, pt.getSize());

			Assert::AreEqual(pt.getProcName(99), (string) "");

			int a = pt.insertProc("ABC");
			Assert::AreEqual(0, a);
			Assert::AreEqual(1, pt.getSize());
			Assert::AreEqual((string)"ABC", pt.getProcName(0));
			Assert::AreEqual(0, pt.getProcIndex("ABC"));
			Assert::AreEqual(0, pt.insertProc("ABC"));

			pt.insertProc("ABCD");
			pt.insertProc("ABCDE");
			pt.insertProc("ABCDEF");
			Assert::AreEqual(4, pt.getSize());
			Assert::AreEqual((string)"ABCDE", pt.getProcName(2));
			Assert::AreEqual(3, pt.getProcIndex("ABCDEF"));
			Assert::AreEqual(-1, pt.getProcIndex("99"));
			Assert::AreEqual(-1, pt.getProcContainStmt(999));

			Assert::AreEqual(false, pt.checkProcExistById(6));
			Assert::AreEqual(true, pt.checkProcExistById(3));
			Assert::AreEqual(false, pt.checkProcExistByName("AB"));
			Assert::AreEqual(false, pt.checkProcExistByName("ABc"));
			Assert::AreEqual(true, pt.checkProcExistByName("ABCD"));

			pt.setProcToStmtRel(1, 89);
			pt.setProcToStmtRel(3, 88);
			pt.setProcToStmtRel(1, 99);

			Assert::IsFalse(pt.setProcToStmtRel(1, 99));

			Assert::IsTrue(TableOperations::isEqualUnorderedSet(pt.getProcStmts(1), unordered_set<int>({ 89, 99 })));
			Assert::AreEqual(pt.getProcContainStmt(88), 3);
			Assert::AreEqual(pt.getProcContainStmt(99), 1);

			Assert::IsTrue(TableOperations::isEqualUnorderedSet(pt.getAllProcId(), unordered_set<int>({ 0, 1, 2, 3 })));
			pt.printContents();
		}

		TEST_METHOD(UnitTest_ConstTable)
		{
			
			ConstTable ct;
			Assert::AreEqual(0, ct.getSize());
			
			bool a = ct.insertConst(10);
			Assert::AreEqual(a, true);
			Assert::IsFalse(ct.insertConst(10));
			Assert::AreEqual(1, ct.getSize());

			
			ct.insertConst(20);
			ct.insertConst(30);
			ct.insertConst(40);

			Assert::AreEqual(4, ct.getSize());
			Assert::AreEqual(true, ct.checkConstExist(30));
			Assert::AreEqual(false, ct.checkConstExist(50));

            Assert::IsTrue(TableOperations::isEqualUnorderedSet(ct.getAllConst(), unordered_set<int>({ 10, 20, 30, 40 })));
			ct.printContents();
		}

		TEST_METHOD(UnitTest_FollowsTable)
		{
			FollowsTable ft;
			Assert::IsFalse(ft.hasFollowRel());

			ft.setStmtFollowStmtRel(1, 2);
			ft.setStmtFollowStmtRel(2, 3);
			ft.setStmtFollowStmtRel(3, 4);
			ft.insertStmtFollowStmtRel(1, 3);
			ft.insertStmtFollowStmtRel(1, 4);
			ft.insertStmtFollowStmtRel(2, 4);
			ft.insertStmtFollowStmtRel(5, 6);
			Assert::AreEqual(2, ft.getDirectFollow(1));
			Assert::AreEqual(-1, ft.getDirectFollow(9));
			Assert::AreEqual(1, ft.getDirectFollowedBy(2));
			Assert::AreEqual(-1, ft.getDirectFollowedBy(9));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 2,3,4 }), ft.getStmtFollowStarStmt(1)));
			Assert::AreEqual(2, (int)ft.getStmtFollowedByStarStmt(3).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 2,1 }), ft.getStmtFollowedByStarStmt(3)));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 6 }), ft.getStmtFollowStarStmt(5)));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>(), ft.getStmtFollowStarStmt(6)));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>(), ft.getStmtFollowedByStarStmt(1)));

			Assert::IsTrue(ft.hasFollowRel());
			Assert::IsFalse(ft.insertStmtFollowStmtRel(20, 20));

			ft.setStmtFollowStmtRel(23, 24);
			Assert::IsFalse(ft.setStmtFollowStmtRel(23, 24));
			ft.printContents();
		}

		TEST_METHOD(UnitTest_ParentsTable)
		{
			ParentsTable pt;
            Assert::IsFalse(pt.hasParentRel());
			pt.setStmtParentStmtRel(2, 3);
			pt.setStmtParentStmtRel(2, 4);
			pt.setStmtParentStmtRel(4, 5);
			pt.setStmtParentStmtRel(4, 6);
			pt.setStmtParentStmtRel(2, 7);
			pt.insertStmtParentStmtRel(2, 5);
			pt.insertStmtParentStmtRel(2, 6);
			Assert::IsFalse(pt.insertStmtParentStmtRel(2, 2));
			Assert::AreEqual(2, pt.getParent(3));
			Assert::AreEqual(4, pt.getParent(6));
			Assert::AreEqual(3, (int)pt.getStmtChildrenStmt(2).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 3,4,7 }), pt.getStmtChildrenStmt(2)));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 5,6 }), pt.getStmtChildrenStmt(4)));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>(), pt.getStmtChildrenStmt(5)));
			Assert::AreEqual(2, (int)pt.getStmtParentStarStmt(5).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 4,2}), pt.getStmtParentStarStmt(5)));
			Assert::AreEqual(5, (int)pt.getStmtChildrenStarStmt(2).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 3,4,7,5,6 }), pt.getStmtChildrenStarStmt(2)));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 5,6 }), pt.getStmtChildrenStarStmt(4)));
            Assert::IsTrue(pt.hasParentRel());
			Assert::IsFalse(pt.setStmtParentStmtRel(10, 3));
			Assert::AreEqual(-1, pt.getParent(109));
			pt.printContents();
		}
		
        TEST_METHOD(UnitTest_IfTable)
		{
			IfTable it;
			Assert::AreEqual(0, it.getSize());
			it.setVarToIfStmt(2, 5);
			it.setVarToIfStmt(3, 6);
			Assert::AreEqual(5, it.getCtrlVarInIfStmt(2));
			Assert::AreEqual(-1, it.getCtrlVarInIfStmt(9));
			Assert::AreEqual(2, it.getSize());
			Assert::IsFalse(it.setVarToIfStmt(2, 9));
			Assert::IsFalse(it.isStmtInTable(9));
			Assert::IsTrue(it.isStmtInTable(2));

			it.setVarToIfStmt(7, 5);
			it.setVarToIfStmt(9, 5);
			unordered_set<int> ifStmtSetWithCtrlVarFive = { 2, 9, 7 };
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(it.getStmtWithCtrlVar(5), ifStmtSetWithCtrlVarFive));

			unordered_set<int> allIfStmtId = { 2, 3, 7, 9 };
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(it.getAllIfId(), allIfStmtId));
			it.printContents();
		}
		
        TEST_METHOD(UnitTest_WhileTable)
		{
			WhileTable wt;
			Assert::AreEqual(0, wt.getSize());
			wt.setVarToWhileStmt(2, 5);
			wt.setVarToWhileStmt(3, 6);
			Assert::AreEqual(5, wt.getCtrlVarInWhileStmt(2));
			Assert::AreEqual(2, wt.getSize());
			Assert::AreEqual(wt.getCtrlVarInWhileStmt(9), -1);
			Assert::IsFalse(wt.setVarToWhileStmt(2, 7));
			Assert::IsFalse(wt.isStmtInTable(88));
			Assert::IsTrue(wt.isStmtInTable(2));

			wt.setVarToWhileStmt(7, 5);
			wt.setVarToWhileStmt(9, 5);
			unordered_set<int> whileStmtSetWithCtrlVarFive = { 2, 9, 7 };
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(wt.getStmtWithCtrlVar(5), whileStmtSetWithCtrlVarFive));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(wt.getStmtWithCtrlVar(7), unordered_set<int>()));

			unordered_set<int> allWhileStmtId = { 2, 3, 7, 9 };
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(wt.getAllStmtId(), allWhileStmtId));
			wt.printContents();
		}
		
        TEST_METHOD(UnitTest_AssignTable)
		{
			AssignTable at;
			Assert::AreEqual(0, at.getSize());
			at.setExpToAssignStmt(2, "a+b");
			at.setExpToAssignStmt(3, "c*d");
			Assert::IsFalse(at.setExpToAssignStmt(2, "+2 3"));
			Assert::IsTrue("a+b" == at.getExpInAssignStmt(2));
			Assert::IsTrue("" == at.getExpInAssignStmt(7));
			Assert::AreEqual(2, at.getSize());
			Assert::IsTrue(at.isStmtInTable(2));
			Assert::IsFalse(at.isStmtInTable(7));

			at.setVarToAssignStmt(2, 5);
			at.setVarToAssignStmt(3, 5);
			Assert::IsFalse(at.setVarToAssignStmt(2, 8));


			Assert::AreEqual(at.getAssignedVarInAssignStmt(2), 5);
			Assert::AreEqual(at.getAssignedVarInAssignStmt(3), 5);
			Assert::AreEqual(at.getAssignedVarInAssignStmt(22), -1);

			at.setVarExpToAssignStmt(60, "++xyz", 99);

			Assert::AreEqual(at.getAssignedVarInAssignStmt(99), 60);
			Assert::IsTrue("++xyz" == at.getExpInAssignStmt(99));

			unordered_set<int> allAssignStmtWithCtrlVarFive = { 2, 3 };
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(at.getStmtWithCtrlVar(5), allAssignStmtWithCtrlVarFive));

			unordered_set<int> allAssignStmtSet = { 99, 2, 3 };
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(at.getAllStmtId(), allAssignStmtSet));
			at.printContents();

		}
		
        TEST_METHOD(UnitTest_CallTable)
		{
			CallTable ct;

			//statement call proc
			Assert::IsTrue(ct.getSize() == 0);
			ct.setStmtCallProcRel(1, 5);
			ct.setStmtCallProcRel(2, 5);
			ct.setStmtCallProcRel(3, 2);
			Assert::AreEqual(3, ct.getSize());
			Assert::IsTrue(ct.isStmtInTable(3));
			Assert::IsFalse(ct.isStmtInTable(4));
			Assert::IsFalse(ct.setStmtCallProcRel(3, 2));
			Assert::AreEqual(ct.getProcCalledByStmt(1), 5);
			Assert::AreEqual(ct.getProcCalledByStmt(3), 2);
			Assert::AreEqual(ct.getProcCalledByStmt(9), -1);

			unordered_set<int> allCallStmtId = { 2, 1, 3 };
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(ct.getAllCallId(), allCallStmtId));

			unordered_set<int> callerStmtSetOfProcFive = { 1, 2 };
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(ct.getCallerStmtCallProc(5), callerStmtSetOfProcFive));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(ct.getCallerStmtCallProc(100), unordered_set<int>()));

			//proc call proc
			ct.setProcCallProcRel(9, 22);
			ct.setProcCallProcRel(9, 24);
			ct.setProcCallProcRel(7, 22);
			ct.setProcCallProcRel(6, 22);
			ct.setProcCallProcRel(22, 26);
			ct.setProcCallProcRel(24, 26);
			ct.setProcCallProcRel(26, 32);
			Assert::IsFalse(ct.setProcCallProcRel(24, 26));
			ct.insertProcCallStarProcRel(9, 26);
			ct.insertProcCallStarProcRel(9, 32);

			Assert::IsTrue(TableOperations::isEqualUnorderedSet(ct.getCallerProcCallProc(22), unordered_set<int>({ 7, 9, 6 })));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(ct.getCallerProcCallProc(1000), unordered_set<int>()));

			unordered_set<int> procCalledByNine = { 22,24 };
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(ct.getProcCalledByProc(9), procCalledByNine));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(ct.getProcCalledByProc(100), unordered_set<int>()));

			unordered_set<int> callStarOfNine = { 22, 24, 26, 32 };
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(ct.getProcCalledByStarProc(9), callStarOfNine));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(ct.getProcCalledByStarProc(100), unordered_set<int>()));

			ct.insertProcCallStarProcRel(25, 26);
			Assert::IsFalse(ct.insertProcCallStarProcRel(25, 26));
			ct.printContents();
		}
		
        TEST_METHOD(UnitTest_UsesTable)
		{
			UsesTable ut;
			ut.setStmtUseVarRel(2, 11);
			ut.setStmtUseVarRel(2, 12);
			ut.setStmtUseVarRel(2, 13);
			ut.insertStmtUseVarRel(3, 11);
			Assert::IsTrue(ut.checkStmtExist(3));
			Assert::IsFalse(ut.checkStmtExist(7));
			Assert::IsTrue(ut.checkStmtVarRelExist(2, 11));
			Assert::IsFalse(ut.checkStmtVarRelExist(3, 12));
			Assert::AreEqual(3, (int)ut.getVarUsedByStmt(2).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 11,12,13 }), ut.getVarUsedByStmt(2)));
			Assert::AreEqual(1, (int)ut.getVarUsedByStmt(3).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 11 }), ut.getVarUsedByStmt(3)));
			Assert::AreEqual(2, (int)ut.getStmtUseVar(11).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 2,3 }), ut.getStmtUseVar(11)));
			Assert::AreEqual(1, (int)ut.getStmtUseVar(13).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 2 }), ut.getStmtUseVar(13)));
			Assert::AreEqual(0, (int)ut.getStmtUseVar(100).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({}), ut.getStmtUseVar(100)));

			ut.setStmtUseConstRel(2, 11);
			ut.setStmtUseConstRel(2, 12);
			ut.setStmtUseConstRel(2, 13);
			ut.insertStmtUseConstRel(3, 11);
			Assert::AreEqual(3, (int)ut.getConstUsedByStmt(2).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 11,12,13 }), ut.getConstUsedByStmt(2)));
			Assert::AreEqual(1, (int)ut.getConstUsedByStmt(3).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 11 }), ut.getConstUsedByStmt(3)));
			Assert::AreEqual(2, (int)ut.getStmtUseConst(11).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 2,3 }), ut.getStmtUseConst(11)));
			Assert::AreEqual(1, (int)ut.getStmtUseConst(13).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 2 }), ut.getStmtUseConst(13)));
			Assert::AreEqual(0, (int)ut.getStmtUseConst(100).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({}), ut.getStmtUseConst(100)));

			ut.setProcUseVarRel(2, 11);
			ut.setProcUseVarRel(2, 12);
			ut.setProcUseVarRel(2, 13);
			ut.insertProcUseVarRel(3, 11);
			Assert::AreEqual(3, (int)ut.getVarUsedByProc(2).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 11,12,13 }), ut.getVarUsedByProc(2)));
			Assert::AreEqual(1, (int)ut.getVarUsedByProc(3).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 11 }), ut.getVarUsedByProc(3)));
			Assert::AreEqual(2, (int)ut.getProcUseVar(11).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 2,3 }), ut.getProcUseVar(11)));
			Assert::AreEqual(1, (int)ut.getProcUseVar(13).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 2 }), ut.getProcUseVar(13)));
			Assert::AreEqual(0, (int)ut.getProcUseVar(100).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({}), ut.getProcUseVar(100)));

			ut.setProcUseConstRel(2, 11);
			ut.setProcUseConstRel(2, 12);
			ut.setProcUseConstRel(2, 13);
			ut.insertProcUseConstRel(4, 11);
			Assert::IsFalse(ut.insertProcUseConstRel(4, 11));
			Assert::AreEqual(3, (int)ut.getConstUsedByProc(2).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 11,12,13 }), ut.getConstUsedByProc(2)));
			Assert::AreEqual(1, (int)ut.getConstUsedByProc(4).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 11 }), ut.getConstUsedByProc(4)));
			Assert::AreEqual(2, (int)ut.getProcUseConst(11).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 2,4 }), ut.getProcUseConst(11)));
			Assert::AreEqual(1, (int)ut.getProcUseConst(13).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 2 }), ut.getProcUseConst(13)));
			Assert::AreEqual(0, (int)ut.getProcUseConst(100).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({}), ut.getProcUseConst(100)));

			Assert::IsTrue(TableOperations::isEqualUnorderedSet(ut.getAllStmtId(), unordered_set<int>({ 2,3 })));

			Assert::IsFalse(ut.setProcUseConstRel(2, 11));
			Assert::IsFalse(ut.insertStmtUseConstRel(2, 11));
			Assert::IsFalse(ut.setStmtUseConstRel(2, 11));

			ut.insertProcUseVarRel(22, 25);
			Assert::IsTrue(ut.insertProcUseVarRel(22, 27));
			Assert::IsFalse(ut.insertProcUseVarRel(22, 27));

			ut.insertProcUseConstRel(22, 25);
			Assert::IsTrue(ut.insertProcUseConstRel(22, 27));

			ut.insertStmtUseConstRel(22, 25);
			Assert::IsTrue(ut.insertStmtUseConstRel(22, 27));

			ut.setProcUseVarRel(78, 36);
			Assert::IsFalse(ut.setProcUseVarRel(78, 36));

			ut.insertStmtUseVarRel(22, 25);
			Assert::IsTrue(ut.insertStmtUseVarRel(22, 27));
			Assert::IsFalse(ut.insertStmtUseVarRel(22, 27));

			ut.setStmtUseVarRel(78, 36);
			Assert::IsFalse(ut.setStmtUseVarRel(78, 36));

			ut.printContents();

		}

		TEST_METHOD(UnitTest_ModifiesTable)
		{
			ModifiesTable mt;
			mt.setStmtModifyVarRel(2, 4);
			mt.setStmtModifyVarRel(2, 5);
			mt.setStmtModifyVarRel(3, 5);
			mt.insertStmtModifyVarRel(4, 5);

			mt.setProcModifyVarRel(2, 4);
			mt.setProcModifyVarRel(2, 5);
			mt.setProcModifyVarRel(3, 5);
			mt.insertProcModifyVarRel(4, 5);

			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 4 }), mt.getVarModifiedInStmt(2)));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 2 }), mt.getStmtModifyVar(4)));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 3,4 }), mt.getStmtModifyVar(5)));

			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 4 }), mt.getVarModifiedInProc(2)));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 2 }), mt.getProcModifyVar(4)));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 3,4 }), mt.getProcModifyVar(5)));

			Assert::IsFalse(mt.checkStmtVarRelExist(2, 99));
			Assert::IsFalse(mt.checkStmtVarRelExist(2, 5));
			Assert::IsTrue(mt.checkStmtVarRelExist(2, 4));
			Assert::IsTrue(mt.checkStmtExist(3));
			Assert::IsFalse(mt.checkStmtExist(99));

			Assert::IsTrue(TableOperations::isEqualUnorderedSet(mt.getAllStmt(), unordered_set<int>({ 2, 3, 4 })));

			mt.insertStmtModifyVarRel(25, 26);
			Assert::IsFalse(mt.insertStmtModifyVarRel(25, 26));
			Assert::IsTrue(mt.insertStmtModifyVarRel(25, 27));

			mt.insertProcModifyVarRel(25, 26);
			Assert::IsFalse(mt.insertProcModifyVarRel(25, 26));
			Assert::IsTrue(mt.insertProcModifyVarRel(25, 27));
			mt.printContents();
		}
	    
        TEST_METHOD(UnitTest_NextTable) {
			NextTable nt;
			nt.setStmtNextStmtRel(3, 5);
			nt.setStmtNextStmtRel(3, 6);
			nt.setStmtNextStmtRel(1, 5);
			nt.setStmtNextStmtRel(10, 5);
			Assert::IsFalse(nt.setStmtNextStmtRel(3, 5));
			Assert::AreEqual(4, nt.getSize());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(nt.getNextStmt(22), unordered_set<int>()));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(nt.getPreviousStmt(22), unordered_set<int>()));

			unordered_set<int> previousOfFive = { 10, 1, 3 };
			unordered_set<int> nextOfThree = { 5, 6 };
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(nt.getPreviousStmt(5), previousOfFive));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(nt.getNextStmt(3), nextOfThree));
			nt.printContents();
        }

        TEST_METHOD(UnitTest_StmtLstTable) {
            StmtLstTable slt;
            slt.setProcStmtLstContainsStmtRel(5, 10);
            slt.setProcStmtLstContainsStmtRel(5, 20);
            slt.setProcStmtLstContainsStmtRel(4, 8);
            slt.setProcStmtLstContainsStmtRel(3, 6);
            slt.setProcStmtLstContainsStmtRel(2, 4);
			Assert::IsFalse(slt.setProcStmtLstContainsStmtRel(2, 4));

            slt.setContainerStmtStmtLstContainsStmtRel(1, 10);
            slt.setContainerStmtStmtLstContainsStmtRel(2, 11);
            slt.setContainerStmtStmtLstContainsStmtRel(2, 20);
            slt.setContainerStmtStmtLstContainsStmtRel(3, 12);
            slt.setContainerStmtStmtLstContainsStmtRel(4, 13);
			Assert::IsFalse(slt.setContainerStmtStmtLstContainsStmtRel(4, 13));

            vector<int> stmtLstInProcFive = { 10, 20 };
            Assert::IsTrue(stmtLstInProcFive == slt.getStmtLstContainedInProc(5));
            vector<int> stmtLstInContainerStmtTwo = { 11, 20 };
            Assert::IsTrue(stmtLstInContainerStmtTwo == slt.getStmtlstContainedInContainerStmt(2));

            unordered_set<int> allFirstStmtOfStmtLsts = { 4, 8, 6, 10, 11, 13, 12, 20 };
            Assert::IsTrue(TableOperations::isEqualUnorderedSet(slt.getAllStmtLst(), allFirstStmtOfStmtLsts));
			slt.printContents();
        }

		TEST_METHOD(UnitTest_CombinedStmtTable) {
			CombinedStmtTable cst;
			
			cst.insertStmt(1);
			cst.insertStmt(9);
			cst.insertStmt(2);

			Assert::IsTrue(cst.getSize() == 3);
			Assert::IsTrue(cst.getAllStmtId() == unordered_set<int>({ 1, 2, 9 }));
		}
    };
}