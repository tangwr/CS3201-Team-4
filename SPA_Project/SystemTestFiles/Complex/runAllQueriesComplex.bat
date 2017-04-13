@echo off
title Running All Queries




AutoTester Complex_Source.txt Complex_Queries_Affects.txt Complex_Queries_Affects_out.xml > output.txt
AutoTester Complex_Source.txt Complex_Queries_Affects_Star.txt Complex_Queries_Affects_Star_out.xml > output.txt
AutoTester Complex_Source.txt Complex_Queries_Calls.txt Complex_Queries_Calls_out.xml > output.txt
AutoTester Complex_Source.txt Complex_Queries_Calls_Star.txt Complex_Queries_Calls_Star_out.xml > output.txt
AutoTester Complex_Source.txt Complex_Queries_Follows.txt Complex_Queries_Follows_out.xml > output.txt
AutoTester Complex_Source.txt Complex_Queries_Follows_Star.txt Complex_Queries_Follows_Star_out.xml > output.txt
AutoTester Complex_Source.txt Complex_Queries_Modifies.txt Complex_Queries_Modifies_out.xml > output.txt
AutoTester Complex_Source.txt Complex_Queries_Multiple_Clauses.txt Complex_Queries_Multiple_Clauses_out.xml > output.txt
AutoTester Complex_Source.txt Complex_Queries_Next.txt Complex_Queries_Next_out.xml > output.txt
AutoTester Complex_Source.txt Complex_Queries_Next_Star.txt Complex_Queries_Next_Star_out.xml > output.txt
AutoTester Complex_Source.txt Complex_Queries_No_Clause.txt Complex_Queries_No_Clause_out.xml > output.txt
AutoTester Complex_Source.txt Complex_Queries_Parent.txt Complex_Queries_Parent_out.xml > output.txt
AutoTester Complex_Source.txt Complex_Queries_Parent_Star.txt Complex_Queries_Parent_Star_out.xml > output.txt
AutoTester Complex_Source.txt Complex_Queries_Pattern.txt Complex_Queries_Pattern_out.xml > output.txt
AutoTester Complex_Source.txt Complex_Queries_Tuple.txt Complex_Queries_Tuple_out.xml > output.txt
AutoTester Complex_Source.txt Complex_Queries_Uses.txt Complex_Queries_Uses_out.xml > output.txt
AutoTester Complex_Source.txt Complex_Queries_With.txt Complex_Queries_With_out.xml > output.txt
AutoTester Complex_Source.txt Complex_Queries_All.txt Complex_Queries_All_out.xml > output.txt


echo.
echo Finish Running All Queries
pause