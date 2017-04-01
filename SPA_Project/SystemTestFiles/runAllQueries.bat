@echo off
title Running All Queries

AutoTester SIMPLE-Source.txt Queries_Follows.txt out_Follows.xml
AutoTester SIMPLE-Source.txt Queries_Follows_Star.txt out_Follows_Star.xml
AutoTester SIMPLE-Source.txt Queries_Parent.txt out_Parent.xml
AutoTester SIMPLE-Source.txt Queries_Parent_Star.txt out_Parent_Star.xml
AutoTester SIMPLE-Source.txt Queries_Calls.txt out_Calls.xml
AutoTester SIMPLE-Source.txt Queries_Calls_Star.txt out_Calls_Star.xml
AutoTester SIMPLE-Source.txt Queries_Modifies.txt out_Modifies.xml
AutoTester SIMPLE-Source.txt Queries_Uses.txt out_Uses.xml
AutoTester SIMPLE-Source.txt Queries_Pattern.txt out_Pattern.xml
AutoTester SIMPLE-Source.txt Query_With.txt out_With.xml
AutoTester SIMPLE-Source.txt Queries_Next.txt out_Next.xml
AutoTester SIMPLE-Source.txt Queries_Next_Star.txt out_Next_Star.xml
AutoTester SIMPLE-Source.txt Queries_One_Common_Synonym.txt out_One_Common_Synonym.xml
AutoTester SIMPLE-Source.txt Queries_Two_Synonyms_NoShare.txt out_Two_Synonyms_NoShare.xml
AutoTester SIMPLE-Source.txt Queries_Many_Common_Synonyms.txt out_Many_Common_Synonym.xml
AutoTester SIMPLE-Source.txt Queries_Tuple.txt out_Tuple.xml

AutoTester Sample-Source.txt Sample-Queries.txt out_Sample.xml

echo.
echo Finish Running All Queries
pause