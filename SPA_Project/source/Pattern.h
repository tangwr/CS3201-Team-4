#ifndef PatternH
#define PatternH

#include <string>
#include "Clause.h"
#include "ClauseType.h"
#include "Type.h"

using namespace std;

class Pattern : public Clause {
public:
	bool isUnderScore;
	string prefix;
	Pattern();
	void setUnderScore(bool);
	void setPrefix(string);
	string getPrefix();
	bool getUnderScore();


};
#endif