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
#include "TableOperations.h"

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

            Assert::IsTrue(vt.getAllVarId() == vector<int>({ 0, 1, 2, 3 }));
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

            vt.setProcToStmtRel(1, 89);
            vt.setProcToStmtRel(3, 88);
            vt.setProcToStmtRel(1, 99);

            Assert::IsTrue(TableOperations::isEqualUnorderedSet(vt.getProcStmts(1), unordered_set<int>({89, 99})));
            Assert::AreEqual(vt.getProcContainStmt(88), 3);
            Assert::AreEqual(vt.getProcContainStmt(99), 1);

            Assert::IsTrue(TableOperations::isEqualUnorderedSet(vt.getAllProcId(), unordered_set<int>({0, 1, 2, 3})));
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

            Assert::IsTrue(ct.getAllConst() == vector<int>({ 10, 20, 30, 40 }));
            Assert::IsTrue(ct.getAllConstId() == vector<int>({ 0, 1, 2, 3 }));
		}

		TEST_METHOD(UnitTest_FollowsTable)
		{
			/*
				Sample: 1,2,3,4-while{5,6}
			*/
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
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({2,3,4}), ft.getStmtFollowStarStmt(1)));
			Assert::AreEqual(2, (int)ft.getStmtFollowedByStarStmt(3).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 2,1 }), ft.getStmtFollowedByStarStmt(3)));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 6 }), ft.getStmtFollowStarStmt(5)));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>(), ft.getStmtFollowStarStmt(6)));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>(), ft.getStmtFollowedByStarStmt(1)));
		}

		TEST_METHOD(UnitTest_ParentsTable)
		{
			/*
				Sample 1, 2_while{3,4-if{5,6}, 7} 
			*/
			ParentsTable pt;
            Assert::IsFalse(pt.hasParentRel());
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
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 3,4,7 }), pt.getStmtChildrenStmt(2)));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 5,6 }), pt.getStmtChildrenStmt(4)));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>(), pt.getStmtChildrenStmt(5)));
			Assert::AreEqual(2, (int)pt.getStmtParentStarStmt(5).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 4,2}), pt.getStmtParentStarStmt(5)));
			Assert::AreEqual(5, (int)pt.getStmtChildrenStarStmt(2).size());
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 3,4,7,5,6 }), pt.getStmtChildrenStarStmt(2)));
			Assert::IsTrue(TableOperations::isEqualUnorderedSet(unordered_set<int>({ 5,6 }), pt.getStmtChildrenStarStmt(4)));
            Assert::IsTrue(pt.hasParentRel());
		}
		
        TEST_METHOD(UnitTest_IfTable)
		{
			IfTable it;
			Assert::AreEqual(0, it.getSize());
			it.setVarToIfStmt(2, 5);
			it.setVarToIfStmt(3, 6);
			Assert::AreEqual(5, it.getCtrlVarInIfStmt(2));
			Assert::AreEqual(2, it.getSize());

            it.setVarToIfStmt(7, 5);
            it.setVarToIfStmt(9, 5);
            unordered_set<int> ifStmtSetWithCtrlVarFive = { 2, 9, 7 };
            Assert::IsTrue(TableOperations::isEqualUnorderedSet(it.getStmtWithCtrlVar(5), ifStmtSetWithCtrlVarFive));

            unordered_set<int> allIfStmtId = { 2, 3, 7, 9 };
            Assert::IsTrue(TableOperations::isEqualUnorderedSet(it.getAllIfId(), allIfStmtId));
		}
		
        TEST_METHOD(UnitTest_WhileTable)
		{
			WhileTable wt;
			Assert::AreEqual(0, wt.getSize());
			wt.setVarToWhileStmt(2, 5);
			wt.setVarToWhileStmt(3, 6);
			Assert::AreEqual(5, wt.getCtrlVarInWhileStmt(2));
			Assert::AreEqual(2, wt.getSize());

            wt.setVarToWhileStmt(7, 5);
            wt.setVarToWhileStmt(9, 5);
            unordered_set<int> whileStmtSetWithCtrlVarFive = { 2, 9, 7 };
            Assert::IsTrue(TableOperations::isEqualUnorderedSet(wt.getStmtWithCtrlVar(5), whileStmtSetWithCtrlVarFive));

            unordered_set<int> allWhileStmtId = { 2, 3, 7, 9 };
            Assert::IsTrue(TableOperations::isEqualUnorderedSet(wt.getAllStmtId(), allWhileStmtId));
		}
		
        TEST_METHOD(UnitTest_AssignTable)
		{
			AssignTable at;
			Assert::AreEqual(0, at.getSize());
			at.setExpToAssignStmt(2, "a+b");
			at.setExpToAssignStmt(3, "c*d");
			Assert::IsTrue("a+b" == at.getExpInAssignStmt(2));
			Assert::AreEqual(2, at.getSize());

            at.setVarToAssignStmt(2, 5);
            at.setVarToAssignStmt(3, 5);
            
            
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


		}
		
        TEST_METHOD(UnitTest_CallTable)
		{
			CallTable ct;
			//Assert::AreEqual(0, ct.getSize());
			//ct.setStmtCallProc(2, 5);
			//ct.setStmtCallProc(3, 6);
			//Assert::AreEqual(5, ct.getCallProc(2));
			//Assert::AreEqual(2, ct.getSize());

            //statement call proc
            ct.setStmtCallProcRel(1, 5);
            ct.setStmtCallProcRel(2, 5);
            ct.setStmtCallProcRel(3, 2);
            Assert::AreEqual(ct.getProcCalledByStmt(1), 5);
            Assert::AreEqual(ct.getProcCalledByStmt(3), 2);

            unordered_set<int> allCallStmtId = { 2, 1, 3 };
            Assert::IsTrue(TableOperations::isEqualUnorderedSet(ct.getAllCallId(), allCallStmtId));

            unordered_set<int> callerStmtSetOfProcFive = { 1, 2 };
            Assert::IsTrue(TableOperations::isEqualUnorderedSet(ct.getCallerStmtCallProc(5), callerStmtSetOfProcFive));

            //proc call proc
            ct.setProcCallProcRel(9, 22);
            ct.setProcCallProcRel(9, 24);
            ct.setProcCallProcRel(7, 22);
            ct.setProcCallProcRel(6, 22);
            ct.setProcCallProcRel(22, 26);
            ct.setProcCallProcRel(24, 26);
            ct.setProcCallProcRel(26, 32);
            ct.insertProcCallStarProcRel(9, 26);
            ct.insertProcCallStarProcRel(9, 32);

            unordered_set<int> procCalledByNine = { 22,24 };
            Assert::IsTrue(TableOperations::isEqualUnorderedSet(ct.getProcCalledByProc(9), procCalledByNine));

            unordered_set<int> callStarOfNine = { 22, 24, 26, 32 };
            Assert::IsTrue(TableOperations::isEqualUnorderedSet(ct.getProcCalledByStarProc(9), callStarOfNine));
		}
		
        TEST_METHOD(UnitTest_UsesTable)
		{
			UsesTable ut;
			ut.setStmtUseVarRel(2, 11);
			ut.setStmtUseVarRel(2, 12);
			ut.setStmtUseVarRel(2, 13);
			ut.insertStmtUseVarRel(3, 11);
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
		}

		TEST_METHOD(UnitTest_ModifiesTable)
		{
			ModifiesTable mt;
			mt.setStmtModifyVarRel(2, 4);
			mt.setStmtModifyVarRel(2, 5);  // this is not executed due to duplicate key
			mt.setStmtModifyVarRel(3, 5);
			mt.insertStmtModifyVarRel(4, 5);

			mt.setProcModifyVarRel(2, 4);
			mt.setProcModifyVarRel(2, 5);  // this is not executed due to duplicate key
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
		}
	    
        TEST_METHOD(UnitTest_NextTable) {
            NextTable nt;
            nt.setStmtNextStmtRel(3, 5);
            nt.setStmtNextStmtRel(3, 6);
            nt.setStmtNextStmtRel(1, 5);
            nt.setStmtNextStmtRel(10, 5);

            unordered_set<int> previousOfFive = { 10, 1, 3 };
            unordered_set<int> nextOfThree = { 5, 6 };
            Assert::IsTrue(TableOperations::isEqualUnorderedSet(nt.getPreviousStmt(5), previousOfFive));
            Assert::IsTrue(TableOperations::isEqualUnorderedSet(nt.getNextStmt(3), nextOfThree));
        }

        TEST_METHOD(UnitTest_StmtLstTable) {
            StmtLstTable slt;
            slt.setProcStmtLstContainsStmtRel(5, 10);
            slt.setProcStmtLstContainsStmtRel(5, 20);
            slt.setProcStmtLstContainsStmtRel(4, 8);
            slt.setProcStmtLstContainsStmtRel(3, 6);
            slt.setProcStmtLstContainsStmtRel(2, 4);

            slt.setContainerStmtStmtLstContainsStmtRel(1, 10);
            slt.setContainerStmtStmtLstContainsStmtRel(2, 11);
            slt.setContainerStmtStmtLstContainsStmtRel(2, 20);
            slt.setContainerStmtStmtLstContainsStmtRel(3, 12);
            slt.setContainerStmtStmtLstContainsStmtRel(4, 13);

            vector<int> stmtLstInProcFive = { 10, 20 };
            Assert::IsTrue(stmtLstInProcFive == slt.getStmtLstContainedInProc(5));
            vector<int> stmtLstInContainerStmtTwo = { 11, 20 };
            Assert::IsTrue(stmtLstInContainerStmtTwo == slt.getStmtlstContainedInContainerStmt(2));

            unordered_set<int> allFirstStmtOfStmtLsts = { 4, 8, 6, 10, 11, 13, 12, 20 };
            Assert::IsTrue(TableOperations::isEqualUnorderedSet(slt.getAllStmtLst(), allFirstStmtOfStmtLsts));
        }
    };
}