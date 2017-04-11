#pragma once
#ifndef ParameterH
#define ParameterH

#include <string>
#include "Type.h"

using namespace std;

class Parameter {
public:
	Parameter();
	Parameter(string, Type);
	/**
	* get the name of the Parameter 
	*
	* @return the Parameter's name
	*/
	string getParaName();
	/**
	* get the type of the Parameter
	*
	* @return the Parameter's type
	*/
	Type getParaType();
	/**
	* set the Parameter's name
	*
	* @param the string of the name
	*/
	void setParaName(string);
	/**
	* if has call.procName then 
	* the boolean true will be passed in
	* the method
	*
	* @param the boolean value
	*/
	void setAttributeProc(bool);
	/**
	* set the Parameter's type by given type 
	*
	* @param the Type of the Parameter
	*/
	void setParaType(Type);
	/**
	* if it is a synonym, the boolean true
	* will be returned
	*
	* @return the boolean value
	*/
	bool isSynonym();
	/**
	* if the Parameter is the same as the passed
	* Parameter, the boolean true will be returned
	*
	* @return the boolean value
	*/
	bool isSame(Parameter);
	/**
	* if the Parameter is an Interger, the boolean true 
	* will be returned
	*
	* @return the boolean value
	*/
	bool isInteger();
	/**
	* if the Parameter is a string, the boolean true
	* will be returned
	*
	* @return the boolean value
	*/
	bool isString();
	/**
	* if the attribute is a procedure, the boolean true
	* will be returned
	*
	* @return the boolean value
	*/
	bool getAttributeProc();

private:
	string paraName;
	Type paraType;
	bool isSyn;
	bool isInt;
	bool isStr;
	bool isAttributeProc;
};
#endif
