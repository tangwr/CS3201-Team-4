#include "ResultTable.h"
#include <unordered_set>


ResultTable::ResultTable()
{
}

bool ResultTable::insertTuple(vector<int> tuple)
{
	if ((int)synList.size() != (int)tuple.size())
		return false;
	tupleList.push_back(tuple);
	return true;
}

bool ResultTable::setBoolean(bool b)
{
	if ((int)synList.size() != 0)
		return false;
	isBoolean = b;
	return true;

}

int ResultTable::getParamId(Parameter p)
{
	int idx = 0;
	if (synList.size() == 0)
		return -1;
	for (Parameter tmp : synList) {
		if (tmp.getParaName().compare(p.getParaName()) == 0)
			return idx;
		idx++;
	}
	return -1;
}

bool ResultTable::setSynList(vector<Parameter> list)
{
	if ((int)list.size() > 2)
		return false;
	synList = list;
	return true;
}

int ResultTable::getsize()
{
	return tupleList.size();
}

int ResultTable::getcount(Parameter p)
{
	unordered_set<int> ans;
	int id = getParamId(p);
	for (vector<int> v : tupleList)
		ans.insert(v.at(id));  // automatically skip when insert duplicate
	return (int)ans.size();
	
}

vector<Parameter> ResultTable::getSynList()
{
	return synList;
}

vector<vector<int>> ResultTable::getTupleList()
{
	return tupleList;
}
