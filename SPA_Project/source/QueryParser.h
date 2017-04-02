#ifndef QueryParser
#include <string>
#include <list>
#include <vector>
#include <unordered_map>

#include "QueryTree.h"
#include "Tokenizer.h"

using namespace std;
class QueryParser {
private:
	unordered_map<string, Parameter> varMap;
	unordered_map<string, Parameter> usedMap;
	bool isSelectBoolean = false;
	Tokenizer *tokenizer;

	void getDeclaration(QueryTree* queryTree);
	void getDeclare(QueryTree* queryTree);
	void getSelect(QueryTree* queryTree);
	void getClause(QueryTree* queryTree);
	void getSuchThat(QueryTree* queryTree);
	void getModifies(QueryTree* queryTree);
	void getUses(QueryTree* queryTree);
	void getCalls(QueryTree* queryTree);
	void getCallsStar(QueryTree* queryTree);
	void getParent(QueryTree* queryTree);
	void getParentStar(QueryTree* queryTree);
	void getFollows(QueryTree* queryTree);
	void getFollowsStar(QueryTree* queryTree);
	void getNext(QueryTree* queryTree);
	void getNextStar(QueryTree* queryTree);
	void getAffects(QueryTree* queryTree);
	void getAffectsStar(QueryTree* queryTree);
	void getPattern(QueryTree* queryTree);
	void getWith(QueryTree* queryTree);
    void match(string token, string matchRe);
	void throwError(string error);

	string getSyn(Type synType);
	string getSelectSyn();
	bool isVarNameExists(string varName);
	bool isPositiveInteger(string str);
	bool isUsedExists(string name);

public:
	QueryParser();
	~QueryParser();
	QueryTree parse(string query);

};
#endif
